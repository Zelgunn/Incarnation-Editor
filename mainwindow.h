#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QMap>

#include "userpreferencesmanager.h"

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void applyUserPreferences();
    void updateSettings();
    void setUserLanguage(const UserLanguage &language);

protected:
    void changeEvent(QEvent *event);

private slots:
    void on_settingsSaveButton_released();

private:
    Ui::MainWindow *ui;

    UserPreferencesManager* m_userPreferences;
    QTranslator m_translator;
};

#endif // MAINWINDOW_H
