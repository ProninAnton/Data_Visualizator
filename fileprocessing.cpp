#include "fileprocessing.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QtCharts/QXYSeries>

FileProcessing::FileProcessing(QObject *parent) : QObject(parent)
{

}

void FileProcessing::openFile()
{
    QFileDialog fileDialog;
    fileDialog.setNameFilters(makeFilters());
    QString fileName = fileDialog.getOpenFileName(0,QString::fromUtf8("Выберите файл данных для визуализации"));

    if (fileName.isEmpty()) {
        emit fileError("Вы не выбрали файл!");
        return;
    }
    if (QFileInfo(fileName).suffix() == "s1p") {
        _dataType = "Измерение s11";
        _source = new S11DataResearch();
    }
    else {
        emit fileError("Неподходящий тип файла!");
        return;
    }
    QString result = _source->readFile(fileName);
    if (result == "Ok") {
        emit calculationReady(_dataType);
    }
    else {
        emit fileError(result);
    }
}

void FileProcessing::drawGraph(QAbstractSeries *series, QValueAxis *axisX, QValueAxis *axisY)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        QVector<QPointF> points = _source->getData();
        xySeries->replace(points);
    }

    qreal xMin;
    qreal xMax;
    qreal yMin;
    qreal yMax;
    _source->getGraphGeometry(xMin, xMax, yMin, yMax);
    if (axisX) {
        axisX->setMin(xMin);
        axisX->setMax(xMax);
    }
    if (axisY) {
        axisY->setMin(yMin);
        axisY->setMax(yMax);
    }

    QString time = "";
    QString date = "";
    _source->getDateTime(date,time);
    emit showDateTime(date, time);
}

QStringList FileProcessing::makeFilters()
{
    const QStringList filters({"Файл результатов измерений s11 (*.s1p)",
                               "Все файлы (*)"
                              });
    return filters;
}
