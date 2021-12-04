#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <vector>
#include "user.hpp"
#include "call.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void authorization();
    void registration();

private:
    void load_users();
    void load_calls();
    void save_user(user);

    int role = -1;
    int index = -1;
    Ui::MainWindow *ui;
    std::vector<user> m_users;
    std::vector<call> m_calls;
};
#endif // MAINWINDOW_HPP
