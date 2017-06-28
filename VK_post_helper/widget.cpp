#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lm = new Listmanager(this);
    vkm = new VKmanager(this);


    this->activequeue = false;

    connect(vkm,SIGNAL(receivedNewAccount(QStringList&)),this,SLOT(newAccount(QStringList&)));
    connect(vkm,SIGNAL(receivedNewGroup(QStringList&)),this,SLOT(newGroup(QStringList&)));
    connect(vkm,SIGNAL(receivedSearshGroup(QStringList&,int,int)),this,SLOT(newSearshGroupResult(QStringList&,int,int)));
    connect(vkm,SIGNAL(SentPost(post*,group*,account*,QString&,bool)),this,SLOT(newSentPost(post*,group*,account*,QString&,bool)));
    connect(vkm,SIGNAL(SentPostFinishvkm()),this,SLOT(startSendNextPost()));
    connect(this,SIGNAL(SentPostFinishw()),SLOT(startSendNextPost()));
    connect(this,SIGNAL(putActiveSendingPost(bool)),vkm,SLOT(setActiveSendingPost(bool)));


    connect(ui->tableWidget_resultSearshGroup->verticalScrollBar(), SIGNAL(valueChanged(int)),ui->tableWidget_tagforsearshgroup->verticalScrollBar(), SLOT(setValue(int)));

    connect(ui->tableWidget_tagforsearshgroup->verticalScrollBar(), SIGNAL(valueChanged(int)),ui->tableWidget_resultSearshGroup->verticalScrollBar(), SLOT(setValue(int)));

    connect(vkm,SIGNAL(StringtoLog(QString&,bool,QColor)),this,SLOT(toLog(QString&,bool,QColor)));
    connect(this,SIGNAL(StringtoLog(QString&,bool,QColor)),SLOT(toLog(QString&,bool,QColor)));
    //connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(reloadgroupslot(int)));

    //  ui->tableWidget_tagforsearshgroup->set

//    this->reloadtag();
//    this->reloadgroup();
//    this->reloadaccount();
//    this->reloadpost();
//    this->reloadQueuePost();


//    QHeaderView *hvt = ui->tableWidget_grouptag->horizontalHeader();
//    connect((QObject*)hvt, SIGNAL(sectionDoubleClicked (int)), this, SLOT(mySlotGroupTagH(int)));
//    QHeaderView *hvg = ui->tableWidget_grouptag->verticalHeader();
//    connect((QObject*)hvg, SIGNAL(sectionDoubleClicked (int)), this, SLOT(mySlotGroupTagV(int)));

//    hvt = ui->tableWidget_accounttag->horizontalHeader();
//    connect((QObject*)hvt, SIGNAL(sectionDoubleClicked (int)), this, SLOT(mySlotAccountTagH(int)));
//    QHeaderView *hva = ui->tableWidget_accounttag->verticalHeader();
//    connect((QObject*)hva, SIGNAL(sectionDoubleClicked (int)), this, SLOT(mySlotAccountTagV(int)));

//    myitemmodel = new MyItemModel(lm,this);
//    myitemmodel->setTypeOutput("GroupTag");

    myitemmodel_foraccounttag = new MyItemModel(lm,this);
    myitemmodel_foraccounttag->setTypeOutput("TagAccount");
    //ui->tableView_tagforsearshgroup->setModel(myitemmodel);
//    ui->tableView_foraccounttag->setModel(myitemmodel_foraccounttag);

//    qDebug()<< ui->tableView_foraccounttag->model()->columnCount();
    //qDebug()<< ui->tableView_tagforsearshgroup->model()->columnCount();
    mymodel_all = new MyModel2(lm,this);
    ui->tableView->setModel(mymodel_all);
    myproxymodel1 = new MyProxyModelGT(0,this);
    myproxymodel2 = new MyProxyModelGT(2,this);
    myproxymodel3 = new MyProxyModelGT(1,this);
    myproxymodel4 = new MyProxyModelGT(3,this);
    myproxymodel5 = new MyProxyModelGT(4,this);
    myproxymodel6 = new MyProxyModelGT(5,this);
    myproxymodel7 = new MyProxyModelGT(6,this);
    myproxymodel8 = new MyProxyModelGT(7,this);
    myproxymodel9 = new MyProxyModelGT(8,this);
    myproxymodel10 = new MyProxyModelGT(9,this);
    myproxymodel11 = new MyProxyModelGT(10,this);
    myproxymodel12 = new MyProxyModelGT(11,this);

    myfiltermodel1 = new myfiltermodel(this);
    myfiltermodel2 = new myfiltermodel(this);

    myproxymodel1->setSourceModel(mymodel_all);
    ui->tableView_2_grouptag->setModel(myproxymodel1);
    myproxymodel2->setSourceModel(mymodel_all);
    ui->tableView_3_accounttag->setModel(myproxymodel2);
    myproxymodel3->setSourceModel(mymodel_all);
    ui->tableView_4_taglistforgroup->setModel(myproxymodel3);
    myproxymodel4->setSourceModel(mymodel_all);
    ui->tableView_5_taglistforaccount->setModel(myproxymodel4);
    myproxymodel5->setSourceModel(mymodel_all);
    ui->tableView_6_post->setModel(myproxymodel5);
    myproxymodel6->setSourceModel(mymodel_all);
    ui->tableView_7_queuepost->setModel(myproxymodel6);
    myproxymodel7->setSourceModel(mymodel_all);
    ui->tableView_8_taggroupfotpost->setModel(myproxymodel7);
    myproxymodel8->setSourceModel(mymodel_all);
    ui->tableView_9_tagaccountforpost->setModel(myproxymodel8);
    myproxymodel9->setSourceModel(mymodel_all);
    myfiltermodel1->setSourceModel(myproxymodel9);
    ui->tableView_10_groupforqueuepost->setModel(myfiltermodel1);
    myproxymodel10->setSourceModel(mymodel_all);
    myfiltermodel2->setSourceModel(myproxymodel10);
    ui->tableView_11_accountforqueuepost->setModel( myfiltermodel2);

    myproxymodel11->setSourceModel(mymodel_all);
    ui->tableView_12_taggroupfotqueuepost->setModel(myproxymodel11);
    myproxymodel12->setSourceModel(mymodel_all);
    ui->tableView_13_tagaccountforqueuepost->setModel(myproxymodel12);



    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel1,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel2,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel3,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel4,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel5,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel6,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel7,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel8,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel9,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel10,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel11,SLOT(resetdata()));
    connect(mymodel_all,SIGNAL(modelReset()),myproxymodel12,SLOT(resetdata()));


    connect(mymodel_all,SIGNAL(updatefilter()),myfiltermodel1,SLOT(updatefilter()));
    connect(mymodel_all,SIGNAL(updatefilter()),myfiltermodel2,SLOT(updatefilter()));

    QHeaderView *hvgtV = ui->tableView_2_grouptag->verticalHeader();
    connect(hvgtV,SIGNAL(sectionClicked(int)),this,SLOT(mySlotGroupTagV(int)));//(QObject*)
    QHeaderView *hvatV = ui->tableView_3_accounttag->verticalHeader();
    connect(hvatV,SIGNAL(sectionClicked(int)),this,SLOT(mySlotAccountTagV(int)));//(QObject*)
    QHeaderView *hvgtH = ui->tableView_2_grouptag->horizontalHeader();
    connect(mymodel_all, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), hvgtH,SLOT(headerDataChanged(Qt::Orientation,int,int)));
    QHeaderView *hvatH = ui->tableView_3_accounttag->horizontalHeader();
    connect(mymodel_all, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), hvatH,SLOT(headerDataChanged(Qt::Orientation,int,int)));


