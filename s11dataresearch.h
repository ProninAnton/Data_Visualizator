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

    QVector<QPointF> getData() const override;

    void getDateTime(QString &date, QString &time) override;

    void getGraphGeometry(qreal &xMin, qreal &xMax, qreal &yMin, qreal &yMax) override;

private:
    bool isValid(QTextStream &in); //Проверка валидности файла

    std::vector<double> complexCalculation(const std::vector<std::complex<double>> vectorCmplx);
    size_t lineCount(const QString fileName); //ф-ция подсчета строк в файле
    void generateData(const int pointsCount, const std::vector<double> frequencyX,
                      const std::vector<double> s11ResY);

    QVector<QPointF> s11_data;
    double  s11_xMin;
    double  s11_xMax;
    double  s11_yMin;
    double  s11_yMax;
    QString s11_date;
    QString s11_time;
};

#endif // S11DATARESEARCH_H
