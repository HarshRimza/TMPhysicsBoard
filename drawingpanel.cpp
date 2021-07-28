#include "drawingpanel.h"

int DrawingPanel::brushSize=1;
int DrawingPanel::selectedComponent=0;
QString DrawingPanel::borderColor="black";
QString DrawingPanel::color="";

DrawingPanel::DrawingPanel(QWidget *parent):QFrame(parent)
{
    setGeometry(46,45,1559,951);
    setAttribute(Qt::WA_TranslucentBackground);
    radioButton=nullptr;
    model=new TMModel();
    flag=0;
    mousePressed=false;
    drawingStarted=false;
    drawLines=false;
    tmLineComponent=nullptr;
    tmRectangleComponent=nullptr;
    tmCircleComponent=nullptr;
    tmFreeHandTool=nullptr;
    tmImageComponent=nullptr;
    pixmap=QPixmap(1559,951);
    pixmap.fill(Qt::white);
    setAcceptDrops(true);
    setMouseTracking(true);
    update();
}

DrawingPanel::~DrawingPanel()
{
    delete this->radioButton;
    if(this->tmImageComponent!=nullptr) delete this->tmImageComponent;
    delete this->model;
}


void DrawingPanel::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    painter.begin(this);
    painter.drawPixmap(0,0,pixmap);
    if(drawLines)
    {
        painter.setPen(QPen(QBrush(Qt::lightGray),1));
        for(int height=60;height<940;height=height+40) painter.drawLine(10,height,1550,height);
    }
    painter.setRenderHint(QPainter::Antialiasing);
    if(mousePressed)
    {
        if(DrawingPanel::selectedComponent==1)
        {
            tmLineComponent->draw(&painter);
        }
        else if(DrawingPanel::selectedComponent==2)
        {
            tmRectangleComponent->draw(&painter);
        }
        else if(DrawingPanel::selectedComponent==3)
        {
            painter.drawLine(this->tmCircleComponent->oldX,this->tmCircleComponent->oldY,this->tmCircleComponent->currentX,this->tmCircleComponent->currentY);
            tmCircleComponent->draw(&painter);
        }
        else if(DrawingPanel::selectedComponent==4)
        {
            tmFreeHandTool->draw(&painter);
      }
        else if(DrawingPanel::selectedComponent==5)
        {
            pixmap.fill(Qt::white);
            this->model->draw(&pixmap);
        }
        else if(DrawingPanel::selectedComponent==6)
        {
            tmImageComponent->draw(&painter);
        }
        drawingStarted=true;
    }
    else if(drawingStarted)
    {
        pixmap.fill(Qt::white);
        this->model->draw(&pixmap);
        painter.drawPixmap(0,0,pixmap);
        if(drawLines)
        {
            painter.setPen(QPen(QBrush(Qt::lightGray),1));
            for(int height=60;height<940;height=height+40) painter.drawLine(10,height,1550,height);
        }
        flag=0;
    }
    painter.end();
}

void DrawingPanel::mousePressEvent(QMouseEvent *event)
{
    mousePressed=true;
    if(DrawingPanel::selectedComponent>=1 && DrawingPanel::selectedComponent<=4 && !(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)))
    {
        if(tmImageComponent!=nullptr)
        {
            delete tmImageComponent;
            tmImageComponent=nullptr;
        }
        if(this->model->components->length()!=0) this->model->removeAllSelection(false);
    }
    if(DrawingPanel::selectedComponent==1)
    {
        tmLineComponent=new TMLineComponent;
        tmLineComponent->oldX=event->x();
        tmLineComponent->oldY=event->y();
        tmLineComponent->currentX=event->x();
        tmLineComponent->currentY=event->y();
        tmLineComponent->brushSize=DrawingPanel::brushSize;
        tmLineComponent->borderColor=DrawingPanel::borderColor;
    }
    else if(DrawingPanel::selectedComponent==2)
    {
        tmRectangleComponent=new TMRectangleComponent;
        tmRectangleComponent->oldX=event->x();
        tmRectangleComponent->oldY=event->y();
        tmRectangleComponent->currentX=event->x();
        tmRectangleComponent->currentY=event->y();
        tmRectangleComponent->brushSize=DrawingPanel::brushSize;
        tmRectangleComponent->borderColor=DrawingPanel::borderColor;
        tmRectangleComponent->color=DrawingPanel::color;
    }
    else if(DrawingPanel::selectedComponent==3)
    {
        tmCircleComponent=new TMCircleComponent;
        tmCircleComponent->oldX=event->x();
        tmCircleComponent->oldY=event->y();
        tmCircleComponent->currentX=event->x();
        tmCircleComponent->currentY=event->y();
        tmCircleComponent->brushSize=DrawingPanel::brushSize;
        tmCircleComponent->borderColor=DrawingPanel::borderColor;
        tmCircleComponent->color=DrawingPanel::color;
    }
    else if(DrawingPanel::selectedComponent==4)
    {
        tmFreeHandTool=new TMFreeHandTool;
        tmFreeHandTool->tmlc=new QList<TMLineComponent *>();
        TMLineComponent *tmLineComponent=new TMLineComponent;
        tmLineComponent->oldX=event->x();
        tmLineComponent->oldY=event->y();
        tmLineComponent->currentX=event->x();
        tmLineComponent->currentY=event->y();
        tmLineComponent->brushSize=DrawingPanel::brushSize;
        tmLineComponent->borderColor=DrawingPanel::borderColor;
        tmFreeHandTool->tmlc->push_front(tmLineComponent);
    }
    else if(DrawingPanel::selectedComponent==5)
    {
        if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) this->model->processClick(event->x(),event->y(),true);
        else this->model->processClick(event->x(),event->y(),false);
    }
    else if(selectedComponent==6)
    {
        tmImageComponent->brushSize=DrawingPanel::brushSize;
        tmImageComponent->borderColor=DrawingPanel::borderColor;
        tmImageComponent->oldX=event->x();
        tmImageComponent->oldY=event->y();
        tmImageComponent->currentX=event->x();
        tmImageComponent->currentY=event->y();
    }
}

