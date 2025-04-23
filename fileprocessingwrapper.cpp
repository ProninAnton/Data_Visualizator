#include "fileprocessingwrapper.h"

FileProcessingWrapper::FileProcessingWrapper(QObject *parent) : QObject(parent)
{
        _thread = new QThread();
        _fileProcess = new FileProcessing();
        _fileProcess->moveToThread(_thread);
        connect(this, &FileProcessingWrapper::readFile,
                _fileProcess, &FileProcessing::openFile);

        connect(_fileProcess, &FileProcessing::fileError,
                this, &FileProcessingWrapper::fileErrorSlot);

        connect(_fileProcess, &FileProcessing::calculationReady,
                this, &FileProcessingWrapper::calculationReadySlot);

        _thread->start();
}

void FileProcessingWrapper::drawGraph(CustomPlotItem *customPlot)
{
    QVector<double> xAxis;
    QVector<double> yAxis;

    qreal xMin;
    qreal xMax;
    qreal yMin;
    qreal yMax;

    _source->getData(xAxis, yAxis);
    _source->getGraphGeometry(xMin, xMax, yMin, yMax);
    customPlot->drawGraph(xAxis, yAxis, xMin, xMax, yMin, yMax);

    QString time = "";
    QString date = "";
    _source->getDateTime(date,time);
    emit showDateTime(date, time);
}

void FileProcessingWrapper::calculationReadySlot(IDataSource *source)
{
    _source = source;
    emit calculationReady();
}

void FileProcessingWrapper::fileErrorSlot(QString error)
{
    emit fileError(error);
}
