#ifndef LAYRICFRAME_H
#define LAYRICFRAME_H

#include "song.h"

#include <QFrame>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QNetworkAccessManager>

#include <memory>

class LyricText {
public:
    LyricText(qint64 start, const QString &text);

    qint64 start;
    QString text;
};

class LyricFrame : public QFrame
{
    Q_OBJECT

public:
    LyricFrame();
    ~LyricFrame();

    inline void setNetworkAccessManager(const std::shared_ptr<QNetworkAccessManager> &namPtr) {manager = namPtr;}
    inline void setLayricAlignment(Qt::Alignment alignment) const
    {layric->setAlignment(alignment);}

    void loadLyric(const Song &song);
    void refreshLyric(qint64 msec);

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

    void loadLyricFinish();
    void setLyricText(const QString &text);
    void addLyricLine(const QString &times, const QString &text);

private:
    std::shared_ptr<QNetworkAccessManager> manager;

    int lyricOffset = 500;
    int nextLyricPos = 0;
    bool mousePressed = false;
    QPoint mousePressPoint;

    QLabel *layric;

    QList<LyricText> lyricsList;

    QGraphicsOpacityEffect *opacityEffect;
    QGraphicsDropShadowEffect *shadowEffect;
};

#endif // LAYRICFRAME_H
