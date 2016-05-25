// uas_model.cpp
#include <QTime>
#include "uas_model.hpp"

UASModel::UASModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int UASModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 2;
}

int UASModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant UASModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        if (row == 0 && col == 0)
        {
            return QTime::currentTime().toString();
        }
    }
    return QVariant();
}
