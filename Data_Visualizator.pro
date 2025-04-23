QT += printsupport qml quick

CONFIG += c++17

SOURCES += \
        customplotitem.cpp \
        fileprocessing.cpp \
        fileprocessingwrapper.cpp \
        main.cpp \
        qcustomplot/qcustomplot.cpp \
        s11dataresearch.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

HEADERS += \
    customplotitem.h \
    fileprocessing.h \
    fileprocessingwrapper.h \
    idatasource.h \
    qcustomplot/qcustomplot.h \
    s11dataresearch.h
