#include "myproxymodel.h"

MyProxyModelGT::MyProxyModelGT(int type_model, QObject *parent) :
    QAbstractProxyModel(parent)
{
    this->type_model = type_model;
}

void MyProxyModelGT::resetdata()
{
    beginResetModel();
    endResetModel();
}


QModelIndex MyProxyModelGT::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())                                   {return QModelIndex();}
    QModelIndex index = this->sourceModel()->index(0,type_model);
    if (row    < 0 || row    >= this->sourceModel()->rowCount(index))   {return QModelIndex();}
    if (column < 0 || column >= this->sourceModel()->columnCount(index)) {return QModelIndex();}
    return createIndex(row, column, (void*)NULL);
}

QModelIndex MyProxyModelGT::parent(const QModelIndex &child) const
{
    return this->sourceModel()->parent(child);
}

int MyProxyModelGT::rowCount(const QModelIndex &parent) const
{
    QModelIndex index = this->sourceModel()->index(0,type_model);
    return this->sourceModel()->rowCount(index);
}

int MyProxyModelGT::columnCount(const QModelIndex &parent) const
{
  QModelIndex index = this->sourceModel()->index(0,type_model);
 return this->sourceModel()->columnCount(index);
}



QModelIndex MyProxyModelGT::mapToSource(const QModelIndex &proxyIndex) const
{
    if (proxyIndex.isValid()) return proxyIndex;
    return QModelIndex();
}

QModelIndex MyProxyModelGT::mapFromSource(const QModelIndex &sourceIndex) const
{
    if (sourceIndex.isValid()) return sourceIndex;
    return QModelIndex();
}



QVariant MyProxyModelGT::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if (role== Qt::DisplayRole) {

        return this->sourceModel()->data(index,Qt::UserRole+type_model+1);
    }
    return this->sourceModel()->data(index,role);

}


QVariant MyProxyModelGT::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role==Qt::DisplayRole) return this->sourceModel()->headerData(section,orientation,Qt::UserRole+type_model+1);
   return this->sourceModel()->headerData(section,orientation,role);
}


bool MyProxyModelGT::setData(const QModelIndex &index, const QVariant &value, int role)
{   bool b;

    if (role == Qt::EditRole) b= this->sourceModel()->setData(index,value,Qt::UserRole+type_model+1);
    else b= this->sourceModel()->setData(index,value,role);



    return b;
}


bool MyProxyModelGT::removeRows(int row, int count, const QModelIndex &parent)
{  bool b;
   //beginResetModel();
   QModelIndex index = this->sourceModel()->index(0,type_model);
   b = this->sourceModel()->removeRows(row,count,index);
   //endResetModel();
   return b;

}
