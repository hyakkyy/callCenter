#ifndef CALL_HPP
#define CALL_HPP
#include <QString>
#include <QDateTime>

class call
{
public:
    call();
    ~call();
    void setNameCalled(QString);
    QString &getNameCalled();
    void setNumCalled(QString);
    QString &getNumCalled();
    void setCityCalled(QString);
    QString &getCityCalled();
    void setNameCalling(QString);
    QString &getNameCalling();
    void setNumCalling(QString);
    QString &getNumCalling();
    void setCityCalling(QString);
    QString &getCityCalling();
    void setStartCall(QDateTime);
    QDateTime &getStartCall();
    void setEndCall(QDateTime);
    QDateTime &getEndCall();
private:
    QString name_called;
    QString num_called;
    QString city_called;
    QString name_calling;
    QString num_calling;
    QString city_calling;
    QDateTime start_call;
    QDateTime end_call;
};

#endif // CALL_HPP
