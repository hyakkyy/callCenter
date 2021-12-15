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
        QMessageBox::warning(0, config::applicationName, "Название компании должно состоять не больше чем из 20 элементов");
        return;
    }
    else if (name == config::nameAdmin)
    {
        QMessageBox::warning(0, config::applicationName, "Эта компания уже внесена в базу данных");
        return;
    }
    else if ( name.contains(config::nameManagers, Qt::CaseSensitive) )
    {
        QMessageBox::warning(0, config::applicationName, "Эта компания уже внесена в базу данных");
        return;
    }

    if ( (password.size() > 24) || (password.size() < 8) )
    {
        QMessageBox::warning(0, config::applicationName, "Пароль должен быть не больше 24 элеметов и не меньше 8");
        return;
    }

    if ( num.size() != 12 || (num[0] != '+') )
    {
        QMessageBox::warning(0, config::applicationName, "Код страны записывается полностью");
        return;
    }
    else if (num == config::numberCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "Этот номер уже есть в базе дынных");
        return;
    }

    if ( inn.size() != 10 )
    {
        QMessageBox::warning(0, config::applicationName, "ИНН должен состоять из 10 цифр");
        return;
    }
    else if (inn == config::innCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "Этот ИНН уже есть в базе данных");
        return;
    }

    if ( bank.size() != 20 )
    {
        QMessageBox::warning(0, config::applicationName, "Банковский счет сосотоит из 20 цифр");
        return;
    }
    else if (bank == config::bankNumCallCenter)
    {
        QMessageBox::warning(0, config::applicationName, "Банковский счет уже внесен в базу данных");
        return;
    }

    if ( adress.size() > 30  || adress.isEmpty())
    {
        QMessageBox::warning(0, config::applicationName, "Слишком длинный адрес");
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
