#include "mymodel2.h"

MyModel2::MyModel2(Listmanager *listmanager,QObject *parent) :
    QAbstractItemModel(parent)
{
    this->lm = listmanager;
}

QModelIndex MyModel2::parent(const QModelIndex &child) const
{
     return QModelIndex();
}
bool MyModel2::hasChildren(const QModelIndex &parent) const {
  if (parent.model() == this || !parent.isValid()) {
    return rowCount(parent) > 0 && columnCount(parent) > 0;
  }
  return false;
}

Qt::ItemFlags MyModel2::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
}

void MyModel2::resetdata()
{
    beginResetModel();
    endResetModel();
}


int MyModel2::rowCount(const QModelIndex &parent) const {

  grouplist *g = lm->getGroupList();
  taglist *tg = lm->getTagGroupList();
  accountlist *a = lm->getAccountList();
  taglist *ta = lm->getTagAccountList();
  postlist *p = lm->getPostList();
  postlist *qp = lm->getQueuePostList();
  int res = 0;

  res = res<g->countitem()?g->countitem():res;
  res = res<tg->countitem()?tg->countitem():res;
  res = res<ta->countitem()?ta->countitem():res;
  res = res<a->countitem()?a->countitem():res;
  res = res<p->countitem()?p->countitem():res;
  res = res<qp->countitem()?qp->countitem():res;
  if (parent.isValid())
  switch (parent.column()) {
  case 0:
      res = g->countitem();
      break;
  case 1:
      res = tg->countitem();
      break;
  case 2:
      res = a->countitem();
      break;
  case 3:
      res = ta->countitem();
      break;
  case 4:
      res = p->countitem();
      break;
  case 5:
      res = qp->countitem();
      break;
  case 6:
      res = tg->countitem();
      break;
  case 7:
      res = ta->countitem();
      break;
  case 8:
      res = g->countitem();
      break;
  case 9:
      res = a->countitem();
      break;
  case 10:
      res = tg->countitem();
      break;
  case 11:
      res = ta->countitem();
      break;
  default:
      res=0;
      break;
  }


  return  res;
}

int MyModel2::columnCount(const QModelIndex &parent) const {


  grouplist *g = lm->getGroupList();
  taglist *tg = lm->getTagGroupList();
  accountlist *a = lm->getAccountList();
  taglist *ta = lm->getTagAccountList();
  postlist *p = lm->getPostList();
  postlist *qp = lm->getQueuePostList();
  int res =6;
  if (parent.isValid())
  switch (parent.column()) {
  case 0:
      res = tg->countitem();
      break;
  case 1:
      res = 1;
      break;
  case 2:
      res = ta->countitem();
      break;
  case 3:
      res = 1;
      break;
  case 4:
      res = 1;
      break;
  case 5:
      res = 1;
      break;
  case 6:
      res = 1;
      break;
  case 7:
      res = 1;
      break;
  case 8:
      res = 1;
      break;
  case 9:
      res = 1;
      break;
  case 10:
      res = 1;
      break;
  case 11:
      res = 1;
      break;
  default:
      res=0;

      break;
  }


  return  res;
}


