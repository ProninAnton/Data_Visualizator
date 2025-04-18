#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "fileprocessing.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    FileProcessing fileProcess(&app);
    engine.rootContext()->setContextProperty("fileProcessing", &fileProcess);
    engine.load(url);

    return app.exec();
}
