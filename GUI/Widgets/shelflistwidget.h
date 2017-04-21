#ifndef SHELFLISTWIDGET_H
#define SHELFLISTWIDGET_H

#include <QListWidget>
#include <QMimeData>
#include <QUrl>

#include "Projects/project.h"
#include "Projects/asset.h"

class ShelfListWidget : public QListWidget
{
public:
    ShelfListWidget(QWidget *parent = Q_NULLPTR);

protected:
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const;
    QStringList mimeTypes() const;
};

#endif // SHELFLISTWIDGET_H
