#ifndef TRIGGERDIALOG_H
#define TRIGGERDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

#include "Projects/trigger.h"
#include "Projects/project.h"

namespace Ui {
class TriggerDialog;
}

class TriggerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TriggerDialog(QWidget *parent = 0);
    ~TriggerDialog();

    void loadTree();

    QTreeWidgetItem *addTreeItem(const QString &name, const QIcon &icon, QTreeWidgetItem *parent = 0);
    QTreeWidgetItem *addTreeItem(const QString &name, QTreeWidgetItem *parent = 0);

private:
    Ui::TriggerDialog *ui;
};

#endif // TRIGGERDIALOG_H