//        this->reloadtag();
//        this->reloadgroup();
//        this->reloadaccount();
//        this->reloadpost();
//        this->reloadQueuePost();
        maxsending=0;
        errorsending=0;
        successsending=0;
     this->max_items_in_searshgrouplist = 0;
     this->maxsending = lm->getCountMaxSending();
     ui->label_9_max_sending->setText(QString::number(maxsending));

     log_file = new QFile("logfile.txt");
if (lm->getPostList()->countitem()>0) lm->setCurrentPost(lm->getPostList()->at(0));
if (lm->getQueuePostList()->countitem()>0) lm->setCurrentQueuePost(lm->getQueuePostList()->at(0));
ui->label_31_countgroup->setText(QString::number(lm->getGroupList()->countitem()));
}

Widget::~Widget()
{
    delete ui;

}

//void Widget::setTagforGroup(int row, int col, int stat)
//{
//        ui->tableWidget_grouptag->setCurrentCell(row,col);

//        QWidget *w =  ui->tableWidget_grouptag->cellWidget(row,col);
//        QCheckBoxTagforGroup* cb = dynamic_cast <QCheckBoxTagforGroup*>(w);

//        switch (stat) {
//        case 1:
//            if (!cb->ischekedBox()){
//                   lm->addTagto(cb->getTag(),cb->getGroup());
//                   cb->checkedBox();
//                   }
//            break;
//        case -1:
//            if (cb->ischekedBox()){
//                lm->removetagfrom(cb->getTag(),cb->getGroup());
//                cb->checkedBox();
//                }
//            break;
//        case 0:
//            cb->checkedBox();
//            if (cb->ischekedBox())lm->addTagto(cb->getTag(),cb->getGroup());
//             else lm->removetagfrom(cb->getTag(),cb->getGroup());
//            break;
//        }
//}

//void Widget::setTagforAccount(int row, int col, int stat)
//{
//        ui->tableWidget_accounttag->setCurrentCell(row,col);

//        QWidget *w =  ui->tableWidget_accounttag->cellWidget(row,col);
//        QCheckBoxTagforAccount* cb = dynamic_cast <QCheckBoxTagforAccount*>(w);

//        switch (stat) {
//        case 1:
//            if (!cb->ischekedBox()){
//                   lm->addTagto(cb->getTag(),cb->getAccount());
//                   cb->checkedBox();
//                   }
//            break;
//        case -1:
//            if (cb->ischekedBox()){
//                lm->removetagfrom(cb->getTag(),cb->getAccount());
//                cb->checkedBox();
//                }
//            break;
//        case 0:
//            cb->checkedBox();
//            if (cb->ischekedBox())lm->addTagto(cb->getTag(),cb->getAccount());
//             else lm->removetagfrom(cb->getTag(),cb->getAccount());
//            break;
//        }
//}

//void Widget::setPostTagforGroup(int row, int col, int stat)
//{
//    ui->tableWidget_tagpostforgroup->setCurrentCell(row,col);

//    QWidget *w =  ui->tableWidget_tagpostforgroup->cellWidget(row,col);
//    QCheckBoxPostTagforAG* cb = dynamic_cast <QCheckBoxPostTagforAG*>(w);

//    switch (stat) {
//    case 1:
//        if (!cb->ischekedBox()){
//               lm->addPostTagtoGroup(cb->getTag(),cb->getPost());
//               cb->checkedBox();
//               }
//        break;
//    case -1:
//        if (cb->ischekedBox()){
//            lm->removePostTagfromGroup(cb->getTag(),cb->getPost());
//            cb->checkedBox();
//            }
//        break;
//    case 0:
//        cb->checkedBox();
//        if (cb->ischekedBox())lm->addPostTagtoGroup(cb->getTag(),cb->getPost());
//         else lm->removePostTagfromGroup(cb->getTag(),cb->getPost());
//        break;
//    }
//}

//void Widget::setPostTagforAccount(int row, int col, int stat)
//{
//    ui->tableWidget_tagpostforaccount->setCurrentCell(row,col);

//    QWidget *w =  ui->tableWidget_tagpostforaccount->cellWidget(row,col);
//    QCheckBoxPostTagforAG* cb = dynamic_cast <QCheckBoxPostTagforAG*>(w);

//    switch (stat) {
//    case 1:
//        if (!cb->ischekedBox()){
//               lm->addPostTagtoAccount(cb->getTag(),cb->getPost());
//               cb->checkedBox();
//               }
//        break;
//    case -1:
//        if (cb->ischekedBox()){
//            lm->removePostTagfromAccount(cb->getTag(),cb->getPost());
//            cb->checkedBox();
//            }
//        break;
//    case 0:
//        cb->checkedBox();
//        if (cb->ischekedBox())lm->addPostTagtoAccount(cb->getTag(),cb->getPost());
//         else lm->removePostTagfromAccount(cb->getTag(),cb->getPost());
//        break;
//    }
//}

void Widget::mySlotGroupTagV(int numRow)
{

QModelIndex index = this->mymodel_all->index(numRow,0);
this->mymodel_all->setData(index,QVariant(),Qt::UserRole+102);
ui->label_31_groupname->setText("Имя группы: "+lm->getCurrentGroup()->getName());



//    for (int col = 0; col < ui->tableWidget_grouptag->columnCount();col++){this->setTagforGroup(numRow,col,(ui->CheckBox_forTagGroup->isChecked()?1:-1)); }
//   qDebug() << "row" << numRow;
}

void Widget::mySlotGroupTagH(int numCol)
{
  qDebug() << "col" << numCol;

// for (int row = 0; row < ui->tableWidget_grouptag->rowCount();row++){this->setTagforGroup(row,numCol,(ui->CheckBox_forTagGroup->isChecked()?1:-1)); }
}

