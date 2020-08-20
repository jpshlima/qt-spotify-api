#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include "clientid.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
    //delete manager;

}


void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

        QUrl url("https://accounts.spotify.com/api/token");
        QNetworkRequest request(url);
        QString header = clientId + ":" + clientSecret;
        qDebug() << header;
        QByteArray ba;
        ba.append(header);
        //ui->teOutput->appendPlainText(ba.toBase64());
        QString secret = ba.toBase64();
        qDebug() << secret;
        QByteArray full_header= "Basic " + ba.toBase64();
        qDebug() << full_header;
        //ui->teOutput->appendPlainText(full_header);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        //request.setHeader(QNetworkRequest::ContentDispositionHeader, full_header);
        request.setRawHeader("Authorization", full_header);

        QUrlQuery params;
        params.addQueryItem("grant_type", "client_credentials");
        //params.addQueryItem("refresh_token", "here_is_my_refresh_token");

        QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinish(QNetworkReply*)));
        manager->post(request, params.query().toUtf8());


}

void MainWindow::onFinish(QNetworkReply* rep)
{
    QByteArray buffer = rep->readAll();
        qDebug() << buffer;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
        QJsonObject jsonReply = jsonDoc.object();
        qDebug() << jsonReply;

        QJsonValue access_token = jsonReply.value("access_token");
        qDebug() << access_token;

        //QJsonArray  data     = jsonReply["data"].toArray();
        //qDebug() << data;
        //qDebug() << response;
}
