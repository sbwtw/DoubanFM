#include "channelframe.h"
#include "channel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

ChannelFrame::ChannelFrame(QWidget *parent) :
    QFrame(parent)
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
    setWindowFlags(Qt::FramelessWindowHint);
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
        qDebug() << value;
    }
}


