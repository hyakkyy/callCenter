#include "managermainwindow.hpp"
#include "ui_managermainwindow.h"
#include "users_table.hpp"

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
    if (ut.exec() != users_table::Accepted)
    {
        return;
    }
}

