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

private:
    QJsonValue data;
};

#endif // SONG_H
