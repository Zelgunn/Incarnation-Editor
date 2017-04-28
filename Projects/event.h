#ifndef EVENT_H
#define EVENT_H

#include <QtGlobal>
#include <QFlags>

class Event
{
public:
    enum Option
    {

        Repeated
    };
    Q_DECLARE_FLAGS(Options, Option)

    Event();

protected:
    Option m_option;
    qreal m_start;
    qreal m_duration;
    qreal m_period;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Event::Options)

#endif // EVENT_H
