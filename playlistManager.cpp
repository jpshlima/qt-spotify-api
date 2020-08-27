#include "playlistManager.h"
#include "track.h"
#include "playlist.h"

void playlistManager::appendPlaylist(playlist playlist)
{
    allPlaylists.append(playlist);
}

void playlistManager::addTrackToPlaylist(track track, int playlistIndex)
{
    allPlaylists[playlistIndex].addTrack(track);
}

void playlistManager::removeTrackFromPlaylist(int trackIndex, int playlistIndex)
{
    allPlaylists[playlistIndex].removeTrack(trackIndex);
}

/*void playlistManager::renamePlaylist(QString newName, int playlistIndex)
{
    allPlaylists[playlistIndex].setPlaylistName(newName);
}
*/
