#ifndef FILEPROCESSINGWRAPPER_H
#define FILEPROCESSINGWRAPPER_H

#include <QObject>
#include <QThread>
#include "fileprocessing.h"
#include "idatasource.h"
#include "customplotitem.h"

class QCustomPlot;
// Класс обертка для разделения графического потока и потока, отвечающего за обработку файла
class FileProcessingWrapper : public QObject
{
    Q_OBJECT
public:
    FileProcessingWrapper();
public:
    explicit FileProcessingWrapper(QObject *parent = nullptr);

    Q_INVOKABLE void openFile(QString file){
        emit readFile(file);
    }

    Q_INVOKABLE void drawGraph(CustomPlotItem* customPlot);

public slots:
    void fileErrorSlot(QString fileError);
    void calculationReadySlot(IDataSource *source);

signals :
    void readFile(QString file);

    void fileError(QString error);
    void calculationReady();
    void showDateTime(QString fileDate, QString fileTime);

public:
    QThread *_thread;
    FileProcessing *_fileProcess;
    IDataSource *_source;
};

#endif // FILEPROCESSINGWRAPPER_H
