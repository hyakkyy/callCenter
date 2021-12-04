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

void call::setStartCall(QString start_)
{
    start_call = QDateTime::fromString(start_, "dd MMM yyyy HH:mm:ss");
}

QDateTime &call::getStartCall()
{
    return start_call;
}

void call::setEndCall(QDateTime end_)
{
    end_call = end_;
}

void call::setEndCall(QString end_)
{
    end_call = QDateTime::fromString(end_, "dd MMM yyyy HH:mm:ss");
}

QDateTime &call::getEndCall()
{
    return end_call;
}

void call::save(QDataStream &ost) const
{
    ost << name_called << num_called << city_called << name_calling << num_calling << city_calling
        << start_call << end_call;
}

void call::load(QDataStream &ist)
{
    ist >> name_called >> num_called >> city_called >> name_calling >> num_calling >> city_calling
        >> start_call >> end_call;
}
