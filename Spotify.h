#ifndef SPOTIFY_H
#define SPOTIFY_H

//#include <QMainWindow>
#include <QNetworkAccessManager>


QT_BEGIN_NAMESPACE
namespace Ui { class Spotify; }
QT_END_NAMESPACE

class Spotify : public QObject
{
    Q_OBJECT

public:
    Spotify();
    ~Spotify();
    //spotify(const spotify &other);
    void login();
    QString getToken();
    void searchTrack();
    void getTracksFromSearch(QJsonObject);
    /*void add_track();
    void remove_track();
    void show_my_playlists();
    void add_playlist();
    void remove_playlist();
    void play_track();
    */



private slots:

    void onFinish(QNetworkReply*);
    void trackSearched(QNetworkReply*);

private:
    QString token;
    QNetworkAccessManager *manager;
    //QJsonObject searchResult();
    /*QArrayData playlists;
    */

};

#endif // SPOTIFY_H
