#include "Spotify.h"
#include "clientid.h"
#include "track.h"
#include "playlist.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


Spotify::Spotify()
{

};

Spotify::~Spotify()
{
    delete manager;
}


void Spotify::login()
{
    // Faz uma HTTP POST request para obter o token

    // Configura a request
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    this->manager = manager;
    QUrl url("https://accounts.spotify.com/api/token");
    QNetworkRequest request(url);

    // Configura o header
    QString header = clientId + ":" + clientSecret;

    QByteArray ba;
    ba.append(header);
    QString secret = ba.toBase64();
    QByteArray full_header= "Basic " + ba.toBase64();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", full_header);

    // Configura a query
    QUrlQuery params;
    params.addQueryItem("grant_type", "client_credentials");

    // Faz a POST request e o connect
    connect(manager, &QNetworkAccessManager::finished, this, &Spotify::onFinish);
    manager->post(request, params.query().toUtf8());

}


void Spotify::onFinish(QNetworkReply* rep)
{
    // Vamos ler o conteúdo da resposta do primeiro POST
    QByteArray buffer = rep->readAll();

    // Transforma o que foi lido em QJSON object
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();

    // Obtem o token
    QJsonValue access_token = jsonReply.value("access_token");
    this->token = access_token.toString();
}

QString Spotify::getToken()
{
    return token;
}

void Spotify::searchTrack(QString searchInput)
{
    // Realiza uma HTTP GET request para buscar itens
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.spotify.com/v1/search");

    // Vamos descrever os parametros da query
    QUrlQuery params;
    params.addQueryItem("q", searchInput);
    params.addQueryItem("type", "track");
    // Especifica limit = 10 nessa fase de dev
    params.addQueryItem("limit", "10");
    url.setQuery(params);

    // Configura a request
    QNetworkRequest request(url);
    QByteArray header = "Bearer " + token.toUtf8();
    request.setRawHeader("Accept", "application/json");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", header);

    // Faz a GET request e o connect
    connect(manager, &QNetworkAccessManager::finished,this,&Spotify::trackSearched);
    manager->get(request);

}

void Spotify::trackSearched(QNetworkReply* rep)
{
    // Vamos ler o conteúdo da resposta da pesquisa GET
    QByteArray buffer = rep->readAll();

    // Transforma o que foi lido em QJSON object
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonObj = jsonDoc.object();

    // Vamos fazer o parsing do JSON obtido para objetos track
    QJsonObject jsonObj2 = jsonObj["tracks"].toObject();

    // Extrai o conteúdo em um array
    QJsonArray array = jsonObj2["items"].toArray();

    // Vamos criar uma QList com as tracks
    QList<track> data;
    int i=0;
    int j=0;
    for(i=0; i<array.size(); i++)
    {
        track track;
        QJsonObject temp = array[i].toObject();
        QJsonObject albumInfo = temp["album"].toObject();
        QJsonArray artistArray = temp["artists"].toArray();
        // Tem vez que o artista da track é um array
        QStringList artistName;
        // Varrendo o array de artistas
        for(j=0; j<artistArray.size(); j++)
        {
            QJsonObject artistInfo = artistArray[j].toObject();
            artistName.append(artistInfo["name"].toString());
        }
        QString artistNameString = artistName.join(" + ");
        track.setTrackArtist(artistNameString);
        track.setTrackAlbum(albumInfo["name"].toString());
        track.setTrackName(temp["name"].toString());
        track.setTrackPreview(temp["preview_url"].toString());
        data.append(track);
    }
    this->searchResult = data;
}

QList<track> Spotify::getSearch()
{
    return searchResult;
}


