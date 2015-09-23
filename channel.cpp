#include "channel.h"
#include "ui_channel.h"

Channel::Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channel)
{
    ui->setupUi(this);
}

Channel::~Channel()
{
    delete ui;
}