void DrawingPanel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type()==QEvent::MouseMove)
    {
        if(this->mousePressed==false && DrawingPanel::selectedComponent==5)
        {
            int x=event->x();
            int y=event->y();
            for(DrawableComponent *dc:*this->model->components)
            {
                if(dc->isPointOnBorder(x,y))
                {
                    setCursor(Qt::SizeAllCursor);
                    break;
                }
                else if(dc->isOwnedByYou(x,y))
                {
                    setCursor(Qt::PointingHandCursor);
                    break;
                }
                else setCursor(Qt::ArrowCursor);
            }
        }
        else if(DrawingPanel::selectedComponent==1 && mousePressed==true)
        {
            this->tmLineComponent->currentX=event->x();
            this->tmLineComponent->currentY=event->y();
        }
        else if(DrawingPanel::selectedComponent==2 && mousePressed==true)
        {
            this->tmRectangleComponent->currentX=event->x();
            this->tmRectangleComponent->currentY=event->y();
            tmRectangleComponent->width=(tmRectangleComponent->currentX)-(tmRectangleComponent->oldX);
            tmRectangleComponent->height=(tmRectangleComponent->currentY)-(tmRectangleComponent->oldY);
        }
        else if(DrawingPanel::selectedComponent==3 && mousePressed==true)
        {
            this->tmCircleComponent->currentX=event->x();
            this->tmCircleComponent->currentY=event->y();
            int x,y;
            x=(tmCircleComponent->currentX)-(tmCircleComponent->oldX);
            y=(tmCircleComponent->currentY)-(tmCircleComponent->oldY);
            tmCircleComponent->length=sqrt((x*x)+(y*y));
        }
        else if(DrawingPanel::selectedComponent==4 && mousePressed==true)
        {
            tmFreeHandTool->tmlc->front()->currentX=event->x();
            tmFreeHandTool->tmlc->front()->currentY=event->y();
            tmFreeHandTool->setOtherPropertiesOfTMLineComponent(tmFreeHandTool->tmlc->front());
            TMLineComponent *tmLineComponent=new TMLineComponent;
            tmFreeHandTool->tmlc->push_front(tmLineComponent);
            tmLineComponent->oldX=event->x();
            tmLineComponent->oldY=event->y();
            tmLineComponent->currentX=event->x();
            tmLineComponent->currentY=event->y();
            tmLineComponent->brushSize=DrawingPanel::brushSize;
            tmLineComponent->borderColor=DrawingPanel::borderColor;
        }
        else if(DrawingPanel::selectedComponent==5 && mousePressed==true)
        {
            for(DrawableComponent *drawableComponent:*this->model->groupedComponents)
            {
                if(!(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) && drawableComponent->getCoordinateNumber()!=0)
                {
                    drawableComponent->shapeChanged(event->x(),event->y());
                }
                drawableComponent->setPointsToNull();
                drawableComponent->setSelected(false);
                if(drawableComponent->getCoordinateNumber()==0) drawableComponent->drag(event->x(),event->y());
            }
        }
        else if(DrawingPanel::selectedComponent==6 && mousePressed==true)
        {
            this->tmImageComponent->currentX=event->x();
            this->tmImageComponent->currentY=event->y();
            tmImageComponent->width=(tmImageComponent->currentX)-(tmImageComponent->oldX);
            tmImageComponent->height=(tmImageComponent->currentY)-(tmImageComponent->oldY);
        }
    }
    update();
}

