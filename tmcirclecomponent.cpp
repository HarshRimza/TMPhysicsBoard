#include "tmcirclecomponent.h"

TMCircleComponent::TMCircleComponent()
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
    color="";
    borderColor="black";
    componentNameByUser="Circle";
    coordinateNumber=0;
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
}

void TMCircleComponent::circlePoints(int xc,int yc,int x,int y,QPainter *painter)
{
    if(x==0)
    {
        painter->drawPoint(xc,yc+y);
        painter->drawPoint(xc,yc-y);
        painter->drawPoint(xc+y,yc);
        painter->drawPoint(xc-y,yc);
    }
    else if(x==y)
    {
        painter->drawPoint(xc+x,yc+y);
        painter->drawPoint(xc-x,yc+y);
        painter->drawPoint(xc+x,yc-y);
        painter->drawPoint(xc-x,yc-y);
    }
    else if(x<y)
    {
        painter->drawPoint(xc+x,yc+y);
        painter->drawPoint(xc-x,yc+y);
        painter->drawPoint(xc+x,yc-y);
        painter->drawPoint(xc-x,yc-y);
        painter->drawPoint(xc+y,yc+x);
        painter->drawPoint(xc-y,yc+x);
        painter->drawPoint(xc+y,yc-x);
        painter->drawPoint(xc-y,yc-x);
    }
}

void TMCircleComponent::fillCircle(int xc,int yc,int x,int y,QPainter *painter)
{
    if(x==0)
    {
        painter->drawLine(xc,yc,xc,yc+y);
        painter->drawLine(xc,yc,xc,yc-y);
        painter->drawLine(xc,yc,xc+y,yc);
        painter->drawLine(xc,yc,xc-y,yc);
    }
    else if(x==y)
    {
        painter->drawLine(xc,yc,xc+x,yc+y);
        painter->drawLine(xc,yc,xc-x,yc+y);
        painter->drawLine(xc,yc,xc+x,yc-y);
        painter->drawLine(xc,yc,xc-x,yc-y);
    }
    else if(x<y)
    {
        painter->drawLine(xc,yc,xc+x,yc+y);
        painter->drawLine(xc,yc,xc-x,yc+y);
        painter->drawLine(xc,yc,xc+x,yc-y);
        painter->drawLine(xc,yc,xc-x,yc-y);
        painter->drawLine(xc,yc,xc+y,yc+x);
        painter->drawLine(xc,yc,xc-y,yc+x);
        painter->drawLine(xc,yc,xc+y,yc-x);
        painter->drawLine(xc,yc,xc-y,yc-x);
    }
}
void TMCircleComponent::drawCircle(int xc,int yc,int r, QPainter *painter)
{
    int x=0;
    int y=r;
    int p=(5-r*4)/4;
    if(this->color.length()!=0)
    {
        painter->setPen(QPen(QBrush(QColor(this->color)),this->brushSize));
        while(x<y)
        {
            x++;
            if(p<0)
            {
                p+=2*x+1;
            }
            else
            {
                y--;
                p+=2*(x-y)+1;
            }
            fillCircle(xc,yc,x,y,painter);
        }
        painter->drawLine(xc,yc,xc,(yc+r));
        painter->drawLine(xc,yc,xc-r,yc);
        painter->drawLine(xc,yc,xc,yc-r);
        painter->drawLine(xc,yc,xc+r,yc);
    }

    painter->setPen(QPen(QBrush(QColor(this->borderColor)),this->brushSize));
    x=0;
    y=r;
    p=(5-r*4)/4;
    while(x<y)
    {
        x++;
        if(p<0)
        {
            p+=2*x+1;
        }
        else
        {
            y--;
            p+=2*(x-y)+1;
        }
        circlePoints(xc,yc,x,y,painter);
    }
    painter->drawPoint(xc,(yc+r));
    painter->drawPoint(xc-r,yc);
    painter->drawPoint(xc,yc-r);
    painter->drawPoint(xc+r,yc);

}

void TMCircleComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QBrush(QColor(this->borderColor)),this->brushSize));
    drawCircle(this->oldX,this->oldY,this->length,painter);
    if(this->points!=nullptr)
    {
        this->points->draw(painter);
    }
}


QString TMCircleComponent::toString()
{
    return "Circle";
}

QString TMCircleComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMCircleComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMCircleComponent::select()
{
    if(this->isSelected()) return;
    this->points=new TMPointComponent;
    this->points->numberOfPoints=4;
    this->points->x=new int[4];
    this->points->y=new int[4];
    this->points->x[0]=this->oldX;
    this->points->x[1]=this->oldX-this->length;
    this->points->x[2]=this->oldX;
    this->points->x[3]=this->oldX+this->length;

    this->points->y[0]=this->oldY+this->length;
    this->points->y[1]=this->oldY;
    this->points->y[2]=this->oldY-this->length;
    this->points->y[3]=this->oldY;
    this->points->points=new QPoint[4];
    for(int i=0;i<4;i++)
    {
        this->points->points[i]=QPoint(this->points->x[i],this->points->y[i]);
    }
}

