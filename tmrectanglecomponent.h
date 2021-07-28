#ifndef TMRECTANGLECOMPONENT_H
#define TMRECTANGLECOMPONENT_H

#include<drawablecomponent.h>
#include<tmpointcomponent.h>
class TMRectangleComponent : public DrawableComponent
{
public:
    int oldX,oldY,currentX,currentY,width,height;
    int coordinateNumber;
    QString componentNameByUser;
    int distanceFromXYToOldX;
    int distanceFromXYToOldY;
    int brushSize;
    QString color;
    QString borderColor;
    bool selected;
    TMPointComponent *points;
    TMRectangleComponent();
    void draw(QPainter *painter) override;
    QString toString() override;
    QString getComponentNameByUser() override;
    void setComponentNameByUser(QString text) override;
    void select() override;
    bool isOwnedByYou(int x,int y) override;
    void setSelected(bool selection) override;
    bool isSelected() override;
    void setPointsToNull() override;
    int area() override;
    void setDistanceFromXY(int x,int y) override;
    void setDefaultDistanceFromXY() override;
    void drag(int x,int y) override;
    void toJsonComponent(QJsonObject *component) override;
    static DrawableComponent * toTMRectangleComponent(QJsonValue jsonValue);
    bool isPointOnBorder(int x,int y) override;
    void shapeChanged(int x,int y) override;
    void setCoordinateNumberToDefault() override;
    int getCoordinateNumber() override;
    ~TMRectangleComponent();
};

#endif // TMRECTANGLECOMPONENT_H
