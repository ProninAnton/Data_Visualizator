#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <QString>
#include <QPointF>

//Класс интерфейс для обеспечения интеграции классов обработчиков для новых типов данных
class IDataSource
{
public:
    virtual ~IDataSource() = default;
    //Функция чтения файла
    virtual QString readFile(QString fileName) = 0;
    //Функция получения данных, необходимых для построения графика
    virtual QVector<QPointF> getData() const = 0;
    //Функция для получения данных о граицах графика
    virtual void getGraphGeometry(qreal &xMin, qreal &xMax, qreal &yMin, qreal &yMax) = 0;

    virtual void getDateTime(QString &date, QString &time) = 0;
};

#endif // IDATASOURCE_H
