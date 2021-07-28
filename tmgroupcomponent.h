#ifndef TMGROUPCOMPONENT_H
#define TMGROUPCOMPONENT_H

#include<QJsonArray>
#include<drawablecomponent.h>
#include<tmlinecomponent.h>
#include<tmcirclecomponent.h>
#include<tmfreehandtool.h>
#include<tmrectanglecomponent.h>
#include<tmimagecomponent.h>

class TMGroupComponent : public DrawableComponent
{
public:
    QList<DrawableComponent *> *group;
    QString componentNameByUser;
    bool selected;
    int areaOfGroup;
    TMGroupComponent();
    void draw(QPainter *painter) override;
    void createGroup(QList<DrawableComponent *> *components);
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
    static DrawableComponent * toTMGroupComponent(QJsonValue jsonValue);
    ~TMGroupComponent();
};

#endif // TMGROUPCOMPONENT_H
