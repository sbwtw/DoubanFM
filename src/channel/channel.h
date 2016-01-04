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

    void setId(const int id);
    int id() const;
    int seq() const;
    void setName(const QString &name);
    inline const QString name() const {return getString("name");}
    inline void setData(const QJsonValue &jsonObj) {data = jsonObj;}
    inline QJsonValue jsonValue() const {return data;}

private:
    const QString getString(const QString &key) const;
    template<typename T>
    void setData(const QString &key, const T &value);

private:
    QJsonValue data;
};

#endif // CHANNEL_H
