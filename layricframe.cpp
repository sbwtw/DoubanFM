#include "layricframe.h"

LayricFrame::LayricFrame() : QFrame(0)
{
    setFixedSize(800, 50);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("background-color:red;");
}

