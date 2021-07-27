#include "admin.h"
#include "ui_admin.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QMessageBox>
#include <QDebug>
#include <QListWidgetItem>
#include <QSqlTableModel>
#include <QDir>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    QString path = "C:/Users/beoo/Desktop/Kursishi2/baza.db";
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open()?qDebug()<<"Baza Ulandi!":qDebug()<<("Baza ulanmadi! :( ");

    ui->lineEdit_4->hide();
    ui->lineEdit_12->hide();

    QSqlQuery q;
    QString sql="SELECT * FROM users";
    q.prepare(sql);
    q.exec();
    while(q.next()){
        QString fio = q.value(1).toString();
        ui->listWidget->addItem(fio);
    }

    QSqlQuery q1;
    QString sql1="SELECT * FROM tovarlar";
    q1.prepare(sql1);
    q1.exec();
    while(q1.next()){
        QString nomi = q1.value(1).toString();
        ui->listWidget_2->addItem(nomi);
    }

    QSqlTableModel *md = new QSqlTableModel(this);
    md->setTable("orders");
    md->select();
    ui->tableView->setModel(md);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Admin::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Admin::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Admin::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Admin::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void Admin::on_listWidget_currentTextChanged(const QString &fio)
{
    QString login,parol,sql,id;
    ui->lineEdit->setText(fio);

    QSqlQuery q;
    sql="SELECT * FROM users WHERE fio='"+fio+"'";
    q.prepare(sql);
    q.exec();
    if(q.next()){
        id=q.value(0).toString();
        login=q.value(2).toString();
        parol=q.value(3).toString();
    }

    ui->lineEdit_2->setText(login);
    ui->lineEdit_3->setText(parol);
    ui->lineEdit_4->setText(id);
}

void Admin::on_pushButton_6_clicked()
{
    QSqlQuery qu;
    QString fio = ui->lineEdit->text().trimmed();
    QString login = ui->lineEdit_2->text().trimmed();
    QString parol = ui->lineEdit_3->text().trimmed();
    QString id = ui->lineEdit_4->text();

    QString sqlu = "UPDATE users SET fio='"+fio+"', login='"+login+"', parol='"+parol+"' WHERE id="+id;
    qu.prepare(sqlu);
    qu.exec();

    ui->listWidget->clear();

    QSqlQuery q;
    QString sql="SELECT * FROM users";
    q.prepare(sql);
    q.exec();
    while(q.next()){
        QString fio = q.value(1).toString();
        ui->listWidget->addItem(fio);
    }
}

void Admin::on_pushButton_8_clicked()
{
    QString id=ui->lineEdit_4->text();
    QString fio = ui->listWidget->currentItem()->text();
    QMessageBox msg;
    msg.setText(fio+"ni foydalanuvchilar ro'yxatidan' o'chirmoqchimisiz?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msg.exec();
    switch (ret) {
        case QMessageBox::Ok:{
            QSqlQuery del;
            QString sqld="DELETE FROM users WHERE id="+id;
            del.prepare(sqld);
            if(del.exec())
                QMessageBox::information(this,("!"),"O'chirildi",QMessageBox::Ok);
                QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
                delete it;
            break;
        }
          case QMessageBox::Cancel:
              msg.hide();
              break;
        }
}

void Admin::on_pushButton_7_clicked()
{
    QSqlQuery q;
    QString fio = ui->lineEdit_5->text().trimmed();
    QString login = ui->lineEdit_6->text().trimmed();
    QString parol = ui->lineEdit_7->text().trimmed();
    if(fio.size()>0&&login.size()>0&&parol.size()>0){
        QString sql = "INSERT into users (fio,login,parol,rol) VALUES ('"+fio+"','"+login+"','"+parol+"','user')";
        q.prepare(sql);
        if(q.exec()){
            QMessageBox::information(this,"ok","Foydalanuvchi qo'shildi!",QMessageBox::Ok|QMessageBox::Cancel);
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->listWidget->addItem(fio);

        }
        else{
            QMessageBox::information(this,"error","xatolik!",QMessageBox::Ok|QMessageBox::Cancel);
        }
    }

}


void Admin::on_listWidget_2_currentTextChanged(const QString &name)
{
    QString nomi,category,soni,narxi,sql,id;
    ui->lineEdit_8->setText(name);

    QSqlQuery q;
    sql="SELECT * FROM tovarlar WHERE name='"+name+"'";
    q.prepare(sql);
    q.exec();
    if(q.next()){
        id=q.value(0).toString();
        category=q.value(2).toString();
        soni=q.value(3).toString();
        narxi=q.value(4).toString();
    }

    ui->comboBox->setCurrentText(category);
    ui->lineEdit_10->setText(soni);
    ui->lineEdit_11->setText(narxi);
    ui->lineEdit_12->setText(id);
}

void Admin::on_pushButton_9_clicked()
{
    QString id=ui->lineEdit_12->text();
    QString name = ui->listWidget_2->currentItem()->text();
    QMessageBox msg;
    msg.setText(name+"ni tovarlar ro'yxatidan o'chirmoqchimisiz?");
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msg.exec();
    switch (ret) {
        case QMessageBox::Ok:{
            QSqlQuery del;
            QString sqld="DELETE FROM tovarlar WHERE id="+id;
            del.prepare(sqld);
            if(del.exec())
                QMessageBox::information(this,("!"),"O'chirildi",QMessageBox::Ok);
                QListWidgetItem *it = ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
                delete it;
            break;
        }
          case QMessageBox::Cancel:
              msg.hide();
              break;
        }
}

void Admin::on_pushButton_10_clicked()
{
    QSqlQuery qu;
    QString name = ui->lineEdit_8->text().trimmed();
    QString category = ui->comboBox->currentText();
    QString soni = ui->lineEdit_10->text().trimmed();
    QString narxi = ui->lineEdit_11->text().trimmed();
    QString id = ui->lineEdit_12->text();

    QString sqlu = "UPDATE tovarlar SET name='"+name+"', category='"+category+"', soni="+soni+",narxi="+narxi+" WHERE id="+id;
    qu.prepare(sqlu);
    qu.exec();

    ui->listWidget_2->clear();

    QSqlQuery q;
    QString sql="SELECT * FROM tovarlar";
    q.prepare(sql);
    q.exec();
    while(q.next()){
        QString name = q.value(1).toString();
        ui->listWidget_2->addItem(name);
    }
}

void Admin::on_pushButton_11_clicked()
{
    QSqlQuery q;
    QString name = ui->lineEdit_13->text().trimmed();
    QString category = ui->comboBox_2->currentText();
    QString soni = ui->lineEdit_15->text().trimmed();
    QString narxi = ui->lineEdit_16->text().trimmed();
    if(name.size()>0&&category.size()>0&&soni.size()>0&&narxi.size()>0){
        QString sql = "INSERT into tovarlar (name,category,soni,narxi) VALUES ('"+name+"','"+category+"',"+soni+","+narxi+")";
        q.prepare(sql);
        if(q.exec()){
            QMessageBox::information(this,"ok","Tovar qo'shildi!",QMessageBox::Ok|QMessageBox::Cancel);
            ui->lineEdit_13->clear();
            ui->comboBox_2->clear();
            ui->lineEdit_15->clear();
            ui->lineEdit_16->clear();
            ui->listWidget_2->addItem(name);

        }
        else{
            QMessageBox::information(this,"error","xatolik!",QMessageBox::Ok|QMessageBox::Cancel);
        }
    }
}
