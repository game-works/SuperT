#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T10:28:29
#
#-------------------------------------------------

QT       += core gui widgets opengl

TARGET = SuperT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        game.cpp \
    entity.cpp \
    movecommand.cpp \
    player.cpp \
    bush.cpp \
    inputhandler.cpp \
    cloud.cpp \
    vulture.cpp \
    helicopter.cpp \
    aircraft.cpp \
    playershot.cpp \
    explosion.cpp \
    tank.cpp \
    artillery.cpp \
    enemyshot.cpp \
    playerbomb.cpp \
    bombcommand.cpp \
    shotcommand.cpp \
    artilleryshot.cpp \
    hud.cpp \
    spritesheet.cpp \
    rock.cpp \
    special.cpp \
    specialcommand.cpp \
    menu.cpp \
    customtextitem.cpp \
    levelmanager.cpp

HEADERS += \
        game.h \
    entity.h \
    command.h \
    movecommand.h \
    entitypool.h \
    player.h \
    bush.h \
    inputhandler.h \
    cloud.h \
    vulture.h \
    helicopter.h \
    aircraft.h \
    playershot.h \
    explosion.h \
    tank.h \
    artillery.h \
    enemyshot.h \
    playerbomb.h \
    bombcommand.h \
    shotcommand.h \
    artilleryshot.h \
    hud.h \
    spritesheet.h \
    rock.h \
    special.h \
    specialcommand.h \
    menu.h \
    customtextitem.h \
    levelmanager.h

RESOURCES += \
    images.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/icon.ico \
    gameicon.rc

RC_FILE = gameicon.rc

