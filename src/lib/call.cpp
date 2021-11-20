#include "call.hpp"

call::call()
{

}

call::~call()
{

}

void call::setNameCalled(QString name_)
{
    name_called = name_;
}

QString &call::getNameCalled()
{
    return name_called;
}
void call::setNumCalled(QString num_)
{
    num_called = num_;
}
QString &call::getNumCalled()
{
    return num_called;
}
void call::setCityCalled(QString city_)
{
    city_called = city_;
}
QString &call::getCityCalled()
{
    return city_called;
}
void call::setNameCalling(QString name_)
{
    name_calling = name_;
}
QString &call::getNameCalling()
{
    return name_calling;
}
void call::setNumCalling(QString num_)
{
    num_calling = num_;
}
QString &call::getNumCalling()
{
    return num_calling;
}
void call::setCityCalling(QString city_)
{
    city_calling = city_;
}
QString &call::getCityCalling()
{
    return city_calling;
}
void call::setStartCall(QDateTime start_)
{
    start_call = start_;
}
QDateTime &call::getStartCall()
{
    return start_call;
}
void call::setEndCall(QDateTime end_)
{
    end_call = end_;
}
QDateTime &call::getEndCall()
{
    return end_call;
}
