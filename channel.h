#ifndef CHANNEL_H
#define CHANNEL_H

#include <QDebug>
#include <QObject>
#include <QJsonValue>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);
    Channel(const Channel &channel);

    void operator=(const Channel &channel);

    friend QDebug operator<<(QDebug debug, const Channel &channel);

    int id() const;
    int seq() const;
    inline void setData(const QJsonValue &jsonObj) {data = jsonObj;}
    inline QJsonValue jsonValue() const {return data;}

private:
    QJsonValue data;
};

#endif // CHANNEL_H
