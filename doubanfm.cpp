#include "doubanfm.h"
#include "buttonlabel.h"

#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QProgressBar>
#include <QSlider>

DoubanFM::DoubanFM()
{
    picture = new ButtonLabel;
    picture->setFixedWidth(245);
    picture->setStyleSheet("background-color:red;");
    pause = new ButtonLabel;
    pause->setNormalImage(QPixmap(":/images/resource/images/pause.png"));
    like = new ButtonLabel;
    like->setNormalImage(QPixmap(":/images/resource/images/like.png"));
    trash = new ButtonLabel;
    trash->setNormalImage(QPixmap(":/images/resource/images/remove.png"));
    next = new ButtonLabel;
    next->setNormalImage(QPixmap(":/images/resource/images/next.png"));
    volumeIcon = new ButtonLabel;
    volumeIcon->setNormalImage(QPixmap(":/images/resource/images/audio.png"));

    timeAxis = new QProgressBar();
    timeAxis->setOrientation(Qt::Horizontal);
    timeAxis->setFixedHeight(2);
    timeAxis->setStyleSheet("QProgressBar { \
                                 background-color:#ddd; \
                                 border:none; \
                             } \
                             QProgressBar::chunk { \
                                 background-color:#9DD6C5; \
                                 border:none; \
                             }");

    artist = new QLabel;
    artist->setStyleSheet("font-size:24px;");
    album = new QLabel;
    album->setStyleSheet("font-size:13px;");
    songName = new QLabel;
    songName->setStyleSheet("font-size:15px;");
    time = new QLabel;
#ifdef QT_DEBUG
    artist->setText("Artist");
    album->setText("< Album >");
    songName->setText("SongName");
    time->setText("-0:00");
#endif

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(pause);
    rightLayout->setAlignment(pause, Qt::AlignRight);
    rightLayout->addWidget(artist);
    rightLayout->addWidget(album);
    rightLayout->addWidget(songName);
    rightLayout->addWidget(timeAxis);
    rightLayout->addStretch();
    rightLayout->setSpacing(0);
    rightLayout->setContentsMargins(15, 0, 15, 0);

    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);
    rightWidget->installEventFilter(this);
    rightWidget->setStyleSheet("background-color:white;");

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(picture);
    mainLayout->addWidget(rightWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(30, 26, 30, 34);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(30.0);
    shadowEffect->setColor(Qt::black);
    shadowEffect->setOffset(0, 4);

    setLayout(mainLayout);
    setFixedSize(570, 305);
    setGraphicsEffect(shadowEffect);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/images/resource/images/doubanFM.png"));
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

DoubanFM::~DoubanFM()
{

}

void DoubanFM::mousePressEvent(QMouseEvent *e)
{
    mousePressed = true;
    mousePressPoint = e->pos();
}

void DoubanFM::mouseMoveEvent(QMouseEvent *e)
{
    if (!mousePressed)
        return;

    move(e->pos() - mousePressPoint + pos());
}

void DoubanFM::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    mousePressed = false;
}

bool DoubanFM::eventFilter(QObject *o, QEvent *e)
{
    Q_UNUSED(o)
    Q_UNUSED(e)

    return false;
}
