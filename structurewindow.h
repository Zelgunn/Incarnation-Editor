#ifndef STRUCTUREWINDOW_H
#define STRUCTUREWINDOW_H

#include <QMainWindow>

namespace Ui {
class StructureWindow;
}

class StructureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StructureWindow(QWidget *parent = 0);
    ~StructureWindow();

private:
    Ui::StructureWindow *ui;
};

#endif // STRUCTUREWINDOW_H
