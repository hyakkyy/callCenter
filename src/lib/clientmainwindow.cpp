#include "clientmainwindow.hpp"
#include "ui_clientmainwindow.h"
#include "startcall.hpp"
#include "callhistory.hpp"

#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

clientMainWindow::clientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientMainWindow)
{
    ui->setupUi(this);
}



void clientMainWindow::setIndexUser(int index_)
{
    index = index_;

    ui->nameUser->setText(m_users[index].getName());
    ui->numberUser->setText(m_users[index].getNumber());
}

clientMainWindow::~clientMainWindow()
{
    delete ui;
}

void clientMainWindow::startCallTime()
{
    auto updateTimer = new QTimer;
    updateTimer->setInterval(1000);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateDisplayedValues()));
    updateTimer->start();
}

void clientMainWindow::updateDisplayedValues()
{
    if (!stop)
    {
        QTime time = QTime::currentTime();
        //int diff = time.msecsTo(m_call.getStartCall().time());
        time = time.addSecs(-60 * m_call.getStartCall().time().minute());
        time = time.addSecs(-1 * m_call.getStartCall().time().second());
        //time = time.addSecs(diff);
        ui->callTimeEdit->setTime(time);
    }
}

void clientMainWindow::setUsers(std::vector<user> m_users_)
{
    m_users = m_users_;
}

void clientMainWindow::setCalls(std::vector<call> m_calls_)
{
    m_calls = m_calls_;
}

void clientMainWindow::startCallButton()
{
    startcall sc;
    sc.setUsers(m_users);
    sc.setCall(&m_call);
    sc.setIndexUser(index);
    if (sc.exec() != startcall::Accepted)
    {
        return;
    }
    stop = false;
    ui->startCallButton->setEnabled(false);
    ui->endCallButton->setEnabled(true);
    startCallTime();
}


void clientMainWindow::on_endCallButton_clicked()
{
    m_call.setEndCall(QDateTime::currentDateTime());
    m_calls.push_back(m_call);

    stop = true;
    ui->startCallButton->setEnabled(true);
    ui->endCallButton->setEnabled(false);
    //ui->callTimeEdit->setTime(QTime::)
}


void clientMainWindow::on_callHistoryButton_clicked()
{
    if (m_calls.empty())
    {
        QMessageBox::information(0, "Information", "Calls history is empty.");
        return;
    }
    callhistory ch;
    ch.setIndex(index);
    ch.setCalls(m_calls);
    if (ch.exec())
    {
        return;
    }
}

