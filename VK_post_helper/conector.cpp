#include "conector.h"
#include <QtSql/QtSql>
#include <QDebug>
Conector::Conector(QObject *parent) :
    QObject(parent)
{
dbopen = false;
return;
}

bool Conector::OpenDB(QString SqlDrv, QString HostName,QString Port, QString NameDB,  QString User, QString Password)
{

 if (!dbopen) {
     db = QSqlDatabase::addDatabase(SqlDrv);
     db.setDatabaseName(NameDB);
//     db.setHostName(HostName);
//     db.setUserName(User);
//     db.setPort(Port.toInt());
//     db.setPassword(Password);
  if (db.open()){
     this->NameDB = NameDB;
     this->SqlDrvDB = SqlDrv;
     this->HostNameDB = HostName;
     this->PortDB = Port;
     this->UserDB = User;
     this->PasswordDB = Password;
     dbopen = true;
     return true;
      }
  else {
    qDebug() << db.lastError().text();
    return false;
   }
  }
 return true;
}

bool Conector::QueryDB(QString querydb, QStringList &sl, QString strrzr)
{   sl.clear();
    QString s;

    QSqlQuery query = QSqlQuery();
    if (dbopen){
       if (!query.exec(querydb)) {
           qDebug() << query.lastError().type();
           qDebug() << query.lastError();
//           db.close();
//           db.open();
//           if (!query.exec(querydb)) {
//               qDebug()<< "13456789";
//               qDebug() << query.lastError().type();
//               qDebug() << query.lastError();
               sl<<  query.lastError().text();//query.lastError().type().text()
//               dbopen = false;

               return false;
//           }
       }

        while (query.next()) {
                for(int i=0;i< query.record().count();i++){
                s+=query.record().field(i).value().toString();
                if ((i+1) < query.record().count()) s+=strrzr;
                }
                qDebug() << s <<"987654321";
                sl.append(s);
                s="";
            }
         qDebug() << sl;

         return true;
        }
sl<< "База не открыта";
return false;
}
