#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "track.h"
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class playlistManager; }
QT_END_NAMESPACE


class playlistManager
{

public:
    QList<playlist> allPlaylists;
    void appendPlaylist(playlist);
    void addTrackToPlaylist(track, int);
    void removeTrackFromPlaylist(int, int);
    //void renamePlaylist(QString, int);

private slots:

private:



};

#endif // PLAYLISTMANAGER_H
