#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class LoginDialog : public QDialog
{
public:
    LoginDialog(QWidget *parent = 0);

private:
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QCheckBox *autoLoginCheck;
    QPushButton *acceptBtn;
    QPushButton *cancelBtn;
};

#endif // LOGINDIALOG_H
