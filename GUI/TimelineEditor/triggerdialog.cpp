#include "triggerdialog.h"
#include "ui_triggerdialog.h"

TriggerDialog::TriggerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TriggerDialog)
{
    ui->setupUi(this);
    loadTree();
}

TriggerDialog::~TriggerDialog()
{
    delete ui;
}

void TriggerDialog::loadTree()
{
    ui->treeWidget->clear();

    QList<Trigger> globalTriggers = Project::globalTriggersDatabase();

    QTreeWidgetItem *globalRoom = addTreeItem("Global");
    for(int i = 0; i < globalTriggers.length(); i++)
    {
        addTreeItem(globalTriggers[i].action(), globalRoom);
    }

    QList<Trigger> commonTriggers = Project::commonTriggersDatabase();
    QList<QWeakPointer<Room> > rooms = Project::activeProject()->getRooms();
    //QList<QWeakPointer<Asset> > assets = Project::activeProject()->getAssets();

    for(int i = 0; i < rooms.length(); i++)
    {
       QTreeWidgetItem *roomItem = addTreeItem(rooms[i].data()->getName());
       QList<QWeakPointer<Asset> > roomAssets = rooms[i].data()->assets();
       for(int j = 0; j < roomAssets.length(); j++)
       {
            QTreeWidgetItem *assetItem = addTreeItem(roomAssets[j].data()->name(), roomItem);
            QTreeWidgetItem *commonTriggerItem = addTreeItem("Common", assetItem);
            for(int k = 0; k < commonTriggers.length(); k++)
            {
                addTreeItem(commonTriggers[k].action(), commonTriggerItem);
            }

            AssetModel assetModel = Project::modelOf(roomAssets[j]);
            QList<Trigger> assetTriggers = assetModel.triggers();
            QList<QString> assetTriggersCaterogies;
            QList<QTreeWidgetItem *> assetTriggersCaterogiesItems;
            for(int k = 0; k < assetTriggers.length(); k++)
            {
                QString assetTriggerCaterogy = assetTriggers[k].category();
                if(!assetTriggersCaterogies.contains(assetTriggerCaterogy))
                {
                    assetTriggersCaterogies.append(assetTriggerCaterogy);
                    assetTriggersCaterogiesItems.append(addTreeItem(assetTriggerCaterogy, assetItem));
                }
            }

            for(int k = 0; k < assetTriggers.length(); k++)
            {
                int assetTriggerCaterogyItemIndex = assetTriggersCaterogies.indexOf(assetTriggers[k].category());
                QTreeWidgetItem *assetTriggerCaterogyItem = assetTriggersCaterogiesItems[assetTriggerCaterogyItemIndex];
                addTreeItem(assetTriggers[k].action(), assetTriggerCaterogyItem);
            }
       }
    }
}

QTreeWidgetItem *TriggerDialog::addTreeItem(const QString &name, const QIcon &icon, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item;
    if(parent != 0)
    {
        item = new QTreeWidgetItem(parent);
    }
    else
    {
        item = new QTreeWidgetItem(ui->treeWidget);
    }

    item->setText(0, name);
    item->setIcon(0, icon);

    return item;
}

QTreeWidgetItem* TriggerDialog::addTreeItem(const QString &name, QTreeWidgetItem* parent)
{
    return addTreeItem(name, QIcon(), parent);
}
