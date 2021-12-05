#include <QMessageBox>
#include <QDateTime>
#include "startcall.hpp"
#include "ui_startcall.h"
#include "config.hpp"

startcall::startcall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startcall)
{
    ui->setupUi(this);
}

startcall::~startcall()
{
    delete ui;
}

void startcall::setUsers(std::vector<user> m_users_)
{
    m_users = m_users_;
}

void startcall::setCall(call *m_call_)
{
    m_call = m_call_;
}

void startcall::setIndexUser(int index_)
{
    index_called = index_;
}

void startcall::on_checkNum_clicked()
{
    QString num = ui->numClient->text();

    for (size_t i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getNumber() == num)
        {
            ui->nameClient->setText(m_users[i].getName());
            ui->cityClient->setText(m_users[i].getCity());
            index_calling = i;
        }
    }
    if (index_calling == -1)
    {
        QMessageBox::warning(0, config::applicationName, "Num not finded.");
    }
}

void startcall::accept()
{
    if (index_calling == -1)
    {
        QMessageBox::warning(0, config::applicationName, "Press a check button.");
        return;
    }
    m_call->setNameCalled(m_users[index_called].getName());
    m_call->setNumCalled(m_users[index_called].getNumber());
    m_call->setCityCalled(m_users[index_called].getCity());

    m_call->setNameCalling(m_users[index_calling].getName());
    m_call->setNumCalling(m_users[index_calling].getNumber());
    m_call->setCityCalling(m_users[index_calling].getCity());

    m_call->setStartCall(QDateTime::currentDateTime());

    return QDialog::accept();
}
