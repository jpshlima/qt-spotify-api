#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "track.h"

QT_BEGIN_NAMESPACE
namespace Ui { class playlist; }
QT_END_NAMESPACE


class playlist : public QObject
{
    Q_OBJECT

public:
    playlist(QString namePlaylist);
    ~playlist();
   //void getTrack(track);


private slots:



private:
    QString namePlaylist;
   // QArrayData playlistTracks;

};


#endif // PLAYLIST_H
