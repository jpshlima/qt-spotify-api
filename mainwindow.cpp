#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include "clientid.h"
#include "Spotify.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , spotify()
{
    ui->setupUi(this);
    //Spotify spotify;
    spotify.login();
    /*QString authtoken = spotify->get_token();
    ui->teOutput->appendPlainText(authtoken);
    */
}


MainWindow::~MainWindow()
{
    delete ui;
    //delete spotify;
    //delete manager;
}

void MainWindow::on_pushButton_clicked()
{
    QString authtoken = spotify.get_token();
    ui->teOutput->appendPlainText(authtoken);
}
