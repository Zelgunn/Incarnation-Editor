#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    UserPreferences::loadUserPreferences();

    ui->setupUi(this);

    m_structureWindow = new StructureWindow;
    ui->structureTabLayout->addWidget(m_structureWindow);
    connect(m_structureWindow, &StructureWindow::roomEditionModeTriggered, this, &MainWindow::loadRoomInEditor);

    m_roomWindow = new RoomWindow;
    ui->roomTabLayout->addWidget(m_roomWindow);

    applyUserPreferences();

    activateProjectTabs(false);

    connect(ui->menuTabWidget, &QTabWidget::currentChanged, this, &MainWindow::refreshCurrentTab);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(onCancelPreviousUserAction()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z), this, SLOT(onRestoreCanceledAction()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(onSaveActiveProject()));
}

MainWindow::~MainWindow()
{
    UserPreferences::saveUserPreferences();
    Project::activeProject()->save();

    delete ui;
}

void MainWindow::applyUserPreferences()
{
    setUserLanguage(UserPreferences::userLanguage());
    setWindowState(UserPreferences::mainWindowState());

    if(Project::activeProject() != Q_NULLPTR)
    {
        m_structureWindow->updateFromProjectData();
    }

    updateSettings();
}

void MainWindow::updateSettings()
{
    ui->userLanguageComboBox->setCurrentText(UserPreferences::userLanguageName());
    ui->workspaceLineEdit->setText(UserPreferences::workspaceDirectory());
    ui->structureEditorZoomSlider->setValue(UserPreferences::structureEditorZoom());
    ui->structureEditorZoomValueLabel->setText(QString("%1%").arg(UserPreferences::structureEditorZoom()));
    updateRecentProjectsListWidget();
}

void MainWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);

    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        updateSettings();
    }

    if(event->type() == QEvent::WindowStateChange)
    {
        UserPreferences::setMainWindowState(windowState());
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    ui->settingsSaveButton->setEnabled(UserPreferences::dirty());
}

void MainWindow::setUserLanguage(const UserLanguage &language)
{
    bool unload = false;
    switch (language)
    {
    case UserLanguage::French:
        m_translator.load(":/all/translations/french.qm");
        break;
    default:
        unload = true;
        break;
    }

    QApplication::removeTranslator(&m_translator);

    if(!unload)
    {
        QApplication::installTranslator(&m_translator);
    }
}

void MainWindow::addRecentProject(const QString &projectFilepath)
{
    m_projectManager.addRecentProjectPath(projectFilepath);
    updateRecentProjectsListWidget();
}

void MainWindow::updateRecentProjectsListWidget()
{
    ui->previousProjectsListWidget->clear();
    ui->previousProjectsListWidget->addItems(m_projectManager.getRecentProjectsPaths());
    QBrush foregroundBrush(QColor(0, 0, 175));
    for(int i = 0; i < ui->previousProjectsListWidget->count(); i++)
    {
        ui->previousProjectsListWidget->item(i)->setForeground(foregroundBrush);
    }
}

void MainWindow::createProject(const QString &projectFilepath)
{
    if(projectFilepath.isNull() || projectFilepath.isEmpty())
    {
        return;
    }

    if(!Project::createProject(projectFilepath))
    {
        qDebug() << "An error occured while trying to create the project file.";
        return;
    }

    setUpProject();
}

void MainWindow::openProject(const QString &projectFilepath)
{
    if(projectFilepath.isNull() || projectFilepath.isEmpty())
    {
        return;
    }

    if(!Project::openProject(projectFilepath))
    {
        qDebug() << "An error occured while trying to open the project file.";
        return;
    }

    setUpProject();
}

void MainWindow::copyProject(const QString &sourceProjectFilepath, const QString &projectFilepath)
{
    if(sourceProjectFilepath.isNull() ||sourceProjectFilepath.isEmpty() ||
            projectFilepath.isNull() || projectFilepath.isEmpty())
    {
        return;
    }

    if(!Project::copyProject(sourceProjectFilepath, projectFilepath))
    {
        qDebug() << "An error occured while trying to copy the project file.";
        return;
    }

    setUpProject();
}

