#include "tmlinecomponent.h"

TMLineComponent::TMLineComponent()
{
    oldX=0;
    oldY=0;
    currentX=0;
    currentY=0;
    width=0;
    height=0;
    length=0;
    selected=false;
    points=nullptr;
    brushSize=1;
    borderColor="black";
    componentNameByUser="Line";
    coordinateNumber=0;
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
}

void TMLineComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(QColor(this->borderColor)),this->brushSize));
    painter->drawLine(this->oldX,this->oldY,this->currentX,this->currentY);
    if(points!=nullptr && selected==true)
    {
        points->draw(painter);
    }
}

QString TMLineComponent::toString()
{
    return "Line";
}

QString TMLineComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMLineComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMLineComponent::select()
{
    if(this->isSelected()) return;
    this->points=new TMPointComponent;
    this->points->numberOfPoints=2;
    this->points->x=new int[2];
    this->points->y=new int[2];
    this->points->x[0]=this->oldX;
    this->points->x[1]=this->currentX;
    this->points->y[0]=this->oldY;
    this->points->y[1]=this->currentY;
    this->points->points=new QPoint[2];
    for(int i=0;i<2;i++)
    {
        this->points->points[i]=QPoint(this->points->x[i],this->points->y[i]);
    }
}

bool TMLineComponent::isOwnedByYou(int x, int y)
{
    int differenceX,differenceY,differenceCurrentX,differenceCurrentY;
    differenceX=x-(this->oldX);
    differenceCurrentX=(this->currentX)-x;
    differenceY=y-(this->oldY);
    differenceCurrentY=(this->currentY)-y;
    int length1=sqrt((differenceX*differenceX)+(differenceY*differenceY));
    int length2=sqrt((differenceCurrentX*differenceCurrentX)+(differenceCurrentY*differenceCurrentY));
    if(this->length!=(length1+length2)) return false;
    return true;
}

void TMLineComponent::setSelected(bool selection)
{
    this->selected=selection;
}

bool TMLineComponent::isSelected()
{
    return this->selected;
}

void TMLineComponent::setPointsToNull()
{
    delete this->points;
    this->points=nullptr;
}

int TMLineComponent::area()
{
    return this->length;
}

void TMLineComponent::setDistanceFromXY(int x,int y)
{
    int x1,y1;
    x1=x-oldX;
    y1=y-oldY;
    if(x1<0) x1*=-1;
    if(y1<0) y1*=-1;
    this->distanceFromXYToOldX=x1;
    this->distanceFromXYToOldY=y1;
    if(this->oldX<=x && this->oldY<=y) this->distanceFromXYToOldX*=1;
    else if(this->oldX>=x && this->oldY<=y) this->distanceFromXYToOldX*=-1;
    else if(this->oldX<=x && this->oldY>=y) this->distanceFromXYToOldY*=-1;
    else if(this->oldX>=x && this->oldY>=y)
    {
        this->distanceFromXYToOldX*=-1;
        this->distanceFromXYToOldY*=-1;
    }
}

void TMLineComponent::setDefaultDistanceFromXY()
{
    this->distanceFromXYToOldX=0;
    this->distanceFromXYToOldY=0;
}

void TMLineComponent::drag(int x,int y)
{
    this->oldX=x-this->distanceFromXYToOldX;
    this->oldY=y-this->distanceFromXYToOldY;
    this->currentX=this->oldX+this->width;
    this->currentY=this->oldY+this->height;
}

void TMLineComponent::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Line");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("oldX",this->oldX);
    component->insert("oldY",this->oldY);
    component->insert("currentX",this->currentX);
    component->insert("currentY",this->currentY);
    component->insert("length",this->length);
    component->insert("width",this->width);
    component->insert("height",this->height);
    component->insert("brushSize",this->brushSize);
    component->insert("borderColor",this->borderColor);
}

DrawableComponent * TMLineComponent::toTMLineComponent(QJsonValue jsonValue)
{
    TMLineComponent *component=new TMLineComponent;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->oldX=jsonValue["oldX"].toInt();
    component->oldY=jsonValue["oldY"].toInt();
    component->currentX=jsonValue["currentX"].toInt();
    component->currentY=jsonValue["currentY"].toInt();
    component->length=jsonValue["length"].toInt();
    component->width=jsonValue["width"].toInt();
    component->height=jsonValue["height"].toInt();
    component->brushSize=jsonValue["brushSize"].toInt();
    component->borderColor=jsonValue["borderColor"].toString();
    return component;
}

bool TMLineComponent::isPointOnBorder(int x,int y)
{
    if(this->oldX==x && this->oldY==y)
    {
        this->coordinateNumber=1;
        return true;
    }
    else if(x==this->currentX && y==this->currentY)
    {
        this->coordinateNumber=2;
        return true;
    }
    return false;
}
void TMLineComponent::shapeChanged(int x,int y)
{
    if(this->coordinateNumber==0) return;
    if(this->coordinateNumber==1)
    {
        this->oldX=x;
        this->oldY=y;
    }
    else if(this->coordinateNumber==2)
    {
        this->currentX=x;
        this->currentY=y;
    }
    this->width=(this->currentX)-(this->oldX);
    this->height=(this->currentY)-(this->oldY);
    this->length=sqrt((this->width*this->width)+(this->height*this->height));
}
void TMLineComponent::setCoordinateNumberToDefault()
{
    this->coordinateNumber=0;
}
int TMLineComponent::getCoordinateNumber()
{
    return this->coordinateNumber;
}

TMLineComponent::~TMLineComponent()
{
    if(points!=nullptr) delete points;
}