void Widget::mySlotAccountTagV(int numRow)
{
    QModelIndex index = this->mymodel_all->index(numRow,0);
    this->mymodel_all->setData(index,QVariant(),Qt::UserRole+103);
}

void Widget::mySlotAccountTagH(int numCol)
{
//    for (int row = 0; row < ui->tableWidget_accounttag->rowCount();row++){this->setTagforAccount(row,numCol,(ui->checkBox_accounttag->isChecked()?1:-1)); }
    qDebug() << "col" << numCol;
}




//void Widget::on_tableWidget_taglist_clicked(const QModelIndex &index)
//{
//    if (!index.isValid()) return;
//    ui->tableWidget_taglist->setCurrentCell(index.row(),index.column());
//    QWidget *w =  ui->tableWidget_taglist->cellWidget(index.row(),index.column());
//    QLineEditforTag* lt = dynamic_cast <QLineEditforTag*>(w);
//    ui->lineEdit_tagname->setText(lt->getTag()->GetNameTag());

//}

void Widget::on_pushButton_2_newtag_clicked()
{

    if (ui->lineEdit_tagname->text()== "") {QMessageBox::warning(0,"Пустой тег!", "Пустое имя тега! Исправить!"); return;}
    QModelIndex index = this->mymodel_all->index(0,1);
    QStringList sl;
    sl<< "new" << ui->lineEdit_tagname->text();
    this->myproxymodel3->setData(index,QVariant(sl),Qt::UserRole+2);
    ui->tableView_4_taglistforgroup->reset();


//    tag *t = lm->addTagGroup(ui->lineEdit_tagname->text());
//    if (t == NULL) return;
//    ui->tableWidget_taglist->setRowCount(ui->tableWidget_taglist->rowCount()+1);
//    QLineEditforTag *LEforTag = new QLineEditforTag(t,this);
//    ui->tableWidget_taglist->setCellWidget(ui->tableWidget_taglist->rowCount()-1, 0, LEforTag);
//    //this->reloadgroup();
//    this->reloadaccount();
//    this->reloadPostTag();
//    this->reloadQueuePostTag();

}

void Widget::on_pushButton_3_deltag_clicked()
{
    QModelIndex index = this->mymodel_all->index(0,1);
    this->myproxymodel3->removeRows(0,0,index);
    ui->tableView_4_taglistforgroup->reset();

//    int row = ui->tableWidget_taglist->currentRow();
//    int col = ui->tableWidget_taglist->currentColumn();
//    if ((row == -1) || (col == -1)) return;
//    QWidget *w =  ui->tableWidget_taglist->cellWidget(row,col);
//    QLineEditforTag* lt = dynamic_cast <QLineEditforTag*>(w);
//    lm->removetag(lt->getTag());
//    this->reloadtag();
//    //this->reloadgroup();
//    this->reloadaccount();
//    this->reloadPostTag();
//    this->reloadQueuePostTag();

}

//void Widget::reloadtag()
//{
//    ui->tableWidget_taglist->clear();
//    taglist *tagl = lm->getTagGroupList();
//    ui->tableWidget_taglist->setColumnCount(1);
//    ui->tableWidget_taglist->setRowCount(tagl->countitem());
//    ui->tableWidget_taglist->setHorizontalHeaderLabels(QStringList("Имя тега"));
//    tagl->begin();
//    for(int row=0; row<ui->tableWidget_taglist->rowCount(); row++){
//            QLineEditforTag * LEforTag = new QLineEditforTag(tagl->nextitem(),this);
//            ui->tableWidget_taglist->setCellWidget(row, 0, LEforTag);
//    }

//}

//void Widget::reloadgroup()
//{
//ui->tableWidget_grouptag->setColumnCount(lm->countTagGroup());
//ui->tableWidget_grouptag->setRowCount(lm->countGroup());

//ui->tableWidget_grouptag->setHorizontalHeaderLabels(lm->getNameTagGroupList());
//ui->tableWidget_grouptag->setVerticalHeaderLabels(lm->getNameGroupList());
//grouplist *gl = lm->getGroupList();
//taglist *tl = lm->getTagGroupList();
//gl->begin();

//for(int row=0; row<gl->countitem();row++){
//    group *g = gl->nextitem();
//    tl->begin();
//    for(int col=0;col<tl->countitem();col++)
//    {
//        tag *t =tl->nextitem();
//        QCheckBoxTagforGroup *CBTagforGroup = new QCheckBoxTagforGroup(t,g,this);


//        ui->tableWidget_grouptag->setCellWidget(row, col, CBTagforGroup);
//    }
//}

//}

//void Widget::reloadaccount()
//{
//    ui->tableWidget_accounttag->setColumnCount(lm->countTagAccount());
//    ui->tableWidget_accounttag->setRowCount(lm->countAccount());

//    ui->tableWidget_accounttag->setHorizontalHeaderLabels(lm->getNameTagAccountList());
//    ui->tableWidget_accounttag->setVerticalHeaderLabels(lm->getNameAccountList());
//    accountlist *al = lm->getAccountList();
//    taglist *tl = lm->getTagAccountList();
//    al->begin();

//    for(int row=0; row<al->countitem();row++){
//        account *a = al->nextitem();
//        tl->begin();
//        for(int col=0;col<tl->countitem();col++)
//        {
//            tag *t =tl->nextitem();
//            QCheckBoxTagforAccount *CBTagforAccount = new QCheckBoxTagforAccount(t,a,this);
//            ui->tableWidget_accounttag->setCellWidget(row, col, CBTagforAccount);
//        }
//    }
//}

//void Widget::reloadpost()
//{

//    ui->tableWidget_post->setColumnCount(1);
//    ui->tableWidget_post->setRowCount(lm->countPost());
//    postlist *pl = lm->getPostList();
//    pl->begin();
//    for (int row = 0; row < lm->countPost(); row++ ){
//        QLabelforPost *lp = new QLabelforPost(pl->nextitem(),this);
//        ui->tableWidget_post->setCellWidget(row,0,lp);
//    }

//    QModelIndex index = ui->tableWidget_post->currentIndex();
//    if (index.isValid()) this->on_tableWidget_post_clicked(index);


//}

