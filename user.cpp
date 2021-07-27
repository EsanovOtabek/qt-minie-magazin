#include "user.h"
#include "ui_user.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QDir>
#include <QPixmap>

User::User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);

    QString path = "C:/Users/beoo/Desktop/Kursishi2/baza.db";
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open()?qDebug()<<"Baza Ulandi!":qDebug()<<("Baza ulanmadi! :( ");

     ui->lineEdit_5->hide();

    QSqlQuery q;
    QString sql="SELECT * FROM tovarlar";
    q.prepare(sql);
    q.exec();
    while(q.next()){
        QString name = q.value(1).toString();
        ui->listWidget->addItem(name);
    }




}

User::~User()
{
    delete ui;
}

void User::on_listWidget_currentTextChanged(const QString &name)
{
    QString nomi,category,soni,narxi,sql,id;
    ui->lineEdit->setText(name);

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
    ui->lineEdit_3->setText(soni);
    ui->lineEdit_4->setText(narxi);
    ui->lineEdit_5->setText(id);

    QPixmap pix(":/new/prefix1/images/"+category+".jpg");
    ui->label_4->setPixmap(pix);
}

void User::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString soni=ui->lineEdit_3->text();
    QString id=ui->lineEdit_5->text();
    QTime time=QTime::currentTime();
    QDate date=QDate::currentDate();
    QString sdate=date.toString("dd.MM.yyyy ");
    QString stime=time.toString("H:m:s");
    if(soni=="0"){
        QMessageBox::warning(this,":(","Kechirasiz magazinda "+name+" bunday tovarimiz tugagan :(",QMessageBox::Ok|QMessageBox::Cancel);
    }
    else{
        QSqlQuery q;
        QString sql="INSERT into orders (tovar_id,tovar_name,buyurtma_vaqti) VALUES ("+id+",'"+name+"','"+sdate+stime+"')";
        q.prepare(sql);
        if(q.exec()){
            QMessageBox::information(this,"Ok",""+name+" tovarga buyurtma berildi!",QMessageBox::Ok|QMessageBox::Cancel);

        }
    }
}
