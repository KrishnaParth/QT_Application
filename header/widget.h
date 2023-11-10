#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QtSql>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTableView>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <QStringList>
#include <QVector>
#include <QPushButton>
#include <QCheckBox>
#include <QList>
#include <QDateTime>
#include<QDebug>
#include<QDialog>
#include<QCryptographicHash>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>

#include"registration_window.h"
#include"employee_info.h"

#include<QtXml/QDomDocument>
#include<QtCore>
#include<QXmlStreamReader>



namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase db;
    void db_connection_close(){
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
        qDebug()<<" Database Connection removed!";
    }

    bool db_connection_open(){
        db = QSqlDatabase :: addDatabase("QMYSQL");
        db.setHostName("10.131.83.61");
        db.setUserName("kodiak");
        db.setPassword("K1o2d3i4a5k$");
        db.setDatabaseName("test");

        if(db.open()) {
            qDebug()<<" Database Connected Successfully..."; //<<QSqlDatabase::lastError();
            return true;
        }
        else
        {
            qDebug()<<"Error : Failed to open Database ";
            return false;
        }

    }

//extern int role_id;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void login_file_write();
    void login_file_read();

    void login_xml_read();
    void login_xml_write();
    void login_xml_list_elements(QDomElement root , QString tagname, QString attribute);

    QString encryptdecrypt(QString str);




public slots:
    void check_user_role(QString username);

signals:

  //  void user_logged_in(const QString);
    void username_password_verified();
    void admin_logged_in(const QString text);
    void remember_up();

//{
//        qDebug()<<"I am emitted now";
//    }

private slots:
    void on_login_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_reg_pushButton_clicked();

    void remembered_username_password();

    void on_remember_username_passwd_checkBox_stateChanged(int arg1);

    void on_remember_username_passwd_checkBox_clicked();

private:
    Ui::Widget *ui;
    class employee_info* employee;

    QSettings setting;
    QCheckBox *checkbox;

};

#endif // WIDGET_H
