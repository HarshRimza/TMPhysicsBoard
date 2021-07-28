#ifndef TMFREEHANDTOOL_H
#define TMFREEHANDTOOL_H

#include<drawablecomponent.h>
#include<tmpointcomponent.h>
#include<tmlinecomponent.h>
#include<QJsonArray>

class TMFreeHandTool : public DrawableComponent
{
public:
    int oldX,oldY;
    int currentX,currentY;
    int distanceFromXYToOldX;
    int distanceFromXYToOldY;
    int coordinateNumber;
    int width,height;
    bool selected;
    int brushSize;
    QString borderColor;
    TMPointComponent *points;
    QList <TMLineComponent *> *tmlc;
    QString componentNameByUser;
    TMFreeHandTool();
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
    static DrawableComponent * toTMFreeHandTool(QJsonValue jsonValue);
    void setSelectionFrameForText();
    void setOtherPropertiesOfTMLineComponent(TMLineComponent *tmLineComponent);
//    bool isPointOnBorder(int x,int y) override;
//    void shapeChanged(int x,int y) override;
//    void setCoordinateNumberToDefault() override;
//    int getCoordinateNumber() override;
    ~TMFreeHandTool();
};

#endif // TMFREEHANDTOOL_H
