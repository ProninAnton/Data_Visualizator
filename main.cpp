#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "fileprocessingwrapper.h"
#include "customplotitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CustomPlotItem>("CustomPlotItem",1,0,"CustomPlotItem");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    FileProcessingWrapper fpWrapper(&app);
    engine.rootContext()->setContextProperty("fpWrapper", &fpWrapper);
    engine.load(url);

    return app.exec();
}
