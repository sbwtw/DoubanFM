#include "user.h"

#include <QJsonObject>

User::User(QObject *parent) : QObject(parent)
{

}

User::User(const User &user) : QObject()
{
    *this = user;
}

void User::operator=(const User &user)
{
    data = user.getData();
}

int User::getInt(const QString &key, int def) const
{
    if (!data.isObject())
        return def;

    const QJsonObject &obj = data.toObject();
    return obj.value(key).toInt(def);
}

const QString User::getString(const QString &key, const QString &def) const
{
    if (!data.isObject())
        return def;

    const QJsonObject &obj = data.toObject();
    return obj.value(key).toString(def);
}

QDebug operator <<(QDebug debug, const User &user)
{
    const QJsonValue &data = user.getData();

    debug << data;

    return debug;
}
