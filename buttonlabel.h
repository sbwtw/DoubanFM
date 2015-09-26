#ifndef BUTTONLABEL_H
#define BUTTONLABEL_H

#include <QLabel>
#include <QPixmap>

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

    inline void setNormalImage(const QPixmap &img) {normalImage = img;}
    inline void setHoverImage(const QPixmap &img) {hoverImage = img;}
    inline void setPressImage(const QPixmap &img) {pressImage = img;}
    inline void setCheckedImage(const QPixmap &img) {checkedImage = img;}

private:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private slots:
    void setShownImage();

private:
    State state = Normal;

    bool checked = false;
    bool checkable = false;

    QPixmap normalImage;
    QPixmap hoverImage;
    QPixmap pressImage;
    QPixmap checkedImage;
};

#endif // BUTTONLABEL_H
