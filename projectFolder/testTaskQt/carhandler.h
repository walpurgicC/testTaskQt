#ifndef CARHANDLER_H
#define CARHANDLER_H

#include <QString>
#include <QTextStream>
#include <QTime>
#include <QPair>

class CarHandler
{
  public:
    using carData_t = std::pair<const QString &, const QMap<QTime, int> &>;

    CarHandler();

    CarHandler &handleCarData(const carData_t &car);
    void printCarData(QTextStream &out);

  private:
    QString id;
    QTime runtime;
    QTime downtime;
};

#endif // CARHANDLER_H
