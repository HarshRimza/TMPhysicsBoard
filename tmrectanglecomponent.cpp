#include "tmrectanglecomponent.h"

TMRectangleComponent::TMRectangleComponent()
{
    oldX=0;
    oldY=0;
    currentX=0;
    currentY=0;
    width=0;
    height=0;
    selected=false;
    points=nullptr;
    brushSize=1;
    borderColor="black";
    color="";
    componentNameByUser="Rectangle";
    coordinateNumber=0;
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
}

void TMRectangleComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(QColor(this->borderColor)),this->brushSize));
    if(this->color.length()!=0)painter->fillRect(this->oldX,this->oldY,this->width,this->height,this->color);
    painter->drawRect(this->oldX,this->oldY,this->width,this->height);
    if(points!=nullptr && selected==true)
    {
        points->draw(painter);
    }
}

QString TMRectangleComponent::toString()
{
    return "Rectangle";
}

QString TMRectangleComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMRectangleComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMRectangleComponent::select()
{
    if(this->isSelected()) return;
    this->points=new TMPointComponent;
    this->points->numberOfPoints=4;
    this->points->x=new int[4];
    this->points->y=new int[4];
    this->points->x[0]=this->oldX;
    this->points->x[1]=this->currentX;
    this->points->x[2]=this->oldX;
    this->points->x[3]=this->currentX;

    this->points->y[0]=this->oldY;
    this->points->y[1]=this->oldY;
    this->points->y[2]=this->currentY;
    this->points->y[3]=this->currentY;
    this->points->points=new QPoint[4];
    for(int i=0;i<4;++i)
    {
        this->points->points[i]=QPoint(this->points->x[i],this->points->y[i]);
    }
}

bool TMRectangleComponent::isOwnedByYou(int x, int y)
{
    int diffx,diffy,diffcurrx,diffcurry;
    diffx=x-(this->oldX);
    diffcurrx=(this->currentX)-x;
    diffy=y-(this->oldY);
    diffcurry=(this->currentY)-y;
    if(diffx<0) diffx*=-1;
    if(diffcurrx<0) diffcurrx*=-1;
    if(diffy<0) diffy*=-1;
    if(diffcurry<0) diffcurry*=-1;
    int width=diffx+diffcurrx;
    int height=diffy+diffcurry;
    if(this->width<0) width*=-1;
    if(this->height<0) height*=-1;
    if(width!=this->width || height!=this->height) return false;
    return true;
}

void TMRectangleComponent::setSelected(bool selection)
{
    this->selected=selection;
}

bool TMRectangleComponent::isSelected()
{
    return this->selected;
}

void TMRectangleComponent::setPointsToNull()
{
    delete this->points;
    this->points=nullptr;
}

int TMRectangleComponent::area()
{
    int area=this->width*this->height;
    if(area<0) area*=-1;
    return area;
}

void TMRectangleComponent::setDistanceFromXY(int x,int y)
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

void TMRectangleComponent::setDefaultDistanceFromXY()
{
    this->distanceFromXYToOldX=0;
    this->distanceFromXYToOldY=0;
}

void TMRectangleComponent::drag(int x,int y)
{
    this->oldX=x-this->distanceFromXYToOldX;
    this->oldY=y-this->distanceFromXYToOldY;
    this->currentX=this->oldX+this->width;
    this->currentY=this->oldY+this->height;
}

void TMRectangleComponent::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Rectangle");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("oldX",this->oldX);
    component->insert("oldY",this->oldY);
    component->insert("currentX",this->currentX);
    component->insert("currentY",this->currentY);
    component->insert("width",this->width);
    component->insert("height",this->height);
    component->insert("brushSize",this->brushSize);
    component->insert("color",this->color);
    component->insert("borderColor",this->borderColor);
}

DrawableComponent * TMRectangleComponent::toTMRectangleComponent(QJsonValue jsonValue)
{
    TMRectangleComponent *component=new TMRectangleComponent;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->oldX=jsonValue["oldX"].toInt();
    component->oldY=jsonValue["oldY"].toInt();
    component->currentX=jsonValue["currentX"].toInt();
    component->currentY=jsonValue["currentY"].toInt();
    component->width=jsonValue["width"].toInt();
    component->height=jsonValue["height"].toInt();
    component->brushSize=jsonValue["brushSize"].toInt();
    component->color=jsonValue["color"].toString();
    component->borderColor=jsonValue["borderColor"].toString();
    return component;
}

bool TMRectangleComponent::isPointOnBorder(int x,int y)
{
    if(x==this->oldX && ((y>=this->oldY && y<=this->currentY)|| (y>=this->currentY && y<=this->oldY)))
    {
        this->coordinateNumber=1;
        return true;
    }
    else if(x==this->currentX && ((y>=this->oldY && y<=this->currentY)|| (y>=this->currentY && y<=this->oldY)))
    {
        this->coordinateNumber=3;
        return true;
    }
    else if(y==this->oldY && ((x>=this->oldX && x<=this->currentX)||(x>=this->currentX && x<=this->oldX)))
    {
        this->coordinateNumber=2;
        return true;
    }
    else if(y==this->currentY && ((x>=this->oldX && x<=this->currentX) || (x>=this->currentX && x<=this->oldX)))
    {
        this->coordinateNumber=4;
        return true;
    }
    return false;
}

void TMRectangleComponent::shapeChanged(int x,int y)
{
    if(this->coordinateNumber==0) return;
    if(this->coordinateNumber==1) this->oldX=x;
    else if(this->coordinateNumber==2) this->oldY=y;
    else if(this->coordinateNumber==3) this->currentX=x;
    else if(this->coordinateNumber==4) this->currentY=y;
    this->width=(this->currentX)-(this->oldX);
    this->height=(this->currentY)-(this->oldY);
}

void TMRectangleComponent::setCoordinateNumberToDefault()
{
    this->coordinateNumber=0;
}

int TMRectangleComponent::getCoordinateNumber()
{
    return this->coordinateNumber;
}

TMRectangleComponent::~TMRectangleComponent()
{
    if(points!=nullptr) delete points;
}
