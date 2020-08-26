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
    QString playlistName;
    QList<track> playlistTracks;

private slots:



private:



};


#endif // PLAYLIST_H
