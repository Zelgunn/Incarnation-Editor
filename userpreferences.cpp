#include "userpreferencesmanager.h"

UserPreferencesManager::UserPreferencesManager()
{

}

void UserPreferencesManager::loadUserPreferences()
{
    QString configFilePath = QApplication::applicationDirPath() + "/config.ini";
    if(!QFile::exists(configFilePath))
    {
        return;
    }

    QFile configFile(configFilePath);
    if(!configFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QString config = QString(configFile.readAll());
    QStringList configLines = config.split("\r\n");

    int linesCount = configLines.length();

    for(int i = 0; i < linesCount; i++)
    {
        QString line = configLines[i];
        if(line.isEmpty())
        {
            continue;
        }

        if(line.contains('='))
        {
            int splitIndex = line.indexOf('=');
            QString fieldName = line.left(splitIndex - 1).trimmed();
            QString fieldValue = line.right(line.length() - splitIndex -1).trimmed();

            m_userPreferences.insert(fieldName, fieldValue);
        }
    }
}

void UserPreferencesManager::saveUserPreferences()
{
    QString configFilePath = QApplication::applicationDirPath() + "/config.ini";
    QFile configFile(configFilePath);
    if(!configFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream(&configFile);
    stream << "[General]" << endl;
    stream << "Language = " << getUserPreference("Language");
}

QString UserPreferencesManager::getUserPreference(const QString &fieldName) const
{
    if(!m_userPreferences.contains(fieldName))
    {
        return "";
    }

    return m_userPreferences[fieldName];
}

void UserPreferencesManager::setUserPreference(const QString &fieldName, const QString &fieldValue)
{
    if(!m_userPreferences.contains(fieldName))
    {
        m_userPreferences.insert(fieldName, fieldValue);
    }
    else
    {
        m_userPreferences[fieldName] = fieldValue;
    }
}

QString UserPreferencesManager::getUserLanguageName() const
{
    return getUserPreference("Language");
}

UserLanguage UserPreferencesManager::getUserLanguage() const
{
    QString userLanguage = getUserLanguageName();

    if(userLanguage == "Français")
    {
        return UserLanguage::French;
    }

    return UserLanguage::English;
}


