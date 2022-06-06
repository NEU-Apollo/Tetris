QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
TEMPLATE = app


SOURCES += main.cpp\
    doublemainmeun.cpp \
    exitdialog.cpp \
    setdialog.cpp \
    shape.cpp \
    singlegame.cpp \
    singlegamegiledialog.cpp \
    singlemainmenu.cpp \
    singlerank.cpp \
        tetris.cpp \
    bin.cpp \
    brick.cpp \
    widget.cpp

HEADERS  += tetris.h \
    bin.h \
    brick.h \
    doublemainmeun.h \
    exitdialog.h \
    setdialog.h \
    shape.h \
    singlegame.h \
    singlegamegiledialog.h \
    singlemainmenu.h \
    singlerank.h \
    widget.h

FORMS    += tetris.ui \
    doublemainmeun.ui \
    exitdialog.ui \
    setdialog.ui \
    singlegame.ui \
    singlegamegiledialog.ui \
    singlemainmenu.ui \
    singlerank.ui \
    widget.ui

OTHER_FILES += \
    images/background.png \
    images/green.bmp \
    images/purple.bmp \
    images/red.bmp \
    images/ya.bmp \
    images/yello.bmp \
    images/blue.png \
    images/green.png \
    images/purple.png \
    images/red.png \
    images/ya.png \
    images/yello.png \
    images/Tetris.ico \
    myicon.rc

RESOURCES += \
    Resource.qrc
RC_FILES += \
    myicon.rc

DISTFILES += \
    music/Faded.mp3 \
    music/River.mp3 \
    music/See_You_Again.mp3 \
    music/See_You_Again.mp3 \
    music/李闰珉 (이루마) - River Flows in You (V0).mp3 \
    music/李闰珉 (이루마) - River Flows in You (V0).mp3
