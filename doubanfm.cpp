#include "doubanfm.h"
#include "ui_doubanfm.h"
#include "song.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMediaContent>
#include <QString>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

DouBanFM::DouBanFM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DouBanFM), m_paused(true), m_mouseMoving(false)
{
    ui->setupUi(this);
    ui->wgt_ctrlWidget->installEventFilter(this);

    m_popUpMenu.addAction(ui->act_selectChannel);
    m_popUpMenu.addSeparator();
    m_popUpMenu.addAction(ui->act_exit);
    m_popUpMenu.addSeparator();
    m_popUpMenu.addAction(ui->act_authorBlog);

    connect(&m_player, SIGNAL(mediaChanged(QMediaContent)), this, SLOT(mediaPlayerMediaContentChanged(QMediaContent)));
    connect(&m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(mediaPlayerMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(&m_player, SIGNAL(durationChanged(qint64)), this, SLOT(mediaPlayerDurationChanged(qint64)));
    connect(&m_timerRefresh, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(ui->sld_volume, SIGNAL(valueChanged(int)), &m_player, SLOT(setVolume(int)));
    connect(ui->btn_pause, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->btn_nextSong, SIGNAL(clicked()), this, SLOT(mediaPlayerNextSong()));
    connect(ui->act_exit, SIGNAL(triggered()), this, SLOT(close()));

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30.0);
    shadow->setColor(Qt::black);
    shadow->setOffset(0, 4);

    this->setGraphicsEffect(shadow);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->pause();
}

DouBanFM::~DouBanFM()
{
    delete ui;
}

bool DouBanFM::eventFilter(QObject *o, QEvent *e)
{
    if (o == ui->wgt_ctrlWidget && e->type() == QEvent::MouseButtonPress)
    {
        this->mousePressEvent(static_cast<QMouseEvent *>(e));
        return true;
    }

    if (o == ui->wgt_ctrlWidget && e->type() == QEvent::MouseButtonRelease)
    {
        this->mouseReleaseEvent(static_cast<QMouseEvent *>(e));
        return true;
    }

    if (o == ui->wgt_ctrlWidget && e->type() == QEvent::MouseMove)
    {
        this->mouseMoveEvent(static_cast<QMouseEvent *>(e));
        return true;
    }

    return QMainWindow::eventFilter(o, e);
}

void DouBanFM::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mouseMoving && e->buttons() == Qt::LeftButton)
    {
        this->move(this->pos() + (QCursor::pos() - m_mouseLastPos));
        m_mouseLastPos = QCursor::pos();

        return ;
    }

    QMainWindow::mouseMoveEvent(e);
}

void DouBanFM::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_mouseMoving = true;
        m_mouseLastPos = QCursor::pos();

        return ;
    }
    else if (e->button() == Qt::RightButton)
    {
        m_popUpMenu.exec(QCursor::pos());

        return ;
    }

    QMainWindow::mousePressEvent(e);
}

void DouBanFM::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_mouseMoving = false;

        return ;
    }

    QMainWindow::mouseReleaseEvent(e);
}

void DouBanFM::pause()
{
    m_paused = !m_paused;

    if (m_paused)
    {
        m_timerRefresh.stop();
        m_player.pause();
    } else {
        m_timerRefresh.start(1000);
        this->mediaPlayerPlay();
    }
}

void DouBanFM::refresh()
{
    if (!m_paused)
    {
        ui->pgs_timeLine->setValue(m_player.position() / 1000);
        this->setTimeLeft();

        if (m_songList.size() < 2)
            this->loadMoreSong();
    } else {

    }

    this->update();
}

void DouBanFM::loadMoreSong()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("http://douban.fm/j/mine/playlist?type=n&sid=&pt=0.0&channel=0&from=mainsite&r=1d85d147d5");

    manager->get(QNetworkRequest(url));

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(loadMoreSong_finish(QNetworkReply *)));
}

void DouBanFM::loadMoreSong_finish(QNetworkReply *reply)
{
    QString response = reply->readAll();

    QJsonDocument document = QJsonDocument::fromJson(response.toStdString().c_str());

    if (!document.isObject() ||
        !document.object().contains("song") ||
        !document.object()["song"].isArray())
        return ;

    QJsonArray songList(document.object()["song"].toArray());

    for (int i(0); i != songList.size(); ++i)
    {
        Song song(songList.at(i).toObject());

        m_songList.append(song);
    }

    reply->deleteLater();
    this->mediaPlayerPlay();
}

void DouBanFM::setTimeLeft()
{
    if (m_player.state() != QMediaPlayer::PlayingState)
    {
        ui->lab_timeLeft->setText("-0:00");
        return ;
    }

    int timeLeft(m_player.duration() - m_player.position());
    timeLeft /= 1000;

    ui->lab_timeLeft->setText(QString("-%1:%2")
                              .arg(timeLeft / 60)
                              .arg(timeLeft % 60, 2, 10, QLatin1Char('0')));
}

void DouBanFM::loadSongPicture_finish(QNetworkReply *reply)
{
    QPixmap pixmap;
    pixmap.loadFromData(reply->readAll());
    pixmap = pixmap.scaled(245, 245, Qt::KeepAspectRatioByExpanding);
    pixmap = pixmap.copy((pixmap.width() - 245) >> 1, (pixmap.height() - 245) >> 1, 245, 245);

    ui->btn_songPicture->setIcon(QIcon(pixmap));
}

void DouBanFM::mediaPlayerDurationChanged(qint64 duration)
{
    ui->pgs_timeLine->setMaximum(duration / 1000);
}

void DouBanFM::mediaPlayerPlay()
{
    if (m_player.state() == QMediaPlayer::PlayingState)
        return ;

    if (m_player.state() == QMediaPlayer::PausedState)
        m_player.play();

    if (m_player.state() == QMediaPlayer::StoppedState)
    {
        if (m_songList.empty()) {
            //std::cout << "m_songList is empty" << std::endl;
            return ;
        }

        QUrl url(m_songList.at(0).url());
        QMediaContent mediaContent(url);

        m_player.setMedia(mediaContent);
        m_player.play();
    }
}

void DouBanFM::mediaPlayerMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        this->mediaPlayerNextSong();
    }
}

void DouBanFM::mediaPlayerMediaContentChanged(const QMediaContent &)
{
    const Song &song = m_songList.at(0);

    ui->text_artist->setText(song.artist());
    ui->text_albumTitle->setText(QString("< %1 > %2")
                                 .arg(song.albumtitle())
                                 .arg(song.public_time()));
    ui->text_songName->setText(song.title());

    // load song picture
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(song.picture());

    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadSongPicture_finish(QNetworkReply*)));
}

void DouBanFM::mediaPlayerNextSong()
{
    ui->pgs_timeLine->setValue(0);
    ui->pgs_timeLine->setMaximum(0);
    m_player.stop();

    if (!m_songList.empty())
        m_songList.erase(m_songList.begin());

    this->mediaPlayerPlay();
}
