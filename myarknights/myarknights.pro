QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    changedirection.cpp \
    config.cpp \
    ending.cpp \
    enemy.cpp \
    episodes.cpp \
    gamescene.cpp \
    hero.cpp \
    main.cpp \
    mainwindow.cpp \
    state.cpp \
    unit.cpp

HEADERS += \
    cell.h \
    changedirection.h \
    config.h \
    ending.h \
    enemy.h \
    episodes.h \
    gamescene.h \
    hero.h \
    mainwindow.h \
    state.h \
    unit.h

FORMS += \
    changedirection.ui \
    ending.ui \
    episodes.ui \
    gamescene.ui \
    mainwindow.ui \
    state.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    CG/CG.qrc \
    map_config/map_config.qrc
