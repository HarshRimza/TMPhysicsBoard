#include "drawablecomponent.h"

DrawableComponent::DrawableComponent()
{

}

QString DrawableComponent::toString()
{
    return "Drawable";
}

void DrawableComponent::select()
{}

bool DrawableComponent::isOwnedByYou(int x,int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return false;
}

void DrawableComponent::setSelected(bool selection)
{
    Q_UNUSED(selection);
}

bool DrawableComponent::isSelected()
{
    return false;
}

void DrawableComponent::setPointsToNull()
{
}

int DrawableComponent::area()
{
    return 0;
}

void DrawableComponent::setDistanceFromXY(int x,int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
}
void DrawableComponent::setDefaultDistanceFromXY()
{
}
void DrawableComponent::drag(int x,int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
}

void DrawableComponent::toJsonComponent(QJsonObject *component)
{
    Q_UNUSED(component);
}

bool DrawableComponent::isPointOnBorder(int x,int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return false;
}

void DrawableComponent::shapeChanged(int x,int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
}

void DrawableComponent::setCoordinateNumberToDefault()
{}

int DrawableComponent::getCoordinateNumber()
{
    return 0;
}

QString DrawableComponent::getComponentNameByUser()
{
    return "";
}

void DrawableComponent::setComponentNameByUser(const QString text)
{
    Q_UNUSED(text);
}

DrawableComponent::~DrawableComponent()
{

}
