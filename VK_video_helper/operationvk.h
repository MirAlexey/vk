#ifndef OPERATIONVK_H
#define OPERATIONVK_H

#include <QObject>

class OperationVK : public QObject
{
    Q_OBJECT
public:
    explicit OperationVK(QObject *parent = 0);
    virtual  bool  RunOperation(CastomVKwebview *vkweb){return true;}
signals:

public slots:

};


class EnterLoginPass : public OperationVK
{
    Q_OBJECT
    explicit EnterLoginPass(QObject *parent = 0):OperationVK(parent){}
    virtual bool RunOperation(CastomVKwebview *vkweb);
}

class EnterinVK : public OperationVK
{
    Q_OBJECT
    explicit EnterinVK(QObject *parent = 0):OperationVK(parent){}
    virtual bool RunOperation();
}








#endif // OPERATIONVK_H
