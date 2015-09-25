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
    void stateChanged(const State state);

public:
    explicit ButtonLabel(QWidget *parent = 0);

private:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    State state = Normal;

    bool checked = false;
    bool checkable = false;
};

#endif // BUTTONLABEL_H
