#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{

}

void ColorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));

    painter.drawRect(this->rect());
}

void ColorWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QColorDialog dialog;
    dialog.setCurrentColor(m_color);
    if(dialog.exec() == QDialog::Accepted)
    {
        m_color = dialog.selectedColor();
    }
}

QColor ColorWidget::color() const
{
    return m_color;
}

void ColorWidget::setColor(const QColor &color)
{
    m_color = color;
}
