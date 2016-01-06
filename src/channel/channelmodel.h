#ifndef CHANNELLISTMODEL_H
#define CHANNELLISTMODEL_H

#include "channel.h"

#include <QAbstractListModel>

class ChannelModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ChannelModel(QObject *parent = nullptr);

protected:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QList<Channel> channelList;
};

#endif // CHANNELLISTMODEL_H
