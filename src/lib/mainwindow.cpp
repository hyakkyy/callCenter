#include <QMessageBox>
#include <QFile>
#include <QSaveFile>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ui_authform.h"
#include "clientmainwindow.hpp"
#include "managermainwindow.hpp"
#include "register_user.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    load_users();

    //тестовый пользователь 1
    user u1;
    u1.setName("AlphaBank"); // ограничение в 26 сивмолов
    u1.setPassword("alpha_top"); // пароль генерируется
    u1.setNumber("+79509123456"); // обязательно через +7 и вместе с '+' 12 символов
    u1.setInn("1234567899"); // 10 цифр
    u1.setBankNum("12345678912345678999"); // 20 цифр
    u1.setCity("Achinsk"); // 25 букв
    u1.setRole(0); // 0 - клиент, 1 - менеджер, 2 - администратор
    m_users.push_back(u1);

    //тестовый пользователь 2
    user u2;
    u2.setName("Sberbank"); // ограничение в 26 сивмолов
    u2.setPassword("sber_pushka"); // вбивается пользователем
    u2.setNumber("+79509654321"); // обязательно через +7 и вместе с '+' 12 символов
    u2.setInn("9987654321"); // 10 цифр
    u2.setBankNum("12345678999987654321"); // 20 цифр
    u2.setCity("Krasnoyarsk"); // 25 букв
    u2.setRole(1); // 0 - клиент, 1 - менеджер, 2 - администратор
    m_users.push_back(u2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_user(user m_user_)
{
    QSaveFile outf("users.tnb");
    outf.open(QIODevice::Append);
    QDataStream ost(&outf);
    ost << m_user_;
    outf.commit();
}

void MainWindow::load_users()
{
    QFile inf("users.tnb");
    inf.open(QIODevice::ReadOnly);
    QDataStream ist(&inf);
    m_users.clear();
    while (!ist.atEnd())
    {
        user u;
        ist >> u;
        m_users.push_back(u);
    }
}

void MainWindow::on_authButton_clicked()
{
    QDialog *authForm = new QDialog;
    Ui::authForm ui_authform;
    ui_authform.setupUi(authForm);
    if (authForm->exec() == authForm->Accepted)
    {
        QString login = ui_authform.nameEdit->text();
        QString password = ui_authform.passwordEdit->text();

        for (size_t i = 0; i < m_users.size(); i++)
        {
            if ((m_users[i].getName() == login) && (m_users[i].getPassword() == password))
            {
                role = m_users[i].getRole();
                index = i;
            }
        }
    }
    if (role > 0)
    {
        QMessageBox::information(0, "Succeful", "You'r succeful authorisation.");
        managerMainWindow *mmw = new managerMainWindow;
        mmw->setUsers(m_users);
        mmw->setCalls(m_calls);
        mmw->setIndex(index);
        mmw->show();
        this->close();
    }
    else if (role == 0)
    {
        QMessageBox::information(0, "Succeful", "You'r succeful authorisation.");
        clientMainWindow *cmw = new clientMainWindow;
        cmw->setUsers(m_users);
        cmw->setCalls(m_calls);
        cmw->setIndexUser(index);
        cmw->show();
        this->close();
    }
    else
    {
        QMessageBox::information(0, "Error", "User not finding.\nTry again.");
    }
}


void MainWindow::on_registerButton_clicked()
{
    user m_user;
    register_user ru;
    ru.setUser(&m_user);
    if (ru.exec() != register_user::Accepted)
    {
        return;
    }
    save_user(m_user);
    m_users.push_back(m_user);
}

