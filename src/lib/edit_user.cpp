#include "edit_user.hpp"
#include "ui_edit_user.h"

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

    m_user->setNumber(num);
    m_user->setCity(adress);
}

edit_user::~edit_user()
{
    delete ui;
}
