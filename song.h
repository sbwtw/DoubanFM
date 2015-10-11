#ifndef SONG_H
#define SONG_H

#include <QDebug>
#include <QObject>
#include <QJsonValue>

class Song : public QObject
{
    Q_OBJECT
public:
    Song(QObject *parent = 0);
    Song(const Song &song);

    void operator =(const Song &song);

    friend QDebug operator <<(QDebug debug, const Song &song);

    inline void setData(const QJsonValue &jsonObj) {data = jsonObj;}
    inline QJsonValue getData() const {return data;}

    inline const QString aid() const {return getString("aid");}
    inline const QString album() const {return getString("album");}
    inline const QString albumtitle() const {return getString("albumtitle");}
    inline const QString artist() const {return getString("artist");}
    inline const QString picture() const {return getString("picture");}
    inline const QString sha256() const {return getString("sha256");}
    inline const QString sid() const {return getString("sid");}
    inline const QString ssid() const {return getString("ssid");}
    inline const QString title() const {return getString("title");}
    inline const QString url() const {return getString("url");}

private:
    const QString getString(const QString &key) const;

private:
    QJsonValue data;
};

#endif // SONG_H
