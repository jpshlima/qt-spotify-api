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

    void setTrackName(QString);

    QString getTrackName();

    void setTrackAlbum(QString);

    QString getTrackAlbum();

    void setTrackPreview(QString);

    QString getTrackPreview();

    void setTrackArtist(QString);

    QString getTrackArtist();


private slots:



private:
    QString trackName;
    QString trackAlbum;
    QString trackArtist;
    QString trackPreview;

};


#endif // TRACK_H
