QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET          = CheckPanelState
DESTDIR         = ../bin
MOC_DIR         = ../debug/moc
UI_DIR          = ../debug/ui
OBJECTS_DIR     = ../debug/obj
TEMPLATE        = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mysetting.cpp \
    workonserialport.cpp

HEADERS += \
    mainwindow.h \
    mysetting.h \
    workonserialport.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