QModelIndex MyModel2::index(int row, int column, const QModelIndex &parent) const {

    grouplist *g = lm->getGroupList();
    taglist *tg = lm->getTagGroupList();
    taglist *ta = lm->getTagAccountList();
    accountlist *a = lm->getAccountList();
    postlist *p = lm->getPostList();
    postlist *qp = lm->getQueuePostList();
    int res;
    res=0;
    res = res<g->countitem()?g->countitem():res;
    res = res<tg->countitem()?tg->countitem():res;
    res = res<ta->countitem()?ta->countitem():res;
    res = res<a->countitem()?a->countitem():res;
    res = res<p->countitem()?p->countitem():res;
    res = res<qp->countitem()?qp->countitem():res;

  if (parent.isValid())                                   {return QModelIndex();}
  if (row    < 0 || row    >= res)   {return QModelIndex();}
  if (column < 0 || column >= 12) {return QModelIndex();}

  switch (column) {
  case 0:
      if (row    < 0 ||row    >= g->countitem())    {return QModelIndex();}
      break;
  case 1:
      if (row    < 0 || row    >= tg->countitem())    {return QModelIndex();}
      break;
  case 2:
      if (row    < 0 || row    >= a->countitem())    {return QModelIndex();}
      break;
  case 3:
      if (row    < 0 || row    >= ta->countitem())    {return QModelIndex();}
      break;
  case 4:
      if (row    < 0 || row    >= p->countitem())    {return QModelIndex();}
      break;
  case 5:
      if (row    < 0 || row    >= qp->countitem())    {return QModelIndex();}
      break;
  case 6:
      if (row    < 0 || row    >= tg->countitem())    {return QModelIndex();}
      break;
  case 7:
      if (row    < 0 || row    >= ta->countitem())    {return QModelIndex();}
      break;
  case 8:
      if (row    < 0 || row    >= g->countitem())    {return QModelIndex();}
      break;
  case 9:
      if (row    < 0 || row    >= a->countitem())    {return QModelIndex();}
      break;
  case 10:
      if (row    < 0 || row    >= tg->countitem())    {return QModelIndex();}
      break;
  case 11:
      if (row    < 0 || row    >= ta->countitem())    {return QModelIndex();}
      break;
  default:
      return QModelIndex();
      break;
  }
  return createIndex(row, column, (void*)NULL);
}


