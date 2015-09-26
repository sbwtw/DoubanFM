#include "doubanfm.h"
#include "buttonlabel.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

DoubanFM::DoubanFM()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(30.0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 4);

    ButtonLabel *btn = new ButtonLabel(this);
    btn->setStyleSheet("background-color:red;");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(btn);
    mainLayout->setContentsMargins(30, 26, 30, 34);

    setLayout(mainLayout);
    setFixedSize(500, 300);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

