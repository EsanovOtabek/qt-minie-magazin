#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "admin.h"
#include "user.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    Admin admin_page;
    User user_page;
};

#endif // LOGIN_H
