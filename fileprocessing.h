#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QValueAxis>
#include "idatasource.h"
#include "s11dataresearch.h"

QT_CHARTS_USE_NAMESPACE

// Класс для управления взаимодействием между формой и классами обработчиками файлов
class FileProcessing : public QObject
{
    Q_OBJECT
public:
    explicit FileProcessing(QObject *parent = nullptr);

public slots:
    void openFile();
    void drawGraph(QAbstractSeries *series, QValueAxis *axisX, QValueAxis *axisY);

signals:
    void calculationReady(QString typeName);
    void fileError(QString error);
    void showDateTime(QString fileDate, QString fileTime);

private:
    QStringList makeFilters();

    IDataSource *_source;
    QString _dataType;
};

#endif // FILEPROCESSING_H
