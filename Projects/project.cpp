#include "project.h"

Project *Project::s_activeProject = Q_NULLPTR;
QList<QSharedPointer<Asset> > Project::s_assetDatabase;
QList<Trigger > Project::s_globalTriggersDatabase;
QList<Trigger > Project::s_commonTriggersDatabase;

Project::Project(const QString projectFilepath)
{
    m_projectFilepath = projectFilepath;
}

Project* Project::activeProject()
{
    return s_activeProject;
}

bool Project::openProject(const QString &projectFilepath)
{
    // 1] Check for currently active project
    // if the project is not saved : prompt user
    // 2] Close project (reset graphics view, menus, ...)
    // 3] Load and init new project

    if(s_activeProject != Q_NULLPTR)
    {
        if(!s_activeProject->m_saved)
        {
            if(!s_activeProject->save())
            {
                return false;
            }
        }
    }

    Project *project = new Project(projectFilepath);
    if(!project->load())
    {
        return false;
    }

    s_activeProject = project;
    return true;
}

bool Project::createProject(const QString &projectFilepath)
{
    if(s_activeProject != Q_NULLPTR)
    {
        if(!s_activeProject->m_saved)
        {
            if(!s_activeProject->save())
            {
                return false;
            }
        }
    }

    Project *project = new Project(projectFilepath);
    if(!project->save())
    {
        return false;
    }

    s_activeProject = project;
    return true;
}

bool Project::copyProject(const QString &sourceProjectFilepath, const QString &projectFilepath)
{
    if(!QFile::exists(sourceProjectFilepath))
    {
        return false;
    }

    QFile source(sourceProjectFilepath);
    if(!source.open(QIODevice::ReadOnly))
    {
        return false;
    }

    if(QFile::exists(projectFilepath))
    {
        QFile previousProject(projectFilepath);
        if(!previousProject.open(QIODevice::WriteOnly))
        {
            return false;
        }
        previousProject.remove();
    }

    bool copySuccess = source.copy(projectFilepath);
    if(!copySuccess)
    {
        return false;
    }

    Project *project = new Project(projectFilepath);
    if(!project->load())
    {
        return false;
    }

    s_activeProject = project;
    return true;
}

