#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QPaintEvent>
#include <QTimer>

#include "roomscene.h"

class RoomView : public QGraphicsView
{
    Q_OBJECT
public:
    RoomView(QWidget *parent = Q_NULLPTR);
    RoomView(RoomScene *scene, QWidget *parent = Q_NULLPTR);

    void loadRoom(const QWeakPointer<Room> &room, const QPixmap &roomRender);

    RoomScene *scene() const;

    void manualUpdate();

protected:
    void init();
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

protected slots:
    void updateMidButtonViewDrag();

private:
    RoomScene *m_scene;
    QTimer *m_midButtonViewDragTimer;
    QPoint m_midButtonViewDragSnapPos;
    QPoint m_mousePosition;
};

#endif // ROOMVIEW_H