//void Widget::reloadPostTagforGroup(post *p)
//{
//    ui->tableWidget_tagpostforgroup->clear();
//    taglist *tagl = lm->getTagGroupList();
//    ui->tableWidget_tagpostforgroup->setColumnCount(1);
//    ui->tableWidget_tagpostforgroup->setRowCount(tagl->countitem());
//    ui->tableWidget_tagpostforgroup->setVerticalHeaderLabels(lm->getNameTagGroupList());
//    tagl->begin();
//    for(int row=0; row<ui->tableWidget_tagpostforgroup->rowCount(); row++){
//            QCheckBoxPostTagforAG * CBposttagforAG = new QCheckBoxPostTagforAG(tagl->nextitem(),p,true,this);
//            ui->tableWidget_tagpostforgroup->setCellWidget(row, 0, CBposttagforAG);
//    }
//}

//void Widget::reloadPostTagforAccount(post *p)
//{
//    ui->tableWidget_tagpostforaccount->clear();
//    taglist *tagl = lm->getTagAccountList();
//    ui->tableWidget_tagpostforaccount->setColumnCount(1);
//    ui->tableWidget_tagpostforaccount->setRowCount(tagl->countitem());
//    ui->tableWidget_tagpostforaccount->setVerticalHeaderLabels(lm->getNameTagAccountList());
//    tagl->begin();
//    for(int row=0; row<ui->tableWidget_tagpostforaccount->rowCount(); row++){
//            QCheckBoxPostTagforAG * CBposttagforAG = new QCheckBoxPostTagforAG(tagl->nextitem(),p,false,this);
//            ui->tableWidget_tagpostforaccount->setCellWidget(row, 0, CBposttagforAG);
//    }
//}

//void Widget::reloadPostTag()
//{
//    QModelIndex index = ui->tableWidget_post->currentIndex();
//    if (index.isValid()) this->on_tableWidget_post_clicked(index);
//}

//void Widget::reloadQueuePost()
//{
//    ui->tableWidget_queuepost->setColumnCount(1);
//    ui->tableWidget_queuepost->setRowCount(lm->countQueuePost());
//    postlist *pl = lm->getQueuePostList();
//    pl->begin();
//    for (int row = 0; row < lm->countQueuePost(); row++ ){
//        QLabelforPost *lp = new QLabelforPost(pl->nextitem(),this);
//        ui->tableWidget_queuepost->setCellWidget(row,0,lp);
//    }

//    QModelIndex index = ui->tableWidget_queuepost->currentIndex();
//    if (index.isValid()) this->on_tableWidget_queuepost_clicked(index);
//}

//void Widget::reloadQueuePostTagforGroup(post *p)
//{
//    ui->tableWidget_3_queueposttagforgroup->clear();
//    taglist *tagl = p->getTagforGroup();
//    ui->tableWidget_3_queueposttagforgroup->setColumnCount(1);
//    ui->tableWidget_3_queueposttagforgroup->setRowCount(tagl->countitem());
//    //ui->tableWidget_3_queueposttagforgroup->setVerticalHeaderLabels(lm->getNameTagList(tagl));
//    tagl->begin();
//    for(int row=0; row<ui->tableWidget_3_queueposttagforgroup->rowCount(); row++){
//            QLineEditforTag * LBqueueposttagforAG = new QLineEditforTag(tagl->nextitem(),this);
//            ui->tableWidget_3_queueposttagforgroup->setCellWidget(row, 0, LBqueueposttagforAG);
//    }
//}

//void Widget::reloadQueuePostTagforAccount(post *p)
//{
//    ui->tableWidget_2_queueposttagforaccount->clear();
//    taglist *tagl = p->getTagforAccount();
//    ui->tableWidget_2_queueposttagforaccount->setColumnCount(1);
//    ui->tableWidget_2_queueposttagforaccount->setRowCount(tagl->countitem());
//    //ui->tableWidget_2_queueposttagforaccount->setVerticalHeaderLabels(lm->getNameTagList(tagl));
//    tagl->begin();
//    for(int row=0; row<ui->tableWidget_2_queueposttagforaccount->rowCount(); row++){
//            QLineEditforTag * LBqueueposttagforAG = new QLineEditforTag(tagl->nextitem(),this);
//            ui->tableWidget_2_queueposttagforaccount->setCellWidget(row, 0, LBqueueposttagforAG);
//    }
//}

//void Widget::reloadQueuePostTag()
//{
//    QModelIndex index = ui->tableWidget_queuepost->currentIndex();
//    if (index.isValid()) this->on_tableWidget_queuepost_clicked(index);
//}

void Widget::pushPosttoSendQueue(int col, int row)
{
    if(!this->activequeue) return;
    count_queue++;
    if ((this->count_queue)>(lm->getQueuePostList()->countitem())) {
        ui->pushButton_15_startsendingpost->setEnabled(true);
        return;
    }
//    QModelIndex index = ui->tableWidget_queuepost->model()->index(row,col);
//    if(!index.isValid()) {
//        qDebug() << "pushPSQ: Не валидный индекс";
//        emit SentPostFinishw();
//        return;}
//    QWidget *w =  ui->tableWidget_queuepost->cellWidget(index.row(),index.column());


//    if (w == NULL) {
//        qDebug() << "pushPSQ: Пустой указатель";
//        emit SentPostFinishw();
//        return;}
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
    post *p = lm->getQueuePostList()->at(row);
    grouplist *glf = lm->getGroupforPost(p);
    grouplist *gl = lm->getGroupforPostRem(p);
    ui->progressBar_countsendpost->setMaximum(glf->countitem());
    ui->progressBar_countsendpost->setValue(glf->countitem()-gl->countitem());
    accountlist *al = lm->getAccountforPost(p);
    if (al->countitem() ==0) {
        emit SentPostFinishw();
         qDebug() << "pushPSQ: Нет аккаунтов";
        return;}
    if (gl->countitem() == 0) {
        emit SentPostFinishw();
         qDebug() << "pushPSQ: Нет групп для отправки";
        return;}
    p = lm->getCopyPost(p);
    al = lm->getCopyAccountList(al);
    gl = lm->getCopyGroupList(gl);
     qDebug() << "pushPSQ: Пост отправлен на посылку";
    vkm->querySendPost(p,gl,al,ui->spinBox_delay_forsendpost->value());
}

//void Widget::on_tableWidget_grouptag_clicked(const QModelIndex &index)
//{
//    qDebug()<<index;
//    if (!index.isValid()) return;
//    this->setTagforGroup(index.row(),index.column(),0);
//}

//void Widget::on_tableWidget_accounttag_clicked(const QModelIndex &index)
//{
//    qDebug()<<index;
//    if (!index.isValid()) return;
//    this->setTagforAccount(index.row(),index.column(),0);
//}



