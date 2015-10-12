#include "doubanfm.h"
#include "logindialog.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QIcon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QKeyEvent>
#include <QMediaContent>
#include <QMouseEvent>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSlider>
#include <QUrlQuery>

DoubanFM::DoubanFM() :
    lyricWindow(new LyricFrame),
    channelWindow(new ChannelFrame),
    manager(new QNetworkAccessManager)
{
    channelWindow->setNetworkAccessManager(manager);
    lyricWindow->setNetworkAccessManager(manager);

    picture = new ButtonLabel;
    picture->setFixedWidth(245);
    picture->installEventFilter(this);
    picture->setStyleSheet("background-color:red;");
    pause = new ButtonLabel;
    pause->setNormalImage(QPixmap(":/images/resource/images/pause.png"));
    like = new ButtonLabel;
    like->setNormalImage(QPixmap(":/images/resource/images/like.png"));
    like->setHoverImage(QPixmap(":/images/resource/images/like-hover.png"));
    trash = new ButtonLabel;
    trash->setNormalImage(QPixmap(":/images/resource/images/remove.png"));
    trash->setHoverImage(QPixmap(":/images/resource/images/remove-hover.png"));
    next = new ButtonLabel;
    next->setNormalImage(QPixmap(":/images/resource/images/next.png"));
    next->setHoverImage(QPixmap(":/images/resource/images/next-hover.png"));
    volumeIcon = new ButtonLabel;
    volumeIcon->setNormalImage(QPixmap(":/images/resource/images/audio.png"));
    volumeIcon->setFixedHeight(10);
    volumeIcon->installEventFilter(this);
    layricTips = new ButtonLabel(picture);
    layricTips->setText(tr("Click to show lyrics"));
    layricTips->setVisible(false);
    layricTips->setStyleSheet("QLabel {"
                                "padding:4px 6px;"
                                "background-color:rgba(66, 66, 66, .6);"
                                "border-radius:4px;"
                              "}");

    timeAxis = new QProgressBar();
    timeAxis->setOrientation(Qt::Horizontal);
    timeAxis->setFixedHeight(2);
    timeAxis->setMinimum(0);
    timeAxis->setStyleSheet("QProgressBar { \
                                 background-color:#ddd; \
                                 border:none; \
                             } \
                             QProgressBar::chunk { \
                                 background-color:#9DD6C5; \
                                 border:none; \
                             }");

    volumeSlider = new QSlider;
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setFixedHeight(3);
    volumeSlider->setMaximumWidth(0);
    volumeSlider->installEventFilter(this);
    volumeSlider->setStyleSheet("QSlider::handle:horizontal { \
                                     background-color:transparent; \
                                 } \
                                 QSlider::sub-page { \
                                     background-color:black; \
                                 } \
                                 QSlider::add-page { \
                                     background-color:#ddd; \
                                 }");

    volumeAnimation = new QPropertyAnimation(volumeSlider, "maximumWidth");

    artist = new QLabel;
    artist->setStyleSheet("font-size:24px;");
    album = new QLabel;
    album->setStyleSheet("font-size:13px;");
    songName = new QLabel;
    songName->setStyleSheet("font-size:15px;");
    time = new QLabel;
    time->setAlignment(Qt::AlignCenter);
#ifdef QT_DEBUG
    artist->setText("Artist");
    album->setText("< Album >");
    songName->setText("SongName");
    time->setText("-0:00");
#endif

    refreshUITimer = new QTimer(this);
    refreshUITimer->setInterval(1000);
    refreshUITimer->start();
    refreshLyricTimer = new QTimer(this);
    refreshLyricTimer->setInterval(90);
    refreshLyricTimer->start();

    QHBoxLayout *centerCtrlLayout = new QHBoxLayout;
    centerCtrlLayout->addStretch();
    centerCtrlLayout->addWidget(time);
    centerCtrlLayout->setAlignment(time, Qt::AlignVCenter);
    centerCtrlLayout->addWidget(volumeIcon);
    centerCtrlLayout->setAlignment(volumeIcon, Qt::AlignVCenter);
    centerCtrlLayout->addWidget(volumeSlider);
    centerCtrlLayout->setAlignment(volumeSlider, Qt::AlignVCenter);
    centerCtrlLayout->setSpacing(5);
    centerCtrlLayout->setMargin(0);

    QHBoxLayout *bottomCtrlLayout = new QHBoxLayout;
    bottomCtrlLayout->addStretch();
    bottomCtrlLayout->addWidget(like);
    bottomCtrlLayout->addWidget(trash);
    bottomCtrlLayout->addWidget(next);
    bottomCtrlLayout->setMargin(0);
    bottomCtrlLayout->setSpacing(20);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(pause);
    rightLayout->setAlignment(pause, Qt::AlignRight);
    rightLayout->addWidget(artist);
    rightLayout->addWidget(album);
    rightLayout->addSpacing(15);
    rightLayout->addWidget(songName);
    rightLayout->addSpacing(3);
    rightLayout->addWidget(timeAxis);
    rightLayout->addLayout(centerCtrlLayout);
    rightLayout->addSpacing(45);
    rightLayout->addLayout(bottomCtrlLayout);
    rightLayout->addStretch();
    rightLayout->setSpacing(0);
    rightLayout->setContentsMargins(15, 0, 15, 0);

    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);
    rightWidget->setStyleSheet("background-color:white;");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(picture);
    mainLayout->addWidget(rightWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(30, 26, 30, 34);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(30.0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 4);

    setLayout(mainLayout);
    setFixedSize(570, 305);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(tr("Douban FM"));
    setWindowIcon(QIcon(":/images/resource/images/doubanFM.png"));
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    connect(layricTips, &ButtonLabel::clicked, picture, &ButtonLabel::clicked);
    connect(picture, &ButtonLabel::clicked, this, &DoubanFM::toggleLayricsWindow);
    connect(channelWindow, &ChannelFrame::ChannelSelected, this, &DoubanFM::channelChanged);
    connect(&player, &QMediaPlayer::durationChanged, timeAxis, &QProgressBar::setMaximum);
    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &DoubanFM::playerStateChanged);
    connect(refreshUITimer, &QTimer::timeout, this, &DoubanFM::refreshTimeInfo);
    connect(refreshUITimer, &QTimer::timeout, this, &DoubanFM::refreshLyricText);
    connect(next, &ButtonLabel::clicked, this, &DoubanFM::nextSong);

