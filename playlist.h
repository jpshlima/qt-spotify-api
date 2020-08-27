#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "track.h"

QT_BEGIN_NAMESPACE
namespace Ui { class playlist; }
QT_END_NAMESPACE


class playlist
{


public:
    playlist();
    ~playlist();
    void addTrack(track);
    void removeTrack(int);
    void setPlaylistName(QString);
    //QList<track> getPlaylist();

    QList<track> playlistTracks;
    QString getPlaylistName();

private slots:



private:
    QString playlistName;


};


#endif // PLAYLIST_H