//void Widget::on_tableWidget_post_clicked(const QModelIndex &index)
//{
//    if (!index.isValid()) return;
//    ui->tableWidget_post->setCurrentCell(index.row(),index.column());
//    QWidget *w =  ui->tableWidget_post->cellWidget(index.row(),index.column());
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//    post *p = lp->getpost();
//    ui->lineEdit_namepost->setText(p->GetNamePost());
//    ui->plainTextEdit_textpost->setPlainText(p->GetTextPost());
//    ui->plainTextEdit_attachpost->setPlainText(p->GetAttachPost());
//    this->reloadPostTagforGroup(p);
//    this->reloadPostTagforAccount(p);

//}

//void Widget::on_tableWidget_tagpostforgroup_clicked(const QModelIndex &index)
//{
//    qDebug()<<index;
//    if (!index.isValid()) return;
//    this->setPostTagforGroup(index.row(),index.column(),0);
//    this->reloadQueuePostTag();
//}

//void Widget::on_tableWidget_tagpostforaccount_clicked(const QModelIndex &index)
//{
//    qDebug()<<index;
//    if (!index.isValid()) return;
//    this->setPostTagforAccount(index.row(),index.column(),0);
//    this->reloadQueuePostTag();
//}



void Widget::on_pushButton_7_delgroup_clicked()
{
    QMessageBox::StandardButton mesRepl;
    mesRepl = QMessageBox::question(this, "Внимание",
                                       "Удалить сообщество?",
                                       QMessageBox::Yes |
                                       QMessageBox::No);
     if(mesRepl == QMessageBox::No) return;
     int sbVal = ui->tableView_2_grouptag->verticalScrollBar()->value();
     ui->tableView_2_grouptag->model()->removeRows(0,0);
     ui->tableView_2_grouptag->verticalScrollBar()->setValue(sbVal);


//    QModelIndex index = ui->tableWidget_grouptag->currentIndex();
//    if (!index.isValid()) return;
//    QWidget *w =  ui->tableWidget_grouptag->cellWidget(index.row(),index.column());
//    QCheckBoxTagforGroup* cb = dynamic_cast <QCheckBoxTagforGroup*>(w);
//    group *g = cb->getGroup();
//    lm->removeGroup(g);
//    this->reloadgroup();
//    ui->tableWidget_grouptag->setCurrentCell(0,0);
}

void Widget::on_pushButton_10_delaccount_clicked()
{
    QMessageBox::StandardButton mesRepl;
    mesRepl = QMessageBox::question(this, "Внимание",
                                       "Удалить аккаунт?",
                                       QMessageBox::Yes |
                                       QMessageBox::No);


    if(mesRepl == QMessageBox::No) return;
    int sbVal = ui->tableView_3_accounttag->verticalScrollBar()->value();
    ui->tableView_3_accounttag->model()->removeRows(0,0);
    ui->tableView_3_accounttag->verticalScrollBar()->setValue(sbVal);

//    QModelIndex index = ui->tableWidget_accounttag->currentIndex();
//    if (!index.isValid()) return;
//    QWidget *w =  ui->tableWidget_accounttag->cellWidget(index.row(),index.column());
//    QCheckBoxTagforAccount* cb = dynamic_cast <QCheckBoxTagforAccount*>(w);
//    account *a = cb->getAccount();
//    lm->removeAccount(a);
//    this->reloadaccount();
//    ui->tableWidget_accounttag->setCurrentCell(0,0);
}

void Widget::on_pushButton_19_delpost_clicked()
{
    QMessageBox::StandardButton mesRepl;
    mesRepl = QMessageBox::question(this, "Внимание",
                                       "Удалить пост?",
                                       QMessageBox::Yes |
                                       QMessageBox::No);


    if(mesRepl == QMessageBox::No) return;

    ui->tableView_6_post->model()->removeRows(0,0);

//    QModelIndex index = ui->tableWidget_post->currentIndex();
//    if (!index.isValid()) return;
//    QWidget *w =  ui->tableWidget_post->cellWidget(index.row(),index.column());
//    QLabelforPost* cb = dynamic_cast <QLabelforPost*>(w);
//    post *p = cb->getpost();
//    lm->removePost(p);
//    this->reloadpost();
//    ui->tableWidget_post->setCurrentCell(0,0);
}

void Widget::on_pushButton_18_addpost_clicked()
{
    QString name_post,text_post,attach_post;
    name_post = ui->lineEdit_namepost->text();
    text_post = ui->plainTextEdit_textpost->toPlainText();
    attach_post = ui->plainTextEdit_attachpost->toPlainText().remove(" ");
    if ((name_post != "")&&((text_post!="")||(attach_post!=""))) {
        QStringList sl;
        sl << "new"<< name_post << text_post << attach_post;
        QModelIndex index = ui->tableView_6_post->model()->index(0,0);
        ui->tableView_6_post->model()->setData(index,QVariant(sl));
    }
//        lm->addPost(name_post,text_post,attach_post);
//    this->reloadpost();
}

//void Widget::on_tableWidget_queuepost_clicked(const QModelIndex &index)
//{
//    if (!index.isValid()) return;
//    ui->tableWidget_queuepost->setCurrentCell(index.row(),index.column());
//    QWidget *w =  ui->tableWidget_queuepost->cellWidget(index.row(),index.column());
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//    post *p = lp->getpost();
//    ui->label_20_namepostinqueue->setText(p->GetNamePost());
//    ui->plainTextEdit_3_queueposttext->setPlainText(p->GetTextPost());
//    ui->plainTextEdit_4_queueattachpost->setPlainText(p->GetAttachPost());
//    this->reloadQueuePostTagforGroup(p);
//    this->reloadQueuePostTagforAccount(p);
//}

void Widget::newAccount(QStringList &sl)
{
   QModelIndex index = ui->tableView_3_accounttag->model()->index(0,0);
   ui->tableView_3_accounttag->model()->setData(index,QVariant(sl));


   //lm->addAccount(sl);
   //this->reloadaccount();
}

void Widget::newGroup(QStringList &sl)
{
    QModelIndex index = ui->tableView_2_grouptag->model()->index(0,0);
    ui->tableView_2_grouptag->model()->setData(index,QVariant(sl));
    //this->reloadgroup();
}

