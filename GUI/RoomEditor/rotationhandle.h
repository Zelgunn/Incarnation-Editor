#ifndef ROTATIONHANDLE_H
#define ROTATIONHANDLE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QPen>

#include <QDebug>

class RotationHandle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    RotationHandle(QGraphicsItem *parent = Q_NULLPTR);
    RotationHandle(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR);
    RotationHandle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR);

    QGraphicsItem *handledItem() const;
    void setHandledItem(QGraphicsItem *handledItem);
    void updatePos();

    qreal distanceToCenter() const;
    void setDistanceToCenter(const qreal &distanceToCenter);

protected:
    void init();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QGraphicsItem *m_handledItem = Q_NULLPTR;
    qreal m_distanceToCenter = 100;
};

#endif // ROTATIONHANDLE_H
