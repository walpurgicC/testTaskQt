#include <QFileInfo>
#include <QScopedPointer>
#include <QDebug>
#include "csvparser.h"
#include "carhandler.h"

int main(int argc, char *argv[])
{
  constexpr auto CSV_EXTENSION  = "csv";

  if (argc == 2)
  {
    QFile logFile(argv[1]);
    if (logFile.exists() && logFile.size() != 0)
    {
      QFileInfo logFileInfo(logFile.fileName());
      QString   fileExtension = logFileInfo.suffix();

      QScopedPointer<ParserInterface> parser;
      if (fileExtension == CSV_EXTENSION)
      {
        parser.reset(new CsvParser);
      }
      // cars is a QHash<QString, QMap<QTime, int>>
      // where QString is an id of certain car
      // QMap contains time-speed records from logfile of certain id
      auto cars { parser->parseFile(logFile) };

      QFile      outputFile("output.txt");
      CarHandler carHandler;

      if (outputFile.open(QFile::WriteOnly))
      {
        QTextStream out(&outputFile);
        out.setRealNumberNotation(QTextStream::FixedNotation);
        out.setRealNumberPrecision(1);
        out << "-----" << Qt::endl;

        // iterating over cars collection
        for (auto car = cars.constKeyValueBegin(); car != cars.constKeyValueEnd() ; ++car)
        {
          // calculating runtime and downtime of current car
          // and printing data to output file
          carHandler.handleCarData(*car)
                    .printCarData(out);
        }
        outputFile.close();
      }
      else
      {
        qCritical() << outputFile.errorString();
      }
    }
  }
  else if (argc == 1)
  {
    qCritical() << QString("No input file received.");
  }
  else
  {
    qCritical() << QString("Wrong program parameters.");
  }

  return 0;
}