bool Project::load()
{
    QFile file(m_projectFilepath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QDomDocument dom;
    if(!dom.setContent(&file))
    {
        return false;
    }

    QDomElement elem = dom.documentElement();
    QDomNode node = elem.firstChild();

    while(!node.isNull())
    {
        elem = node.toElement();

        if(!elem.isNull())
        {
            if(elem.tagName() == "Room")
            {
                m_rooms.append(QSharedPointer<Room>(new Room(elem)));
            }

            if(elem.tagName() == "Event")
            {
                m_events.append(QSharedPointer<Event>(new Event(elem)));
            }

            if(elem.tagName() == "Trigger")
            {
                m_globalTriggers.append(QSharedPointer<Trigger>(new Trigger(elem)));
            }
        }

        node = node.nextSibling();
    }

    for(int i = 0; i < m_events.length(); i++)
    {
        QList<QWeakPointer<Trigger> > triggers;
        QStringList triggersIDs = m_events[i]->triggersIDs();

        for(int j = 0; j < triggersIDs.length(); j++)
        {
            triggers.append(getTriggerWithID(triggersIDs[j]));
        }

        m_events[i]->linkToTriggers(triggers);
    }

    return true;
}

bool Project::save()
{
    if(s_activeProject == Q_NULLPTR)
    {
        return false;
    }

    QDomDocument dom;
    QDomElement elem;
    QDomProcessingInstruction qdpi = dom.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    dom.appendChild(qdpi);

    QDomElement root = dom.createElement("root");
    dom.appendChild(root);

    QFile file(m_projectFilepath);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    for(int i = 0; i < m_rooms.length(); i++)
    {
        elem = dom.createElement("Room");
        m_rooms[i]->toXml(&dom, &elem);
        root.appendChild(elem);
    }

    for(int i = 0; i < m_globalTriggers.length(); i++)
    {
        elem = dom.createElement("Trigger");
        m_globalTriggers[i]->toXML(&elem);
        root.appendChild(elem);
    }

    for(int i = 0; i < m_events.length(); i++)
    {
        elem = dom.createElement("Event");
        m_events[i]->toXML(&elem);
        root.appendChild(elem);
    }

    QTextStream out(&file);
    out.setCodec("utf8");
    out << dom.toString();

    file.close();

    return true;
}

void Project::loadDatabases()
{
    loadAssetDatabase();
    loadGlobalTriggersDatabase();
    loadCommonTriggersDatabase();
}

void Project::loadAssetDatabase()
{
    QFile file(ASSET_DB_PATH);
    file.open(QIODevice::ReadOnly);

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement elem = dom.documentElement();
    QDomNode node = elem.firstChild();

    while(!node.isNull())
    {
        elem = node.toElement();

        if(!elem.isNull())
        {
            s_assetDatabase.append(QSharedPointer<Asset>(new Asset(elem)));
        }

        node = node.nextSibling();
    }

    sortAssetDatabase();
}

void Project::sortAssetDatabase()
{
    std::sort(s_assetDatabase.begin(), s_assetDatabase.end(), Project::compareAssetName);
}

bool Project::compareAssetName(const QWeakPointer<Asset> a1, const QWeakPointer<Asset> a2)
{
    return a1.data()->name() < a2.data()->name();
}

int Project::assetDatabaseSize()
{
    return s_assetDatabase.length();
}

QWeakPointer<Asset> Project::assetDatabaseAt(int index)
{
    Q_ASSERT_X((index >= 0) && (index < s_assetDatabase.length()), "Project::databaseAssetAt(int index)", "index is out of range");
    return s_assetDatabase[index];
}

QList<QWeakPointer<Asset> > Project::assetDatabase()
{
    QList<QWeakPointer<Asset> > tmp;
    foreach (QSharedPointer<Asset> asset, s_assetDatabase)
    {
        tmp.append(asset.toWeakRef());
    }
    return tmp;
}

void Project::loadGlobalTriggersDatabase()
{
    QFile file(GLOBTRIG_DB_PATH);
    file.open(QIODevice::ReadOnly);

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement elem = dom.documentElement();
    QDomNode node = elem.firstChild();

    while(!node.isNull())
    {
        elem = node.toElement();

        if(!elem.isNull())
        {
            s_globalTriggersDatabase.append(Trigger(elem));
        }

        node = node.nextSibling();
    }
}

void Project::loadCommonTriggersDatabase()
{
    QFile file(COMTRIG_DB_PATH);
    file.open(QIODevice::ReadOnly);

    QDomDocument dom;
    dom.setContent(&file);

    QDomElement elem = dom.documentElement();
    QDomNode node = elem.firstChild();

    while(!node.isNull())
    {
        elem = node.toElement();

        if(!elem.isNull())
        {
            s_commonTriggersDatabase.append(Trigger(elem));
        }

        node = node.nextSibling();
    }
}

QString Project::getFilepath() const
{
    return m_projectFilepath;
}

QWeakPointer<Room> Project::addRoom(const Room &room)
{
    QSharedPointer<Room> tmp(new Room(room));
    m_rooms.append(tmp);

    return tmp.toWeakRef();
}

QWeakPointer<Room> Project::addRoom(const QString &name, const QSizeF &size, qreal position)
{
    QSharedPointer<Room> room(new Room(name, size, position));
    m_rooms.append(room);

    return room.toWeakRef();
}

void Project::removeRoom(QWeakPointer<Room> room)
{
    int index = m_rooms.indexOf(room);
    if(index < 0)
    {
        return;
    }

    m_rooms.removeAt(index);
}

QList<QWeakPointer<Room> > Project::getRooms() const
{
    QList<QWeakPointer<Room> > rooms;
    foreach (QSharedPointer<Room> room, m_rooms)
    {
        rooms.append(room.toWeakRef());
    }
    return rooms;
}

QWeakPointer<Room> Project::getRoomWithID(int id)
{
    foreach (QSharedPointer<Room> room, m_rooms)
    {
        if(room.data()->getId() == id)
        {
            return room;
        }
    }

    qDebug() << "WARNING : No room with id" << id;
    return QWeakPointer<Room>(Q_NULLPTR);
}

QList<QWeakPointer<Asset> > Project::getAssets() const
{
    QList<QWeakPointer<Asset> > assets;
    foreach (QSharedPointer<Room> room, m_rooms)
    {
        QList<QWeakPointer<Asset> > roomAssets = room.data()->assets();
        foreach (QSharedPointer<Asset> asset, roomAssets)
        {
            assets.append(asset);
        }
    }
    return assets;
}

QWeakPointer<Asset> Project::getAssetWithID(int id)
{
    foreach (QSharedPointer<Room> room, m_rooms)
    {
        QList<QWeakPointer<Asset> > roomAssets = room.data()->assets();
        foreach (QSharedPointer<Asset> asset, roomAssets)
        {
            if(asset.data()->getId() == id)
            {
                return asset;
            }
        }
    }

    qDebug() << "WARNING : No asset with id" << id;
    return QWeakPointer<Asset>(Q_NULLPTR);
}

QList<QWeakPointer<Event> > Project::getEvents() const
{
    QList<QWeakPointer<Event> > events;
    foreach (QSharedPointer<Event> event, m_events)
    {
        events.append(event.toWeakRef());
    }

    return events;
}

void Project::addEvent(Event *event)
{
    m_events.append(QSharedPointer<Event>(event));
}

QList<QWeakPointer<Trigger> > Project::getGlobalTriggers() const
{
    QList<QWeakPointer<Trigger> > triggers;
    foreach (QSharedPointer<Trigger> trigger, m_globalTriggers)
    {
        triggers.append(trigger.toWeakRef());
    }

    return triggers;
}

QWeakPointer<Trigger> Project::getTriggerWithID(const QString &id)
{
    foreach (QSharedPointer<Trigger> trigger, m_globalTriggers)
    {
        if(trigger.data()->id() == id)
        {
            return trigger.toWeakRef();
        }
    }

    qDebug() << "getTriggerWithID : No trigger with given ID :" << id;
    qDebug() << "getTriggerWithID : search in Events too";
    return QWeakPointer<Trigger>(Q_NULLPTR);
}

QList<Trigger> Project::globalTriggersDatabase()
{
    return s_globalTriggersDatabase;
}

QList<Trigger> Project::commonTriggersDatabase()
{
    return s_commonTriggersDatabase;
}
