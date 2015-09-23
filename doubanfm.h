#ifndef DOUBANFM_H
#define DOUBANFM_H

#include "song.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QTimer>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPoint>
#include <QMenu>

namespace Ui {
class DouBanFM;
}

class DouBanFM : public QMainWindow
{
    Q_OBJECT

public:
    explicit DouBanFM(QWidget *parent = 0);
    ~DouBanFM();

protected:
    bool eventFilter(QObject *o, QEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void pause();
    void refresh();
    void setTimeLeft();
    void loadMoreSong();
    void loadMoreSong_finish(QNetworkReply *reply);
    void loadSongPicture_finish(QNetworkReply *reply);
    void mediaPlayerDurationChanged(qint64 duration);
    void mediaPlayerPlay();
    void mediaPlayerMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void mediaPlayerMediaContentChanged(const QMediaContent &);
    void mediaPlayerNextSong();

private:
    Ui::DouBanFM *ui;

    QTimer m_timerRefresh;
    QList<Song> m_songList;
    QMediaPlayer m_player;
    QMenu m_popUpMenu;
    QPoint m_mouseLastPos;

    bool m_paused;
    bool m_mouseMoving;
};

#endif // DOUBANFM_H
