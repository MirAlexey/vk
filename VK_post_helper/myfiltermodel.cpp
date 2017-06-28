#include "myfiltermodel.h"

myfiltermodel::myfiltermodel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

void myfiltermodel::updatefilter()
{
    invalidateFilter();
}


bool myfiltermodel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row,0,source_parent);
    QVariant value = sourceModel()->data(index);
    if (value.isValid()){
        qDebug()<< value.toString();
        if (value.toString()=="") return false;
        return true;
    }
    return false;
}