void Widget::newSearshGroupResult(QStringList &sl, int count_all_items, int  max_item)
{
ui->label_countallgroup->setText("Всего: "+ QString::number(count_all_items));

QStringList hsl;
hsl << "name" << "type_group"  << "member_count"<< "id_vk" << "screen_name" << "description";

if(!sl.isEmpty()){
    ui->tableWidget_resultSearshGroup->setRowCount(max_item);
    ui->tableWidget_resultSearshGroup->setColumnCount(6);
    ui->tableWidget_resultSearshGroup->setHorizontalHeaderLabels(hsl);
    for(int row = 0; row < max_item;row++)
        for(int column = 0; column < 6; column++)
            ui->tableWidget_resultSearshGroup->setItem(row, column, new QTableWidgetItem(sl[row*6+column]));}
else return;


ui->tableWidget_tagforsearshgroup->setColumnCount(lm->countTagGroup());
ui->tableWidget_tagforsearshgroup->setRowCount(max_item);
ui->tableWidget_tagforsearshgroup->setHorizontalHeaderLabels(lm->getNameTagGroupList());

 for (int row = 0; row< max_item ;row++ )
          for (int col = 0; col < lm->countTagGroup();col++ ){
                     QTableWidgetItem *item = new QTableWidgetItem();
                     item->setTextAlignment(Qt::AlignCenter);
                     item->setText("");
                     ui->tableWidget_tagforsearshgroup->setItem(row, col, item);
          }

}

void Widget::newSentPost(post *p, group *g, account *a, QString &id_post_on_wall, bool b)
{
    if (b) {successsending++;
            ui->label_3_success_sending->setText(QString::number(successsending));}
    else {errorsending++;
          ui->label_28_error_success->setText(QString::number(successsending));}
    maxsending--;
    ui->label_9_max_sending->setText(QString::number(maxsending));


    ui->progressBar_countsendpost->setValue(ui->progressBar_countsendpost->value()+1);
    lm->addSendPost(p,g,a,id_post_on_wall,b);
}

void Widget::startSendNextPost()
{
   if(!ui->checkBox_allsendpost->isChecked() || count_queue>lm->countQueuePost()){
            ui->pushButton_15_startsendingpost->setEnabled(true);
            return;
   }

   //QModelIndex index = ui->tableWidget_queuepost->currentIndex();
   //if(!index.isValid()) return;
   ui->progressBar_countqueue->setValue(ui->progressBar_countqueue->value()+1);
   this->pushPosttoSendQueue(0,this->count_queue);

}

void Widget::toLog(QString &s, bool b,QColor color)
{
  log_file->open(QIODevice::Append|QIODevice::Text);
  QTextStream out(log_file);

  if (b) {QColor tc = ui->textEdit_log->textColor();
      ui->textEdit_log->setTextColor(color);
      ui->textEdit_log->append(s);
      ui->textEdit_log->setTextColor(tc);
  }

  s= QDateTime::currentDateTime().toString()+" "+ s;
  out<< s <<endl;
  log_file->close();
}

void Widget::on_pushButton_2_updatepost_clicked()
{
    QString name_post,text_post,attach_post;
    name_post = ui->lineEdit_namepost->text();
    text_post = ui->plainTextEdit_textpost->toPlainText();
    attach_post = ui->plainTextEdit_attachpost->toPlainText().remove(" ");
    if ((name_post != "")&&((text_post!="")||(attach_post!=""))) {
        QStringList sl;
        sl << "update"<< name_post << text_post << attach_post;
        QModelIndex index = ui->tableView_6_post->model()->index(0,0);
        ui->tableView_6_post->model()->setData(index,QVariant(sl));
    }


//    QModelIndex index = ui->tableWidget_post->currentIndex();
//    int row_index = index.row();
//    int col_index = index.column();
//    if ((!row_index<0)&&(!col_index<0)) return;

//    QWidget *w =  ui->tableWidget_post->cellWidget(row_index,col_index);
//    if (w == NULL) return;
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//    post *p = lp->getpost();
//    lm->updatePost(p,ui->lineEdit_namepost->text(),ui->plainTextEdit_textpost->toPlainText(),ui->plainTextEdit_attachpost->toPlainText());
//    this->reloadpost();
//    this->reloadQueuePost();
}

void Widget::on_pushButton_12_posttoQueue_clicked()
{
   QModelIndex index = ui->tableView_7_queuepost->model()->index(0,0);
   ui->tableView_7_queuepost->model()->setData(index,QVariant());
   //this->myproxymodel6->resetdata();
   ui->tableView_7_queuepost->reset();
//   QModelIndex index = ui->tableWidget_post->currentIndex();
//   if (!index.isValid()) return;
//   QWidget *w =  ui->tableWidget_post->cellWidget(index.row(),index.column());
//   if (w == NULL) return;
//   QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//   post *p = lp->getpost();
//   lm->addPosttoQueue(p);
//   this->reloadQueuePost();
}



void Widget::on_pushButton_2_removepostfromqueue_clicked()
{
    //QModelIndex index = ui->tableView_7_queuepost->model()->index(0,0);
    ui->tableView_7_queuepost->model()->removeRows(0,0);
//    QModelIndex index = ui->tableWidget_queuepost->currentIndex();
//    if (!index.isValid()) return;
//    QWidget *w =  ui->tableWidget_queuepost->cellWidget(index.row(),index.column());
//    if (w == NULL) return;
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//    post *p = lp->getpost();
//    lm->removePostfromQueue(p);
//    this->reloadQueuePost();
}

void Widget::on_pushButton_addnewaccount_clicked()
{
    vkm->queryNewAccount();
}

void Widget::on_pushButton_addgroup_clicked()
{
    vkm->queryNewGroup(ui->lineEdit_id_vk_fornewgroup->text());
}



void Widget::on_pushButton_searchgroup_clicked()
{
  if (lm->getAccountList()->countitem()<=0) {QMessageBox::warning(this,"Внимание","Для проведения поиска необходим хотя бы один аккаунт!",QMessageBox::Ok)  ;return;}

    QString s;

   ui->tableWidget_resultSearshGroup->clear();
   ui->tableWidget_resultSearshGroup->setRowCount(0);
   ui->tableWidget_tagforsearshgroup->clear();
   ui->tableWidget_tagforsearshgroup->setRowCount(0);

    switch (ui->comboBox_typegroup_to_search->currentIndex()) {
    case 0:
        s="";
        break;
    case 1:
        s = "group";
        break;
    case 2:
        s = "page";
        break;
    case 3:
        s = "event";
        break;
    }

    vkm->querySearchGroups(lm->getAccountList()->lastitem()->getAccountToken(),
                           ui->lineEdit_search_param->text(),
                           QString::number(ui->spinBox_count_to_search->value()*(ui->spinBox_offset_to_search->value()-1)),
                           QString::number(ui->spinBox_count_to_search->value()),
                           QString::number(ui->comboBox_sort_to_search->currentIndex()),
                           s);
}

void Widget::on_tableWidget_resultSearshGroup_clicked(const QModelIndex &index)
{
    if(!index.isValid()) return;
    if(index.column()<1) return;
    QMessageBox::about(0,"",index.data().toString());
}

