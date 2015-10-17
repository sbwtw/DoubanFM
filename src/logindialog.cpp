#include "logindialog.h"

#include <QVBoxLayout>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
{
    usernameLabel = new QLabel(tr("User name:"));
    passwordLabel = new QLabel(tr("Password:"));
    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    autoLoginCheck = new QCheckBox(tr("Auto login"));
    autoLoginCheck->setChecked(true);
    acceptBtn = new QPushButton(tr("Ok"));
    cancelBtn = new QPushButton(tr("Cancel"));

    QGridLayout *topGrid = new QGridLayout;
    topGrid->addWidget(usernameLabel, 0, 0);
    topGrid->addWidget(passwordLabel, 1, 0);
    topGrid->addWidget(usernameEdit, 0, 1);
    topGrid->addWidget(passwordEdit, 1, 1);
    topGrid->addWidget(autoLoginCheck, 2, 1);

    QHBoxLayout *btnsLayout = new QHBoxLayout;
    btnsLayout->addWidget(acceptBtn);
    btnsLayout->addWidget(cancelBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addLayout(topGrid);
    mainLayout->addLayout(btnsLayout);
    mainLayout->addStretch();

    connect(cancelBtn, &QPushButton::clicked, this, &LoginDialog::accept);

    setLayout(mainLayout);
}
