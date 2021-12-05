#ifndef MANAGERMAINWINDOW_HPP
#define MANAGERMAINWINDOW_HPP

#include <QMainWindow>
#include "user.hpp"
#include "call.hpp"

namespace Ui {
class managerMainWindow;
}

class managerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit managerMainWindow(QWidget *parent = nullptr);
    ~managerMainWindow();
    void setUsers(std::vector<user>);
    void setCalls(std::vector<call>);
    void setIndex(int);

public slots:
    void add_manager();
    void delete_manager();
    void exportUsersCSV();
    void importUsersCSV();
    void exportCallsCSV();
    void importCallsCSV();
    void exit();

private slots:
    void on_usersButton_clicked();

    void on_callHistoryButton_clicked();

private:
    void save_users();

    Ui::managerMainWindow *ui;
    std::vector<user> m_users;
    std::vector<call> m_calls;

    int index;
    int role;
};

#endif // MANAGERMAINWINDOW_HPP
