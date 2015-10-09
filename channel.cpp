#include "channel.h"

#include <QJsonObject>

Channel::Channel(QObject *parent) : QObject(parent)
{

}

Channel::Channel(const Channel &channel) : QObject(0)
{
    *this = channel;
}

void Channel::operator=(const Channel &channel)
{
    data = channel.jsonValue();
}

int Channel::id() const
{
    if (!data.isObject())
        return -1;

    QJsonValue value = data.toObject().value("channel_id");
    if (value.isString())
        return value.toString("-1").toInt();
    if (value.isDouble())
        return value.toDouble(-1);

    return -1;
}

int Channel::seq() const
{
    if (!data.isObject())
        return -1;

    QJsonValue value = data.toObject().value("seq_id");
    if (value.isDouble())
        return value.toDouble(-1);

    return -1;
}

QDebug operator<<(QDebug debug, const Channel &channel)
{
    const QJsonValue &data = channel.jsonValue();

    debug << data;

    return debug;
}
