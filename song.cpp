#include "song.h"

Song::Song(QObject *parent) : QObject(parent)
{

}

Song::Song(const Song &song) : QObject()
{
    *this = song;
}

void Song::operator =(const Song &song)
{
    *this = song;
}

QDebug operator <<(QDebug debug, const Song &song)
{
    const QJsonValue &data = song.getData();

    debug << data;

    return debug;
}