void DrawingPanel::mouseReleaseEvent(QMouseEvent *event)
{
    if(DrawingPanel::selectedComponent==1)
    {
        int x,y;
        tmLineComponent->currentX=event->x();
        tmLineComponent->currentY=event->y();
        x=(tmLineComponent->currentX)-(tmLineComponent->oldX);
        y=(tmLineComponent->currentY)-(tmLineComponent->oldY);
        tmLineComponent->width=x;
        tmLineComponent->height=y;
        tmLineComponent->length=sqrt((x*x)+(y*y));
        this->model->add(tmLineComponent);
        tmLineComponent=nullptr;
    }
    else if(DrawingPanel::selectedComponent==2)
    {
        tmRectangleComponent->width=(tmRectangleComponent->currentX)-(tmRectangleComponent->oldX);
        tmRectangleComponent->height=(tmRectangleComponent->currentY)-(tmRectangleComponent->oldY);
        this->model->add(tmRectangleComponent);
        tmRectangleComponent=nullptr;
    }
    else if(DrawingPanel::selectedComponent==3)
    {
        int x,y;
        x=(tmCircleComponent->currentX)-(tmCircleComponent->oldX);
        y=(tmCircleComponent->currentY)-(tmCircleComponent->oldY);
        tmCircleComponent->length=sqrt((x*x)+(y*y));
        tmCircleComponent->width=tmCircleComponent->currentX-tmCircleComponent->oldX;
        tmCircleComponent->height=tmCircleComponent->currentY-tmCircleComponent->oldY;
        this->model->add(tmCircleComponent);
        tmCircleComponent=nullptr;
    }
    else if(DrawingPanel::selectedComponent==4)
    {
        tmFreeHandTool->tmlc->front()->currentX=event->x();
        tmFreeHandTool->tmlc->front()->currentY=event->y();
        tmFreeHandTool->setOtherPropertiesOfTMLineComponent(tmFreeHandTool->tmlc->front());
        this->model->add(tmFreeHandTool);
        tmFreeHandTool->setSelectionFrameForText();
        tmFreeHandTool=nullptr;
    }
    else if(DrawingPanel::selectedComponent==5)
    {
        for(DrawableComponent *dc:*this->model->groupedComponents)
        {
            dc->select();
            dc->setSelected(true);
            dc->setCoordinateNumberToDefault();
            dc->setDefaultDistanceFromXY();
        }
    }
    else if(DrawingPanel::selectedComponent==6)
    {
        QString imagePath=tmImageComponent->imagePath;
        this->model->add(tmImageComponent);
        tmImageComponent=nullptr;
        tmImageComponent=new TMImageComponent;
        tmImageComponent->imagePath=imagePath;
    }
    mousePressed=false;
    update();
}

void DrawingPanel::dragEnterEvent(QDragEnterEvent *event)
{
    if(DrawingPanel::selectedComponent==5)
    {
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source()==this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
    }
}

void DrawingPanel::dragMoveEvent(QDragMoveEvent *event)
{
    if(DrawingPanel::selectedComponent==5)
    {
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if (event->source()==this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
    }
}
void DrawingPanel::dropEvent(QDropEvent *event)
{
    if (DrawingPanel::selectedComponent==5 && event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QLabel *selectedLabel=SymbolTray::getSelectedLabel();
        QList<QLabel *> *labels=SymbolTray::getLabels();
        int i=1;
        for(QLabel * label:*labels)
        {
            if(label==selectedLabel)
            {
                break;
            }
            ++i;
        }

        TMImageComponent *tmic=new TMImageComponent;
        tmic->imagePath=":images/"+QString::number(i)+".png";
        tmic->oldX=event->pos().x();
        tmic->oldY=event->pos().y();
        tmic->currentX=event->pos().x()+32;
        tmic->currentY=event->pos().y()+32;
        tmic->width=32;
        tmic->height=32;
        tmic->componentNameByUser="Sign";
        tmic->brushSize=1;
        tmic->borderColor="";
        this->model->add(tmic);
        this->update();
    }
    else
    {
        event->ignore();
    }
}

QJsonArray DrawingPanel::toJSON()
{
    QJsonArray jsonComponents;
    QJsonObject component;
    component.insert("drawLines",this->drawLines);
    jsonComponents=model->getJsonList();
    jsonComponents.push_front(component);
    return jsonComponents;
}

void DrawingPanel::fromJSON(QJsonValue jsonModel)
{
    QString componentName="";
    bool drawLines;
    this->drawingStarted=true;
    for(QJsonValue jsonValue:jsonModel.toArray())
    {
        drawLines=jsonValue["drawLines"].toBool();
        if(drawLines) this->drawLines=drawLines;
        componentName=jsonValue["componentName"].toString();
        if(componentName.compare("Line")==0)
        {
            model->add(TMLineComponent::toTMLineComponent(jsonValue));
        }
        else if(componentName.compare("Rectangle")==0)
        {
            model->add(TMRectangleComponent::toTMRectangleComponent(jsonValue));
        }
        else if(componentName.compare("Circle")==0)
        {
            model->add(TMCircleComponent::toTMCircleComponent(jsonValue));
        }
        else if(componentName.compare("Free Hand Tool")==0)
        {
            model->add(TMFreeHandTool::toTMFreeHandTool(jsonValue));
        }
        else if(componentName.compare("Image")==0)
        {
            model->add(TMImageComponent::toTMImageComponent(jsonValue));
        }
        else if(componentName.compare("Group")==0)
        {
            model->add(TMGroupComponent::toTMGroupComponent(jsonValue));
        }
    }
}
