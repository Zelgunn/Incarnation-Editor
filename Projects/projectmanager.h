#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QFile>
#include <QDir>
#include <QtXml>
#include <QApplication>
#include <QTextStream>

#include <QDebug>

#define RECENT_PROJ "RecentProject"

class ProjectManager
{
public:
    ProjectManager();

    static QString projectListFilePath();
    void loadProjectList();
    void saveProjectList();

    int recentProjectCount() const;
    QString getRecentProjectPath(int index = 0) const;
    void setRecentProjectPath(const QString &path, int index = 0);
    void addRecentProjectPath(const QString &path);
    QStringList getRecentProjectsPaths() const;
    void checkRecentProjectsPaths();

private:
    QStringList m_recentProjectsPaths;
};

#endif // PROJECTMANAGER_H
