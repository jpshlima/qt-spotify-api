#include "track.h"

track::track()
{

}

track::~track()
{
    //delete track;
}

void track::setTrackName(QString name)
{
    this->trackName = name;
}

QString track::getTrackName()
{
    return this->trackName;
}

void track::setTrackAlbum(QString album)
{
    this->trackAlbum = album;
}

QString track::getTrackAlbum()
{
    return this->trackAlbum;
}

void track::setTrackArtist(QString artist)
{
    this->trackArtist = artist;
}

QString track::getTrackArtist()
{
    /*QString artist;
    if(this->trackArtist.size()!=1)
    {
        artist = trackArtist.join(" + ");
    }
    else
    {
        artist = this->trackArtist.at(0);
    }*/
    return this->trackArtist;
}

void track::setTrackId(QString trackId)
{
    this->trackId = trackId;
}

QString track::getTrackId()
{
    return this->trackId;
}