void Widget::on_tableWidget_resultSearshGroup_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid()) return;
    if(index.column()>0) return;
    QString s;
    QString s1 = ui->tableWidget_resultSearshGroup->model()->index(index.row(),1).data().toString();
    if (s1=="group") s="club";
    else if (s1=="page") s="public";
      else if (s1 == "event") s="event";
            else s="id";

   // QString id = index.data(Qt::DisplayRole).toString();
    QString id = ui->tableWidget_resultSearshGroup->model()->index(index.row(),3).data().toString();

    QDesktopServices::openUrl(QUrl("http://vk.com/"+s+id));



}

void Widget::on_pushButton_4_addnewgroup_clicked()
{
    bool groupinlist = false;
    QModelIndex index = ui->tableWidget_resultSearshGroup->currentIndex();
    if(!index.isValid()) return;
    QStringList sl;
    for(int col = 0;col < 6; col++)
               sl << ui->tableWidget_resultSearshGroup->model()->index(index.row(),col).data().toString();


    for (int col=0;col<lm->countTagGroup();col++){
        if (ui->tableWidget_tagforsearshgroup->model()->index(index.row(),col).data().toString() !="")groupinlist=true;
    }


    if (groupinlist) {
        group *g = NULL;
        if (lm->groupingrouplist(sl) == NULL)
                    lm->addGroup(sl);
        g = lm->groupingrouplist(sl);
        if (g == NULL) return;
        for (int col=0;col<lm->countTagGroup();col++){
            if ((ui->tableWidget_tagforsearshgroup->model()->index(index.row(),col).data().toString()) !=""){
               if (!g->tagin(lm->getTagGroupList()->at(col)))
                       lm->addTagto(lm->getTagGroupList()->at(col),g);
            }
        }
    }
    this->mymodel_all->resetdata();


    //this->reloadgroup();
}



void Widget::on_pushButton_15_startsendingpost_clicked()
{


//    QModelIndex index = ui->tableWidget_queuepost->currentIndex();
//    if (!index.isValid()){
//        index = ui->tableWidget_queuepost->model()->index(0,0);
//        ui->tableWidget_queuepost->setCurrentIndex(index);
//        index = ui->tableWidget_queuepost->currentIndex();
//        if (!index.isValid())
//            return;
//    }
    if (count_queue<0 || count_queue>lm->getQueuePostList()->countitem()) count_queue =0;
    ui->pushButton_15_startsendingpost->setEnabled(false);
    emit putActiveSendingPost(true);
    //this->count_queue = index.row();
    this->activequeue = true;
    ui->progressBar_countsendpost->setValue(0);
    ui->progressBar_countqueue->setValue(0);
    ui->progressBar_countqueue->setMaximum(lm->countQueuePost()-count_queue);
    this->pushPosttoSendQueue(0,count_queue);
}

void Widget::on_pushButton_17_stopsendingpost_clicked()
{
  emit putActiveSendingPost(false);
  this->activequeue = false;
  ui->pushButton_15_startsendingpost->setEnabled(true);
}



void Widget::on_pushBatton_opengroupinbr_clicked()
{
//    int row = ui->tableWidget_grouptag->currentRow();
//    int col = ui->tableWidget_grouptag->currentColumn();
//    if ((row == -1) || (col == -1)) return;
//    QWidget *w =  ui->tableWidget_grouptag->cellWidget(row,col);
//    if (w == NULL) return;
//    QCheckBoxTagforGroup *CBTagforGroup = dynamic_cast <QCheckBoxTagforGroup*>(w);
    group *g =  lm->getCurrentGroup();
    if (g == NULL) return;
    QString s1 = g->getTypeGroup();
    QString id = QString::number(g->getID());
    QString s;
    if (s1=="group") s="club";
    else if (s1=="page") s="public";
      else if (s1 == "event") s="event";
            else s="id-";
    QDesktopServices::openUrl(QUrl("http://vk.com/"+s+id));

}

void Widget::on_pushButton_13_testpost_clicked()
{
//    QModelIndex index = ui->tableWidget_queuepost->currentIndex();
//    qDebug()<< index;
//    if (!index.isValid()) return;

//    QWidget *w =  ui->tableWidget_post->cellWidget(index.row(),index.column());
//    if (w == NULL) return;
//    QLabelforPost *lp = dynamic_cast <QLabelforPost*>(w);
//    post *p = lp->getpost();
    emit putActiveSendingPost(true);
    if (lm->getAccountList()->countitem()<=0) {QMessageBox::warning(0,"Внимание", "Список аккаунтов пуст!",QMessageBox::Ok);return;}
    vkm->queryTestPost(lm->getCurrentQueuePost(),ui->lineEdit_id_for_testpost->text(),lm->getAccountList());
    QEventLoop wait;
    QTimer::singleShot(2000,&wait,SLOT(quit()));
    wait.exec();
    emit putActiveSendingPost(false);

}

void Widget::on_pushButton_newtagaccount_clicked()
{
    if (ui->lineEdit_nametagaccount->text()== "") {QMessageBox::warning(0,"Пустой тег!", "Пустое имя тега! Исправить!"); return;}
    QModelIndex index = this->mymodel_all->index(0,3);
    QStringList sl;
    sl << "new" << ui->lineEdit_nametagaccount->text();
    this->myproxymodel4->setData(index,QVariant(sl),Qt::UserRole+4);
    ui->tableView_5_taglistforaccount->reset();




//   if (ui->lineEdit_nametagaccount->text()== "") {QMessageBox::warning(0,"Пустой тег!", "Пустое имя тега! Исправить!"); return;}
//   lm->addTagAccount(ui->lineEdit_nametagaccount->text());
//   myitemmodel_foraccounttag = new MyItemModel(lm,this);

//   myitemmodel_foraccounttag->setTypeOutput("TagAccount");
//   ui->tableView_foraccounttag->setModel(myitemmodel_foraccounttag);

//   //this->reloadgroup();
//   this->reloadaccount();
//   this->reloadPostTag();
//   this->reloadQueuePostTag();
}

void Widget::on_pushButton_deltagaccount_clicked()
{

    QModelIndex index = this->mymodel_all->index(0,3);
    this->myproxymodel4->removeRows(0,0,index);
    ui->tableView_5_taglistforaccount->reset();

//    QModelIndex index = ui->tableView_foraccounttag->currentIndex();
//    if (!index.isValid()) return;
//    lm->removetag(lm->getTagAccountList()->at(index.row()));

//    myitemmodel_foraccounttag = new MyItemModel(lm,this);
//    myitemmodel_foraccounttag->setTypeOutput("TagAccount");
//    ui->tableView_foraccounttag->setModel(myitemmodel_foraccounttag);

//    //this->reloadgroup();
//    this->reloadaccount();
//    this->reloadPostTag();
//    this->reloadQueuePostTag();
}


