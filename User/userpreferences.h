#ifndef USERPREFERENCES_H
#define USERPREFERENCES_H

#include <QFile>
#include <QDir>
#include <QtXml>
#include <QApplication>
#include <QTextStream>

#include <QDebug>

#define USER_LANG "UserLanguage"
#define WORKSPACE_DIR "WorkspaceDirectory"
#define MAIN_WINDOW "MainWindow"
#define STR_ZOOM "StrZoom"
#define BASE_ZOOM 0.5

enum UserLanguage
{
    English,
    French
};

class UserPreferences
{
public:
    UserPreferences();
    static QString userPreferencesFilePath();
    static UserPreferences userPreferences();

    static void loadUserPreferences();
    static void saveUserPreferences();

    static QString userLanguageName();
    static UserLanguage userLanguage();
    static void setUserLanguage(const QString &language);
    static void setUserLanguage(UserLanguage language);

    static QString workspaceDirectory();
    static void setWorkspaceDirectory(const QString &directory);

    static Qt::WindowStates mainWindowState();
    static void setMainWindowState(Qt::WindowStates state);

    static int structureEditorZoom();
    static void setStructureEditorZoom(int zoom);
    static float structureEditorZoomRatio();

    static bool dirty();
    static void setDirty(bool dirty = true);

protected:
    void _loadUserPreferences();
    void _saveUserPreferences();

private:
    static UserPreferences s_userPreferences;
    UserLanguage m_userLanguage = UserLanguage::English;
    QString m_workspaceDirectory = "";
    Qt::WindowStates m_mainWindowState = Qt::WindowNoState;
    int m_structureEditorZoom = 100;

    bool m_dirty = false;
};

#endif // USERPREFERENCES_H
