#ifndef CLIENTMAINWINDOW_HPP
#define CLIENTMAINWINDOW_HPP

#include <QMainWindow>
#include "user.hpp"
#include "call.hpp"

namespace Ui {
class clientMainWindow;
}

class clientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientMainWindow(QWidget *parent = nullptr);
    ~clientMainWindow();
    void setUsers(std::vector<user>);
    void setCalls(std::vector<call>);
    void setIndexUser(int);
    void startCallTime();

private slots:
    void startCallButton();
    void updateDisplayedValues();

    void on_endCallButton_clicked();

    void on_callHistoryButton_clicked();

private:
    Ui::clientMainWindow *ui;
    std::vector<user> m_users;
    std::vector<call> m_calls;
    int index;
    call m_call;
    bool stop = false;

    void save_call(call);
};

#endif // CLIENTMAINWINDOW_HPP
