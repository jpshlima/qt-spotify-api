#ifndef SPOTIFY_H
#define SPOTIFY_H

//#include <QMainWindow>
#include <QNetworkAccessManager>
#include "track.h"
#include "playlist.h"
#include "playlistManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Spotify; }
QT_END_NAMESPACE

class Spotify : public QObject
{
    Q_OBJECT

public:
    Spotify();
    ~Spotify();
    void login();
    QString getToken();
    void searchTrack(QString);
    QList<track> getSearch();
    QList<track> searchResult;

private slots:

    void onFinish(QNetworkReply*);
    void trackSearched(QNetworkReply*);

private:
    QString token;
    QNetworkAccessManager *manager;

};

#endif // SPOTIFY_H
