#include "tmgroupcomponent.h"

TMGroupComponent::TMGroupComponent()
{
    group=nullptr;
    componentNameByUser="Group";
    selected=false;
    areaOfGroup=0;
}

void TMGroupComponent::draw(QPainter *painter)
{
    for(DrawableComponent *dc:*this->group) dc->draw(painter);
}

void TMGroupComponent::createGroup(QList<DrawableComponent *> *group)
{
    this->group=new QList<DrawableComponent *>();
    for(DrawableComponent *dc:*group)
    {
        this->group->append(dc);
    }

}

QString TMGroupComponent::toString()
{
    return "Group";
}

QString TMGroupComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMGroupComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMGroupComponent::select()
{
    if(this->isSelected()) return;
    for(DrawableComponent *dc:*this->group) dc->select();
}

bool TMGroupComponent::isOwnedByYou(int x,int y)
{
    for(DrawableComponent *dc:*this->group) if(dc->isOwnedByYou(x,y)) return true;
    return false;
}

void TMGroupComponent::setSelected(bool selection)
{
    for(DrawableComponent *dc:*this->group) dc->setSelected(selection);
    this->selected=selection;
}

bool TMGroupComponent::isSelected()
{
    return this->selected;
}

void TMGroupComponent::setPointsToNull()
{
    for(DrawableComponent *dc:*this->group) dc->setPointsToNull();
}

int TMGroupComponent::area()
{
    if(this->areaOfGroup!=0) return this->areaOfGroup;
    this->areaOfGroup=this->group->value(0)->area();
    for(DrawableComponent *dc:*this->group)
    {
        if(this->areaOfGroup<dc->area())
        {
            this->areaOfGroup=dc->area();
        }
    }
    return this->areaOfGroup;
}

void TMGroupComponent::setDistanceFromXY(int x,int y)
{
    for(DrawableComponent *dc:*this->group) dc->setDistanceFromXY(x,y);
}

void TMGroupComponent::setDefaultDistanceFromXY()
{
    for(DrawableComponent *dc:*this->group) dc->setDefaultDistanceFromXY();
}

void TMGroupComponent::drag(int x,int y)
{
for(DrawableComponent *dc:*this->group) dc->drag(x,y);
}

void TMGroupComponent::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Group");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("area",this->areaOfGroup);

    QJsonArray jsonComponents;
    for(DrawableComponent *drawableComponent:*this->group)
    {
        QJsonObject component;
        drawableComponent->toJsonComponent(&component);
        jsonComponents.append(component);
    }
    component->insert("group",jsonComponents);
}

DrawableComponent * TMGroupComponent::toTMGroupComponent(QJsonValue jsonValue)
{
    QString componentName="";
    TMGroupComponent *component=new TMGroupComponent;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->areaOfGroup=jsonValue["area"].toInt();
    component->group=new QList<DrawableComponent *>();
    for(QJsonValue jsonValue:jsonValue["group"].toArray())
    {
        componentName=jsonValue["componentName"].toString();
        if(componentName.compare("Line")==0)
        {
            component->group->append(TMLineComponent::toTMLineComponent(jsonValue));
        }
        else if(componentName.compare("Rectangle")==0)
        {
            component->group->append(TMRectangleComponent::toTMRectangleComponent(jsonValue));
        }
        else if(componentName.compare("Circle")==0)
        {
            component->group->append(TMCircleComponent::toTMCircleComponent(jsonValue));
        }
        else if(componentName.compare("Free Hand Tool")==0)
        {
            component->group->append(TMFreeHandTool::toTMFreeHandTool(jsonValue));
        }
        else if(componentName.compare("Image")==0)
        {
            component->group->append(TMImageComponent::toTMImageComponent(jsonValue));
        }
        else if(componentName.compare("Group")==0)
        {
            component->group->append(TMGroupComponent::toTMGroupComponent(jsonValue));
        }
    }
    return component;
}

TMGroupComponent::~TMGroupComponent()
{
    for(DrawableComponent *drawableComponent:*this->group) delete drawableComponent;
    delete this->group;
}
