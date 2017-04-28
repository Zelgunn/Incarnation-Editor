#ifndef EVENT_H
#define EVENT_H

#include <QDomElement>
#include <QWeakPointer>
#include <QColor>

#include "trigger.h"

class Event
{
public:
    Event(const QString &name, const qreal &start = 0, const qreal &duration = -1, const qreal &period = -1);
    Event(const QDomElement &eventElem);
    void toXML(QDomElement *eventElem);
    void linkToTriggers(const QList<QWeakPointer<Trigger>> &triggers);

    QStringList triggersIDs() const;
    void setTriggersIDs(const QList<QString> &triggersIDs);

    QString name() const;
    void setName(const QString &name);

    qreal start() const;
    void setStart(const qreal &start);

    qreal duration() const;
    void setDuration(const qreal &duration);

    qreal period() const;
    void setPeriod(const qreal &period);

    QColor color() const;
    void setColor(const QColor &color);

protected:
    QString m_name;
    qreal m_start = 0;
    qreal m_duration = -1;
    qreal m_period = -1;

    QStringList m_triggersIDs;
    QList<QWeakPointer<Trigger>> m_triggers;

    QColor m_color;
};

#endif // EVENT_H
