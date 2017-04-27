#ifndef PIT_H
#define PIT_H

#include <QSizeF>
#include <QDomElement>

class Pit
{
public:
    Pit();
    Pit(const QSizeF &dimensions);
    Pit(const QDomElement &elem);

    void toXML(QDomElement *pitElement);

    QSizeF dimensions() const;
    void setDimensions(const QSizeF &dimensions);

private:
    QSizeF m_dimensions;
};

#endif // PIT_H
