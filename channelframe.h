#ifndef CHANNELFRAME_H
#define CHANNELFRAME_H

#include <QFrame>
#include <QNetworkAccessManager>

#include <memory>

class ChannelFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ChannelFrame(QWidget *parent = 0);

    void setNetworkAccessManager(const std::shared_ptr<QNetworkAccessManager> &namPtr) {manager = namPtr;}

public:
    void loadChannelList();

private:
    void loadChannelListFinish();

private:
    std::shared_ptr<QNetworkAccessManager> manager;
};

#endif // CHANNELFRAME_H
