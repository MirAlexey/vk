#ifndef TOLOG_H
#define TOLOG_H

#include <QObject>
#include <QDir>
#include <QFile>

class toLog : public QObject
{
    Q_OBJECT
public:
    explicit toLog(QObject *parent = 0);

signals:

public slots:
    void StringToLog

private:
    QFile file;


};

#endif // TOLOG_H
