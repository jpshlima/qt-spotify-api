#include "playlist.h"
#include "track.h"


playlist::playlist()
{

}

playlist::~playlist()
{

}


void playlist::setPlaylistName(QString playlistName)
{
    this->playlistName = playlistName;
}

void playlist::addTrack(track selectedTrack)
{
    this->playlistTracks.append(selectedTrack);
}

void playlist::removeTrack(int index)
{
    this->playlistTracks.removeAt(index);
}

/*
QList<track> playlist::getPlaylist()
{
    return playlistTracks;
}




*/
