#include <QSaveFile>
#include <QMessageBox>

#include "managermainwindow.hpp"
#include "ui_managermainwindow.h"
#include "users_table.hpp"
#include "callhistory.hpp"

managerMainWindow::managerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::managerMainWindow)
{
    ui->setupUi(this);
}

managerMainWindow::~managerMainWindow()
{
    delete ui;
}

void managerMainWindow::save_users()
{
    QSaveFile outf("users.tnb");
    outf.open(QIODevice::WriteOnly);
    QDataStream ost(&outf);
    for (size_t i = 0; i < m_users.size(); i++)
    {
        ost << m_users[i];
    }
    outf.commit();
}

void managerMainWindow::setUsers(std::vector<user> m_users_)
{
    m_users = m_users_;
}

void managerMainWindow::setCalls(std::vector<call> m_calls_)
{
    m_calls = m_calls_;
}

void managerMainWindow::setIndex(int index_)
{
    index = index_;

    role = m_users[index].getRole();
}

void managerMainWindow::on_usersButton_clicked()
{
    users_table ut;
    ut.setUsers(&m_users);
    ut.exec();
    save_users();
}


void managerMainWindow::on_callHistoryButton_clicked()
{
    if (m_calls.empty())
    {
        QMessageBox::information(0, "Information", "Calls history is empty.");
        return;
    }
    callhistory ch;
    ch.setIndex(index);
    ch.setCalls(m_calls);
    ch.setRole(role);
    ch.exec();
}

