#ifndef DOUBANFM_H
#define DOUBANFM_H

#include "buttonlabel.h"
#include "lyricframe.h"
#include "channelframe.h"
#include "song.h"
#include "user.h"

#include <QFrame>
#include <QLabel>
#include <QList>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSlider>
#include <QSystemTrayIcon>
#include <QTimer>

#include <memory>

class DoubanFM : public QFrame
{
    Q_OBJECT

public:
    DoubanFM();
    ~DoubanFM();

    void show();

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void moveEvent(QMoveEvent *e);
    bool eventFilter(QObject *o, QEvent *e);

private slots:
    void showVolumeSlider();
    void hideVolumeSlider();
    void toggleLayricsWindow();
    void toggleChannelsWindow();
    void channelChanged(const Channel &channel);
    void playerStateChanged(const QMediaPlayer::MediaStatus stat);

    void quit();
    void quitOrHide();
    void hide();
    void systemTrayActivated(QSystemTrayIcon::ActivationReason reason);
    void loginRequest(const QString &username, const QString &password);
    void loginRequestFinish();

    void play();
    void nextSong();
    void pauseSong();

    void toggleLikeSong();
    void removeSong();

    void refreshTimeInfo();
    void refreshLyricText();

    void loadSongList();
    void loadSongListFinish();
    void loadSongPicture(const Song &song);
    void loadSongPictureFinish();

private:
    bool mousePressed = false;
    QPoint mousePressPoint;
    QPoint channelWindowOffset = QPoint(530, 0);
    QSystemTrayIcon systemTray;

    ButtonLabel *picture;
    ButtonLabel *pause;
    ButtonLabel *like;
    ButtonLabel *trash;
    ButtonLabel *next;
    ButtonLabel *volumeIcon;
    ButtonLabel *layricTips;
    QLabel *artist;
    QLabel *album;
    QLabel *songName;
    QLabel *time;
    QProgressBar *timeAxis;
    QSlider *volumeSlider;

    QList<Song> songList;
    QMediaPlayer player;

    User user;

    QTimer *refreshUITimer;
    QTimer *refreshLyricTimer;
    QTimer *quitOrHideTimer;

    LyricFrame *lyricWindow;
    ChannelFrame *channelWindow;

    QPropertyAnimation *volumeAnimation;
    std::shared_ptr<QNetworkAccessManager> manager;
};

#endif // DOUBANFM_H
