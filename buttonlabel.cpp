#include "buttonlabel.h"

#include <QMouseEvent>

ButtonLabel::ButtonLabel()
{

}

void ButtonLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
    e->accept();
}

void ButtonLabel::mouseEnterEvent(QMouseEvent *e)
{

}

