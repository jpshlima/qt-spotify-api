#include "Spotify.h"
#include "clientid.h"
#include "track.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

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

QString Spotify::getToken()
{
    return token;
}


void Spotify::searchTrack()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // Inicia o processo para a request GET
    QUrl url("https://api.spotify.com/v1/search");
    // Vamos descrever os parametros da query GET
    QUrlQuery params;
    params.addQueryItem("q", "nada sera como antes");
    params.addQueryItem("type", "track");
    params.addQueryItem("limit", "10");
    url.setQuery(params);

    QNetworkRequest request(url);
    QByteArray header = "Bearer " + token.toUtf8();
    //qDebug() << header;
    request.setRawHeader("Accept", "application/json");

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", header);


    //qDebug() << url.toString();
    connect(manager, &QNetworkAccessManager::finished,this,&Spotify::trackSearched);
    QNetworkReply *reply = manager->get(request);
    //qDebug() << reply;

}

void Spotify::trackSearched(QNetworkReply* rep)
{
    /*
    if(rep->error() == QNetworkReply::NoError)
    {

        // check http status code
        int v = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if(v!=200)
        {
            abort();
            qDebug() << "bad request!";
        }
    }
    */
    // vamos ler o conteúdo da resposta da pesquisa GET
    QByteArray buffer = rep->readAll();
    //qDebug() << buffer;
    // transforma o que foi lido em QJSON object
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonObj = jsonDoc.object();
    //ui->teOutput->appendPlainText(buffer);
    //qDebug() << jsonReply;
    //this->searchResult() = jsonReply;
    // Vamos fazer o parsing do JSON obtido para objetos tracks
    //qDebug() << search;
    QJsonObject jsonObj2 = jsonObj["tracks"].toObject();
    //qDebug() << jsonObj;
    // Extrai o conteúdo em um array
    QJsonArray array = jsonObj2["items"].toArray();
    //qDebug() << array;

    //track track;
    QList<track> data;
    int i=0;
    int j=0;
    for(i=0; i<array.size(); i++)
    {
        track track;
        QJsonObject temp = array[i].toObject();
        QJsonObject albumInfo = temp["album"].toObject();
        QJsonArray artistArray = temp["artists"].toArray();
        for(j=0; j<artistArray.size(); j++)
        {
            QJsonObject artistInfo = artistArray[j].toObject();
            track.artist.append(artistInfo["name"].toString());
        }
        track.album = albumInfo["name"].toString();
        track.name = temp["name"].toString();
        track.id = temp["id"].toString();
        data.append(track);
    }
    //qDebug() << data[9].name;
    //qDebug() << data[9].id;
    //qDebug() << data[0].album;
    //qDebug() << data[8].artist;
    this->searchResult = data;



    //getTracksFromSearch(jsonObj);
}
/*
void Spotify::getTracksFromSearch(QJsonObject search)
{
    // Vamos fazer o parsing do JSON obtido para objetos tracks
    //qDebug() << search;
    QJsonObject jsonObj = search["tracks"].toObject();
    //qDebug() << jsonObj;
    // Extrai o conteúdo em um array
    QJsonArray array = jsonObj["items"].toArray();
    //qDebug() << array;

    //track track;
    QList<track> data;
    int i=0;
    int j=0;
    for(i=0; i<array.size(); i++)
    {
        track track;
        QJsonObject temp = array[i].toObject();
        QJsonObject albumInfo = temp["album"].toObject();
        QJsonArray artistArray = temp["artists"].toArray();
        for(j=0; j<artistArray.size(); j++)
        {
            QJsonObject artistInfo = artistArray[j].toObject();
            track.artist.append(artistInfo["name"].toString());
        }
        track.album = albumInfo["name"].toString();
        track.name = temp["name"].toString();
        track.id = temp["id"].toString();
        data.append(track);
    }
    //qDebug() << data[9].name;
    //qDebug() << data[9].id;
    //qDebug() << data[0].album;
    //qDebug() << data[8].artist;
    this->searchResult = data;
}
*/
QList<track> Spotify::getSearch()
{
    //searchTrack();
    //emit onFinish()
    return searchResult;
}
