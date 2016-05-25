// uas_model.hpp
#include <QAbstractTableModel>

class UASModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    UASModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
