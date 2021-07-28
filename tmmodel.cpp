#include "tmmodel.h"

TMModel::TMModel()
{
    components=new QList<DrawableComponent *>();
    groupedComponents=new QList<DrawableComponent *>();
    removedComponents=new QList<DrawableComponent *>();
}

void TMModel::add(DrawableComponent *drawableComponent)
{
    this->components->push_front(drawableComponent);
    showComponents();
}

void TMModel::addSelectedComponentsToGroupedComponents(int x,int y)
{
    this->groupedComponents->clear();
    for(DrawableComponent *dc:*components)
    {
        if(dc->isSelected())
        {
            this->groupedComponents->append(dc);
            dc->setDistanceFromXY(x,y);
        }
    }
}

void TMModel::draw(QPixmap *drawingPanel)
{
    QPainter painter;
    for(DrawableComponent *drawableComponent:*this->components)
    {
        painter.begin(drawingPanel);
        painter.setRenderHint(QPainter::Antialiasing);
        drawableComponent->draw(&painter);
        painter.end();
    }
}

void TMModel::processClick(int x, int y,bool ctrlPressed)
{
    DrawableComponent *drawableComponent=nullptr;
    bool componentSelected=false;
    int index=-1;
    int i=0;
    for(DrawableComponent *dc:*this->components)
    {
        if(dc->isSelected() && !ctrlPressed)
        {
            dc->setPointsToNull();
            dc->setSelected(false);
        }
        if(componentSelected && dc->isOwnedByYou(x,y))
        {
            if(drawableComponent->area()>=dc->area())
            {
                drawableComponent=dc;
                index=i;
            }
        }
        else
        {
            if(dc->isOwnedByYou(x,y))
            {
                componentSelected=true;
                drawableComponent=dc;
                index=i;
            }
        }
        ++i;
    }
    if(drawableComponent!=nullptr)
    {
        removeAllSelection(ctrlPressed);
        drawableComponent->select();
        drawableComponent->setSelected(true);
        drawableComponent->setDistanceFromXY(x,y);
        if(!ctrlPressed)
        {
            this->componentPanel->reset();
            drawableComponent->isPointOnBorder(x,y);
        }
        this->componentPanel->item(index)->setSelected(true);
        this->componentPanel->setCurrentRow(index);
    }
    else
    {
        removeAllSelection(ctrlPressed);
        if(!ctrlPressed) this->componentPanel->reset();
    }
    this->addSelectedComponentsToGroupedComponents(x,y);
}

void TMModel::showComponents()
{
    this->componentPanel->clear();
    int index=0;
    for(DrawableComponent *drawableComponent:*this->components)
    {
        this->componentPanel->addItem(drawableComponent->getComponentNameByUser());
        if(drawableComponent->isSelected())
        {
            this->componentPanel->item(index)->setSelected(true);
            this->componentPanel->setCurrentRow(index);
        }
        ++index;
    }
}

void TMModel::removeAllSelection(bool ctrlPressed)
{
    if(!ctrlPressed)
    {
        for(DrawableComponent *drawableComponent:*this->components)
        {
            if(drawableComponent->isSelected())
            {
                drawableComponent->setPointsToNull();
                drawableComponent->setSelected(false);
            }
        }
    }
}

void TMModel::createGroup()
{
    TMGroupComponent *tmGroupComponent=new TMGroupComponent;
    tmGroupComponent->createGroup(this->groupedComponents);
    for(DrawableComponent *dc:*this->groupedComponents)
    {
            this->components->removeOne(dc);
    }
    if(tmGroupComponent->group->length()!=0)
    {
        this->groupedComponents->clear();
        this->groupedComponents->append(tmGroupComponent);
        tmGroupComponent->setSelected(true);
        this->add(tmGroupComponent);
        this->componentPanel->item(0)->setSelected(true);
        this->componentPanel->setCurrentRow(0);
    }
}

void TMModel::unGroup()
{
    TMGroupComponent *tmGroupComponent=nullptr;
    QList<DrawableComponent *> *groupedComponents=new QList<DrawableComponent *>();
    for(DrawableComponent *dc: *this->groupedComponents)
    {
        if(dc->toString().compare("Group")==0)
        {
            tmGroupComponent=(TMGroupComponent *)dc;
            this->components->removeOne(tmGroupComponent);
            this->groupedComponents->removeOne(tmGroupComponent);
            for(DrawableComponent *drawableComponent:*tmGroupComponent->group)
            {
                this->add(drawableComponent);
                groupedComponents->append(drawableComponent);
            }
            tmGroupComponent->group->clear();
            tmGroupComponent=nullptr;
            delete dc;
        }
    }
    for(DrawableComponent *dc:*groupedComponents) this->groupedComponents->append(dc);
    delete groupedComponents;
}

QJsonArray TMModel::getJsonList()
{
    QJsonArray jsonComponents;
    for(DrawableComponent *drawableComponent:*this->components)
    {
        QJsonObject component;
        drawableComponent->toJsonComponent(&component);
        jsonComponents.push_front(component);
    }
    return jsonComponents;
}

void TMModel::redo()
{
    if(this->removedComponents->length()!=0)
    {
        this->add(this->removedComponents->front());
        this->removedComponents->removeFirst();
    }
}

void TMModel::undo()
{
    if(this->components->length()!=0)
    {
        this->removedComponents->push_front(this->components->front());
        this->components->removeFirst();
        this->showComponents();
    }
}

void TMModel::deleteComponent()
{
    for(DrawableComponent *dc:*this->groupedComponents)
    {
        this->groupedComponents->removeOne(dc);
        this->components->removeOne(dc);
        delete dc;
    }
    this->showComponents();
}

TMModel::~TMModel()
{
    for(DrawableComponent *drawableComponent:*this->components)
    {
        delete drawableComponent;
    }
    delete this->components;
    delete this->groupedComponents;
}
