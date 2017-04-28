#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QMap>
#include <QFileDialog>
#include <QToolBar>
#include <QListWidgetItem>
#include <QShortcut>
#include <QMessageBox>

#include "User/userpreferences.h"
#include "User/useraction.h"
#include "Projects/projectmanager.h"
#include "Projects/project.h"
#include "GUI/StructureEditor/structurewindow.h"
#include "GUI/RoomEditor/roomwindow.h"
#include "GUI/TimelineEditor/timelinewindow.h"

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

    void addRecentProject(const QString &projectFilepath);
    void updateRecentProjectsListWidget();
    void createProject(const QString &projectFilepath);
    void openProject(const QString &projectFilepath);
    void copyProject(const QString &sourceProjectFilepath, const QString &projectFilepath);

    void setUpProject(Project *project = Q_NULLPTR);
    void unloadProject();
    void activateProjectTabs(bool activate = true);

protected:
    void changeEvent(QEvent *event);
    void paintEvent(QPaintEvent* event);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_newProjectButton_clicked();
    void on_openProjectButton_clicked();
    void on_copyProjectButton_clicked();
    void loadRoomInEditor(const QWeakPointer<Room> &room);

    void on_settingsSaveButton_released();
    void on_workspaceToolButton_clicked();
    void on_userLanguageComboBox_currentTextChanged(const QString &arg1);
    void on_structureEditorZoomSlider_valueChanged(int value);

    void on_previousProjectsListWidget_itemDoubleClicked(QListWidgetItem *item);
    void refreshCurrentTab();

    void onCancelPreviousUserAction();
    void onRestoreCanceledAction();
    void onSaveActiveProject();

private:
    Ui::MainWindow *ui;

    //UserPreferences m_userPreferences;

    QTranslator m_translator;
    ProjectManager m_projectManager;

    TimelineWindow *m_timelineWindow;
    StructureWindow *m_structureWindow;
    RoomWindow *m_roomWindow;

    bool m_userPreferencesSaved = true;
};

#endif // MAINWINDOW_H
