#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include<QPainter>
#include<QFrame>
#include<QPaintEvent>
#include<tmmodel.h>
#include<tmlinecomponent.h>
#include<tmrectanglecomponent.h>
#include<tmcirclecomponent.h>
#include<tmfreehandtool.h>
#include<tmpointcomponent.h>
#include<tmimagecomponent.h>
#include<tmgroupcomponent.h>
#include<QMessageBox>
#include<QListWidget>
#include<QtMath>
#include<QApplication>
#include<symboltray.h>
#include<QRadioButton>

class DrawingPanel:public QFrame
{
public:
    DrawingPanel(QWidget *);
    int flag;
    bool mousePressed;
    bool drawingStarted;
    bool drawLines;
    static int brushSize;
    static int selectedComponent;
    static QString color;
    static QString borderColor;
    QRadioButton *radioButton;
    TMModel *model;
    TMLineComponent *tmLineComponent;
    TMRectangleComponent *tmRectangleComponent;
    TMCircleComponent *tmCircleComponent;
    TMFreeHandTool *tmFreeHandTool;
    TMImageComponent *tmImageComponent;
    QPainter painter;
    QPixmap pixmap;
    ~DrawingPanel();
    QJsonArray toJSON();
    void fromJSON(QJsonValue jsonModel);
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // DRAWINGPANEL_H
