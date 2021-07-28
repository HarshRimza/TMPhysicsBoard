#ifndef TMPOINTCOMPONENT_H
#define TMPOINTCOMPONENT_H

#include<drawablecomponent.h>
#include<QMessageBox>

class TMPointComponent : public DrawableComponent
{
public:
    int *x,*y,numberOfPoints;
    QString componentNameByUser;
    QPoint *points;
    TMPointComponent();
    void draw(QPainter *painter) override;
    QString toString() override;
    QString getComponentNameByUser() override;
    void setComponentNameByUser(QString text) override;
    ~TMPointComponent();
};

#endif // TMPOINTCOMPONENT_H
