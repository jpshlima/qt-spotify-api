#include "playlistManager.h"
#include "track.h"
#include "playlist.h"

void playlistManager::appendPlaylist(playlist playlist)
{
    allPlaylists.append(playlist);
}

void playlistManager::addTrackToPlaylist(track track, QString playlistName)
{
    // Recebemos o nome da playlist na qual será adicionada a track
    int i=0;
    for(i=0; i<allPlaylists.size(); i++)
    {
        if(playlistName == allPlaylists[i].getPlaylistName())
        {
            allPlaylists[i].addTrack(track);
        }
    }
}

void playlistManager::removeTrackFromPlaylist(int trackIndex, int playlistIndex)
{
    allPlaylists[playlistIndex].removeTrack(trackIndex);
}

void playlistManager::renamePlaylist(QString newName, int playlistIndex)
{
    allPlaylists[playlistIndex].setPlaylistName(newName);
}

void playlistManager::deletePlaylist(int playlistIndex)
{
    allPlaylists.removeAt(playlistIndex);
}

QStringList playlistManager::getAllPlaylistsNames()
{
    QStringList allPlaylistsNames;
    int i=0;
    for(i=0; i<this->allPlaylists.size();i++)
    {
        allPlaylistsNames.append(this->allPlaylists[i].getPlaylistName());
    }
    return allPlaylistsNames;
}

QList<playlist> playlistManager::getAllPlaylists()
{
    return this->allPlaylists;
}
