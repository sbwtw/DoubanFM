#include "buttonlabel.h"

#include <QMouseEvent>

ButtonLabel::ButtonLabel(QWidget *parent) :
    QLabel(parent)
{

}

void ButtonLabel::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();

    if (!rect().contains(e->pos()))
    {
        if (state == Normal)
            return;
        state = Normal;
        emit stateChanged(state);
        return;
    }

    state = Hover;
    emit stateChanged(state);
    emit clicked();
}

void ButtonLabel::mousePressEvent(QMouseEvent *e)
{
    e->accept();

    if (state != Hover)
        return;
    state = Press;
    emit stateChanged(state);
}

void ButtonLabel::enterEvent(QEvent *e)
{
    e->accept();

    if (state != Normal)
        return;
    state = Hover;
    emit stateChanged(state);
}

void ButtonLabel::leaveEvent(QEvent *e)
{
    e->accept();

    if (state != Hover)
        return;
    state = Normal;
    emit stateChanged(state);
}

