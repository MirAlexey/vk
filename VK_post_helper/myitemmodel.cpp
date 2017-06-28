#include "myitemmodel.h"

MyItemModel::MyItemModel(Listmanager *listmanager, QObject *parent) :
    QAbstractItemModel(parent)
{
    this->lm = listmanager;

}

MyItemModel::~MyItemModel()
{
    return;
}

QModelIndex MyItemModel::parent(const QModelIndex &child) const
{
     return QModelIndex();
}
bool MyItemModel::hasChildren(const QModelIndex &parent) const {
  if (parent.model() == this || !parent.isValid()) {
    return rowCount(parent) > 0 && columnCount(parent) > 0;
  }
  return false;
}

int MyItemModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {return 0;}
  if (typeoutput == "SearshGroupTag") return lm->CountSearshGroupList();
  if (typeoutput == "GroupTag") return lm->countGroup();
  if (typeoutput == "AccountTag") return lm->countAccount();
  if (typeoutput == "PostGroupTag")return lm->countTagGroup();
  if (typeoutput == "PostAccountTag")return lm->countTagAccount();
  if (typeoutput == "Post")return lm->countPost();
  if (typeoutput == "QueuePost")return lm->countQueuePost();
  if (typeoutput == "TagGroup")return lm->countTagGroup();
  if (typeoutput == "TagAccount")return lm->countTagAccount();

  return 0;
}

int MyItemModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {return 0;}
  if (typeoutput == "SearshGroupTag") return lm->countTagGroup();
  if (typeoutput == "GroupTag") return lm->countTagGroup();
  if (typeoutput == "AccountTag") return lm->countTagAccount();
  if (typeoutput == "PostGroupTag")return 2;
  if (typeoutput == "PostAccountTag")return 2;
  if (typeoutput == "Post")return 1;
  if (typeoutput == "QueuePost")return 1;
  if (typeoutput == "TagGroup")return 1;
  if (typeoutput == "TagAccount")return 1;
  return 0;
}


QModelIndex MyItemModel::index(int row, int column, const QModelIndex &parent) const {
  if (parent.isValid())                                   {return QModelIndex();}
  if (typeoutput == "GroupTag") {
      if (row    < 0 || row    >= lm->countGroup())   {return QModelIndex();}
      if (column < 0 || column >= lm->countTagGroup()) {return QModelIndex();}
  }
  if (typeoutput == "AccountTag") {
      if (row    < 0 || row    >= lm->countAccount())   {return QModelIndex();}
      if (column < 0 || column >= lm->countTagAccount()) {return QModelIndex();}
  }
  if (typeoutput == "PostGroupTag"){
      if (row    < 0 || row    >= lm->countTagGroup())   {return QModelIndex();}
      if (column < 0 || column >= 2) {return QModelIndex();}
  }
  if (typeoutput == "PostAccountTag"){
      if (row    < 0 || row    >= lm->countTagAccount())   {return QModelIndex();}
      if (column < 0 || column >= 2) {return QModelIndex();}
  }
  if (typeoutput == "Post"){
      if (row    < 0 || row    >= lm->countPost())   {return QModelIndex();}
      if (column < 0 || column >= 1) {return QModelIndex();}
  }
  if (typeoutput == "QueuePost"){
      if (row    < 0 || row    >= lm->countQueuePost())   {return QModelIndex();}
      if (column < 0 || column >= 1) {return QModelIndex();}
  }
  if (typeoutput == "TagGroup"){
      if (row    < 0 || row    >= lm->countTagGroup())   {return QModelIndex();}
      if (column < 0 || column >= 1) {return QModelIndex();}
  }
  if (typeoutput == "TagAccount"){
      if (row    < 0 || row    >= lm->countTagAccount())   {return QModelIndex();}
      if (column < 0 || column >= 1) {return QModelIndex();}
  }


  return createIndex(row, column, (void*)NULL);
}


