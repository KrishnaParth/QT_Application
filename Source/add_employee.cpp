#include "add_employee.h"
#include "ui_add_employee.h"
#include"widget.h"

add_employee::add_employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_employee)
{
    ui->setupUi(this);
    add_employee::setWindowTitle("Add Employee");
    //this->setWindowFlags(this->windowFlags() & Qt::WindowMinimizeButtonHint & Qt::WindowMaximizeButtonHint);
   // this->show();

    Widget db_connection;
    if(db_connection.db_connection_open()) {
        qDebug()<<" Database Connected Successfully with Employee_Info...";
    }
    else
    {
        qDebug()<<"Error : Failed to open Database in Employee_Info ";
    }

}

add_employee::~add_employee()
{
    delete ui;
}

void add_employee::on_save_tab_pushButton_clicked()
{
    Widget db_connection;
    QString first_name,last_name,gender,age,salary;
    first_name = ui->fname_tab_lineEdit->text();
    last_name = ui->lname_tab_lineEdit->text();
    gender = ui->sex_tab_lineEdit->text();
    age = ui->age_tab_lineEdit->text();
    salary = ui->salary_tab_lineEdit->text();


//    if(!db_connection.db_connection_open())
//    {
//        ui->message_tab_label->setText(" Failed to open the Database! ");
//        qDebug()<<"Error : Database is not Reachable";
//    }

   db_connection.db_connection_open();
   QSqlQuery query;

   query.prepare("INSERT INTO employee (first_name,last_name,age,gender,salary) "
                 " VALUES ('"+first_name+"' ,'"+last_name+"','"+age+"','"+gender+"','"+salary+"')");

   if(query.exec())
   {
     QMessageBox::information(this, "Saved" , "Congrats! Data Saved Successfully");
     db_connection.db_connection_close();
     ui->fname_tab_lineEdit->clear();
     ui->lname_tab_lineEdit->clear();
     ui->age_tab_lineEdit->clear();
     ui->sex_tab_lineEdit->clear();
     ui->salary_tab_lineEdit->clear();

       }else {
           QMessageBox::warning(this, "Error::" , query.lastError().text());
           qDebug()<<"Error :: Query Not executed in Employee Tab";
       }
}

void add_employee::on_cancel_tab_pushButton_clicked()
{
    this->close();
     qDebug()<<"Error :: Employee has pressed cancel button";
}
