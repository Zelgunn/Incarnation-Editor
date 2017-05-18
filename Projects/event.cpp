#include "event.h"

Event::Event(const QString &name, const qreal &start, const qreal &duration, const qreal &period)
    : m_name(name), m_start(start), m_duration(duration), m_period(period)
{

}

Event::Event(const QDomElement &eventElem)
{
    m_name = eventElem.attribute("name", "Nameless event");
    m_start = eventElem.attribute("start", "0").toFloat();
    m_duration = eventElem.attribute("duration", "-1").toFloat();
    m_period = eventElem.attribute("period", "-1").toFloat();
    m_color = QColor(eventElem.attribute("color", "#FF0000"));

    QString triggersIDs = eventElem.attribute("triggersIDs");
    m_triggersIDs = triggersIDs.split(',');
}

void Event::toXML(QDomElement *eventElem)
{
    eventElem->setAttribute("name", m_name);
    eventElem->setAttribute("start", m_start);
    eventElem->setAttribute("duration", m_duration);
    eventElem->setAttribute("period", m_period);
    eventElem->setAttribute("color", m_color.name());

    QString triggersIDs = "";
    for(int i = 0; i < m_triggersIDs.length(); i++)
    {
        if(i != 0) triggersIDs.append(',');
        triggersIDs.append(m_triggersIDs[i]);
    }
    eventElem->setAttribute("triggersIDs", triggersIDs);
}

void Event::linkToTriggers(const QList<QWeakPointer<Trigger> > &triggers)
{
    m_triggers = triggers;
}

QStringList Event::triggersIDs() const
{
    return m_triggersIDs;
}

void Event::setTriggersIDs(const QList<QString> &triggersIDs)
{
    m_triggersIDs = triggersIDs;
}

QString Event::name() const
{
    return m_name;
}

void Event::setName(const QString &name)
{
    m_name = name;
}

qreal Event::start() const
{
    return m_start;
}

void Event::setStart(const qreal &start)
{
    m_start = start;
}

qreal Event::duration() const
{
    return m_duration;
}

void Event::setDuration(const qreal &duration)
{
    m_duration = duration;
    if((m_duration >= 0) && (m_duration <= MIN_EVENT_DURATION))
    {
        m_duration = MIN_EVENT_DURATION;
    }
}

bool Event::isPunctual() const
{
    return m_duration < 0;
}

qreal Event::period() const
{
    return m_period;
}

void Event::setPeriod(const qreal &period)
{
    m_period = period;
}

QColor Event::color() const
{
    return m_color;
}

void Event::setColor(const QColor &color)
{
    m_color = color;
}