//    LoginDialog *login = new LoginDialog(this);
//    login->setModal(true);
//    login->show();

    toggleLayricsWindow();
    channelWindow->loadChannelList();
}

DoubanFM::~DoubanFM()
{
    delete lyricWindow;
    delete channelWindow;
}

void DoubanFM::mousePressEvent(QMouseEvent *e)
{
    mousePressed = true;
    mousePressPoint = e->pos();
}

void DoubanFM::mouseMoveEvent(QMouseEvent *e)
{
    if (!mousePressed)
        return;

    move(e->pos() - mousePressPoint + pos());
}

void DoubanFM::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    mousePressed = false;
}

void DoubanFM::keyPressEvent(QKeyEvent *e)
{
    const int key = e->key();

    switch (key) {
    case Qt::Key_L:     toggleLayricsWindow();      break;
    case Qt::Key_C:     toggleChannelsWindow();     break;
    case Qt::Key_Escape:qApp->quit();               break;
    default:;
    }

    activateWindow();
}

void DoubanFM::moveEvent(QMoveEvent *e)
{
    channelWindow->move(e->pos() + channelWindowOffset);
}

bool DoubanFM::eventFilter(QObject *o, QEvent *e)
{
    if (o == volumeIcon && e->type() == QEvent::Enter)
        showVolumeSlider();
    else if (o == volumeSlider && e->type() == QEvent::Leave)
        hideVolumeSlider();
    else if (o == picture && e->type() == QEvent::Enter) {
        layricTips->show();
        layricTips->move(picture->rect().center() - layricTips->rect().center());
    } else if (o == picture && e->type() == QEvent::Leave)
        layricTips->hide();

    return false;
}

void DoubanFM::showVolumeSlider()
{
    if (volumeAnimation->state() == QPropertyAnimation::Running ||
        volumeSlider->width() != 0)
        return;

    volumeAnimation->setStartValue(0);
    volumeAnimation->setEndValue(60);
    volumeAnimation->start();
}

void DoubanFM::hideVolumeSlider()
{
    if (volumeAnimation->state() == QPropertyAnimation::Running ||
        volumeSlider->width() == 0)
        return;

    volumeAnimation->setStartValue(60);
    volumeAnimation->setEndValue(0);
    volumeAnimation->start();
}

void DoubanFM::toggleLayricsWindow()
{
    qDebug() << "toggle layrics";
    lyricWindow->setVisible(!lyricWindow->isVisible());

    if (!lyricWindow->isVisible())
        return;
}

void DoubanFM::toggleChannelsWindow()
{
    channelWindow->setVisible(!channelWindow->isVisible());
}

void DoubanFM::channelChanged(const Channel &channel)
{
    qDebug() << "select to channel: " << channel;

    // clear old list
    songList.clear();

    // load new song list
    loadSongList();
}

void DoubanFM::playerStateChanged(const QMediaPlayer::MediaStatus stat)
{
    switch (stat)
    {
    case QMediaPlayer::EndOfMedia:      nextSong();             break;
    default:;
    }
}

void DoubanFM::play()
{
    qDebug() << songList.first();
    player.setMedia(QMediaContent(songList.first().url()));
    player.play();

    lyricWindow->loadLyric(songList.first());
}

void DoubanFM::nextSong()
{
    player.stop();
    songList.pop_front();

    if (songList.isEmpty())
        loadSongList();
    else
        play();
}

void DoubanFM::refreshTimeInfo()
{
    const int duration = player.duration();
    const int position = player.position();

    timeAxis->setValue(position);
    timeAxis->update();

    const int timeLeft = (duration - position) / 1000;
    time->setText(QString("-%1:%2")
                  .arg(timeLeft / 60)
                  .arg(timeLeft % 60, 2, 10, QLatin1Char('0')));
}

void DoubanFM::refreshLyricText()
{
    lyricWindow->refreshLyric(player.position());
}

void DoubanFM::loadSongList()
{
    QUrl url("http://www.douban.com/j/app/radio/people");
    QUrlQuery query;
    query.addQueryItem("app_name", "radio_desktop_win");
    query.addQueryItem("version", "100");
    query.addQueryItem("type", "n");
    query.addQueryItem("channel", QString::number(channelWindow->channel().id()));
    url.setQuery(query);
    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, &DoubanFM::loadSongListFinish);
}

void DoubanFM::loadSongListFinish()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    const QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    reply->deleteLater();
    if (!document.isObject())
        return;

    const QJsonObject &obj = document.object();
    const int stat = obj.value("r").toInt(-1);
    if (stat) {
        qWarning() << "error: " << obj;
        return;
    }

    const QJsonValue &value = obj.value("song");
    if (!value.isArray())
        return;

    Song song;
    const QJsonArray &list = value.toArray();
    for (const QJsonValue &value : list) {
        song.setData(value);
        songList.append(song);
    }

    play();
}
