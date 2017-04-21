#include "shelflistwidget.h"

ShelfListWidget::ShelfListWidget(QWidget *parent)
    : QListWidget(parent)
{

}

QMimeData *ShelfListWidget::mimeData(const QList<QListWidgetItem *> items) const
{
    // List should only contain one item, since selection is limited to only one item.
    QMimeData *mimeData = QListWidget::mimeData(items);
    int itemIndex = row(items.first());
    mimeData->setText(QString("databaseAsset%1").arg(itemIndex));
    return mimeData;
}

QStringList ShelfListWidget::mimeTypes() const
{
    return QListWidget::mimeTypes();
}
