#include "buttonlabel.h"

#include <QMouseEvent>
#include <QDebug>

ButtonLabel::ButtonLabel(QWidget *parent) :
    QLabel(parent)
{
    connect(this, &ButtonLabel::stateChanged, this, &ButtonLabel::setShownImage);
}

void ButtonLabel::setChecked(bool stat)
{
    if (checked() == stat)
        return;

    if (stat)
        state = Checked;
    else
        state = Normal;

    emit stateChanged(state);
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

    if (m_checkable && state == Press)
        state = Checked;
    else
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

void ButtonLabel::setShownImage()
{
    switch (state)
    {
    case Normal:    if (!normalImage.isNull()) setPixmap(normalImage);      break;
    case Hover:     if (!hoverImage.isNull()) setPixmap(hoverImage);        break;
    case Press:     if (!pressImage.isNull()) setPixmap(pressImage);        break;
    case Checked:   if (!checkedImage.isNull()) setPixmap(checkedImage);    break;
    }
}

