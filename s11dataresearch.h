#ifndef S11DATARESEARCH_H
#define S11DATARESEARCH_H

#include "idatasource.h"
#include <QFile>
#include <QTextStream>
#include <complex>
#include <QtCharts/QValueAxis>

class S11DataResearch : public IDataSource
{
public:
    S11DataResearch();

    QString readFile(const QString fileName) override;

    void getData(QVector<double> &xAxis, QVector<double> &yAxis) const override;

    void getDateTime(QString &date, QString &time) override;

    void getGraphGeometry(qreal &xMin, qreal &xMax, qreal &yMin, qreal &yMax) override;

private:
    bool isValid(QTextStream &in); //Проверка валидности файла
    // Получение значения s11 из комплексныого числа
    QVector<double> complexCalculation(const std::vector<std::complex<double>> vectorCmplx);
    size_t lineCount(const QString fileName); //ф-ция подсчета строк в файле

    QVector<double> s11_frequency;
    QVector<double> s11_value;
    double  s11_xMin;
    double  s11_xMax;
    double  s11_yMin;
    double  s11_yMax;
    QString s11_date;
    QString s11_time;
};

#endif // S11DATARESEARCH_H
