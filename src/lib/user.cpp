#include "user.hpp"

user::user()
{

}

user::~user()
{

}

void user::setName(QString name_)
{
    name = name_;
}

QString &user::getName()
{
    return name;
}

void user::setPassword(QString password_)
{
    password = password_;
}

QString &user::getPassword()
{
    return password;
}

void user::setNumber(QString number_)
{
    number = number_;
}

QString &user::getNumber()
{
    return number;
}

void user::setInn(QString inn_)
{
    inn = inn_;
}

void user::setBankNum(QString bank_num_)
{
    bank_num = bank_num_;
}

void user::setCity(QString city_)
{
    city = city_;
}

QString &user::getCity()
{
    return city;
}

void user::setRole(int role_)
{
    role = role_;
}

int user::getRole()
{
    return role;
}
