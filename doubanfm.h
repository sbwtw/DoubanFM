#ifndef DOUBANFM_H
#define DOUBANFM_H

#include <QFrame>
#include <QLabel>
#include <QSlider>
#include <QProgressBar>
#include <QPropertyAnimation>

class ButtonLabel;
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
    bool eventFilter(QObject *o, QEvent *e);

private slots:
    void showVolumeSlider();
    void hideVolumeSlider();
    void toggleLayricsWindow();

private:
    bool mousePressed = false;

    QPoint mousePressPoint;

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

    QPropertyAnimation *volumeAnimation;
};

#endif // DOUBANFM_H
