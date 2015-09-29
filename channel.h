#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QJsonValue>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QObject *parent = 0);

    inline void setData(const QJsonValue &jsonObj) {data = jsonObj;}
    inline QJsonValue getData() const {return data;}

private:
    QJsonValue data;
};

#endif // CHANNEL_H