bool TMCircleComponent::isOwnedByYou(int x, int y)
{
    int diffx,diffy;
    diffx=x-(this->oldX);
    diffy=y-(this->oldY);
    if(diffx<0) diffx*=-1;
    if(diffy<0) diffy*=-1;
    int length=sqrt((diffx*diffx)+(diffy*diffy));
    if(this->length<length) return false;
    return true;
}

void TMCircleComponent::setSelected(bool selection)
{
    this->selected=selection;
}

bool TMCircleComponent::isSelected()
{
    return this->selected;
}

void TMCircleComponent::setPointsToNull()
{
    delete this->points;
    this->points=nullptr;
}

int TMCircleComponent::area()
{
    float pi=3.14;
    return this->length*this->length*pi;
}

void TMCircleComponent::setDistanceFromXY(int x,int y)
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
void TMCircleComponent::setDefaultDistanceFromXY()
{
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
}
void TMCircleComponent::drag(int x,int y)
{
    this->oldX=x-this->distanceFromXYToOldX;
    this->oldY=y-this->distanceFromXYToOldY;
    this->currentX=this->oldX+this->width;
    this->currentY=this->oldY+this->height;
}

void TMCircleComponent::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Circle");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("oldX",this->oldX);
    component->insert("oldY",this->oldY);
    component->insert("currentX",this->currentX);
    component->insert("currentY",this->currentY);
    component->insert("length",this->length);
    component->insert("brushSize",this->brushSize);
    component->insert("color",this->color);
    component->insert("borderColor",this->borderColor);
}

DrawableComponent * TMCircleComponent::toTMCircleComponent(QJsonValue jsonValue)
{
    TMCircleComponent *component=new TMCircleComponent;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->oldX=jsonValue["oldX"].toInt();
    component->oldY=jsonValue["oldY"].toInt();
    component->currentX=jsonValue["currentX"].toInt();
    component->currentY=jsonValue["currentY"].toInt();
    component->length=jsonValue["length"].toInt();
    component->brushSize=jsonValue["brushSize"].toInt();
    component->color=jsonValue["color"].toString();
    component->borderColor=jsonValue["borderColor"].toString();
    return component;
}

bool TMCircleComponent::isPointOnBorder(int x,int y)
{
    if((this->oldX==x && this->oldY+this->length==y) || (this->oldX++==x && this->oldY+this->length==y) || (this->oldX--==x && this->oldY+this->length==y) || (this->oldX==x && this->oldY+this->length-1==y) || (this->oldX++==x && this->oldY+this->length-1==y) || (this->oldX--==x && this->oldY+this->length-1==y))
    {
        this->coordinateNumber=1;
        return true;
    }
    else if((this->oldX-this->length==x && this->oldY==y) ||
            (this->oldX-this->length==x && this->oldY--==y) ||
            (this->oldX-this->length==x && this->oldY++==y) ||
            (this->oldX-this->length+1==x && this->oldY==y) ||
            (this->oldX-this->length+1==x && this->oldY--==y) ||
            (this->oldX-this->length+1==x && this->oldY++==y))
    {
        this->coordinateNumber=2;
        return true;
    }
    else if((this->oldX==x && this->oldY-this->length==y)||
            (this->oldX--==x && this->oldY-this->length==y)||
            (this->oldX++==x && this->oldY-this->length==y)||
            (this->oldX==x && this->oldY-this->length+1==y)||
            (this->oldX--==x && this->oldY-this->length+1==y)||
            (this->oldX++==x && this->oldY-this->length+1==y))
    {
        this->coordinateNumber=3;
        return true;
    }
    else if((this->oldX+this->length==x && this->oldY==y)||
            (this->oldX+this->length==x && this->oldY--==y)||
            (this->oldX+this->length==x && this->oldY++==y)||
            (this->oldX+this->length+1==x && this->oldY==y)||
            (this->oldX+this->length+1==x && this->oldY--==y)||
            (this->oldX+this->length+1==x && this->oldY++==y))
    {
        this->coordinateNumber=4;
        return true;
    }
    return false;
}

void TMCircleComponent::shapeChanged(int x,int y)
{
    if(this->coordinateNumber==0) return;
    if(this->coordinateNumber>=1 && this->coordinateNumber<=4)
    {
        this->currentX=x;
        this->currentY=y;
    }
    this->width=(this->currentX)-(this->oldX);
    this->height=(this->currentY)-(this->oldY);
    this->length=sqrt((this->width*this->width)+(this->height*this->height));
}
void TMCircleComponent::setCoordinateNumberToDefault()
{
    this->coordinateNumber=0;
}
int TMCircleComponent::getCoordinateNumber()
{
    return this->coordinateNumber;
}

TMCircleComponent::~TMCircleComponent()
{
    if(points!=nullptr) delete points;
}
