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
    QList<track> getPlaylistTracks();
    QString getPlaylistName();

private slots:



private:
    QString playlistName;
    QList<track> playlistTracks;

};


#endif // PLAYLIST_H
