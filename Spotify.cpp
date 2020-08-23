#include "Spotify.h"
#include "clientid.h"


#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>

Spotify::Spotify(){

    //spotify spotify;
};

Spotify::~Spotify()
{
    //delete token;
    delete manager;
}


void Spotify::login()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    this->manager = manager;
    QUrl url("https://accounts.spotify.com/api/token");
    QNetworkRequest request(url);
    QString header = clientId + ":" + clientSecret;
    //qDebug() << header;
    QByteArray ba;
    ba.append(header);
    //ui->teOutput->appendPlainText(ba.toBase64());
    QString secret = ba.toBase64();
    //qDebug() << secret;
    QByteArray full_header= "Basic " + ba.toBase64();
    //qDebug() << full_header;
    //ui->teOutput->appendPlainText(full_header);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    //request.setHeader(QNetworkRequest::ContentDispositionHeader, full_header);
    request.setRawHeader("Authorization", full_header);

    QUrlQuery params;
    params.addQueryItem("grant_type", "client_credentials");
    //params.addQueryItem("refresh_token", "here_is_my_refresh_token");

    connect(manager, &QNetworkAccessManager::finished, this, &Spotify::onFinish);
    manager->post(request, params.query().toUtf8());

}


void Spotify::onFinish(QNetworkReply* rep)
{
    // vamos ler o conteúdo da resposta do primeiro POST
    QByteArray buffer = rep->readAll();
    //qDebug() << buffer;
    // transforma o que foi lido em QJSON object
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();
    //ui->teOutput->appendPlainText(buffer);
    // obtem o token
    QJsonValue access_token = jsonReply.value("access_token");
    this->token = access_token.toString();
    //ui->teOutput->appendPlainText(token);
    //qDebug() << access_token;

}

QString Spotify::get_token()
{
    return token;
}
