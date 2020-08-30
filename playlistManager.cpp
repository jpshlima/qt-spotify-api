#include "playlistManager.h"
#include "track.h"
#include "playlist.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>


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
    // Vamos checar se essa playlist existe localmente para excluir também
    /*
     * QString filename = allPlaylists[playlistIndex].getPlaylistName() + ".json";
    QFile check(filename);
    if(check.exists())
    {
        QFile::moveToTrash foi implementada apenas no Qt 5.15.
    }*/
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
        trackInfo.insert("artists", playlist.getPlaylistTracks()[i].getTrackArtist());
        trackInfo.insert("preview_url", playlist.getPlaylistTracks()[i].getTrackPreview());
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

void playlistManager::loadPlaylists()
{
    // Obtem o path do diretorio atual
    QString path =  QDir::currentPath();
    // Cria um objeto Dir
    QDir dir(path);
    // Aplica filtros para pesquisar objetos .json
    // obs: as playlists são salvas em .json
    QStringList filters;
    filters << "*.json";
    dir.setNameFilters(filters);
    QStringList savedItems = dir.entryList();

    if(!savedItems.isEmpty())
    {
        // Para cada item encontrado, vamos criar uma playlist
        int i=0;
        int j=0;
        for(i=0; i<savedItems.size(); i++)
        {
            // Vamos ler o conteudo do arquivo
            QFile loadedFile(savedItems.at(i));
            loadedFile.open(QFile::ReadOnly);
            QByteArray fileContent = loadedFile.readAll();
            // Cria JSON objects para manipular o conteudo
            QJsonDocument jsonDoc(QJsonDocument::fromJson(fileContent));
            QJsonObject jsonObj = jsonDoc.object();
            // Extrai o nome da playlist e cria o objeto playlist
            QString playlistName = jsonObj["playlist name"].toString();
            playlist playlist;
            playlist.setPlaylistName(playlistName);

            // Vamos varrer um JSON array para extrair as tracks
            QJsonArray tracks = jsonObj["tracks"].toArray();
            for(j=0; j<tracks.size(); j++)
            {
                QJsonObject jsonTrack = tracks[j].toObject();
                track track;
                track.setTrackName(jsonTrack["name"].toString());
                track.setTrackAlbum(jsonTrack["album"].toString());
                track.setTrackPreview(jsonTrack["preview_url"].toString());
                track.setTrackArtist(jsonTrack["artists"].toString());
                playlist.addTrack(track);
            }
            allPlaylists.append(playlist);
        }
    }
}


