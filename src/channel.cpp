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

void Channel::setId(const int id)
{
    setData("channel_id", id);
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

void Channel::setName(const QString &name)
{
    setData("name", name);
    qDebug() << "get name: " << getString("name");
}

const QString Channel::getString(const QString &key) const
{
    if (!data.isObject())
        return QString();

    const QJsonObject &obj = data.toObject();
    return obj.value(key).toString();
}

template<typename T>
void Channel::setData(const QString &key, const T &value)
{
    if (!data.isObject())
        data = QJsonObject();

    QJsonObject obj = data.toObject();
    obj[key] = value;

    qDebug() << obj;

    data = QJsonValue(obj);
}

QDebug operator<<(QDebug debug, const Channel &channel)
{
    const QJsonValue &data = channel.jsonValue();

    debug << data;

    return debug;
}
