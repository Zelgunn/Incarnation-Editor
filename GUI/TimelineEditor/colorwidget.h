#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include <QColor>
#include <QColorDialog>
#include <QPainter>

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    ColorWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    QColor color() const;
    void setColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    QColor m_color;
};

#endif // COLORWIDGET_H
