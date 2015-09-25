#ifndef DOUBANFM_H
#define DOUBANFM_H

#include <QFrame>

class QLabel;
class ButtonLabel;
class DoubanFM : public QFrame
{
public:
    DoubanFM();

private:
    ButtonLabel *picture;
};

#endif // DOUBANFM_H
