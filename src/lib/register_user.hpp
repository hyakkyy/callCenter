/*!
 * \file
 * \brief Заголовочный файл класса Register_user
 */
#ifndef REGISTER_USER_HPP
#define REGISTER_USER_HPP
#include <QDialog>
#include "user.hpp"

namespace Ui {
class register_user;
}

class register_user : public QDialog
{
    Q_OBJECT

public:
    explicit register_user(QWidget *parent = nullptr);
    ~register_user();
    void setName(QString);
    void setPassword(QString);
    void setNumber(QString);
    void setInn(QString);
    void setBankNum(QString);
    void setCity(QString);
    void setUser(user*);

public slots:
    void accept() Q_DECL_OVERRIDE;;

private:
    user *m_user;
    Ui::register_user *ui;
};

#endif // REGISTER_USER_HPP
