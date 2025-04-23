#include "fileprocessing.h"
#include <QFileDialog>
#include <QFileInfo>

FileProcessing::FileProcessing(QObject *parent) : QObject(parent)
{

}

void FileProcessing::openFile(QString fileName)
{
    fileName = fileName.mid(8);
    if (QFileInfo(fileName).suffix() == "s1p") {
        //_dataType = "Измерение s11";
        _source = new S11DataResearch();
    }
    else {
        emit fileError("Неподходящий тип файла!");
        return;
    }
    QString result = _source->readFile(fileName);
    if (result == "Ok") {
        emit calculationReady(_source);
    }
    else {
        emit fileError(result);
    }
}




QStringList FileProcessing::makeFilters()
{
    const QStringList filters({"Файл результатов измерений s11 (*.s1p)",
                               "Все файлы (*)"
                              });
    return filters;
}
