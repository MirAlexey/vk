#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QAbstractProxyModel>

class MyProxyModelGT : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit MyProxyModelGT(int type_model, QObject *parent = 0);

signals:

public slots:
    void resetdata();

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    // QAbstractProxyModel interface
public:
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

private:
    int type_model;

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    // QAbstractItemModel interface
public:
    bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // MYPROXYMODEL_H
