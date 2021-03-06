#include <QMessageBox>

#include "edit_user.hpp"
#include "ui_edit_user.h"
#include "config.hpp"

edit_user::edit_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_user)
{
    ui->setupUi(this);
}

void edit_user::setUser(user* m_user_)
{
    m_user = m_user_;

    if (m_user)
    {
        ui->nameEdit->setText(m_user->getName());
        ui->numEdit->setText(m_user->getNumber());
        ui->adressEdit->setText(m_user->getCity());
    }
    else
        ui->numEdit->setReadOnly(false);
}

void edit_user::accept()
{
    QString num = ui->numEdit->text();
    QString adress = ui->adressEdit->text();
    QString name = ui->nameEdit->text();

    if (name.size() > 20 || name.isEmpty())
    {
        QMessageBox::warning(0, config::applicationName, "Название компании должно состоять не больше чем из 20 элементов");
        return;
    }

    if ( num.size() != 12 || (num[0] != '+') )
    {
        QMessageBox::warning(0, config::applicationName, "Код страны записывается полностью");
        return;
    }

    if ( adress.size() > 30 )
    {
        QMessageBox::warning(0, config::applicationName, "Слишком длинный адрес");
        return;
    }

    m_user->setName(name);
    m_user->setNumber(num);
    m_user->setCity(adress);

    return QDialog::accept();
}

edit_user::~edit_user()
{
    delete ui;
}
