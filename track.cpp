#include "track.h"

track::track()
{

}

track::~track()
{

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
    return this->trackArtist;
}

void track::setTrackPreview(QString trackPreview)
{
    this->trackPreview = trackPreview;
}

QString track::getTrackPreview()
{
    return this->trackPreview;
}

