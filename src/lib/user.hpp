/*!
 * \file
 * \brief Заголовочный файл класса user
 */
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
    QString &getInn();
    void setBankNum(QString);
    QString &getBankNum();
    void setCity(QString);
    QString &getCity();
    void setRole(int);
    int getRole();

    void save(QDataStream &ost) const;
    void load(QDataStream &ist);
private:
    QString name;
    QString password;
    QString number;
    QString inn;
    QString bank_num;
    QString city;
    int role;
};

inline QDataStream &operator<<(QDataStream &ost, const user &u)
{
    u.save(ost);
    return ost;
}

inline QDataStream &operator>>(QDataStream &ist, user &u)
{
    u.load(ist);
    return ist;
}

#endif // USER_HPP
