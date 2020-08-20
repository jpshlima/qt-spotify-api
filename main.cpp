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


/*QString base64_encode(QString string){
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //std::cout << "Hello World!" << std::endl;
    w.show();

    /*QString CLIENT_ID = "88445adec2f04d558527c52d9f8688ac";
    QString CLIENT_SECRET = "35d431ce698849e8b675034c586e8f2a";
    QString BASE_URL = "https://api.spotify.com/";
    QString secret = CLIENT_ID + ":" + CLIENT_SECRET;
    qDebug().nospace() << secret;

    QString encoded_secret = base64_encode(secret);
    qDebug().nospace() << encoded_secret;


    // Inicializa o network manager
    QNetworkAccessManager *manager = new QNetworkAccessManager();

   // Vamos configurar a request
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.spotify.com/token/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   // Agora o conteudo do body da request
   QByteArray jsonString = "{\"Authorization\":\"Basic ODg0NDVhZGVjMmYwNGQ1NTg1MjdjNTJkOWY4Njg4YWM6MzVkNDMxY2U2OTg4NDllOGI2NzUwMzRjNTg2ZThmMmE=\":\"grant_type\":\"client_credentials\"}";
   // Content-lenght
   QByteArray postDataSize = QByteArray::number(jsonString.size());
   // Adiciona ao header o tamanho do body
   request.setHeader(QNetworkRequest::ContentLengthHeader, postDataSize);



    QNetworkReply *reply = manager->get(request);
    qDebug() << reply;*/

    return a.exec();
    //return 0;
}
