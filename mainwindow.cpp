#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include "clientid.h"
#include "Spotify.h"
#include <QThread>


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

void MainWindow::on_iniciarButton_clicked()
{
    QString authtoken = spotify.getToken();
    //ui->teOutput->appendPlainText(authtoken);
}


void MainWindow::on_searchButton_clicked()
{
    QString searchInput;
    searchInput = ui->teOutput->toPlainText();
    qDebug() << searchInput;
    spotify.searchTrack(searchInput);
    //track track0 = searchResults.takeFirst();
    //qDebug() << track0.name;
    //QString trackname = track0.name;
    //ui->listWidget->addItem(trackname);
}


void MainWindow::on_showResultsButton_clicked()
{
    // Primeiro, limpa a listWidget
    ui->listWidget->clear();
    // Vamos mostrar o resultado da pesquisa na lista
    QList<track> results = spotify.getSearch();
    //qDebug() << results.isEmpty();
    // Varrer a QList obtida com um loop
    int i=0;
    for(i=0; i<results.size();i++)
    {
        QString trackname = results[i].name;
        QString trackalbum = results[i].album;
        QString trackartist = results[i].artist;
        //qDebug() << trackname;
        QString listItem = trackname + " | " + trackartist + " | " + trackalbum;
        ui->listWidget->addItem(listItem);
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui->listWidget->row(item);
    qDebug() << row;
    track selectedTrack = spotify.searchResult[row];
    qDebug() << selectedTrack.name;
}
