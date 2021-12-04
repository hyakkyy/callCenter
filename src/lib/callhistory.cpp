#include <QStandardItemModel>
#include "callhistory.hpp"
#include "ui_callhistory.h"

callhistory::callhistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::callhistory)
{
    ui->setupUi(this);
    addColumns();
}

void callhistory::setRole(int role_)
{
    role = role_;

    if (role > 0)
        addRowsForManager();
}
void callhistory::setIndex(int index_)
{
    index = index_;
}

void callhistory::setUser(user m_user_)
{
    m_user = m_user_;

    addRowsForClient();
}

void callhistory::setCalls(std::vector<call> m_calls_)
{
    m_calls = m_calls_;
}

void callhistory::addColumns()
{
    tbl = new QStandardItemModel;
    tbl->setColumnCount(9);
    tbl->setHorizontalHeaderLabels(QStringList() << "Компания звонившая" << "Номер звонившего" << "Город звонившего"
                                   << "Компания вызываемая" << "Номер вызываемого" << "Город вызываемого"
                                   << "Начало разговора" << "Конец разговра" << "Длительность");
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(tbl);
}

void callhistory::addRowsForClient()
{
    for (size_t i = 0; i < m_calls.size(); i++)
    {
        if ( ( m_calls[i].getNameCalled() == m_user.getName() )
                || ( m_calls[i].getNameCalling() == m_user.getName() ) )
        {
                QList<QStandardItem *> standardItemsList;
                standardItemsList.append(new QStandardItem(m_calls[i].getNameCalled()));
                standardItemsList.append(new QStandardItem(m_calls[i].getNumCalled()));
                standardItemsList.append(new QStandardItem(m_calls[i].getCityCalled()));
                standardItemsList.append(new QStandardItem(m_calls[i].getNameCalling()));
                standardItemsList.append(new QStandardItem(m_calls[i].getNumCalling()));
                standardItemsList.append(new QStandardItem(m_calls[i].getCityCalling()));
                standardItemsList.append(new QStandardItem(m_calls[i].getStartCall().toString()));
                standardItemsList.append(new QStandardItem(m_calls[i].getEndCall().toString()));

                QTime time = m_calls[i].getEndCall().time();
                time = time.addSecs(-60 * m_calls[i].getStartCall().time().minute());
                time = time.addSecs(-1 * m_calls[i].getStartCall().time().second());
                time = time.addSecs(-3600 * m_calls[i].getStartCall().time().hour());
                standardItemsList.append(new QStandardItem(time.toString()));
                tbl->insertRow(tbl->rowCount(), standardItemsList);
        }

    }
}

void callhistory::addRowsForManager()
{
    for (size_t i = 0; i < m_calls.size(); i++)
    {
        QList<QStandardItem *> standardItemsList;
        standardItemsList.append(new QStandardItem(m_calls[i].getNameCalled()));
        standardItemsList.append(new QStandardItem(m_calls[i].getNumCalled()));
        standardItemsList.append(new QStandardItem(m_calls[i].getCityCalled()));
        standardItemsList.append(new QStandardItem(m_calls[i].getNameCalling()));
        standardItemsList.append(new QStandardItem(m_calls[i].getNumCalling()));
        standardItemsList.append(new QStandardItem(m_calls[i].getCityCalling()));
        standardItemsList.append(new QStandardItem(m_calls[i].getStartCall().toString()));
        standardItemsList.append(new QStandardItem(m_calls[i].getEndCall().toString()));

        QTime time = m_calls[i].getEndCall().time();
        time = time.addSecs(-60 * m_calls[i].getStartCall().time().minute());
        time = time.addSecs(-1 * m_calls[i].getStartCall().time().second());
        time = time.addSecs(-3600 * m_calls[i].getStartCall().time().hour());
        standardItemsList.append(new QStandardItem(time.toString()));
        tbl->insertRow(tbl->rowCount(), standardItemsList);
    }
}

//void callhistory::addRowsForClient()
//{
//    for (int i = 0; i < m_calls.size(); i++)
//    {
//        if (i == index)
//        {
//            QList<QStandardItem *> standardItemsList;
//            standardItemsList.append(new QStandardItem(m_calls[i].getNameCalled()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getNumCalled()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getCityCalled()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getNameCalling()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getNumCalling()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getCityCalling()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getStartCall().toString()));
//            standardItemsList.append(new QStandardItem(m_calls[i].getEndCall().toString()));

//            QTime time = m_calls[i].getEndCall().time();
//            time = time.addSecs(-60 * m_calls[i].getStartCall().time().minute());
//            time = time.addSecs(-1 * m_calls[i].getStartCall().time().second());
//            standardItemsList.append(new QStandardItem(time.toString()));
//            tbl->insertRow(tbl->rowCount(), standardItemsList);
//        }
//    }
//    ui->tableView->setModel(tbl);
//}

callhistory::~callhistory()
{
    delete ui;
}
