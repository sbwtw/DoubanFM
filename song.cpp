#include "song.h"

Song::Song(const QJsonObject &json)
{
    m_songInfo = json;
}

const QString Song::albumtitle() const
{
    return m_songInfo["albumtitle"].toString();
}

const QString Song::url() const
{
    return m_songInfo["url"].toString();
}

const QString Song::picture() const
{
    return m_songInfo["picture"].toString();
}

const QString Song::artist() const
{
    return m_songInfo["artist"].toString();
}

const QString Song::public_time() const
{
    return m_songInfo["public_time"].toString();
}

const QString Song::title() const
{
    return m_songInfo["title"].toString();
}
