#include "channelmodel.h"

ChannelModel::ChannelModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

int ChannelModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 0;
}

QVariant ChannelModel::data(const QModelIndex &index, int role) const
{

    return QVariant();
}

