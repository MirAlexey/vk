#ifndef CONECTOR_H
#define CONECTOR_H

#include <QObject>
#include <QtSql/QtSql>

class Conector : public QObject
{
    Q_OBJECT
public:
    explicit Conector(QObject *parent = 0);
    bool OpenDB (QString SqlDrv, QString HostName, QString  Port, QString NameDB, QString  User, QString  Password);
    bool QueryDB (QString querydb, QStringList &sl, QString strrzr);
private:
    QSqlDatabase db;
    QString SqlDrvDB, HostNameDB, PortDB, UserDB, PasswordDB, NameDB;
    bool dbopen;
signals:

public slots:

};

#endif // CONECTOR_H