QVariant MyItemModel::data(const QModelIndex &index, int role) const {

  grouplist *g = lm->getGroupList();
  taglist *t = lm->getTagGroupList();
  taglist *t1 = lm->getTagAccountList();
  accountlist *a = lm->getAccountList();
  postlist *p = lm->getPostList();
  postlist *qp = lm->getQueuePostList();


  if (!index.isValid())                                                  {return QVariant();}
//  if (index.row()    < 0 || index.row()    >= g->countgroup())    {return QVariant();}
//  if (index.column() < 0 || index.column() >= t->countTag())  {return QVariant();}

  if  (role == Qt::DisplayRole){
      if (typeoutput == "GroupTag"){
          if (index.row()    < 0 || index.row()    >= g->countitem())    {return QVariant();}
          if (index.column() < 0 || index.column() >= t->countitem())  {return QVariant();}
          if (g->at(index.row())->tagin(t->at(index.column()))) return QString("V");
          return QString("");
      }
      if (typeoutput == "AccountTag"){
          if (index.row()    < 0 || index.row()    >= a->countitem())    {return QVariant();}
          if (index.column() < 0 || index.column() >= t1->countitem())  {return QVariant();}
          if (a->at(index.row())->tagin(t1->at(index.column()))) return QString("V");
          return QString("");
      }
      if (typeoutput == "PostGroupTag"){
          if (index.row()    < 0 || index.row()    >= t->countitem())    {return QVariant();}
          if (index.column() < 0 || index.column() >= 2)  {return QVariant();}
          if (index.column() == 0 ) return lm->getCurrentPost()->getTagforGroup()->at(index.row())->GetNameTag();
          if (index.column() == 1 )
              if (lm->getCurrentPost()->getTagforGroup()->iteminlist(t->at(index.row()))) return QString("V");
              else return QString("");
      }
      if (typeoutput == "PostAccountTag"){
          if (index.row()    < 0 || index.row()    >= t1->countitem())    {return QVariant();}
          if (index.column() < 0 || index.column() >= 2)  {return QVariant();}
          if (index.column() == 0 ) return lm->getCurrentPost()->getTagforAccount()->at(index.row())->GetNameTag();
          if (index.column() == 1 )
              if (lm->getCurrentPost()->getTagforAccount()->iteminlist(t1->at(index.row()))) return QString("V");
              else return QString("");
      }
      if (typeoutput == "Post"){
          if (index.row()    < 0 || index.row()    >= p->countitem()) return QVariant();
          if (index.column() !=0) return QVariant();
          return p->at(index.row())->GetNamePost();
      }
      if (typeoutput == "QueuePost"){
          if (index.row()    < 0 || index.row()    >= qp->countitem()) return QVariant();
          if (index.column() !=0 ) return QVariant();
          return qp->at(index.row())->GetNamePost();
      }
      if (typeoutput == "TagGroup"){
          if (index.column() !=0) return QVariant();
          if (index.row()    < 0 || index.row()    >= t->countitem()) return QVariant();
          int j = index.row();
          qDebug() <<j;
          return t->at(index.row())->GetNameTag();
      }
      if (typeoutput == "TagAccount"){
          if (index.column() !=0) return QVariant();
          if (index.row()    < 0 || index.row()    >= t1->countitem()) return QVariant();
          int j = index.row();
          qDebug() <<j;
          return t1->at(index.row())->GetNameTag();
      }
  return QVariant();
  }
  if(role ==  Qt::UserRole+1){

  if (typeoutput == "GroupTag")       return QVariant((uint)lm->getGroupList()->at(index.row()) );
  if (typeoutput == "AccountTag")     return QVariant((uint)lm->getAccountList()->at(index.row()));
  if (typeoutput == "PostGroupTag")   return QVariant((uint)lm->getTagGroupList()->at(index.row()));
  if (typeoutput == "PostAccountTag") return QVariant((uint)lm->getTagAccountList()->at(index.row()));
  if (typeoutput == "Post")           return QVariant((uint)lm->getPostList()->at(index.row()));
  if (typeoutput == "QueuePost")      return QVariant((uint)lm->getQueuePostList()->at(index.row()));
  if (typeoutput == "TagGroup")       return QVariant((uint)lm->getTagGroupList()->at(index.row()));
  if (typeoutput == "TagAccount")     return QVariant((uint)lm->getTagAccountList()->at(index.row()));

      return QVariant();
  }

  if(role ==  Qt::UserRole+2){

  if (typeoutput == "GroupTag")       return QVariant((uint)lm->getTagGroupList()->at(index.column()) );
  if (typeoutput == "AccountTag")     return QVariant((uint)lm->getTagAccountList()->at(index.column()));
  if (typeoutput == "PostGroupTag")   return QVariant((uint)lm->getTagGroupList()->at(index.row()));
  if (typeoutput == "PostAccountTag") return QVariant((uint)lm->getTagAccountList()->at(index.row()));
  if (typeoutput == "Post")           return QVariant((uint)lm->getPostList()->at(index.row()));
  if (typeoutput == "QueuePost")      return QVariant((uint)lm->getQueuePostList()->at(index.row()));
  if (typeoutput == "TagGroup")       return QVariant((uint)lm->getTagGroupList()->at(index.row()));
  if (typeoutput == "TagAccount")     return QVariant((uint)lm->getTagAccountList()->at(index.row()));

      return QVariant();
  }


  if (role == Qt::TextAlignmentRole) //change text alignment only for
  {
      return Qt::AlignHCenter + Qt::AlignVCenter;
  }

  return QVariant();
}

Qt::ItemFlags MyItemModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void MyItemModel::setTypeOutput(QString to)
{
    this->typeoutput = to;
}

void MyItemModel::needReset()
{
this->dataChanged(this->index(0,0),this->index(this->rowCount(),this->columnCount()+1));
}