void Widget::on_tableWidget_tagforsearshgroup_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    QString s;
    if (index.data().toString() == "") s = "V";
     else s="";
    ui->tableWidget_tagforsearshgroup->model()->setData(index,QVariant(s));
}

//void Widget::reloadgroupslot(int index)
//{
//    if (index == 2) reloadgroup();
//}

void Widget::on_pushButton_addnewgroup_alltag_clicked()
{

    ui->progressBar_addgroupsearsh->setMaximum(ui->tableWidget_resultSearshGroup->rowCount()-1);
    ui->progressBar_addgroupsearsh->setValue(0);

    for(int row=0; row< ui->tableWidget_resultSearshGroup->rowCount();row++){

    ui->tableWidget_resultSearshGroup->setCurrentCell(row,0);
    this->on_pushButton_4_addnewgroup_clicked();
    ui->progressBar_addgroupsearsh->setValue(row);
    }

}

void Widget::on_pushButton_14_testallpost_clicked()
{
    if (lm->getAccountList()->countitem()<=0) {QMessageBox::warning(0,"Внимание", "Список аккаунтов пуст!",QMessageBox::Ok);return;}
    for(int row=0; row< lm->getQueuePostList()->countitem();row++){

    //ui->tableWidget_queuepost->setCurrentCell(row,0);
    lm->setCurrentQueuePost(lm->getQueuePostList()->at(row));
    this->on_pushButton_13_testpost_clicked();
    }

    QMessageBox::information(0,"Тест", "Отправка постов в тестовую группу завершена.",QMessageBox::Ok);
}

void Widget::on_pushButton_6_addgroupfromfile_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open file",".","*.txt");
    QFile file(file_name);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    qDebug() << file.isOpen();
    QTextStream in(&file);
    QString s, s1;
    s = ""; s1 = "";
    while (!in.atEnd()){
        while(!s.contains("id:")) s = in.readLine();
        s1=s.mid(s.indexOf(":")+1);
        if(s1.isEmpty()) continue;
        vkm->queryNewGroup(s1);
        s="";
    }
    file.close();
}

void Widget::on_tableView_2_grouptag_clicked(const QModelIndex &index)
{
    if (lm->getGroupList()->countitem()<=0 || lm->getTagGroupList()->countitem()<=0 ) return;
    int row = index.row();
    int col = index.column();
    ui->tableView_2_grouptag->model()->setData(index,QVariant());
    QModelIndex ind = ui->tableView_2_grouptag->model()->index(row,col);
    this->mymodel_all->setData(ind,QVariant(),Qt::UserRole+102);
    ui->label_31_groupname->setText("Имя группы: "+lm->getCurrentGroup()->getName());
}

void Widget::on_tableView_3_accounttag_clicked(const QModelIndex &index)
{
    if (lm->getAccountList()->countitem()<=0 || lm->getTagAccountList()->countitem()<=0 ) return;
    int row = index.row();
    int col = index.column();
    ui->tableView_3_accounttag->model()->setData(index,QVariant());
    QModelIndex ind = ui->tableView_3_accounttag->model()->index(row,col);
    this->mymodel_all->setData(ind,QVariant(),Qt::UserRole+103);
}

void Widget::on_tableView_8_taggroupfotpost_clicked(const QModelIndex &index)
{
     ui->tableView_8_taggroupfotpost->model()->setData(index,QVariant());
}


void Widget::on_tableView_9_tagaccountforpost_clicked(const QModelIndex &index)
{
     ui->tableView_9_tagaccountforpost->model()->setData(index,QVariant());
}

void Widget::on_tableView_4_taglistforgroup_clicked(const QModelIndex &index)
{
     this->mymodel_all->setData(index,QVariant(),Qt::UserRole+104);
}

void Widget::on_tableView_5_taglistforaccount_clicked(const QModelIndex &index)
{
     this->mymodel_all->setData(index,QVariant(),Qt::UserRole+105);
}

void Widget::on_tableView_6_post_clicked(const QModelIndex &index)
{
    if (lm->getPostList()->countitem()<=0) return;
    this->mymodel_all->setData(index,QVariant(),Qt::UserRole+100);
    ui->tableView_8_taggroupfotpost->reset();
    ui->tableView_9_tagaccountforpost->reset();
    post *p = lm->getCurrentPost();
    ui->lineEdit_namepost->setText(p->GetNamePost());
    ui->plainTextEdit_textpost->setPlainText(p->GetTextPost());
    ui->plainTextEdit_attachpost->setPlainText(p->GetAttachPost());
}

void Widget::on_tableView_7_queuepost_clicked(const QModelIndex &index)
{
    if (lm->getQueuePostList()->countitem()<=0) return;
    this->count_queue=index.row();
    this->mymodel_all->setData(index,QVariant(),Qt::UserRole+101);
    ui->tableView_10_groupforqueuepost->reset();
    ui->tableView_11_accountforqueuepost->reset();
    post *p = lm->getCurrentQueuePost();
        ui->label_20_namepostinqueue->setText(p->GetNamePost());
        ui->plainTextEdit_3_queueposttext->setPlainText(p->GetTextPost());
        ui->plainTextEdit_4_queueattachpost->setPlainText(p->GetAttachPost());
}


void Widget::on_tableView_12_taggroupfotqueuepost_clicked(const QModelIndex &index)
{
    ui->tableView_12_taggroupfotqueuepost->model()->setData(index,QVariant());
}

void Widget::on_tableView_13_tagaccountforqueuepost_clicked(const QModelIndex &index)
{
     ui->tableView_13_tagaccountforqueuepost->model()->setData(index,QVariant());
}



void Widget::on_pushButton_updatetaggroupname_clicked()
{
    if (ui->lineEdit_tagname->text()== "") {QMessageBox::warning(0,"Пустой тег!", "Пустое имя тега! Исправить!"); return;}
    QModelIndex index = this->mymodel_all->index(0,3);
    QStringList sl;
    sl << "update" << ui->lineEdit_tagname->text();
    this->myproxymodel2->setData(index,QVariant(sl),Qt::UserRole+2);
    ui->tableView_4_taglistforgroup->reset();
}

void Widget::on_pushButton_updatetagaccountname_clicked()
{
    if (ui->lineEdit_nametagaccount->text()== "") {QMessageBox::warning(0,"Пустой тег!", "Пустое имя тега! Исправить!"); return;}
    QModelIndex index = this->mymodel_all->index(0,3);
    QStringList sl;
    sl << "update" << ui->lineEdit_nametagaccount->text();
    this->myproxymodel4->setData(index,QVariant(sl),Qt::UserRole+4);
    ui->tableView_5_taglistforaccount->reset();
}
