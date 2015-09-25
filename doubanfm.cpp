#include "doubanfm.h"
#include "buttonlabel.h"

#include <QGraphicsDropShadowEffect>
#include <QDebug>

DoubanFM::DoubanFM()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(30.0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 4);

    setFixedSize(500, 300);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(Qt::FramelessWindowHint);
}

