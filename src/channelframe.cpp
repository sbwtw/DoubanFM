#include "channelframe.h"
#include "channel.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QNetworkReply>
#include <QNetworkRequest>

ChannelFrame::ChannelFrame(QWidget *parent) :
    QDialog(parent)
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(30.0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 4);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(new QLabel("asd"));
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(30, 26, 30, 34);

    setLayout(mainLayout);
    setFixedSize(305, 305);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    setStyleSheet("background-color:red;");
}

void ChannelFrame::loadChannelList()
{
    QUrl url("http://www.douban.com/j/app/radio/channels");
    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &ChannelFrame::loadChannelListFinish);
}

void ChannelFrame::loadChannelListFinish()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    const QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    if (!document.isObject())
        return;

    const QJsonObject &obj = document.object();
    const QJsonValue &value = obj.value("channels");
    if (!value.isArray())
        return;

    Channel channel;
    const QJsonArray &list = value.toArray();
    for (const QJsonValue &value : list) {
        channel.setData(value);
        channelList.append(channel);
    }

    // sort by seq_id and channel_id
    std::sort(channelList.begin(), channelList.end(), [] (const Channel &c1, const Channel &c2) {
        const int seq1 = c1.seq();
        const int seq2 = c2.seq();

        if (seq1 != seq2)
            return seq1 < seq2;
        return c1.id() < c2.id();
    });

    if (currentChannel.id() == -1) {
        currentChannel = channelList.first();
        emit ChannelSelected(currentChannel);
    }

//    for (const Channel &c : channelList)
//        qDebug() << c;
}


