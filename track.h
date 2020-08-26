#ifndef TRACK_H
#define TRACK_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QObject>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class track; }
QT_END_NAMESPACE

class track
{


public:
    track();
    ~track();
    /*void getTrack(track);
    void setTrackName(QString);
    void setTrackAlbum(QString);
    void setTrackArtist(QString);
    void setTrackId(QString);
    */
    QString name;
    QString album;
    QByteArray artist;
    QString id;

private slots:



private:
    /*
    QString name;
    QString album;
    QString artist;
    QString id;
    */
};


#endif // TRACK_H
