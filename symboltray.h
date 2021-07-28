#ifndef SYMBOLTRAY_H
#define SYMBOLTRAY_H

#include<QFrame>
#include<QtWidgets>
#include<QLabel>
#include<QList>


class SymbolTray:public QFrame
{
private:
    static QList <QLabel *> *labels;
    static QLabel * label;
public:
    SymbolTray(QWidget *);
    static QList<QLabel *> * getLabels();
    static QLabel * getSelectedLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // SYMBOLTRAY_H
