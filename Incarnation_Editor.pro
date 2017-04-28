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
    GUI/mainwindow.cpp \
    GUI/StructureEditor/structurewindow.cpp \
    User/useraction.cpp \
    User/userpreferences.cpp \
    Projects/projectmanager.cpp \
    Projects/project.cpp \
    GUI/StructureEditor/roommarker.cpp \
    Projects/room.cpp \
    GUI/StructureEditor/handle.cpp \
    GUI/StructureEditor/structureview.cpp \
    GUI/StructureEditor/structurescene.cpp \
    User/Actions/roomtransformaction.cpp \
    User/Actions/roomhandletransformaction.cpp \
    GUI/StructureEditor/createroomdialog.cpp \
    User/Actions/roomcreationaction.cpp \
    User/Actions/roomdeletionaction.cpp \
    Projects/asset.cpp \
    GUI/RoomEditor/roomwindow.cpp \
    GUI/RoomEditor/roomview.cpp \
    GUI/RoomEditor/roomscene.cpp \
    GUI/RoomEditor/shelflistwidget.cpp \
    GUI/RoomEditor/assetmarker.cpp \
    User/Actions/assettransformaction.cpp \
    Projects/pit.cpp \
    GUI/RoomEditor/rotationhandle.cpp \
    GUI/RoomEditor/asseteditiondialog.cpp \
    GUI/TimelineEditor/timelinewindow.cpp \
    Projects/event.cpp \
    GUI/TimelineEditor/graphicseventitem.cpp \
    Projects/trigger.cpp \
    GUI/TimelineEditor/timelineview.cpp \
    GUI/TimelineEditor/timelinescene.cpp \
    GUI/TimelineEditor/neweventdialog.cpp \
    GUI/TimelineEditor/colorwidget.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/StructureEditor/structurewindow.h \
    User/useraction.h \
    User/userpreferences.h \
    Projects/projectmanager.h \
    Projects/project.h \
    GUI/StructureEditor/roommarker.h \
    Projects/room.h \
    GUI/StructureEditor/handle.h \
    GUI/StructureEditor/structureview.h \
    GUI/StructureEditor/structurescene.h \
    User/Actions/roomtransformaction.h \
    User/Actions/roomhandletransformaction.h \
    GUI/StructureEditor/createroomdialog.h \
    User/Actions/roomcreationaction.h \
    User/Actions/roomdeletionaction.h \
    Projects/asset.h \
    GUI/RoomEditor/roomwindow.h \
    GUI/RoomEditor/roomview.h \
    GUI/RoomEditor/roomscene.h \
    GUI/RoomEditor/shelflistwidget.h \
    GUI/RoomEditor/assetmarker.h \
    User/Actions/assettransformaction.h \
    Projects/pit.h \
    GUI/RoomEditor/rotationhandle.h \
    GUI/RoomEditor/asseteditiondialog.h \
    GUI/TimelineEditor/timelinewindow.h \
    Projects/event.h \
    GUI/TimelineEditor/graphicseventitem.h \
    Projects/trigger.h \
    GUI/TimelineEditor/timelineview.h \
    GUI/TimelineEditor/timelinescene.h \
    GUI/TimelineEditor/neweventdialog.h \
    GUI/TimelineEditor/colorwidget.h

FORMS    += GUI/mainwindow.ui \
    GUI/StructureEditor/structurewindow.ui \
    GUI/StructureEditor/createroomdialog.ui \
    GUI/RoomEditor/roomwindow.ui \
    GUI/RoomEditor/asseteditiondialog.ui \
    GUI/TimelineEditor/timelinewindow.ui \
    GUI/TimelineEditor/neweventdialog.ui

RESOURCES += \
    images.qrc \
    translations.qrc \
    database.qrc
