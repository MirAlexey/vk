#ifndef MYMODEL2_H
#define MYMODEL2_H

#include <QAbstractItemModel>
#include <listmanager.h>
#include <QString>
#include <QDebug>
#include <QModelIndex>
#include <QWidget>


class MyModel2 : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MyModel2(Listmanager *listmanager, QObject *parent = 0);

    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual bool hasChildren(const QModelIndex &parent) const;

//    virtual int rowCountRole(const QModelIndex &parent = QModelIndex(),int role = Qt::DisplayRole) const;
//    virtual int columnCountRole(const QModelIndex &parent = QModelIndex(),int role = Qt::DisplayRole) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void updatefilter()const;
    void updateheader(Qt::Orientation, int, int) const;
public slots:
    void resetdata();
private:
    Listmanager *lm;

   // int maxrownumber();


    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;

    // QAbstractItemModel interface
public:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    // QAbstractItemModel interface
public:
    bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // MYMODEL2_H
