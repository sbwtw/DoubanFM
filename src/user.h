#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QObject>
#include <QJsonValue>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0);
    User(const User &user);

    void operator=(const User &user);
    friend QDebug operator <<(QDebug debug, const User &user);

    inline void setData(const QJsonValue &jsonObj) {data = jsonObj;}
    inline QJsonValue getData() const {return data;}

    inline bool isLogined() const {return getInt("r") == 0;}
    inline const QString token() const {return getString("token");}
    inline const QString user_id() const {return getString("user_id");}
    inline const QString expire() const {return getString("expire");}

private:
    int getInt(const QString &key, const int def = -1) const;
    const QString getString(const QString &key, const QString &def = QString()) const;

private:
    QJsonValue data;
};

#endif // USER_H
