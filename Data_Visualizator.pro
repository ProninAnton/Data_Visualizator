QT += charts qml quick

CONFIG += c++17

SOURCES += \
        fileprocessing.cpp \
        main.cpp \
        s11dataresearch.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

HEADERS += \
    fileprocessing.h \
    idatasource.h \
    s11dataresearch.h
