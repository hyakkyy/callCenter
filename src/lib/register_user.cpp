#include <QMessageBox>

#include "register_user.hpp"
#include "ui_register_user.h"

register_user::register_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_user)
{
    ui->setupUi(this);
}

void register_user::setUser(user *m_user_)
{
    m_user = m_user_;
}

void register_user::accept()
{
    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();
    QString num = ui->numEdit->text();
    QString inn = ui->innEdit->text();
    QString bank = ui->bankEdit->text();
    QString adres = ui->adresEdit->text();

    if (name.size() > 20)
    {
        QMessageBox::warning(0, "Call Center", "Size of company > 20");
        return;
    }

    if ( (password.size() > 24) || (password.size() < 8) )
    {
        QMessageBox::warning(0, "Call Center", "Size password < 8 && > 24");
        return;
    }

    if ( num.size() != 12 || (num[0] != '+') )
    {
        QMessageBox::warning(0, "Call Center", "Num should be size 12 and first symbols is +");
        return;
    }

    if ( inn.size() != 10 )
    {
        QMessageBox::warning(0, "Call Center", "Num should be size 10");
        return;
    }

    if ( bank.size() != 20 )
    {
        QMessageBox::warning(0, "Call Center", "Num should be size 10");
        return;
    }

    if ( adres.size() > 30 )
    {
        QMessageBox::warning(0, "Call Center", "Adres should be <= 30");
        return;
    }

    m_user->setName(name);
    m_user->setPassword(password);
    m_user->setNumber(num);
    m_user->setBankNum(bank);
    m_user->setInn(inn);
    m_user->setCity(adres);
    m_user->setRole(0);

    return QDialog::accept();
}

register_user::~register_user()
{
    delete ui;
}