void MainWindow::setUpProject(Project *project)
{
    unloadProject();
    if(project == Q_NULLPTR)
    {
        project = Project::activeProject();
    }
    addRecentProject(project->getFilepath());
    activateProjectTabs();

    m_structureWindow->setUpProject(project);
}

void MainWindow::unloadProject()
{
    m_structureWindow->unloadProject();
}

void MainWindow::activateProjectTabs(bool activate)
{
    ui->menuTabWidget->setTabEnabled(1, activate);
    ui->menuTabWidget->setTabEnabled(2, activate);
    if(!activate) ui->menuTabWidget->setTabEnabled(3, false);
}

void MainWindow::on_newProjectButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("New project"), UserPreferences::workspaceDirectory(), tr("XML files (*.xml);;All files (*)"));
    createProject(filename);
}

void MainWindow::on_openProjectButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open project"), UserPreferences::workspaceDirectory(), tr("XML files (*.xml);;All files (*)"));
    openProject(filename);
}

void MainWindow::on_copyProjectButton_clicked()
{
    QString sourceFilename = QFileDialog::getOpenFileName(this, tr("Copy project from"), UserPreferences::workspaceDirectory(), tr("XML files (*.xml);;All files (*)"));
    QString targetFilename = QFileDialog::getSaveFileName(this, tr("Copy project to"), UserPreferences::workspaceDirectory(), tr("XML files (*.xml);;All files (*)"));
    copyProject(sourceFilename, targetFilename);
}

void MainWindow::loadRoomInEditor(const QWeakPointer<Room> &room)
{
    ui->menuTabWidget->setTabEnabled(3, true);
    m_roomWindow->loadRoom(room);
    ui->menuTabWidget->setCurrentIndex(3);
}

void MainWindow::on_settingsSaveButton_released()
{
    UserPreferences::setUserLanguage(ui->userLanguageComboBox->currentText());
    UserPreferences::setWorkspaceDirectory(ui->workspaceLineEdit->text());
    UserPreferences::setStructureEditorZoom(ui->structureEditorZoomSlider->value());

    applyUserPreferences();
    UserPreferences::saveUserPreferences();
}

void MainWindow::on_workspaceToolButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select your workspace directory"), ui->workspaceLineEdit->text());
    if(directory.isEmpty() || directory.isNull())
    {
        return;
    }

    ui->workspaceLineEdit->setText(directory);
    if(directory != UserPreferences::workspaceDirectory())
    {
        UserPreferences::setDirty();
    }
}

void MainWindow::on_userLanguageComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 != UserPreferences::userLanguageName())
    {
        UserPreferences::setDirty();
    }
}

void MainWindow::on_structureEditorZoomSlider_valueChanged(int value)
{
    ui->structureEditorZoomValueLabel->setText(QString("%1%").arg(value));
    if(value != UserPreferences::structureEditorZoom())
    {
        UserPreferences::setDirty();
    }
}

void MainWindow::on_previousProjectsListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString itemPath = item->text();
    if((Project::activeProject() != Q_NULLPTR) && (itemPath == Project::activeProject()->getFilepath()))
    {
        return;
    }

    openProject(itemPath);
}

void MainWindow::refreshCurrentTab()
{
    switch (ui->menuTabWidget->currentIndex())
    {
    case 2:
        m_structureWindow->updateFromProjectData();
        break;
    case 3:
        m_roomWindow->updateFromProjectData();
        break;
    default:
        break;
    }
}

void MainWindow::onCancelPreviousUserAction()
{
    UserAction::revertLastAction();
    refreshCurrentTab();
}

void MainWindow::onRestoreCanceledAction()
{
    UserAction::restoreLastRevertedAction();
    refreshCurrentTab();
}

void MainWindow::onSaveActiveProject()
{
    Project::activeProject()->save();
}
