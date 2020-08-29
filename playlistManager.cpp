#include "playlistManager.h"
#include "track.h"
#include "playlist.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

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

void playlistManager::savePlaylist(playlist playlist)
{
    // Pega o nome da playlist e define o nome do arquivo
    QString playlistName = playlist.getPlaylistName();
    QString filename = "./" + playlistName + ".json";

    // Cria um JSON array para receber as tracks
    QJsonArray tracks;

    // Loop para inserir as informações de cada track no array
    int i=0;
    for(i=0; i<playlist.getPlaylistTracks().size(); i++)
    {
        QJsonObject trackInfo;
        trackInfo.insert("name", playlist.getPlaylistTracks()[i].getTrackName());
        trackInfo.insert("album", playlist.getPlaylistTracks()[i].getTrackAlbum());
        trackInfo.insert("artist", playlist.getPlaylistTracks()[i].getTrackArtist());
        trackInfo.insert("id", playlist.getPlaylistTracks()[i].getTrackId());
        tracks.append(trackInfo);
    }

    // Cria um JSON object final, com array de tracks e nome da playlist
    QJsonObject myPlaylist;
    myPlaylist.insert("playlist name", playlistName);
    myPlaylist.insert("tracks", tracks);
    // Cria o JSON doc e formata
    QJsonDocument documento;
    documento.setObject(myPlaylist);
    QFile jsonFile(filename);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(documento.toJson(QJsonDocument::Indented));
    jsonFile.close();
    qDebug() << documento;
}
