#ifndef BUTTONLABEL_H
#define BUTTONLABEL_H

#include <QLabel>

class ButtonLabel : public QLabel
{
    Q_OBJECT

public:
    enum State {
        Normal,
        Hover,
        Press,
        Checked,
    };

signals:
    void clicked();

public:
    ButtonLabel();

private:
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseEnterEvent(QMouseEvent *e);

private:
    State state = Normal;
};

#endif // BUTTONLABEL_H
