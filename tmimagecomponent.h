#ifndef TMIMAGECOMPONENT_H
#define TMIMAGECOMPONENT_H

#include<drawablecomponent.h>
#include<tmpointcomponent.h>
#include<QIcon>

class TMImageComponent:public DrawableComponent
{
public:
    int oldX,oldY,currentX,currentY;
    int width,height;
    int distanceFromXYToOldX,distanceFromXYToOldY;
    int coordinateNumber;
    QString componentNameByUser;
    QString imagePath;
    int brushSize;
    QString borderColor;
    bool selected;
    TMPointComponent *points;
    TMImageComponent();
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
    virtual void setDistanceFromXY(int x,int y) override;
    virtual void setDefaultDistanceFromXY() override;
    virtual void drag(int x,int y) override;
    void toJsonComponent(QJsonObject *component) override;
    static DrawableComponent * toTMImageComponent(QJsonValue jsonValue);
    bool isPointOnBorder(int x,int y) override;
    void shapeChanged(int x,int y) override;
    void setCoordinateNumberToDefault() override;
    int getCoordinateNumber() override;
    ~TMImageComponent();
};

#endif // TMIMAGECOMPONENT_H
