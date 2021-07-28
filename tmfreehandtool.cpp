
#include "tmfreehandtool.h"

TMFreeHandTool::TMFreeHandTool()
{    
    oldX=0;
    oldY=0;
    currentX=0;
    currentY=0;
    width=0;
    height=0;
    distanceFromXYToOldX=0;
    distanceFromXYToOldY=0;
    brushSize=1;
    borderColor="black";
    tmlc=nullptr;
    selected=false;
    points=nullptr;
    componentNameByUser="Free Hand Tool";
}

void TMFreeHandTool::draw(QPainter *painter)
{
//    painter->setPen(QPen(QBrush(QColor(this->borderColor)),this->brushSize));
    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        tmLineComponent->draw(painter);
    }
    if(points!=nullptr && selected==true)
    {
        QPen pen(QPen(QBrush(QColor("")),1));
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(this->oldX,this->oldY,this->width,this->height);
        this->points->draw(painter);
    }
}

QString TMFreeHandTool::toString()
{
    return "Free Hand Tool";
}

QString TMFreeHandTool::getComponentNameByUser()
{
    return this->componentNameByUser;
}

void TMFreeHandTool::setComponentNameByUser(QString text)
{
    this->componentNameByUser=text;
}

void TMFreeHandTool::select()
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

bool TMFreeHandTool::isOwnedByYou(int x, int y)
{
    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        if(tmLineComponent->isOwnedByYou(x,y))
        {
            return true;
        }
    }
    return false;
}

void TMFreeHandTool::setSelected(bool selection)
{
    this->selected=selection;
}

bool TMFreeHandTool::isSelected()
{
    return this->selected;
}

void TMFreeHandTool::setPointsToNull()
{
    delete this->points;
    this->points=nullptr;
}

int TMFreeHandTool::area()
{
    int area=this->width*this->height;
    if(area<0) area*=-1;
    return area;
}

void TMFreeHandTool::setDistanceFromXY(int x,int y)
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
    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        tmLineComponent->setDistanceFromXY(x,y);
    }
}

void TMFreeHandTool::setDefaultDistanceFromXY()
{
    this->distanceFromXYToOldX=0;
    this->distanceFromXYToOldY=0;
}

void TMFreeHandTool::drag(int x,int y)
{
    this->oldX=x-this->distanceFromXYToOldX;
    this->oldY=y-this->distanceFromXYToOldY;
    this->currentX=this->oldX+this->width;
    this->currentY=this->oldY+this->height;
    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        tmLineComponent->drag(x,y);
    }
}

void TMFreeHandTool::toJsonComponent(QJsonObject *component)
{
    component->insert("componentName","Free Hand Tool");
    component->insert("componentNameByUser",this->componentNameByUser);
    component->insert("oldX",this->oldX);
    component->insert("oldY",this->oldY);
    component->insert("currentX",this->currentX);
    component->insert("currentY",this->currentY);
    component->insert("width",this->width);
    component->insert("height",this->height);
    component->insert("brushSize",this->brushSize);
    component->insert("borderColor",this->borderColor);

    QJsonArray jsonComponents;
    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        QJsonObject component;
        tmLineComponent->toJsonComponent(&component);
        jsonComponents.push_front(component);
    }
    component->insert("tmlc",jsonComponents);

}

DrawableComponent * TMFreeHandTool::toTMFreeHandTool(QJsonValue jsonValue)
{
    TMFreeHandTool *component=new TMFreeHandTool;
    component->componentNameByUser=jsonValue["componentNameByUser"].toString();
    component->oldX=jsonValue["oldX"].toInt();
    component->oldY=jsonValue["oldY"].toInt();
    component->currentX=jsonValue["currentX"].toInt();
    component->currentY=jsonValue["currentY"].toInt();
    component->width=jsonValue["width"].toInt();
    component->height=jsonValue["height"].toInt();
    component->brushSize=jsonValue["brushSize"].toInt();
    component->borderColor=jsonValue["borderColor"].toString();

    component->tmlc=new QList<TMLineComponent *>();
    for(QJsonValue jsonValue:jsonValue["tmlc"].toArray())
    {
        component->tmlc->push_front((TMLineComponent *)TMLineComponent::toTMLineComponent(jsonValue));
    }
    return component;
}

void TMFreeHandTool::setSelectionFrameForText()
{
    int smallestXCoordinate=this->tmlc->front()->currentX;
    int smallestYCoordinate=this->tmlc->front()->currentY;
    int largestXCoordinate=this->tmlc->front()->currentX;
    int largestYCoordinate=this->tmlc->front()->currentY;

    for(TMLineComponent *tmLineComponent:*this->tmlc)
    {
        if(smallestXCoordinate>tmLineComponent->oldX) smallestXCoordinate=tmLineComponent->oldX;
        if(smallestYCoordinate>tmLineComponent->oldY) smallestYCoordinate=tmLineComponent->oldY;
        if(largestXCoordinate<tmLineComponent->oldX) largestXCoordinate=tmLineComponent->oldX;
        if(largestYCoordinate<tmLineComponent->oldY) largestYCoordinate=tmLineComponent->oldY;
    }
    this->oldX=smallestXCoordinate;
    this->oldY=smallestYCoordinate;
    this->currentX=largestXCoordinate;
    this->currentY=largestYCoordinate;
    this->width=largestXCoordinate-smallestXCoordinate;
    this->height=largestYCoordinate-smallestYCoordinate;
}

void TMFreeHandTool::setOtherPropertiesOfTMLineComponent(TMLineComponent *tmLineComponent)
{
    int x,y;
    x=(tmLineComponent->currentX)-(tmLineComponent->oldX);
    y=(tmLineComponent->currentY)-(tmLineComponent->oldY);
    tmLineComponent->width=x;
    tmLineComponent->height=y;
    tmLineComponent->length=sqrt((x*x)+(y*y));
}

TMFreeHandTool::~TMFreeHandTool()
{
    for(TMLineComponent *tmLineComponent:*this->tmlc) delete tmLineComponent;
    delete this->tmlc;
    if(points!=nullptr) delete points;
}