QVariant MyModel2::data(const QModelIndex &index, int role) const {

 if (!index.isValid())                                                  {return QVariant();}

  grouplist *g = lm->getGroupList();
  taglist *tg = lm->getTagGroupList();
  accountlist *a = lm->getAccountList();
  taglist *ta = lm->getTagAccountList();
  postlist *p = lm->getPostList();
  postlist *qp = lm->getQueuePostList();
  int res;
  res=0;
  res = res<g->countitem()?g->countitem():res;
  res = res<tg->countitem()?tg->countitem():res;
  res = res<ta->countitem()?ta->countitem():res;
  res = res<a->countitem()?a->countitem():res;
  res = res<p->countitem()?p->countitem():res;
  res = res<qp->countitem()?qp->countitem():res;


  if  (role == Qt::DisplayRole){

          if (index.row()    < 0 || index.row()    >= res)    {return QVariant();}
          if (index.column() < 0 || index.column() >= 6)  {return QVariant();}
          switch (index.column()) {
          case 0:
              if (index.row()    < 0 || index.row()    >= g->countitem())    {return QVariant();}

              return QVariant(g->at(index.row())->getName());

          case 1:
              if (index.row()    < 0 || index.row()    >= tg->countitem())    {return QVariant();}

              return QVariant(tg->at(index.row())->getName());
              break;
          case 2:
              if (index.row()    < 0 || index.row()    >= a->countitem())    {return QVariant();}

              return QVariant(a->at(index.row())->getName());
              break;
          case 3:
              if (index.row()    < 0 || index.row()    >= ta->countitem())    {return QVariant();}

              return QVariant(ta->at(index.row())->getName());
              break;
          case 4:
              if (index.row()    < 0 || index.row()    >= p->countitem())    {return QVariant();}

              return QVariant(p->at(index.row())->getName());
              break;
          case 5:
              if (index.row()    < 0 || index.row()    >= qp->countitem())    {return QVariant();}

              return QVariant(qp->at(index.row())->getName());
              break;
          default:
              return QVariant();
              break;
          }
      }

  if  (role == Qt::UserRole+1){                            // группы с тегами
      if (index.row()    < 0 || index.row()    >= g->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= tg->countitem())  {return QVariant();}
      if (g->at(index.row())->tagin(tg->at(index.column()))) return "V";

      else return "";
  }

  if  (role == Qt::UserRole+2){                               // теги для групп
      if (index.row()    < 0 || index.row()    >= tg->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (index.column()==0) return tg->at(index.row())->getName();
  }

  if  (role == Qt::UserRole+3){                               // аккаунты
      if (index.row()    < 0 || index.row()    >= a->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= ta->countitem())  {return QVariant();}

      if (a->at(index.row())->tagin(ta->at(index.column()))) return "V";
  }

  if  (role == Qt::UserRole+4){                               // теги для аккаунтов
      if (index.row()    < 0 || index.row()    >= ta->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (index.column()==0) return ta->at(index.row())->getName();
  }

  if  (role == Qt::UserRole+5){                                 // посты
      if (index.row()    < 0 || index.row()    >= p->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (index.column()==0) return p->at(index.row())->getName();
  }

  if  (role == Qt::UserRole+6){                                  // очередь постов на отправку
      if (index.row()    < 0 || index.row()    >= qp->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (index.column()==0) return qp->at(index.row())->getName();
  }

  if  (role == Qt::UserRole+7){                                  // теги групп для текущего поста
      if (index.row()    < 0 || index.row()    >= tg->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentPost()!=NULL){
          if (lm->getCurrentPost()->getTagforGroup()->iteminlist(tg->at(index.row()))) return "V";
          else return "";}
      return QVariant();
  }
  if  (role == Qt::UserRole+8){                                  // теги аккаунтов для текущего поста
      if (index.row()    < 0 || index.row()    >= ta->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentPost()!=NULL){
          if (lm->getCurrentPost()->getTagforAccount()->iteminlist(ta->at(index.row()))) return "V";
          else return "";}
      return QVariant();
  }

  if (role == Qt::UserRole+9){   // группы для поста в очереди
      if (index.row()    < 0 || index.row()    >= g->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentQueuePost()!=NULL){
          QVariant res = QVariant("");
          taglist *tgp = lm->getCurrentQueuePost()->getTagforGroup();
          for (int i=0; i< tgp->countitem();i++ ){
              if (g->at(index.row())->tagin(tgp->at(i))) res = QVariant(g->at(index.row())->getName());
          }
          return res;
      }
      return QVariant();
  }

  if (role == Qt::UserRole+10){   // аккаунты для поста в очереди
      if (index.row()    < 0 || index.row()    >= a->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentQueuePost()!=NULL){
          QVariant res = QVariant("");
          taglist *tap = lm->getCurrentQueuePost()->getTagforAccount();
          for (int i=0; i< tap->countitem();i++ ){
              if (a->at(index.row())->tagin(tap->at(i))) res = QVariant(a->at(index.row())->getName());
          }
          return res;
      }
      return QVariant();
  }

  if  (role == Qt::UserRole+11){                                  // теги групп для текущего поста в очереди
      if (index.row()    < 0 || index.row()    >= tg->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentQueuePost()!=NULL){
          if (lm->getCurrentQueuePost()->getTagforGroup()->iteminlist(tg->at(index.row()))) return "V";
          else return "";}
      return QVariant();
  }
  if  (role == Qt::UserRole+12){                                  // теги аккаунтов для текущего поста в очереди
      if (index.row()    < 0 || index.row()    >= ta->countitem())    {return QVariant();}
      if (index.column() < 0 || index.column() >= 1)  {return QVariant();}
      if (lm->getCurrentQueuePost()!=NULL){
          if (lm->getCurrentQueuePost()->getTagforAccount()->iteminlist(ta->at(index.row()))) return "V";
          else return "";}
      return QVariant();
  }





  if (role == Qt::TextAlignmentRole) //change text alignment only for
  {
      return Qt::AlignHCenter + Qt::AlignVCenter;
  }
      return QVariant();
  }


QVariant MyModel2::headerData(int section, Qt::Orientation orientation, int role) const
{
    grouplist *g = lm->getGroupList();
    taglist *tg = lm->getTagGroupList();
    accountlist *a = lm->getAccountList();
    taglist *ta = lm->getTagAccountList();
    postlist *p = lm->getPostList();
    postlist *qp = lm->getQueuePostList();
    switch (role) {
    case Qt::UserRole+1:
        if (orientation == Qt::Horizontal) {if (tg->countitem()<=0) return QVariant();
                                            qDebug() << tg->at(section)->getCountItem();return QVariant(tg->at(section)->getName()+": "+QString::number(tg->at(section)->getCountItem()));}
        if (g->countitem()<=0) return QVariant();
        return QVariant(QString::number(section+1)+". "+g->at(section)->getName().left(35)+ (g->at(section)->getName().size()>35?"...":""));
    case Qt::UserRole+2:
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1));//+". "+tg->at(section)->getName().left(35));
    case Qt::UserRole+3:
        if (orientation == Qt::Horizontal) {if (ta->countitem()<=0) return QVariant();
                                            qDebug() << ta->at(section)->getCountItem(); return QVariant(ta->at(section)->getName()+": "+QString::number(ta->at(section)->getCountItem()));}
        if (a->countitem()<=0) return QVariant();
        return QVariant(QString::number(section+1)+". "+a->at(section)->getName().left(35));
    case Qt::UserRole+4:
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1));//+". "+ta->at(section)->getName().left(35));
    case Qt::UserRole+5:
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1));//+". "+p->at(section)->getName().left(35));
    case Qt::UserRole+6:
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1));//+". "+qp->at(section)->getName().left(35));
    case Qt::UserRole+7:
        if (tg->countitem()<=0) return QVariant();
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1)+". "+tg->at(section)->getName().left(35));
    case Qt::UserRole+8:
        if (ta->countitem()<=0) return QVariant();
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1)+". "+ta->at(section)->getName().left(35));
        break;
    case Qt::UserRole+9:
        return QVariant(QString::number(section+1));
        break;
    case Qt::UserRole+10:
        return QVariant(QString::number(section+1));
        break;
    case Qt::UserRole+11:
        if (tg->countitem()<=0) return QVariant();
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1)+". "+tg->at(section)->getName().left(35));
    case Qt::UserRole+12:
        if (ta->countitem()<=0) return QVariant();
        if (orientation == Qt::Horizontal)return QVariant(QString::number(section+1));
        return QVariant(QString::number(section+1)+". "+ta->at(section)->getName().left(35));
        break;

    case Qt::DisplayRole:
        if (orientation == Qt::Horizontal)
        switch (section) {
        case 0:  return "Group";
        case 1:  return "Tag for Group";
        case 2:  return "Account";
        case 3:  return "Tag for Account";
        case 4:  return "Post";
        case 5:  return "Queue Post";
        default:
            return section+1;

        }
        return section+1;

    }
    return QVariant();
}


