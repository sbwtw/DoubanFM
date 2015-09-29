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
    bool eventFilter(QObject *o, QEvent *e);

private slots:
    void showVolumeSlider();
    void hideVolumeSlider();
    void toggleLayricsWindow();

    void loadSongList();
    void loadSongListFinish();
    void loadChannelList();
    void loadChannelListFinish();

private:
    bool mousePressed = false;

    QPoint mousePressPoint;
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

    QPropertyAnimation *volumeAnimation;
    QNetworkAccessManager *manager;
};

#endif // DOUBANFM_H
