#ifndef CHANNELFRAME_H
#define CHANNELFRAME_H

#include "channel.h"

#include <QList>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QListView>
#include <QStringListModel>

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
    void channelChanged(const Channel &channel) const;

private:
    void loadChannelListFinish();
    void switchToChannel(const Channel &channel);

private:
    std::shared_ptr<QNetworkAccessManager> manager;

    QListView *m_channelView;
    QStringListModel *m_channelModel;

    Channel currentChannel;
    QList<Channel> channelList;
};

#endif // CHANNELFRAME_H
