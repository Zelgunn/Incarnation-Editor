#include "GUI/mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    Project::loadDatabases();

    MainWindow w;
    w.show();

    return a.exec();
}
