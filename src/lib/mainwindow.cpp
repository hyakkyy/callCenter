#include <QMessageBox>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "ui_authform.h"
#include "clientmainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    u2.setPassword("sber_pushka"); // пароль генерируется
    u2.setNumber("+79509654321"); // обязательно через +7 и вместе с '+' 12 символов
    u2.setInn("9987654321"); // 10 цифр
    u2.setBankNum("12345678999987654321"); // 20 цифр
    u2.setCity("Krasnoyarsk"); // 25 букв
    u2.setRole(0); // 0 - клиент, 1 - менеджер, 2 - администратор
    m_users.push_back(u2);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    }
    else if (role == 0)
    {
        QMessageBox::information(0, "Succeful", "You'r succeful authorisation.");
        clientMainWindow *cmw = new clientMainWindow;
        cmw->setUsers(m_users);
        cmw->setIndexUser(index);
        cmw->show();
        this->close();
    }
    else
    {
        QMessageBox::information(0, "Error", "User not finding.\nTry again.");
    }
}

