#ifndef LAYRICFRAME_H
#define LAYRICFRAME_H

#include <QFrame>
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

class LayricFrame : public QFrame
{
    Q_OBJECT

public:
    LayricFrame();

    inline void setLayricAlignment(Qt::Alignment alignment) const
    {layric->setAlignment(alignment);}

private:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    bool mousePressed = false;
    QPoint mousePressPoint;

    QLabel *layric;

    QGraphicsOpacityEffect *opacityEffect;
    QGraphicsDropShadowEffect *shadowEffect;
};

#endif // LAYRICFRAME_H
