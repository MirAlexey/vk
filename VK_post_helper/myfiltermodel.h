#ifndef MYFILTERMODEL_H
#define MYFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QDebug>

class myfiltermodel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit myfiltermodel(QObject *parent = 0);

signals:

public slots:
    void updatefilter();

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MYFILTERMODEL_H
