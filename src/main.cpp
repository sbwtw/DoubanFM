#include "doubanfm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DoubanFM fm;
    fm.show();

    return a.exec();
}
