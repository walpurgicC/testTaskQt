#include "carhandler.h"

CarHandler::CarHandler() :
  id       { },
  runtime  { 0, 0 },
  downtime { 0, 0 }
{ }

CarHandler &CarHandler::handleCarData(const carData_t &car)
{
  constexpr int TWO_MIN_IN_SEC = 120;

  id       = car.first;
  runtime  = { 0, 0 };
  downtime = { 0, 0 };

  // prevlog stores previous logged time
  QTime prevlog { 0, 0 };
  // isMoving indecates if car had positive speed number at prevlog
  bool isMoving { false };
  for (auto it = car.second.cbegin(); it != car.second.cend(); ++it)
  {
    if (isMoving)
    {
      int secsInMotion = prevlog.secsTo(it.key());
      if (secsInMotion <= TWO_MIN_IN_SEC)
      {
        runtime = runtime.addSecs(secsInMotion);
      }
    }
    prevlog = it.key();
    isMoving = it.value() > 0 ? true : false;
  }

  auto downtimeSecs { runtime.secsTo({ 23, 59, 59 }) };
  downtime = downtime.addSecs(downtimeSecs);

  return *this;
}

void CarHandler::printCarData(QTextStream &out)
{
  double run  = runtime.hour()  + runtime.minute() / 60.0  + runtime.second() / 3600.0;
  double down = downtime.hour() + downtime.minute() / 60.0 + downtime.second() / 3600.0;

  out << "id: " << id << Qt::endl
      << QString::fromUtf8("время в пути: ")  << run  << "h" << Qt::endl
      << QString::fromUtf8("время стоянки: ") << down << "h" << Qt::endl
      << "-----" << Qt::endl;
}
