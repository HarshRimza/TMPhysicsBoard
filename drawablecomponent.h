#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include<QPainter>
#include<QtMath>
#include<QMessageBox>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonDocument>

class DrawableComponent
{
public:
    DrawableComponent();
    virtual void draw(QPainter *painter)=0;
    virtual void toJsonComponent(QJsonObject *component);
    virtual QString toString();
    virtual QString getComponentNameByUser();
    virtual void setComponentNameByUser(QString text);
    virtual ~DrawableComponent();
    virtual void select();
    virtual bool isOwnedByYou(int x,int y);
    virtual void setSelected(bool selection);
    virtual bool isSelected();
    virtual void setPointsToNull();
    virtual int area();
    virtual void setDistanceFromXY(int x,int y);
    virtual void setDefaultDistanceFromXY();
    virtual void drag(int x,int y);
    virtual bool isPointOnBorder(int x,int y);
    virtual void shapeChanged(int x,int y);
    virtual void setCoordinateNumberToDefault();
    virtual int getCoordinateNumber();
};

#endif // DRAWABLECOMPONENT_H
