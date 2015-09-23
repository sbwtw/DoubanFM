#ifndef SONG_H
#define SONG_H

#include <QJsonObject>

class Song
{
public:
    Song(const QJsonObject& json);

    const QString albumtitle() const;
    const QString url() const;
    const QString picture() const;
    const QString artist() const;
    const QString public_time() const;
    const QString title() const;

private:
    QJsonObject m_songInfo;
};

#endif // SONG_H
