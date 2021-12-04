#ifndef STARTCALL_HPP
#define STARTCALL_HPP

#include <QDialog>
#include "user.hpp"
#include "call.hpp"

namespace Ui {
class startcall;
}

class startcall : public QDialog
{
    Q_OBJECT

public:
    explicit startcall(QWidget *parent = nullptr);
    ~startcall();
    void setUsers(std::vector<user>);
    void setCall(call*);
    void setIndexUser(int);

private slots:
    void on_checkNum_clicked();

public slots:
    void accept();

private:
    Ui::startcall *ui;
    std::vector<user> m_users;
    call *m_call;
    int index_called;
    int index_calling = -1;
};

#endif // STARTCALL_HPP
