#ifndef TMCIRCLECOMPONENT_H
#define TMCIRCLECOMPONENT_H

#include<drawablecomponent.h>
#include<tmpointcomponent.h>
class TMCircleComponent : public DrawableComponent
{
public:
    int oldX,oldY,currentX,currentY,width,height,length;
    int coordinateNumber;
    QString componentNameByUser;
    int distanceFromXYToOldX;
    int distanceFromXYToOldY;
    bool selected;
    int brushSize;
    QString color;
    QString borderColor;
    TMPointComponent *points;
    TMCircleComponent();
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
    void fillCircle(int xc,int yc,int x,int y,QPainter *painter);
    void circlePoints(int xc,int yc,int x,int y,QPainter *painter);
    void drawCircle(int,int,int,QPainter *);
    void setDistanceFromXY(int x,int y) override;
    void setDefaultDistanceFromXY() override;
    void drag(int x,int y) override;
    void toJsonComponent(QJsonObject *component) override;
    static DrawableComponent * toTMCircleComponent(QJsonValue jsonValue);
    bool isPointOnBorder(int x,int y) override;
    void shapeChanged(int x,int y) override;
    void setCoordinateNumberToDefault() override;
    int getCoordinateNumber() override;
    ~TMCircleComponent();
};

#endif // TMCIRCLECOMPONENT_H
