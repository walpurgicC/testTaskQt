#ifndef PARSERINTERFACE_H
#define PARSERINTERFACE_H

#include <QDateTime>
#include <QFile>
#include <QHash>
#include <QMap>
#include <QString>

class ParserInterface
{
  public:
    using parsedData_t = QHash<QString, QMap<QTime, int>>;
    virtual parsedData_t parseFile(QFile &file) = 0;
    virtual ~ParserInterface() = default;
};

#endif // PARSERINTERFACE_H
