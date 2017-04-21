#include "projectmanager.h"

ProjectManager::ProjectManager()
{
    loadProjectList();
}

QString ProjectManager::projectListFilePath()
{
    return QApplication::applicationDirPath() + "/projects.xml";
}

void ProjectManager::loadProjectList()
{
    QFile file(projectListFilePath());
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QDomDocument dom;
    if(!dom.setContent(&file))
    {
        file.close();
        return;
    }

    QDomElement elem = dom.documentElement();
    QDomNode node = elem.firstChild();

    while(!node.isNull())
    {
        elem = node.toElement();

        if(!elem.isNull())
        {
            if(elem.tagName() == RECENT_PROJ)
            {
                m_recentProjectsPaths.append(elem.attribute("value"));
            }
        }
        node = node.nextSibling();
    }
}

void ProjectManager::saveProjectList()
{
    checkRecentProjectsPaths();

    QDomDocument dom;
    QDomElement elem;
    QDomProcessingInstruction qdpi = dom.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    dom.appendChild(qdpi);

    QDomElement root = dom.createElement("root");
    dom.appendChild(root);

    QFile file(projectListFilePath());
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    // Recent projects
    for(int i = 0; i < m_recentProjectsPaths.length(); i++)
    {
        elem = dom.createElement(RECENT_PROJ);
        elem.setAttribute("value", m_recentProjectsPaths[i]);
        root.appendChild(elem);
    }

    QTextStream out(&file);
    out.setCodec("utf8");
    out << dom.toString();

    file.close();
}

int ProjectManager::recentProjectCount() const
{
    return m_recentProjectsPaths.count();
}

QString ProjectManager::getRecentProjectPath(int index) const
{
    if((index >= 0) && (index >= m_recentProjectsPaths.count()))
    {
        return "";
    }

    return m_recentProjectsPaths[index];
}

void ProjectManager::setRecentProjectPath(const QString &path, int index)
{
    if((index >= 0) && (index < m_recentProjectsPaths.count()))
    {
        m_recentProjectsPaths[index] = path;
    }
    else
    {
        m_recentProjectsPaths.append(path);
    }

    saveProjectList();
}

void ProjectManager::addRecentProjectPath(const QString &path)
{
    if(m_recentProjectsPaths.contains(path))
    {
        m_recentProjectsPaths.removeAll(path);
    }
    m_recentProjectsPaths.insert(0, path);
    saveProjectList();
}

QStringList ProjectManager::getRecentProjectsPaths() const
{
    return m_recentProjectsPaths;
}

void ProjectManager::checkRecentProjectsPaths()
{
    QStringList tmp;

    for(int i = 0; i < m_recentProjectsPaths.length(); i++)
    {
        if(QFile::exists(m_recentProjectsPaths[i]) && !tmp.contains(m_recentProjectsPaths[i]))
        {
            tmp.append(m_recentProjectsPaths[i]);
        }
    }

    m_recentProjectsPaths = tmp;
}
