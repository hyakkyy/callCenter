#include <QSaveFile>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QComboBox>

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

void managerMainWindow::add_manager()
{
    // Create window
    QDialog *dialog = new QDialog();
    QGridLayout *gridLayout = new QGridLayout(dialog);
    dialog->setLayout(gridLayout);
    QLabel* label = new QLabel("Enter password for new manager");
    QLineEdit* passwordEdit = new QLineEdit();
    QDialogButtonBox* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    gridLayout->addWidget(label);
    gridLayout->addWidget(passwordEdit);
    gridLayout->addWidget(btnBox);
    if (dialog->exec() != QDialog::Accepted)
    {
        return;
    }

    int num_manager = 1;
    for (size_t i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getRole() == 1)
        {
            num_manager++;
        }
    }

    user m_user;
    // Default value for this Call Center
    m_user.setName(QString("Call Center Manager №%1").arg(num_manager));
    m_user.setBankNum("12345678911123456789"); // call center bank number
    m_user.setCity("Krasnoyarsk"); // call center city
    m_user.setInn("9876654321"); // call center inn
    m_user.setNumber("+79509777777"); // call center number
    m_user.setRole(1);
    m_user.setPassword(passwordEdit->text());

    m_users.push_back(m_user);
    save_users();
}

void managerMainWindow::delete_manager()
{
    // Create window
    QDialog *dialog = new QDialog();
    QGridLayout *gridLayout = new QGridLayout(dialog);
    dialog->setLayout(gridLayout);
    QLabel* label = new QLabel("Enter a manager");
    QComboBox* cmbBox = new QComboBox();
    QDialogButtonBox* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    gridLayout->addWidget(label);
    gridLayout->addWidget(cmbBox);
    gridLayout->addWidget(btnBox);

    for (size_t i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getRole() == 1)
        {
            cmbBox->addItem(m_users[i].getName());
        }
    }

    if (cmbBox->count() == 0)
    {
        QMessageBox::information(0, "Call Center", "Managers list is empty.");
        return;
    }

    if (dialog->exec() != QDialog::Accepted)
    {
        return;
    }

    size_t i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (cmbBox->currentText() == m_users[i].getName())
        {
            break;
        }
    }
    m_users.erase(m_users.begin() + i);
    save_users();
}

void managerMainWindow::on_callHistoryButton_clicked()
{
    if (m_calls.empty())
    {
        QMessageBox::information(0, "Call Center", "Calls history is empty.");
        return;
    }
    callhistory ch;
    ch.setIndex(index);
    ch.setCalls(m_calls);
    ch.setRole(role);
    ch.exec();
}

