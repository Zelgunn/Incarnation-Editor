#ifndef PROJECT_H
#define PROJECT_H

#include <QtXml>
#include <QFile>
#include <QTextStream>
#include <QSharedPointer>

#include "room.h"
#include "asset.h"

#define ASSET_DB_PATH ":/all/database/assets.xml"

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

    static void loadDatabase();
    static void sortDatabase();
    static bool compareAssetName(const QWeakPointer<Asset> a1, const QWeakPointer<Asset> a2);
    static int assetDatabaseSize();
    static QWeakPointer<Asset> assetDatabaseAt(int index);
    static QList<QWeakPointer<Asset>> assetDatabase();

    QString getFilepath() const;
    QWeakPointer<Room> addRoom(const Room &room);
    QWeakPointer<Room> addRoom(const QString &name, const QSizeF &size = QSizeF(), qreal position = 0);
    void removeRoom(QWeakPointer<Room> room);

    QList<QWeakPointer<Room> > getRooms() const;
    QWeakPointer<Room> getRoomWithID(int id);

    QList<QWeakPointer<Asset> > getAssets() const;
    QWeakPointer<Asset> getAssetWithID(int id);

private:
    static Project *s_activeProject;
    QString m_projectFilepath;
    bool m_saved = false;

    QList<QSharedPointer<Room> > m_rooms;

    static QList<QSharedPointer<Asset> > s_assetDatabase;
};

#endif // PROJECT_H
