#include "clientmainwindow.hpp"
#include "ui_clientmainwindow.h"
#include "startcall.hpp"
#include "callhistory.hpp"
#include "config.hpp"

#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QFile>

clientMainWindow::clientMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientMainWindow)
{
    ui->setupUi(this);
}

void clientMainWindow::save_call(call m_call_)
{
    QFile outf(config::fileCalls);
    outf.open(QIODevice::Append);
    QDataStream out(&outf);
    out << m_call_;
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
    updateTimer->setInterval(500);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateDisplayedValues()));
    updateTimer->start();
}

void clientMainWindow::updateDisplayedValues()
{
    if (!stop)
    {
        QTime time = QTime::currentTime();
        time = time.addSecs(-3600 * m_call.getStartCall().time().hour());
        time = time.addSecs(-60 * m_call.getStartCall().time().minute());
        time = time.addSecs(-1 * m_call.getStartCall().time().second());
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
    save_call(m_call);

    stop = true;
    ui->startCallButton->setEnabled(true);
    ui->endCallButton->setEnabled(false);
    //ui->callTimeEdit->setTime(QTime::)
}

void clientMainWindow::on_callHistoryButton_clicked()
{
    if (m_calls.empty())
    {
        QMessageBox::information(0, "Information", "У вас нет истории звонков.");
        return;
    }
    callhistory ch;
    ch.setIndex(index);
    ch.setCalls(m_calls);
    ch.setUser(m_users[index]);
    ch.exec();
}

void clientMainWindow::exit()
{
    clientMainWindow::close();
}


