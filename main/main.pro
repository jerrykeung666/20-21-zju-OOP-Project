QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calllandlordthread.cpp \
    card.cpp \
    cardgroups.cpp \
    cardwidget.cpp \
    gamecontrol.cpp \
    gamewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mypushbutton.cpp \
    player.cpp \
    robot.cpp \
    strategy.cpp \
    user.cpp \
    playhandthread.cpp

HEADERS += \
    calllandlordthread.h \
    card.h \
    cardgroups.h \
    cardwidget.h \
    gamecontrol.h \
    gamewindow.h \
    mainwindow.h \
    mypushbutton.h \
    player.h \
    robot.h \
    strategy.h \
    user.h \
    playhandthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pokerimage.qrc
