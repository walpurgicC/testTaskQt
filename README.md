# testTaskQt
## Постановка задачи
Разработать консольное приложение для подсчета времени в пути и времени стоянки транспортного
средства за данный промежуток времени на основе информации, полученной от устройства мониторинга.
Стоянкой считается любой период не менее 2 минут, в течение которого выполняется одно из условий:
- от устройства не получено никаких данных;
- от устройства получены данные о нулевой скорости.
## Исходные данные
Лог в формате **.csv**, который содержит данные о передвижении различных транспортных средств в формате:
***DateTime, ID, Speed*** (сепаратор – запятая) за сутки, где:
- ***DateTime*** - метка времени;
- ***ID*** - идентификатор устройства;
- ***Speed*** - скорость транспортного средства.
## Формат вывода
\-\-\-\-\-  
_id: 3907574550806754  
время в пути: 7.3h  
время стоянки: 16.6h_  
\-\-\-\-\-  
_id: 3907574550780629  
время в пути: 5.7h  
время стоянки: 18.3h_  
\-\-\-\-\-  
  
Вывод осуществляется в файл формата **.txt**
## Инструкция по сборке и запуску программы
Необходимо загрузить файлы репозитория и открыть проектный файл **testTaskQt.pro** с помощью _QtCreator_.
После успешного открытия проекта необходимо выполнить его сборку средствами IDE, и в ***ProjectFolder*** появится build-директория.
Для запуска программы используйте терминал, либо укажите путь до входного **.csv** файла в параметрах командной строки проекта.
Если указан относительный путь, то есть только имя файла, поместите файл в build-директорию, либо укажите абсолютный путь.
Результат работы программы выводится в **output.txt**, который создается в build-директории.

## Версии ПО
- Qt 5.15.2;
- Microsoft Visual C++ Compiler 16.8.30804.86 (x86).

## Детали реализации
### Анализ входных данных
После анализа предоставленного log-файла было выявлено, что записи хранятся неупорядоченно и могут дублироваться.
Для построение эффективного алгоритма, имея ввиду вышесказанное, необходимо выбрать подходящую модель хранения данных.
### Хранение данных
Данные хранятся в _QHash_, где ключ это **id**, а значение - _QMap_, содержащий в себе все пары **Время-Скорость** для **id**.
QHash был выбран потому, что порядок **id** не имеет значения, но важна константная скорость доступа к записям.
В свою очередь, _QMap_ гарантирует упорядоченность по времени и уникальность пар **Время-Скорость**.
### Парсинг файла
Парсинг файла реализован с помощью интерфейса _ParserInterface_, реализация которого зависит от расширения входного файла.
Если возникнет необходимость обработки файлов другого типа, достаточно создать новую реализацию интерфейса.
### Обработка и вывод данных
Подсчет времени пути и простоя, а также вывод в **output.txt** осуществляет класс _carHandler_.
Так как данные в _QMap_ отсортированы, сложность подсчета времени линейна.

## Проблемы, возникшие при решении поставленной задачи
Для файлов потенциально больших размера RAM определенной системы, требуется другой подход к решению. Первым этапом файл сортируется External Sort методом, после чего сохранять все данные в памяти не нужно, достаточно текущей и предыдущей записи для вычислений отрезка времени. Соответственно, сложность линейна.
