#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QtGlobal>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include "clientid.h"
//#include "Spotify.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //std::cout << "Hello World!" << std::endl;
    w.show();

    return a.exec();
    //return 0;
}
