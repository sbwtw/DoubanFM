#include "logindialog.h"
#include "constants.h"

#include <QVBoxLayout>

using DouBanFM::APP_NAME;

static const QString CFG_NAME = QString("LoginDialog");

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    settings(new QSettings(APP_NAME, CFG_NAME, this))
{
    usernameLabel = new QLabel(tr("User name:"));
    passwordLabel = new QLabel(tr("Password:"));
    usernameEdit = new QLineEdit;
    usernameEdit->setText(settings->value("username").toString());
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setText(settings->value("password").toString());
    autoLoginCheck = new QCheckBox(tr("Auto login"));
    autoLoginCheck->setChecked(settings->value("autologin", true).toBool());
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
    connect(acceptBtn, &QPushButton::clicked, this, &LoginDialog::accept);
    connect(acceptBtn, &QPushButton::clicked, [this] {emit login(username(), password());});
    connect(this, &LoginDialog::accepted, this, &LoginDialog::deleteLater, Qt::QueuedConnection);

    setLayout(mainLayout);
    setModal(true);
}

LoginDialog::~LoginDialog()
{
    settings->setValue("autologin", autoLoginCheck->isChecked());

    if (autoLoginCheck->isChecked())
    {
        settings->setValue("username", username());
        settings->setValue("password", password());
    } else {
        settings->setValue("username", QVariant());
        settings->setValue("password", QVariant());
    }
}
