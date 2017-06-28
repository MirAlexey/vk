#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H


#include <QWidget>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <listmanager.h>
#include <QString>
#include <QDebug>

class MyItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:


    explicit MyItemModel(Listmanager *listmanager, QObject *parent = 0);
     ~MyItemModel();
//    enum TypeOutput {
//        TagGroup,
//        TagAccount,
//        GroupTag,
//        AccountTag,
//        PostGroupTag,
//        PostAccountTag,
//        Post,
//        QueuePost
//    };



    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual bool hasChildren(const QModelIndex &parent) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    void setTypeOutput(QString to);
    void needReset();




signals:

public slots:

private:
    Listmanager *lm;
    QString   typeoutput;

   // TypeOutput typeoutput = GroutTag;

};

#endif // MYITEMMODEL_H
