#include "tmimagecomponent.h"

TMImageComponent::TMImageComponent()
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
    borderColor="";
    componentNameByUser="Image";
    imagePath="";
    coordinateNumber=0;
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
}

void TMImageComponent::draw(QPainter *painter)
{
    int x=this->oldX;
    int y=this->oldY;
    int width=this->width;
    int height=this->height;
    QImage image(this->imagePath);
    if(this->width<0)
    {
        width=this->width*-1;
        x=this->currentX;
    }
    if(this->height<0)
    {
        height=this->height*-1;
        y=this->currentY;
    }
    if(borderColor.length()!=0)painter->fillRect(QRect(x-this->brushSize,y-this->brushSize,width+(this->brushSize*2),height+(this->brushSize*2)),this->borderColor);
    painter->drawImage(QRect(x,y,width,height),image);
    if(points!=nullptr && selected==true)
    {
        QPen pen(QPen(QBrush(QColor("")),1));
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(--x,--y,width+2,height+2);
        points->draw(painter);
    }
}

QString TMImageComponent::toString()
{
    return "Image";
}

QString TMImageComponent::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMImageComponent::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMImageComponent::select()
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
    for(int i=0;i<4;i++)
    {
        this->points->points[i]=QPoint(this->points->x[i],this->points->y[i]);
    }
}

bool TMImageComponent::isOwnedByYou(int x, int y)
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

void TMImageComponent::setSelected(bool selection)
{
    this->selected=selection;
}

bool TMImageComponent::isSelected()
{
    return this->selected;
}

void TMImageComponent::setPointsToNull()
{
    delete this->points;
    this->points=nullptr;
}

int TMImageComponent::area()
{
    int area=this->width*this->height;
    if(area<0) area*=-1;
    return area;
}

void TMImageComponent::setDistanceFromXY(int x,int y)
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

void TMImageComponent::setDefaultDistanceFromXY()
{
    this->distanceFromXYToOldX=0;
    this->distanceFromXYToOldY=0;
}

void TMImageComponent::drag(int x,int y)
{
    this->oldX=x-this->distanceFromXYToOldX;
    this->oldY=y-this->distanceFromXYToOldY;
    this->currentX=this->oldX+this->width;
    this->currentY=this->oldY+this->height;
}

void TMImageComponent::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Image");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("imagePath",this->imagePath);
    component->insert("oldX",this->oldX);
    component->insert("oldY",this->oldY);
    component->insert("currentX",this->currentX);
    component->insert("currentY",this->currentY);
    component->insert("width",this->width);
    component->insert("height",this->height);
    component->insert("brushSize",this->brushSize);
    component->insert("borderColor",this->borderColor);
}

DrawableComponent * TMImageComponent::toTMImageComponent(QJsonValue jsonValue)
{
    TMImageComponent *component=new TMImageComponent;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->imagePath=jsonValue["imagePath"].toString();
    component->oldX=jsonValue["oldX"].toInt();
    component->oldY=jsonValue["oldY"].toInt();
    component->currentX=jsonValue["currentX"].toInt();
    component->currentY=jsonValue["currentY"].toInt();
    component->width=jsonValue["width"].toInt();
    component->height=jsonValue["height"].toInt();
    component->brushSize=jsonValue["brushSize"].toInt();
    component->borderColor=jsonValue["borderColor"].toString();
    return component;
}

bool TMImageComponent::isPointOnBorder(int x,int y)
{
    if((x==this->oldX) && ((y>=this->oldY && y<=this->currentY) || (y>=this->currentY && y<=this->oldY)))
    {
        this->coordinateNumber=1;
        return true;
    }
    else if((x==this->currentX) && ((y>=this->oldY && y<=this->currentY) || (y>=this->currentY && y<=this->oldY)))
    {
        this->coordinateNumber=3;
        return true;
    }
    else if((y==this->oldY) && ((x>=this->oldX && x<=this->currentX) || (x>=this->currentX && x<=this->oldY)))
    {
        this->coordinateNumber=2;
        return true;
    }
    else if((y==this->currentY) && ((x>=this->oldX && x<=this->currentX) || (x>=this->currentX && x<=this->oldY)))
    {
        this->coordinateNumber=4;
        return true;
    }
    return false;
}

void TMImageComponent::shapeChanged(int x,int y)
{
    if(this->coordinateNumber==0) return;
    if(this->coordinateNumber==1) this->oldX=x;
    else if(this->coordinateNumber==2) this->oldY=y;
    else if(this->coordinateNumber==3) this->currentX=x;
    else if(this->coordinateNumber==4) this->currentY=y;
    this->width=(this->currentX)-(this->oldX);
    this->height=(this->currentY)-(this->oldY);
}

void TMImageComponent::setCoordinateNumberToDefault()
{
    this->coordinateNumber=0;
}

int TMImageComponent::getCoordinateNumber()
{
    return this->coordinateNumber;
}

TMImageComponent::~TMImageComponent()
{
    if(points!=nullptr) delete points;
}



