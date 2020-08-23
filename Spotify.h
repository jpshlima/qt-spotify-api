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
    QString get_token();
    /*void search_track();
    void add_track();
    void remove_track();
    void show_my_playlists();
    void add_playlist();
    void remove_playlist();
    void play_track();
    */



private slots:


   void onFinish(QNetworkReply*);


private:
    QString token;
    QNetworkAccessManager *manager;
    /*QJsonArray search_result;
    QArrayData playlists;
    */

};

#endif // SPOTIFY_H
