#ifndef USER_H
#define USER_H

#include <QMainWindow>

namespace Ui {
class User;
}

class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = 0);
    ~User();

private slots:
    void on_listWidget_currentTextChanged(const QString &name);

    void on_pushButton_clicked();

private:
    Ui::User *ui;
};

#endif // USER_H
