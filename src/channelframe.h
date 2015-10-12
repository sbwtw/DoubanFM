#ifndef CHANNELFRAME_H
#define CHANNELFRAME_H

#include "channel.h"

#include <QList>
#include <QDialog>
#include <QNetworkAccessManager>

#include <memory>

class ChannelFrame : public QDialog
{
    Q_OBJECT

public:
    explicit ChannelFrame(QWidget *parent = 0);

    inline void setNetworkAccessManager(const std::shared_ptr<QNetworkAccessManager> &namPtr) {manager = namPtr;}
    inline const Channel &channel() const {return currentChannel;}

    void loadChannelList();

signals:
    void ChannelSelected(Channel &channel);

private:
    void loadChannelListFinish();

private:
    std::shared_ptr<QNetworkAccessManager> manager;

    Channel currentChannel;
    QList<Channel> channelList;
};

#endif // CHANNELFRAME_H
