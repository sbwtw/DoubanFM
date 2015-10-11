#include "lyricframe.h"

#include <QMoveEvent>
#include <QHBoxLayout>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

LyricFrame::LyricFrame() : QFrame(0)
{
    layric = new QLabel;
    layric->setText("Layric");
    layric->setStyleSheet("QLabel {"
                          "font-size:24px;"
                          "color:#a42727;"
                          "}");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(layric);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

//    shadowEffect = new QGraphicsDropShadowEffect(layric);
//    shadowEffect->setBlurRadius(10);
//    shadowEffect->setOffset(0, 0);
//    shadowEffect->setColor(Qt::cyan);
//    layric->setGraphicsEffect(shadowEffect);

    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(1);

    setLayout(mainLayout);
    setFixedSize(550, 50);
    setGraphicsEffect(opacityEffect);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
}

void LyricFrame::loadLyric(const Song &song)
{
    lyricsList.clear();
    nextLyricPos = 0;
    layric->setText(song.title() + " - " + song.artist());

    QUrl url("http://api.douban.com/v2/fm/lyric");
    QUrlQuery query;
    query.addQueryItem("ssid", song.ssid());
    query.addQueryItem("sid", song.sid());
    url.setQuery(query);
    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &LyricFrame::loadLyricFinish);
}

void LyricFrame::refreshLyric(qint64 msec)
{
    if (lyricsList.isEmpty() || nextLyricPos == lyricsList.count())
        return;

    if (lyricsList.at(nextLyricPos).start <= msec + lyricOffset) {
        layric->setText(lyricsList.at(nextLyricPos).text);
        ++nextLyricPos;
    }
}

void LyricFrame::mousePressEvent(QMouseEvent *e)
{
    mousePressPoint = e->pos();
    mousePressed = true;
}

void LyricFrame::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    mousePressed = false;
}

void LyricFrame::mouseMoveEvent(QMouseEvent *e)
{
    if (!mousePressed)
        return;

    move(e->pos() - mousePressPoint + pos());
}

void LyricFrame::enterEvent(QEvent *e)
{
    Q_UNUSED(e)

    opacityEffect->setOpacity(0.38);
}

void LyricFrame::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)

    opacityEffect->setOpacity(1);
}

void LyricFrame::loadLyricFinish()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    const QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    if (!document.isObject())
        return;

    const QJsonObject &obj = document.object();
    const QString &lyric = obj.value("lyric").toString();

    if (lyric.isEmpty())
        qDebug() << "lyric is empty";
    qDebug() << lyric;

    QRegularExpression re("((?:\\[[\\d\\.:]+\\])+)(.*?)(?=[$\\r])");
    QRegularExpressionMatch match;
    int pos = 0;
    do {
        match = re.match(lyric, pos);
        if (!match.isValid() || !match.hasMatch())
            break;
        pos = match.capturedEnd();

        const QString &text = match.captured(2);
        const QString &time = match.captured(1);

        addLyricLine(time, text);
    } while (pos != -1);

    std::sort(lyricsList.begin(), lyricsList.end(), [] (const LyricText &l1, const LyricText &l2) -> bool {
        return l1.start < l2.start;
    });

    for (const LyricText &lyric : lyricsList)
        qDebug() << lyric.start << lyric.text;
}

void LyricFrame::addLyricLine(const QString &times, const QString &text)
{
    QRegularExpression re("\\[(\\d+):(\\d+)\\.(\\d+)?\\]");
    QRegularExpressionMatch match;
    int pos = 0;
    do {
        match = re.match(times, pos);
        if (!match.isValid() || !match.hasMatch())
            break;
        pos = match.capturedEnd();

        const int min = match.captured(1).toInt();
        const int sec = match.captured(2).toInt();
        const int msec = match.captured(3).toInt() * 10;
        const qint64 start = min * 60 * 1000 + sec * 1000 + msec;

        lyricsList.append(LyricText(start, text));
    } while (pos != -1);
}

LyricText::LyricText(qint64 start, const QString &text) :
    start(start),
    text(text)
{

}
