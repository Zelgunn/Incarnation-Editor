#include "userpreferences.h"

UserPreferences UserPreferences::s_userPreferences;

UserPreferences::UserPreferences()
{

}

QString UserPreferences::userPreferencesFilePath()
{
    return QApplication::applicationDirPath() + "/config.xml";
}

UserPreferences UserPreferences::userPreferences()
{
    return s_userPreferences;
}

void UserPreferences::_loadUserPreferences()
{
    QFile file(userPreferencesFilePath());
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
            if(elem.tagName() == USER_LANG)
            {
                setUserLanguage(elem.attribute("value"));
            }
            else if(elem.tagName() == WORKSPACE_DIR)
            {
                setWorkspaceDirectory(elem.attribute("value"));
            }
            else if(elem.tagName() == MAIN_WINDOW)
            {
                setMainWindowState((Qt::WindowStates)elem.attribute("state").toInt());
            }
            else if(elem.tagName() == STR_ZOOM)
            {
                setStructureEditorZoom(elem.attribute("value").toInt());
            }
        }

        node = node.nextSibling();
    }

    m_dirty = false;
}

void UserPreferences::_saveUserPreferences()
{
    QDomDocument dom;
    QDomElement elem;
    QDomProcessingInstruction qdpi = dom.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    dom.appendChild(qdpi);

    QDomElement root = dom.createElement("root");
    dom.appendChild(root);

    // User language
    elem = dom.createElement(USER_LANG);
    elem.setAttribute("value", userLanguageName());
    root.appendChild(elem);

    // Workspace directory
    elem = dom.createElement(WORKSPACE_DIR);
    elem.setAttribute("value", m_workspaceDirectory);
    root.appendChild(elem);

    // Main window parameters
    elem = dom.createElement(MAIN_WINDOW);
    elem.setAttribute("state", m_mainWindowState);
    root.appendChild(elem);

    // Structure Editor
    elem = dom.createElement(STR_ZOOM);
    elem.setAttribute("value", m_structureEditorZoom);
    root.appendChild(elem);

    QFile file(userPreferencesFilePath());
    if(!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);
    out.setCodec("utf8");
    out << dom.toString();

    file.close();

    m_dirty = false;
}

void UserPreferences::loadUserPreferences()
{
    s_userPreferences._loadUserPreferences();
}

void UserPreferences::saveUserPreferences()
{
    s_userPreferences._saveUserPreferences();
}

QString UserPreferences::userLanguageName()
{
    QString language = "English";
    switch (s_userPreferences.m_userLanguage)
    {
    case UserLanguage::French:
        language = "Français";
        break;
    default:
        language = "English";
        break;
    }
    return language;
}

UserLanguage UserPreferences::userLanguage()
{
    return s_userPreferences.m_userLanguage;
}

void UserPreferences::setUserLanguage(const QString &language)
{
    UserLanguage newLanguage = UserLanguage::English;
    if(language == "Français")
    {
        newLanguage = UserLanguage::French;
    }
    s_userPreferences.m_userLanguage = newLanguage;
    s_userPreferences.m_dirty = true;
}

void UserPreferences::setUserLanguage(UserLanguage language)
{
    s_userPreferences.m_userLanguage = language;
    s_userPreferences.m_dirty = true;
}

QString UserPreferences::workspaceDirectory()
{
    return s_userPreferences.m_workspaceDirectory;
}

void UserPreferences::setWorkspaceDirectory(const QString &directory)
{
    if(QDir(directory).exists())
    {
        s_userPreferences.m_workspaceDirectory = directory;
        s_userPreferences.m_dirty = true;
    }
}

Qt::WindowStates UserPreferences::mainWindowState()
{
    return s_userPreferences.m_mainWindowState;
}

void UserPreferences::setMainWindowState(Qt::WindowStates state)
{
    s_userPreferences.m_mainWindowState = state;
}

int UserPreferences::structureEditorZoom()
{
    return s_userPreferences.m_structureEditorZoom;
}

void UserPreferences::setStructureEditorZoom(int zoom)
{
    s_userPreferences.m_structureEditorZoom = zoom;
}

float UserPreferences::structureEditorZoomRatio()
{
    return BASE_ZOOM * s_userPreferences.m_structureEditorZoom;
}

bool UserPreferences::dirty()
{
    return s_userPreferences.m_dirty;
}

void UserPreferences::setDirty(bool dirty)
{
    s_userPreferences.m_dirty = dirty;
}



