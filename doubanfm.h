#ifndef DOUBANFM_H
#define DOUBANFM_H

#include <QFrame>
#include <QLabel>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSlider>

#include <memory>

class ChannelFrame;
class ButtonLabel;
class Song;
class LayricFrame;
class DoubanFM : public QFrame
{
    Q_OBJECT

public:
    DoubanFM();
    ~DoubanFM();

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
    void selectChannel();

    void loadSongList();
    void loadSongListFinish();

private:
    bool mousePressed = false;
    QPoint mousePressPoint;
    QPoint channelWindowOffset = QPoint(530, 0);

    QString channel;
    QList<Song> songList;

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

    LayricFrame *layricWindow;
    ChannelFrame *channelWindow;

    QPropertyAnimation *volumeAnimation;
    std::shared_ptr<QNetworkAccessManager> manager;
};

#endif // DOUBANFM_H
