#include "registration_window.h"
#include "ui_registration_window.h"
#include"widget.h"
#include"employee_info.h"

Registration_Window::Registration_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration_Window)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & Qt::WindowMinimizeButtonHint & Qt::WindowMaximizeButtonHint);
    this->show();
}

Registration_Window::~Registration_Window()
{
    delete ui;
}

void Registration_Window::on_register_pushButton_clicked()
{
    Widget db_connection;
    QString username,phone,email,password,confirm_password;
    username = ui->username_reg_lineEdit->text();
    phone = ui->Phoneno_reg_lineEdit->text();
    email = ui->email_reg_lineEdit->text();
    password = ui->password_reg_lineEdit->text();
    confirm_password = ui->confirmpasswd_reg_lineEdit->text();

    if(password == confirm_password) {
    if(!db_connection.db_connection_open())
    {
       // ui->registration_label->setText(" Failed to open the Database! ");
        qDebug()<<"Error : Database is not Reachable";
    }

   db_connection.db_connection_open();
   QSqlQuery query;

   query.prepare("INSERT INTO user (username,phone,email,password) "
                 " VALUES ('"+username+"' ,'"+phone+"','"+email+"','"+password+"')");

   if(query.exec())
   {
     QMessageBox::information(this, "Saved" , "Congrats! Data Saved Successfully");
     db_connection.db_connection_close();
     ui->username_reg_lineEdit->clear();
     ui->Phoneno_reg_lineEdit->clear();
     ui->email_reg_lineEdit->clear();
     ui->password_reg_lineEdit->clear();
     ui->confirmpasswd_reg_lineEdit->clear();

       }else {
           QMessageBox::warning(this, "Error::" , query.lastError().text());
           qDebug()<<"Error :: Query Not executed in Employee Tab";
       }
    }else
    {
        QMessageBox::warning(this,"Registration Failed","Password & Confirm Password don't match,try again!");
    }
}

void Registration_Window::on_pushButton_2_clicked()
{
    this->close();
    employee_info login;
    login.~employee_info();

    //login.login_dialog_appear();
//    //employee_info::employee_info::QDialog(parent),ui(employee_info);
   // qApp->exit();
}
