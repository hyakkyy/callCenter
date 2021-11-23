#include "users_table.hpp"
#include "ui_users_table.h"
#include "edit_user.hpp"
#include <set>

users_table::users_table(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::users_table)
{
    ui->setupUi(this);
    addColumns();
}

void users_table::setUsers(std::vector<user>* m_users_)
{
    m_users = m_users_;
    addRows();
}

users_table::~users_table()
{
    delete ui;
}

void users_table::addColumns()
{
    tbl = new QStandardItemModel;
    tbl->setColumnCount(5);
    tbl->setHorizontalHeaderLabels(QStringList() << "Компания" << "Номер" << "Адрес"
                                   << "Банковский счет" << "ИНН компании");

    ui->tableView->setModel(tbl);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void users_table::addRows()
{
    for (size_t i = 0; i < m_users->size(); i++)
    {
        QList<QStandardItem *> standardItemsList;
        standardItemsList.append(new QStandardItem(m_users->at(i).getName()));
        standardItemsList.append(new QStandardItem(m_users->at(i).getNumber()));
        standardItemsList.append(new QStandardItem(m_users->at(i).getCity()));
        standardItemsList.append(new QStandardItem(m_users->at(i).getBankNum()));
        standardItemsList.append(new QStandardItem(m_users->at(i).getInn()));
        tbl->insertRow(tbl->rowCount(), standardItemsList);
    }
}

void users_table::on_addButton_clicked()
{
    edit_user add_user;
    user user;

    add_user.setUser(&user);
    if (add_user.exec() != users_table::Accepted)
    {
        return;
    }
    m_users->push_back(user);
}

void users_table::on_editButton_clicked()
{
    QModelIndex tmp = ui->tableView->currentIndex();
    int index = ui->tableView->model()->data(ui->tableView->model()->
                                             index(tmp.row(),1),0).toInt();
    edit_user add_user;

    add_user.setUser(&m_users->at(index));
    if (add_user.exec() != users_table::Accepted)
    {
        return;
    }
}

void users_table::on_deleteButton_clicked()
{
    QModelIndex tmp = ui->tableView->currentIndex();
    int index = ui->tableView->model()->data(ui->tableView->model()->
                                             index(tmp.row(),1),0).toInt();
    std::vector<user> new_users;
    for (size_t i = 0; i < m_users->size(); i++)
    {
        if (i != index)
        {
            new_users.push_back(m_users->at(i));
        }
    }
    m_users->clear();
    for (size_t i = 0; i < m_users->size(); i++)
    {
        if (i != index)
        {
            m_users->push_back(new_users[i]);
        }
    }

}

