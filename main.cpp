#include "doubanfm.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DouBanFM w;
    w.show();

    return a.exec();
}
