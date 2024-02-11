QT += widgets
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Saver.cpp \
    Sensor.cpp \
    concretesaver.cpp \
    controller.cpp \
    createwindow.cpp \
    error.cpp \
    humiditysensor.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowsensor.cpp \
    mainwinhum.cpp \
    mainwinuv.cpp \
    mainwinwind.cpp \
    sensorlisthum.cpp \
    sensorlistobj.cpp \
    sensorlistuv.cpp \
    sensorlistwind.cpp \
    uvsensor.cpp \
    windsensor.cpp

HEADERS += \
    Observer.h \
    Saver.h \
    Sensor.h \
    concretesaver.h \
    controller.h \
    createwindow.h \
    error.h \
    humiditysensor.h \
    mainwindow.h \
    mainwindowsensor.h \
    mainwinhum.h \
    mainwinuv.h \
    mainwinwind.h \
    sensorlisthum.h \
    sensorlistobj.h \
    sensorlistuv.h \
    sensorlistwind.h \
    uvsensor.h \
    windsensor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