bool MyModel2::setData(const QModelIndex &index, const QVariant &value, int role)
{
     qDebug()<< "ггг1";

    grouplist *g = lm->getGroupList();
    taglist *tg = lm->getTagGroupList();
    accountlist *a = lm->getAccountList();
    taglist *ta = lm->getTagAccountList();
    postlist *p = lm->getPostList();
    postlist *qp = lm->getQueuePostList();

    if (!index.isValid() && !( ((role == Qt::UserRole+2)&&(tg->countitem()==0)) ||
                               ((role == Qt::UserRole+4) && (ta->countitem()==0))  )) return false;

    QStringList slp;
    switch (role) {
    case Qt::UserRole+1:    // установка галки таг-группа и добавление группы при наличии валидного Value
        if (value.isValid()){
            slp = value.toStringList();
            beginResetModel();
            bool b = lm->addGroup(slp);
            endResetModel();
            return b;
        }
        if (g->countitem()==0 || tg->countitem()==0 ) return false;
        if (g->at(index.row())->tagin(tg->at(index.column()))) lm->removetagfrom(tg->at(index.column()),g->at(index.row()));
        else lm->addTagto(tg->at(index.column()),g->at(index.row()));
        //dataChanged(index,index);
        emit headerDataChanged(Qt::Horizontal,index.column(),index.column());
        return true;

    case Qt::UserRole+2:  // добавлене тага для групп
        {
        beginResetModel();
        bool b = false;
        if (value.isValid())
            if (!value.toStringList().count()<2){
            if (value.toStringList().at(0) == "new")
                if (lm->addTagGroup(value.toStringList().at(1))!=NULL) {
                  qDebug()<< "Тег добавлен";   b = true;
                  }
            if ((value.toStringList().at(0) == "update"))
                if (lm->updateTagGroup(lm->getCurrentTagGroup(),value.toStringList().at(1))== true) {
                  qDebug()<< "Тег обновлен";   b = true;
                  }
           }
        endResetModel();
        return b;
        }

    case Qt::UserRole+3:     // установка галки таг-аккаунт  и добавление аккаунта при наличии валидного Value
        if (value.isValid()) {
            slp = value.toStringList();
            beginResetModel();
            bool b = lm->addAccount(slp);
            endResetModel();
            return b;
        }
        if (a->countitem()==0 || ta->countitem()==0 ) return false;
        if (a->at(index.row())->tagin(ta->at(index.column()))) lm->removetagfrom(ta->at(index.column()),a->at(index.row()));
        else lm->addTagto(ta->at(index.column()),a->at(index.row()));
        emit headerDataChanged(Qt::Horizontal,index.column(),index.column());
        // emit this->dataChanged(index,index);
        return true;

    case Qt::UserRole+4:     // добавление тага для аккаунтов при валидном value
       {
        bool b = false;
        beginResetModel();
        if (value.isValid())
            if (!value.toStringList().count()<2){
                if ((value.toStringList().at(0) == "new"))
                    if (lm->addTagAccount(value.toStringList().at(1))!=NULL) b= true;
                if ((value.toStringList().at(0) == "update"))
                    b = lm->updateTagAccount(lm->getCurrentTagAccount(),value.toStringList().at(1));
            }
        endResetModel();
        return b;
        }
    case Qt::UserRole+5:     // добавление или апдейт нового поста
        if (!value.isValid()) return false;

        slp = value.toStringList();
        if(slp.count()<4) return false;
         {
         bool b;
         b=false;
         beginResetModel();
         if (slp.at(0)== "new")    {if (lm->addPost(slp.at(1),slp.at(2),slp.at(3))==NULL)                   b= false;
                                   else                                                                    b= true;}
         if (slp.at(0)== "update") {if (lm->updatePost(lm->getCurrentPost(),slp.at(1),slp.at(2),slp.at(3))) b= false;
                                   else                                                                    b= true;}
         endResetModel();
         return b;
         }
    case Qt::UserRole+6:     // добавление поста в очередь
    {   bool b;
        beginResetModel();
        b = lm->addPosttoQueue(lm->getCurrentPost());
        endResetModel();
        return b;
    }

    case Qt::UserRole+7:     // добавление тагов групп для поста
        if (lm->getCurrentPost()==NULL) return false;
        if (lm->getCurrentPost()->getTagforGroup()->iteminlist(tg->at(index.row())))
            qDebug()<<   lm->removePostTagfromGroup(tg->at(index.row()),lm->getCurrentPost());
        else  qDebug()<<  lm->addPostTagtoGroup(tg->at(index.row()),lm->getCurrentPost());
        emit updatefilter();
        return true;

    case Qt::UserRole+8:      // добавление тагов аккаунтов для поста
        if (lm->getCurrentPost()==NULL) return false;
        if (lm->getCurrentPost()->getTagforAccount()->iteminlist(ta->at(index.row())))
            qDebug()<<  lm->removePostTagfromAccount(ta->at(index.row()),lm->getCurrentPost());
        else qDebug()<< lm->addPostTagtoAccount(ta->at(index.row()),lm->getCurrentPost());
        emit updatefilter();
        return true;
    case Qt::UserRole+11:     // добавление тагов групп для поста в очереди
        if (lm->getCurrentQueuePost()==NULL) return false;
        if (lm->getCurrentQueuePost()->getTagforGroup()->iteminlist(tg->at(index.row())))
            qDebug()<<   lm->removePostTagfromGroup(tg->at(index.row()),lm->getCurrentQueuePost());
        else  qDebug()<<  lm->addPostTagtoGroup(tg->at(index.row()),lm->getCurrentQueuePost());
        emit updatefilter();
        return true;

    case Qt::UserRole+12:      // добавление тагов аккаунтов для поста в очереди
        if (lm->getCurrentQueuePost()==NULL) return false;
        if (lm->getCurrentQueuePost()->getTagforAccount()->iteminlist(ta->at(index.row())))
            qDebug()<<  lm->removePostTagfromAccount(ta->at(index.row()),lm->getCurrentQueuePost());
        else qDebug()<< lm->addPostTagtoAccount(ta->at(index.row()),lm->getCurrentQueuePost());
        emit updatefilter();
        return true;











    case Qt::UserRole+100:   // установка текущего поста
        if (!index.isValid()) return false;
        if ((0>index.row()) || (index.row()>=p->countitem())) return false;
        beginResetModel();
        lm->setCurrentPost(p->at(index.row()));
        qDebug()<< "Обновление текущего поста";
        endResetModel();
        return true;

    case Qt::UserRole+101:  // установка текущего поста в очереди
        if (!index.isValid()) return false;
        if ((0>index.row()) || (index.row()>=qp->countitem())) return false;
        beginResetModel();
        lm->setCurrentQueuePost(qp->at(index.row()));
        qDebug()<< "Обновление текущего поста в очереди";
        endResetModel();
        emit updatefilter();
        return true;

    case Qt::UserRole+102:  // установка текущей группы
        qDebug()<< "гг1";
        if (!index.isValid()) return false;
         qDebug()<< "гг2";
        if ((0>index.row()) || (index.row()>=g->countitem())) return false;
         qDebug()<< "гг3";
        //beginResetModel();
         qDebug()<< "гг4";
        lm->setCurrentGroup(g->at(index.row()));
        qDebug()<< "Обновление текущей группы";
        //endResetModel();
        return true;

    case Qt::UserRole+103:  // установка текущего аккаунта
        if (!index.isValid()) return false;
        if ((0>index.row()) || (index.row()>=a->countitem())) return false;
        //beginResetModel();
        lm->setCurrentAccount(a->at(index.row()));
        qDebug()<< "Обновление текущего аккаунта";
        //endResetModel();
        return true;

    case Qt::UserRole+104:  // установка текущего тега для групп
        if (!index.isValid()) return false;
        if ((0>index.row()) || (index.row()>=tg->countitem())) return false;
        //beginResetModel();
        lm->setCurrentTagGroup(tg->at(index.row()));
        qDebug()<< "Обновление текущего тега для групп";
        //endResetModel();
        return true;

    case Qt::UserRole+105:  // установка текущего тега для аккаунтов
        if (!index.isValid()) return false;
        if ((0>index.row()) || (index.row()>=ta->countitem())) return false;
        //beginResetModel();
        lm->setCurrentTagAccount(ta->at(index.row()));
        qDebug()<< "Обновление текущего тега для аккаунта";
        //endResetModel();

        return true;

    default:
        return false;
        break;
    }

    return false;

}


