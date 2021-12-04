#ifndef CALLHISTORY_HPP
#define CALLHISTORY_HPP

#include <QDialog>
#include <QStandardItemModel>
#include "call.hpp"
#include "user.hpp"

namespace Ui {
class callhistory;
}

class callhistory : public QDialog
{
    Q_OBJECT

public:
    explicit callhistory(QWidget *parent = nullptr);
    ~callhistory();
    void setRole(int);
    void setCalls(std::vector<call>);
    void setIndex(int);
    void setUser(user);
    void addColumns();
    void addRowsForClient();
    void addRowsForManager();

private:
    Ui::callhistory *ui;
    QStandardItemModel *tbl;
    std::vector<call> m_calls;
    user m_user;
    int role = 0;
    int index = 0;
};

#endif // CALLHISTORY_HPP
