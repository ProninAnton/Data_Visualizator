#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QObject>
#include "idatasource.h"
#include "s11dataresearch.h"
#include "customplotitem.h"

QT_CHARTS_USE_NAMESPACE

// Класс для управления взаимодействием между формой и классами обработчиками файлов
class FileProcessing : public QObject
{
    Q_OBJECT
public:
    explicit FileProcessing(QObject *parent = nullptr);

public slots:
    void openFile(QString fileName);

signals:
    void calculationReady(IDataSource *_source);
    void fileError(QString error);

private:
    QStringList makeFilters();

    IDataSource *_source;
    QThread *thread;
};

#endif // FILEPROCESSING_H
