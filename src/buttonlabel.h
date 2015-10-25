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

    void setChecked(bool stat);
    inline bool checked() const {return m_checked;}
    inline bool checkable() const {return m_checkable;}
    inline void setCheckable(bool stat) {m_checkable = stat;}
    inline void setNormalImage(const QPixmap &img) {normalImage = img; setShownImage();}
    inline void setHoverImage(const QPixmap &img) {hoverImage = img; setShownImage();}
    inline void setPressImage(const QPixmap &img) {pressImage = img; setShownImage();}
    inline void setCheckedImage(const QPixmap &img) {checkedImage = img; setShownImage();}

private:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private slots:
    void setShownImage();

private:
    State state = Normal;

    bool m_checked = false;
    bool m_checkable = false;

    QPixmap normalImage;
    QPixmap hoverImage;
    QPixmap pressImage;
    QPixmap checkedImage;
};

#endif // BUTTONLABEL_H
