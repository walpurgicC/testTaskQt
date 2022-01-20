#include "csvparser.h"
#include <QDebug>

CsvParser::parsedData_t CsvParser::parseFile(QFile &file)
{
  parsedData_t cars;

  if (file.open(QFile::ReadOnly))
  {
    while (!file.atEnd())
    {
      QString   line   { file.readLine() };
      auto      parsed { line.split(',') };

      QTime     time   { QDateTime::fromString(parsed[0], "\"yyyy-MM-dd HH:mm:ss\"").time() };
      QString   id     { parsed[1] };
      int       speed  { parsed[2].toInt() };

      cars[id].insert(time, speed);
    }
    file.close();
  }
  else
  {
    qCritical() << file.errorString();
  }
  return cars;
}
