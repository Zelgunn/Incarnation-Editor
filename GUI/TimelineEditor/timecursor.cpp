#include "timecursor.h"

TimeCursor::TimeCursor(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setZValue(1);
    setAcceptedMouseButtons(Qt::NoButton);
}

QRectF TimeCursor::boundingRect() const
{
    qreal lwidth = qMax(- m_width / 2, - x());
    return QRectF(lwidth, 0, m_width + m_textWidth + m_textPadding, m_height);
}

void TimeCursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal rwidth = m_width / 2;
    qreal lwidth = qMax(- m_width / 2, - x());

    QPointF points[5];
    points[0] = QPointF(lwidth, 0);
    points[1] = QPointF(rwidth, 0);
    points[2] = QPointF(rwidth, m_headerHeight / 2);
    points[3] = QPointF(0, m_headerHeight);
    points[4] = QPointF(lwidth, m_headerHeight / 2);

    painter->setBrush(Qt::gray);
    painter->drawPolygon(points, 5);

    painter->drawLine(points[3], QPointF(0, m_height));

    QFontMetrics metrics(painter->font());
    qreal textWidth = metrics.width(m_timeText);

    QRectF textRect(rwidth + m_textPadding, m_textPadding / 2, textWidth, m_headerHeight - m_textPadding);
    QRectF textFrameRect(rwidth + m_textPadding / 2, m_textPadding / 2, textWidth + m_textPadding / 2, m_headerHeight - m_textPadding);
    painter->drawRect(textFrameRect);
    painter->drawText(textRect, m_timeText);
}

qreal TimeCursor::height() const
{
    return m_height;
}

void TimeCursor::setHeight(const qreal &height)
{
    m_height = height;
}

qreal TimeCursor::width() const
{
    return m_width;
}

void TimeCursor::setWidth(const qreal &width)
{
    m_width = width;
}

qreal TimeCursor::headerHeight() const
{
    return m_headerHeight;
}

void TimeCursor::setHeaderHeight(const qreal &headerHeight)
{
    m_headerHeight = headerHeight;
}

QString TimeCursor::timeText() const
{
    return m_timeText;
}

void TimeCursor::setTimeText(const QString &timeText)
{
    m_timeText = timeText;
}

qreal TimeCursor::textWidth() const
{
    return m_textWidth;
}

void TimeCursor::setTextWidth(const qreal &textWidth)
{
    m_textWidth = textWidth;
}

qreal TimeCursor::textPadding() const
{
    return m_textPadding;
}

void TimeCursor::setTextPadding(const qreal &textPadding)
{
    m_textPadding = textPadding;
}
