#include <QSaveFile>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QFileDialog>

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

void managerMainWindow::save_users()
{
    QSaveFile outf("users.tnb");
    outf.open(QIODevice::WriteOnly);
    QDataStream ost(&outf);
    for (size_t i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getRole() != 2)
            ost << m_users[i];
    }
    outf.commit();
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
    m_user.setName(QString("Call Center Manager %1").arg(num_manager));
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

void managerMainWindow::exportUsersCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Users As"), QString("Users-%1").arg(QDate::currentDate().toString()), "*.csv");
    QSaveFile outf(fileName);
    outf.open(QIODevice::WriteOnly);
    QTextStream ost(&outf);
    ost << QString("Название;Пароль;Номер телефона;ИНН;Банковский номер;Адрес\n").toUtf8();
    for (size_t i = 0; i < m_users.size(); i++)
    {
        QString line;
        if (m_users[i].getRole() == 2)
            continue;
        else if (m_users[i].getRole() == 1)
            line = line + "Call Center Manager" + ";";
        else
            line = line + QString("%1").arg(m_users[i].getName()) + ";";
        line = line + QString("%1").arg(m_users[i].getPassword()) + ";";
        line = line + QString("%1").arg(m_users[i].getNumber()) + ";";
        line = line + QString("%1").arg(m_users[i].getInn()) + ";";
        line = line + QString("%1").arg(m_users[i].getBankNum()) + ";";
        line = line + QString("%1").arg(m_users[i].getCity()) + ";\n";
        line = line.toUtf8();
        ost << line;
    }
    outf.commit();
}

void managerMainWindow::importUsersCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Users", "", "*.csv");
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file); bool first_str = true;
    m_users.clear();
    int count_manager = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (first_str)
        {
            first_str = false;
        }
        else
        {
            user m_user;
            QStringList list;
            for (QString item : line.split(";"))
            {
                list.push_back(item);
            }
            m_user.setPassword(list[1]);
            m_user.setNumber(list[2]);
            m_user.setInn(list[3]);
            m_user.setBankNum(list[4]);
            m_user.setCity(list[5]);
            if (list[0] == "Call Center Manager")
            {
                count_manager++;
                m_user.setName(QString("%1 %2").arg(list[0]).arg(count_manager));
                m_user.setRole(1);
            }
            else
            {
                m_user.setName(list[0]);
                m_user.setRole(0);
            }

            m_users.push_back(m_user);
        }
    }
    file.close();
}

void managerMainWindow::exportCallsCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save History Calls As"), QString("Calls-%1").arg(QDate::currentDate().toString()), "*.csv");
    QSaveFile outf(fileName);
    outf.open(QIODevice::WriteOnly);
    QTextStream ost(&outf);
    ost << QString("Имя звонящего;Номер звонящего;Адрес звонящего;Имя вызываемого;Номер вызываемого;"
                   "Адрес вызываемого;Время начала разговора;Время конца разговора;Длительность\n").toUtf8();
    for (size_t i = 0; i < m_calls.size(); i++)
    {
        QString line;
        line = line + QString("%1").arg(m_calls[i].getNameCalled()) + ";";
        line = line + QString("%1").arg(m_calls[i].getNumCalled()) + ";";
        line = line + QString("%1").arg(m_calls[i].getCityCalled()) + ";";
        line = line + QString("%1").arg(m_calls[i].getNameCalling()) + ";";
        line = line + QString("%1").arg(m_calls[i].getNumCalling()) + ";";
        line = line + QString("%1").arg(m_calls[i].getCityCalling()) + ";";
        line = line + QString("%1").arg(m_calls[i].getStartCall().toString("dd MMM yyyy HH:mm:ss")) + ";";
        line = line + QString("%1").arg(m_calls[i].getEndCall().toString("dd MMM yyyy HH:mm:ss")) + ";";

        QTime time = m_calls[i].getEndCall().time();
        time = time.addSecs(-60 * m_calls[i].getStartCall().time().minute());
        time = time.addSecs(-1 * m_calls[i].getStartCall().time().second());
        time = time.addSecs(-3600 * m_calls[i].getStartCall().time().hour());

        line = line + QString("%1").arg(time.toString()) + ";\n";
        line = line.toUtf8();
        ost << line;
    }
    outf.commit();
}

void managerMainWindow::importCallsCSV()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open History Calls", "", "*.csv");
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file); bool first_str = true;
    m_calls.clear();
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (first_str)
        {
            first_str = false;
        }
        else
        {
            call m_call;
            QStringList list;
            for (QString item : line.split(";"))
            {
                list.push_back(item);
            }
            m_call.setNameCalled(list[0]);
            m_call.setNumCalled(list[1]);
            m_call.setCityCalled(list[2]);
            m_call.setNameCalling(list[3]);
            m_call.setNumCalling(list[4]);
            m_call.setCityCalling(list[5]);
            m_call.setStartCall(list[6]);
            m_call.setEndCall(list[7]);
            m_calls.push_back(m_call);
        }
    }
    file.close();
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

