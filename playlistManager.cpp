#include "playlistManager.h"
#include "track.h"
#include "playlist.h"

void playlistManager::appendPlaylist(playlist playlist)
{
    allPlaylists.append(playlist);
}

