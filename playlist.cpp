#include "playlist.h"
#include "track.h"


playlist::playlist()
{
    QString newPlaylist = "new_playlist";
    this->playlistName = newPlaylist;
    //allPlaylists.append();
}

playlist::~playlist()
{

}


void playlist::setPlaylistName(QString playlistName)
{
    this->playlistName = playlistName;
}


/*
QList<track> playlist::getPlaylist()
{
    return playlistTracks;
}

void playlist::addTrack(track selectedTrack)
{
    this->playlistTracks.append(selectedTrack);
}

void playlist::removeTrack(int index)
{
    this->playlistTracks.removeAt(index);
}
*/
