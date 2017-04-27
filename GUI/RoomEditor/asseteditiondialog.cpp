#include "asseteditiondialog.h"
#include "ui_asseteditiondialog.h"

AssetEditionDialog::AssetEditionDialog(const QWeakPointer<Asset> &asset, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssetEditionDialog)
{
    ui->setupUi(this);

    m_asset = new Asset(*(asset.data()));

    ui->nameLineEdit->setText(m_asset->name());
    ui->posXSpinBox->setValue(m_asset->position().x());
    ui->posYSpinBox->setValue(m_asset->position().y());
    ui->posZSpinBox->setValue(m_asset->getZPosition());
    ui->rotationSpinBox->setValue(m_asset->getRotation());
    ui->scaleSpinBox->setValue(m_asset->getScale().x() * 100);


    QList<QVariant> assetParameters = m_asset->getParameters();

    if(assetParameters.length() == 0)
    {
        ui->customParamsBox->hide();
    }
    else
    {
        QList<QString> assetParametersNames = m_asset->getParametersNames();

        for(int i = 0; i < assetParameters.length(); i++)
        {
            QVariant parameter = assetParameters[i];

            switch (parameter.type())
            {
            case QVariant::Int:
                addSpinBox(assetParametersNames[i] + " :", parameter.toInt());
                break;
            case QVariant::Double:
                addDoubleSpinBox(assetParametersNames[i] + " :", parameter.toReal());
            default:
                break;
            }
        }
    }
}

AssetEditionDialog::~AssetEditionDialog()
{
    delete ui;
}

Asset AssetEditionDialog::getAssetValues() const
{
    m_asset->setName(ui->nameLineEdit->text());
    m_asset->setPosition(QPointF(ui->posXSpinBox->value(), ui->posYSpinBox->value()));
    m_asset->setZPosition(ui->posZSpinBox->value());
    m_asset->setRotation(ui->rotationSpinBox->value());
    m_asset->setScale(QPointF(1,1) * ui->scaleSpinBox->value() / 100);
    m_asset->setZScale(ui->scaleSpinBox->value() / 100);

    QList<QVariant> assetParameters = m_asset->getParameters();

    for(int i = 0; i < assetParameters.length(); i++)
    {
        QVariant parameter = assetParameters[i];
        QWidget *widget = m_customParametersWidgets[i];

        switch (parameter.type())
        {
        case QVariant::Int:
            parameter = ((QSpinBox *)widget)->value();
            break;
        case QVariant::Double:
            parameter = ((QDoubleSpinBox *)widget)->value();
            break;
        case QVariant::String:
            //
            break;
        default:
            break;
        }

        assetParameters[i] = parameter;
    }
    m_asset->setParameters(assetParameters);

    return *m_asset;
}

void AssetEditionDialog::addParamWidget(const QString &name, QWidget *widget)
{
    int index = ui->customParamsGrid->rowCount();

    ui->customParamsGrid->addWidget(new QLabel(name), index, 0, 1, 1);
    ui->customParamsGrid->addWidget(widget, index, 1, 1, 1);

    m_customParametersWidgets.append(widget);
}

void AssetEditionDialog::addSpinBox(const QString &name, int initialValue)
{
    QSpinBox *spinBox = new QSpinBox();
    spinBox->setValue(initialValue);

    addParamWidget(name, spinBox);
}

void AssetEditionDialog::addDoubleSpinBox(const QString &name, qreal initialValue)
{
    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox();
    doubleSpinBox->setValue(initialValue);

    addParamWidget(name, doubleSpinBox);
}

void AssetEditionDialog::addLineEdit(const QString &name, const QString &initialValue)
{
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setText(initialValue);

    addParamWidget(name, lineEdit);
}
