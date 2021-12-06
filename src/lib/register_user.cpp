#include <QMessageBox>

#include "register_user.hpp"
#include "ui_register_user.h"
#include "config.hpp"

register_user::register_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_user)
{
    ui->setupUi(this);
}

void register_user::setName(QString m_name_)
{
    ui->nameEdit->setText(m_name_);
}

void register_user::setPassword(QString m_password_)
{
    ui->passwordEdit->setText(m_password_);
}

void register_user::setNumber(QString m_number_)
{
    ui->numEdit->setText(m_number_);
}

void register_user::setInn(QString m_inn_)
{
    ui->innEdit->setText(m_inn_);
}

void register_user::setBankNum(QString m_banknum_)
{
    ui->bankEdit->setText(m_banknum_);
}

void register_user::setCity(QString m_city_)
{
    ui->adresEdit->setText(m_city_);
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
    QString adress = ui->adresEdit->text();

    if (name.size() > 20 || name.isEmpty())
    {
        QMessageBox::warning(0, config::applicationName, "Size of company > 20");
        return;
    }
    else if (name == config::nameAdmin)
    {
        QMessageBox::warning(0, config::applicationName, "This company name is prohibited");
        return;
    }

    if ( (password.size() > 24) || (password.size() < 8) )
    {
        QMessageBox::warning(0, config::applicationName, "Size password < 8 && > 24");
        return;
    }

    if ( num.size() != 12 || (num[0] != '+') )
    {
        QMessageBox::warning(0, config::applicationName, "Num should be size 12 and first symbols is +");
        return;
    }
    else if (num == config::numberCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "This number is prohibited");
        return;
    }

    if ( inn.size() != 10 )
    {
        QMessageBox::warning(0, config::applicationName, "Num should be size 10");
        return;
    }
    else if (inn == config::innCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "This INN is prohibited");
        return;
    }

    if ( bank.size() != 20 )
    {
        QMessageBox::warning(0, config::applicationName, "Num should be size 10");
        return;
    }
    else if (bank == config::bankNumCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "This Bank Num is prohibited");
        return;
    }

    if ( adress.size() > 30  || adress.isEmpty())
    {
        QMessageBox::warning(0, config::applicationName, "Address should be <= 30");
        return;
    }

    m_user->setName(name);
    m_user->setPassword(password);
    m_user->setNumber(num);
    m_user->setBankNum(bank);
    m_user->setInn(inn);
    m_user->setCity(adress);
    m_user->setRole(0);

    return QDialog::accept();
}

register_user::~register_user()
{
    delete ui;
}
