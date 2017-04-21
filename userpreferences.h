#ifndef USERPREFERENCESMANAGER_H
#define USERPREFERENCESMANAGER_H

#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QApplication>

#include <QDebug>

enum UserLanguage
{
    English,
    French
};

class UserPreferencesManager
{
public:
    UserPreferencesManager();
    void loadUserPreferences();
    void saveUserPreferences();

    QString getUserPreference(const QString &fieldName) const;
    void setUserPreference(const QString &fieldName, const QString &fieldValue);

    QString getUserLanguageName() const;
    UserLanguage getUserLanguage() const;

private:
    QMap<QString, QString> m_userPreferences;

};

#endif // USERPREFERENCESMANAGER_H
