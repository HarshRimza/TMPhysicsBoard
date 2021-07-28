#include "tmpointcomponent.h"

TMPointComponent::TMPointComponent()
{
    numberOfPoints=0;
    componentNameByUser="Points";
}

void TMPointComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(QColor(Qt::blue)),5));
    painter->drawPoints(points,numberOfPoints);
}

QString TMPointComponent::toString()
{
    return "Points";
}

QString TMPointComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMPointComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

TMPointComponent::~TMPointComponent()
{
    delete [] x;
    delete [] y;
    delete [] points;
}
