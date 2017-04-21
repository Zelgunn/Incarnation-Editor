#ifndef HANDLE_H
#define HANDLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QApplication>
#include <QPainter>

#include "User/Actions/roomhandletransformaction.h"
#include "User/useraction.h"

#include <QDebug>

enum HandleAnchor
{
    Right = 0,
    Bottom = 1,
    Left = 2,
    Top = 3
};

class Handle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Handle(const QPixmap &pixmap, const QPixmap &shadowPixmap, HandleAnchor anchor,QGraphicsItem *parent = Q_NULLPTR);
    void setLockX(bool lock);
    void setLockY(bool lock);

    void setTwinHandle(Handle *handle);
    Handle *getTwinHandle() const;
    bool hasTwin() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF center() const;
    void setCenter(const QPointF &point);
    void setCenter(qreal x, qreal y);

    QSizeF size() const;

    bool isMoving() const;

    QPointF getShadowPosition() const;

signals:
    void handleMoved();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void rotatePixmaps();

private:
    HandleAnchor m_anchor;
    bool m_lockX = false;
    bool m_lockY = false;
    Handle* m_twin;

    QPointF m_onMousePressPosition;
    bool m_moving = false;
    QPixmap m_shadowPixmap;
    QSizeF m_size;
};

#endif // HANDLE_H
