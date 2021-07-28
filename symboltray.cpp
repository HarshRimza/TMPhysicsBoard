#include "symboltray.h"

QList<QLabel *> * SymbolTray::labels;
QLabel * SymbolTray::label;

SymbolTray::SymbolTray(QWidget *parent):QFrame(parent)
{
    setGeometry(0,0,233,201);
    setAcceptDrops(true);
    setAttribute(Qt::WA_TranslucentBackground);
    labels=new QList<QLabel *>();
    QLabel *i1 ;
    QIcon *icon;
    int k=1;
    for(int i=0;i<6;++i)
    {
        for(int j=0;j<7 && k<=40;++j)
        {
            i1=new QLabel(this);
            i1->setFrameStyle(QFrame::Panel | QFrame::Plain);
            icon=new QIcon(":images/"+QString::number(k)+".png");
            i1->setPixmap(icon->pixmap(QSize(32,32)));
            i1->setGeometry(1+(33*j),1+(33*i),34,34);
            i1->setCursor(Qt::PointingHandCursor);
            labels->append(i1);
            k++;
        }
    }
}

void SymbolTray::mousePressEvent(QMouseEvent *event)
{
    QLabel *child=static_cast<QLabel*>(this->childAt(event->pos()));
    if(!child) return;
    label=child;
    QPixmap pixmap=*child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData,QIODevice::WriteOnly);
    dataStream<<pixmap<<QPoint(event->pos()-child->pos());

    QMimeData *mimeData=new QMimeData;
    mimeData->setData("application/x-dnditemdata",itemData);

    QDrag *drag=new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos()-child->pos());

    QPixmap tempPixmap=pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(),QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction,Qt::CopyAction)==Qt::MoveAction)
    {
        child->close();
    }
    else
    {
        child->show();
        child->setPixmap(pixmap);
    }
}

QList<QLabel*> * SymbolTray::getLabels()
{
    return labels;
}

QLabel * SymbolTray::getSelectedLabel()
{
    return label;
}
