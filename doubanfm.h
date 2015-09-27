#ifndef DOUBANFM_H
#define DOUBANFM_H

#include <QFrame>

class QLabel;
class ButtonLabel;
class QSlider;
class QProgressBar;
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

private:
    bool mousePressed = false;

    QPoint mousePressPoint;

    ButtonLabel *picture;
    ButtonLabel *pause;
    ButtonLabel *like;
    ButtonLabel *trash;
    ButtonLabel *next;
    ButtonLabel *volumeIcon;
    QLabel *artist;
    QLabel *album;
    QLabel *songName;
    QLabel *time;
    QProgressBar *timeAxis;
    QSlider *volume;
};

#endif // DOUBANFM_H
