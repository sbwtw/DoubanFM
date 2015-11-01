#include "song.h"

#include <QJsonObject>

Song::Song(QObject *parent) : QObject(parent)
{

}

Song::Song(const Song &song) : QObject()
{
    *this = song;
}

void Song::operator =(const Song &song)
{
    data = song.getData();
}

void Song::setLikeState(bool liked)
{
    if (!data.isObject())
        data = QJsonObject();

    QJsonObject obj = data.toObject();
    obj["like"] = liked ? 1 : 0;

    data = QJsonValue(obj);
}

int Song::getInt(const QString &key, const int def) const
{
    if (!data.isObject())
        return def;

    const QJsonObject &obj = data.toObject();
    return obj.value(key).toInt(def);
}

const QString Song::getString(const QString &key) const
{
    if (!data.isObject())
        return QString();

    const QJsonObject &obj = data.toObject();
    return obj.value(key).toString();
}

QDebug operator <<(QDebug debug, const Song &song)
{
    const QJsonValue &data = song.getData();

    debug << data;

    return debug;
}
