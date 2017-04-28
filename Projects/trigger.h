#ifndef TRIGGER_H
#define TRIGGER_H

#include <QDomElement>

class Trigger
{
public:
    Trigger(const QDomElement &triggerElem);
    void toXML(QDomElement *triggerElem);

    QString id() const;
    void setId(const QString &id);

private:
    QString m_id;
};

#endif // TRIGGER_H
