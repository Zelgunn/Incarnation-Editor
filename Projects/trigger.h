#ifndef TRIGGER_H
#define TRIGGER_H

#include <QDomElement>

class Trigger
{
public:
    Trigger(const QDomElement &triggerElem);
    void toXML(QDomElement *triggerElem) const;

    QString id() const;
    void setId(const QString &id);

private:
    QString m_id;
    bool m_usesDuration;
};

#endif // TRIGGER_H
