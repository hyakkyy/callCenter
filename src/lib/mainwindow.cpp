#include <QMessageBox>
#include <QFile>
#include <QSaveFile>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ui_authform.h"
#include "clientmainwindow.hpp"
#include "managermainwindow.hpp"
#include "register_user.hpp"
#include "config.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    load_users();
    load_calls();

//    //тестовый пользователь 1
//    user u1;
//    u1.setName("AlphaBank"); // ограничение в 26 сивмолов
//    u1.setPassword("alpha_top"); // пароль генерируется
//    u1.setNumber("+79509123456"); // обязательно через +7 и вместе с '+' 12 символов
//    u1.setInn("1234567899"); // 10 цифр
//    u1.setBankNum("12345678912345678999"); // 20 цифр
//    u1.setCity("Achinsk"); // 25 букв
//    u1.setRole(0); // 0 - клиент, 1 - менеджер, 2 - администратор
//    m_users.push_back(u1);

//    //тестовый пользователь 2
//    user u2;
//    u2.setName("Sberbank"); // ограничение в 26 сивмолов
//    u2.setPassword("sber_pushka"); // вбивается пользователем
//    u2.setNumber("+79509654321"); // обязательно через +7 и вместе с '+' 12 символов
//    u2.setInn("9987654321"); // 10 цифр
//    u2.setBankNum("12345678999987654321"); // 20 цифр
//    u2.setCity("Krasnoyarsk"); // 25 букв
//    u2.setRole(0); // 0 - клиент, 1 - менеджер, 2 - администратор
//    m_users.push_back(u2);

    // администратор
    user admin;
    admin.setName(config::nameAdmin);
    admin.setBankNum(config::bankNumCallCenter); // call center bank number
    admin.setCity(config::cityCallCenter); // call center city
    admin.setInn(config::innCallCenter); // call center inn
    admin.setNumber(config::numberCallCenter); // call center number
    admin.setRole(2); // call center admin role
    admin.setPassword(config::passwordAdmin); // default password for admin
    m_users.push_back(admin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_users()
{
    QSaveFile outf(config::fileUsers);
    outf.open(QIODevice::WriteOnly);
    QDataStream ost(&outf);
    for (size_t i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getRole() != 2)
            ost << m_users[i];
    }
    outf.commit();
}

void MainWindow::load_users()
{
    QFile inf(config::fileUsers);
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

void MainWindow::load_calls()
{
    QFile inf(config::fileCalls);
    inf.open(QIODevice::ReadOnly);
    QDataStream ist(&inf);
    m_calls.clear();
    while (!ist.atEnd())
    {
        call c;
        ist >> c;
        m_calls.push_back(c);
    }
}

void MainWindow::authorization()
{
    QDialog *authForm = new QDialog;
    Ui::authForm ui_authform;
    ui_authform.setupUi(authForm);
    bool try_auth = false;
    if (authForm->exec() == QDialog::Accepted)
    {        
        try_auth = true;
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

    if (try_auth)
    {
        if (role > 0)
        {
            QMessageBox::information(0, config::applicationName, "You'r succeful authorisation.");
            managerMainWindow *mmw = new managerMainWindow;
            mmw->setUsers(m_users);
            mmw->setCalls(m_calls);
            mmw->setIndex(index);
            mmw->show();
            this->close();
        }
        else if (role == 0)
        {
            QMessageBox::information(0, config::applicationName, "You'r succeful authorisation.");
            clientMainWindow *cmw = new clientMainWindow;
            cmw->setUsers(m_users);
            cmw->setCalls(m_calls);
            cmw->setIndexUser(index);
            cmw->show();
            this->close();
        }
        else
        {
            QMessageBox::information(0, config::applicationName, "User not finding.\nTry again.");
            authorization();
        }
    }

}


void MainWindow::registration()
{
    user m_user;
    register_user ru;
    ru.setUser(&m_user);
    if (ru.exec() != register_user::Accepted)
    {
        return;
    }
    m_users.push_back(m_user);
    save_users();
}

void MainWindow::about()
{
    QMessageBox about(this);
    about.setIcon(QMessageBox::Information);
    about.setWindowTitle(QString("About %1").arg("Call Center"));
    about.setText(QString("%1<br>"
        "Author: <a href=\"mailto:cergeu912@gmail.com\">Leushkin Vladislav Olegovich</a><br>"
        "Github: <a href=\"https://github.com/hyakkyy/callCenter\">https://github.com/hyakkyy/callCenter</a><br>"
        "Icons by <a href=\"http://tango.freedesktop.org/"
        "Tango_Desktop_Project\">The Tango! Desktop Project</a><br>"
        "Version %1: %2<br> Version QT: %3")
                  .arg(config::applicationName).arg(config::applicationVersion).arg(qVersion()));
    about.exec();
}

void MainWindow::exit()
{
    MainWindow::close();
}

