/*!
 * \file
 * \brief Заголовочный файл класса Users_table
 */
#ifndef USERS_TABLE_HPP
#define USERS_TABLE_HPP
#include <QDialog>
#include <QStandardItemModel>
#include "user.hpp"

namespace Ui {
class users_table;
}

class users_table : public QDialog
{
    Q_OBJECT

public:
    explicit users_table(QWidget *parent = nullptr);
    ~users_table();
    void setUsers(std::vector<user>*);
    void addColumns();
    void addRows();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::users_table *ui;
    std::vector<user>* m_users;
    QStandardItemModel *tbl;
};

#endif // USERS_TABLE_HPP
