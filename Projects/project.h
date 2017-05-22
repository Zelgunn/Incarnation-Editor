#ifndef PROJECT_H
#define PROJECT_H

#include <QtXml>
#include <QFile>
#include <QTextStream>
#include <QSharedPointer>

#include "room.h"
#include "assetmodel.h"
#include "asset.h"
#include "event.h"
#include "trigger.h"

#define ASSET_DB_PATH ":/all/database/assets.xml"
#define GLOBTRIG_DB_PATH ":/all/database/global_triggers.xml"
#define COMTRIG_DB_PATH ":/all/database/common_triggers.xml"

class Project
{
public:
    Project(const QString projectFilepath);

    static Project* activeProject();
    static bool openProject(const QString &projectFilepath);
    static bool createProject(const QString &projectFilepath);
    static bool copyProject(const QString &sourceProjectFilepath, const QString &projectFilepath);

    bool load();
    bool save();

    static void loadDatabases();

    static void loadAssetModelsDatabase();
    static void sortAssetModelsDatabase();
    static bool compareAssetName(const Asset a1, const Asset a2);
    static int assetModelsCount();
    static AssetModel assetModelAt(int index);
    static QList<AssetModel> assetModelsDatabase();
    static AssetModel modelOf(const QWeakPointer<Asset> &asset);

    static void loadGlobalTriggersDatabase();
    static void loadCommonTriggersDatabase();

    QString getFilepath() const;
    QWeakPointer<Room> addRoom(const Room &room);
    QWeakPointer<Room> addRoom(const QString &name, const QSizeF &size = QSizeF(), qreal position = 0);
    void removeRoom(QWeakPointer<Room> room);

    QList<QWeakPointer<Room> > getRooms() const;
    QWeakPointer<Room> getRoomWithID(int id);

    QList<QWeakPointer<Asset> > getAssets() const;
    QWeakPointer<Asset> getAssetWithID(int id);

    QList<QWeakPointer<Event> > getEvents() const;
    void addEvent(Event *event);

    QList<QWeakPointer<Trigger> > getGlobalTriggers() const;
    QWeakPointer<Trigger> getTriggerWithID(const QString &id);

    static QList<Trigger> globalTriggersDatabase();
    static QList<Trigger> commonTriggersDatabase();

private:
    static Project *s_activeProject;
    QString m_projectFilepath;
    bool m_saved = false;

    QList<QSharedPointer<Room> > m_rooms;
    QList<QSharedPointer<Event> > m_events;
    QList<QSharedPointer<Trigger> > m_globalTriggers;

    static QList<AssetModel> s_assetModelsDatabase;
    static QList<Trigger> s_globalTriggersDatabase;
    static QList<Trigger> s_commonTriggersDatabase;
};

#endif // PROJECT_H
