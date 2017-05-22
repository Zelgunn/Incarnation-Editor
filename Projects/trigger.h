#ifndef TRIGGER_H
#define TRIGGER_H

#include <QDomElement>

class Trigger
{
public:
    Trigger(const QDomElement &triggerElem);
    void toXML(QDomElement *triggerElem) const;

    int id() const;
    void setId(int id);

    QString action() const;
    void setAction(const QString &action);

    QString category() const;
    void setCategory(const QString &category);

private:
    int m_id;
    QString m_action;
    QString m_category;
};

#endif // TRIGGER_H