bool MyModel2::removeRows(int row, int count, const QModelIndex &parent)
{

    bool res = false;
    if (!parent.isValid()) return false;

    beginResetModel();
    switch (parent.column()) {
    case 0:
        if (lm->getCurrentGroup()==NULL)  break;
        if (lm->removeGroup(lm->getCurrentGroup())) res = true;
        break;
    case 1:
        if (lm->getCurrentTagGroup()==NULL) break;
        if (lm->removetag(lm->getCurrentTagGroup())) res = true;
        break;
    case 2:
        if (lm->getCurrentAccount()==NULL) break;
        if (lm->removeAccount(lm->getCurrentAccount())) res = true;
        break;
    case 3:
        if (lm->getCurrentTagAccount()==NULL) break;
        if (lm->removetag(lm->getCurrentTagAccount())) res = true;
        break;
    case 4:
        if (lm->getCurrentPost()==NULL) break;
        if (lm->removePost(lm->getCurrentPost())) res = true;
        break;
    case 5:
        if (lm->getCurrentQueuePost()==NULL) break;
        if (lm->removePostfromQueue(lm->getCurrentQueuePost())) res = true;
        break;
    default:
        //if (lm->getCurrentTagGroup()==NULL) return false;
        res = false;
        break;

    }
    qDebug()<<"хедеры";
    endResetModel();
    return res;
}





