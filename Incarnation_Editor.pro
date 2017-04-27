#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T09:18:51
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Incarnation_Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    GUI/Windows/mainwindow.cpp \
    GUI/Windows/structurewindow.cpp \
    User/useraction.cpp \
    User/userpreferences.cpp \
    Projects/projectmanager.cpp \
    Projects/project.cpp \
    GUI/GraphicsItems/roommarker.cpp \
    Projects/room.cpp \
    GUI/GraphicsItems/handle.cpp \
    GUI/Widgets/structureview.cpp \
    GUI/Widgets/structurescene.cpp \
    User/Actions/roomtransformaction.cpp \
    User/Actions/roomhandletransformaction.cpp \
    GUI/Windows/createroomdialog.cpp \
    User/Actions/roomcreationaction.cpp \
    User/Actions/roomdeletionaction.cpp \
    Projects/asset.cpp \
    GUI/Windows/roomwindow.cpp \
    GUI/Widgets/roomview.cpp \
    GUI/Widgets/roomscene.cpp \
    GUI/Widgets/shelflistwidget.cpp \
    GUI/GraphicsItems/assetmarker.cpp \
    User/Actions/assettransformaction.cpp \
    Projects/pit.cpp \
    GUI/GraphicsItems/rotationhandle.cpp \
    GUI/Windows/asseteditiondialog.cpp

HEADERS  += GUI/Windows/mainwindow.h \
    GUI/Windows/structurewindow.h \
    User/useraction.h \
    User/userpreferences.h \
    Projects/projectmanager.h \
    Projects/project.h \
    GUI/GraphicsItems/roommarker.h \
    Projects/room.h \
    GUI/GraphicsItems/handle.h \
    GUI/Widgets/structureview.h \
    GUI/Widgets/structurescene.h \
    User/Actions/roomtransformaction.h \
    User/Actions/roomhandletransformaction.h \
    GUI/Windows/createroomdialog.h \
    User/Actions/roomcreationaction.h \
    User/Actions/roomdeletionaction.h \
    Projects/asset.h \
    GUI/Windows/roomwindow.h \
    GUI/Widgets/roomview.h \
    GUI/Widgets/roomscene.h \
    GUI/Widgets/shelflistwidget.h \
    GUI/GraphicsItems/assetmarker.h \
    User/Actions/assettransformaction.h \
    Projects/pit.h \
    GUI/GraphicsItems/rotationhandle.h \
    GUI/Windows/asseteditiondialog.h

FORMS    += GUI/Windows/mainwindow.ui \
    GUI/Windows/structurewindow.ui \
    GUI/Windows/createroomdialog.ui \
    GUI/Windows/roomwindow.ui \
    GUI/Windows/asseteditiondialog.ui

RESOURCES += \
    images.qrc \
    translations.qrc \
    database.qrc
