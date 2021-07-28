#ifndef TMMODEL_H
#define TMMODEL_H

#include<QList>
#include<QListWidget>
#include<drawablecomponent.h>
#include<tmlinecomponent.h>
#include<tmrectanglecomponent.h>
#include<tmcirclecomponent.h>
#include<tmfreehandtool.h>
#include<tmgroupcomponent.h>
#include<QMessageBox>
#include<QJsonArray>

class TMModel
{
public:
    TMModel();
    QList<DrawableComponent *> *removedComponents;
    QList<DrawableComponent *> *components;
    QList<DrawableComponent *> *groupedComponents;
    QListWidget *componentPanel;
    void draw(QPixmap *drawingPanel);
    void add(DrawableComponent *drawableComponent);
    void addSelectedComponentsToGroupedComponents(int x,int y);
    void processClick(int x,int y,bool ctrlPressed);
    void showComponents();
    void removeAllSelection(bool ctrlPressed);
    void createGroup();
    void unGroup();
    void redo();
    void undo();
    void deleteComponent();
    QJsonArray getJsonList();
    ~TMModel();
};

#endif // TMMODEL_H
