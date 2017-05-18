#ifndef TIMECURSOR_H
#define TIMECURSOR_H

#include <QGraphicsItem>
#include <QPainter>

class TimeCursor : public QGraphicsItem
{
public:
    TimeCursor(QGraphicsItem *parent = Q_NULLPTR);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    qreal height() const;
    void setHeight(const qreal &height);

    qreal width() const;
    void setWidth(const qreal &width);

    qreal headerHeight() const;
    void setHeaderHeight(const qreal &headerHeight);

    QString timeText() const;
    void setTimeText(const QString &timeText);

    qreal textWidth() const;
    void setTextWidth(const qreal &textWidth);

    qreal textPadding() const;
    void setTextPadding(const qreal &textPadding);

private:
    qreal m_height = 100;
    qreal m_headerHeight = 20;
    qreal m_width = 11;

    qreal m_textWidth = 100;
    qreal m_textPadding = 5;

    QString m_timeText = "00:00";
};

#endif // TIMECURSOR_H
