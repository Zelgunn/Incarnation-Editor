#ifndef ASSETEDITIONDIALOG_H
#define ASSETEDITIONDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>

#include "Projects/asset.h"

namespace Ui {
class AssetEditionDialog;
}

class AssetEditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssetEditionDialog(const QWeakPointer<Asset> &asset, QWidget *parent = 0);
    ~AssetEditionDialog();

    Asset getAssetValues() const;

    void addSpinBox(const QString &name, int initialValue);
    void addDoubleSpinBox(const QString &name, qreal initialValue);

private:
    Ui::AssetEditionDialog *ui;
    Asset *m_asset = Q_NULLPTR;
    QList<QWidget *> m_customParametersWidgets;
};

#endif // ASSETEDITIONDIALOG_H
