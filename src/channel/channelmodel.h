#ifndef CHANNELLISTMODEL_H
#define CHANNELLISTMODEL_H

#include <QAbstractListModel>

class ChannelModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ChannelModel(QObject *parent = nullptr);

protected:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // CHANNELLISTMODEL_H
