#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_userPreferences = new UserPreferencesManager();
    m_userPreferences->loadUserPreferences();
    applyUserPreferences();
}

MainWindow::~MainWindow()
{
    m_userPreferences->saveUserPreferences();
    delete m_userPreferences;

    delete ui;
}

void MainWindow::applyUserPreferences()
{
    setUserLanguage(m_userPreferences->getUserLanguage());

    updateSettings();
}

void MainWindow::updateSettings()
{
    ui->userLanguageComboBox->setCurrentText(m_userPreferences->getUserLanguageName());
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
        updateSettings();
    }
    QWidget::changeEvent(event);
}

void MainWindow::on_settingsSaveButton_released()
{
    m_userPreferences->setUserPreference("Language", ui->userLanguageComboBox->currentText());

    m_userPreferences->saveUserPreferences();
    applyUserPreferences();
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
