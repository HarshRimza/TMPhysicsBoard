#include "mainwindow.h"

#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splashScreen;
    splashScreen.setPixmap(QPixmap(":images/splashScreen3.jpg"));
    splashScreen.show();
    MainWindow w;
    QTimer::singleShot(2500,&splashScreen,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));
    return a.exec();
}
