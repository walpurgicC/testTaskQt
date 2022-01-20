#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <parserinterface.h>

class CsvParser : public ParserInterface
{
  public:
    parsedData_t parseFile(QFile &file) override;
};

#endif // CSVPARSER_H
