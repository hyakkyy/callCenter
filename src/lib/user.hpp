#ifndef USER_HPP
#define USER_HPP

#include <QString>

class user
{
public:
    user();
    ~user();
    void setName(QString);
    QString &getName();
    void setPassword(QString);
    QString &getPassword();
    void setNumber(QString);
    QString &getNumber();
    void setInn(QString);
    void setBankNum(QString);
    void setCity(QString);
    QString &getCity();
    void setRole(int);
    int getRole();
private:
    QString name;
    QString password;
    QString number;
    QString inn;
    QString bank_num;
    QString city;
    int role;
};

#endif // USER_HPP
