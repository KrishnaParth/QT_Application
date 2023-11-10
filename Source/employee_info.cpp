#include "employee_info.h"
#include "ui_employee_info.h"
#include"widget.h"
#include<QMessageBox>
#include<QTableView>
#include<QSqlTableModel>
#include<QSqlRelationalTableModel>
#include<QObject>
#include"add_employee.h"
#include<QDialog>
#include<QPoint>
#include<table_model.h>
#include<QtGui>
#include<QWidget>
#include<QMainWindow>
#include<QToolBar>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QApplication>




//void employee_info::check_user_role(const QString username)
//{
//    QString user_name = username;
//    employee_info();
//    Widget();
// //  user_name = ui->username_lineEdit->text();
// //   passwd = ui->password_lineEdit->text();
//    qDebug()<<"role username is : "<<user_name;
//    int role_id;
//    QSqlQuery query;
//    query.prepare("SELECT role_id FROM user "
//                  "WHERE username = '"+ user_name +"' ");   //AND password = '"+ passwd +"'

//    if(query.exec())
//    {
//        while(query.next() ){
//        role_id = query.value(0).toInt();
//        qDebug()<<"role_id is : "<<role_id;}
//    }
//    else {
//        qDebug()<<"error in role func"<<query.lastError().text();
//    }


//    if(role_id == 1)
//    {
//        qDebug()<<"user role is admin";

//        ui->add_user_pushButton->setEnabled(true);
//        ui->remove_user_pushButton_2->setEnabled(true);
//        ui->savechanges_user_pushButton->setEnabled(true);

//    }
//    else
//    {
//        qDebug()<<"user role is normal";

//        ui->add_user_pushButton->setEnabled(false);
//        ui->remove_user_pushButton_2->setEnabled(false);
//        ui->savechanges_user_pushButton->setEnabled(false);

//    }


//    if( !check_user_role(user_name) ){

//    }
//    else
//    {

//    }
//}

void employee_info::login_dialog_appear()
{

    login_dialog = new Widget(this);

    QBoxLayout* layout = new QBoxLayout (QBoxLayout::LeftToRight);
    layout->setAlignment(login_dialog, Qt::AlignCenter);

    connect(login_dialog,&Widget::accepted,[=](){
        qDebug()<<"Dialog has been Accepted";
    });

    connect(login_dialog,&Widget::rejected,[=](){
        qApp->exit(),qDebug()<<"Dialog has been Rejected";
    });

  //    QPoint dialogPos = dialog->mapToParent(dialog->pos()); //Centering the Login Dialog
  //    QPoint thisPos = mapToGlobal(this->pos());
  //    QTabWidget* tab = new QTabWidget(this);

  //addWidget(dialog, Qt::AlignCenter);
    login_dialog->setModal(true);  //makes the dialog modal, cant reach main window

    login_dialog->show();
    login_dialog->raise();
    login_dialog->activateWindow();


//        login_dialog->exec();
//        login_dialog->raise();
//        login_dialog->activateWindow();
}


employee_info::employee_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee_info)
{


    ui->setupUi(this);
    employee_info::setWindowTitle("Employee Managment");
     this->setWindowFlags(this->windowFlags() & Qt::WindowMinimizeButtonHint & Qt::WindowMaximizeButtonHint);
    //this->setWindowFlags(this->windowFlags() & Qt::FramelessWindowHint);


    //menubar1
    QWidget* topwidget = new QWidget(this);
    QHBoxLayout *hlayout = new QHBoxLayout(topwidget);
   //hlayout->setContentsMargins(0,0,0,0);
    //this->layout()=QHBoxLayout();
    hlayout->addStretch(1);
    topwidget->setFixedHeight(0);
    topwidget->setFixedSize(QSize(110,40));
    QMenuBar *menubar = new QMenuBar(this);
   // QMenuBar::item {background-color : };
    menubar->setStyleSheet("background-color : pink ;");
    hlayout->addWidget(menubar);
    QMenu *menu1 = menubar->addMenu("Menu");
    QMenu *menu2 = menubar->addMenu("Help");
    QAction* action1 = menu1->addAction("Log Out");
    QAction* action2 = menu1->addAction("Exit");
    QAction* action3 = menu2->addAction("About");

    QObject::connect(action1, SIGNAL(triggered()),this,SLOT(login_dialog_appear()));
    QObject::connect(action2, SIGNAL(triggered()),this,SLOT(on_cancel_table_pushButton_clicked()));



//    QMainWindow *mainwindow = new QMainWindow();
//    QToolBar *mytoolbar = new QToolBar();
//    mainwindow->addToolBar(mytoolbar);

//    QHBoxLayout* layout = new QHBoxLayout();
//   // layout->setMenuBar(this);
//    layout->addWidget(mainwindow);
//    setLayout(layout);



    //login_dialog = new Widget();
    //connect(login_dialog,SIGNAL(admin_logged_in(QString)),this,SLOT(activate_user_functions(QString)));

    //this->raise();
    this->show();

    Widget db_connection;
    //db_connection.login_dialog_appear();

    if(db_connection.db_connection_open()) {
        qDebug()<<" Database Connected Successfully with Employee_Info...";
    }
    else
    {
        qDebug()<<"Error : Failed to open Database in Employee_Info ";
    }

    /*Creating table in database */

    if(db_connection.db_connection_open()) {
  //      ui->message_tab_label->setText(" Database Connected Successfully with Employee_Info... ");
        qDebug()<<" Database Connected Successfully with Employee_Info to add table...";

        //Creating Table user

        db_connection.db_connection_open(); //to make connection with database

        QSqlQuery qry("CREATE TABLE IF NOT EXISTS employee ( "
                      "employee_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
                      "first_name VARCHAR(20) NOT NULL ,"
                      "last_name VARCHAR(20) NOT NULL ,"
                      "sex VARCHAR(20) NOT NULL ,"
                      "age VARCHAR(20) NOT NULL ,"
                      "salary INT NOT NULL )");
}
       login_dialog_appear();


//      Widget* role = new Widget;
//      connect(role,SIGNAL(user_logged_in(const QString)),this,SLOT(check_user_role(const QString)));

      /* setting user filters */
      //int role = role_id;


      //qDebug()<<"role id in employee is"<<db_connection.role_id;
      //if(role_id == 1) {
      ui->add_user_pushButton->setEnabled(true);
      ui->remove_user_pushButton_2->setEnabled(true);
      ui->savechanges_user_pushButton->setEnabled(true);
     // else
      //{
//          ui->add_user_pushButton->setEnabled(false);
//          ui->remove_user_pushButton_2->setEnabled(false);
//          ui->savechanges_user_pushButton->setEnabled(false);
//      }


      /* Automatically Load Employee Table */
     // employee = new employee_info;

      ui->search_employee_comboBox->setCurrentIndex(0);
      ui->search_employee_comboBox->setStyleSheet("QComboBox {background-color : pink ;}");



      ui->add_row_pushButton->setVisible(false);
      ui->add_row_pushButton->setEnabled(false);

}

employee_info::~employee_info()
{
    delete ui;
}

void employee_info::load_emloyee_management_table()
{
    myspinboxdelegate = new delegate(this);
    mycombobox_delegate = new combobox_delegate(this);
    checkbox_dell = new checkbox_delegate(this);
   // checkbox_del = new checkbox_delegate2(this);

    Widget db_connection;
    qDebug()<< " Automatically Load Employee Table";
    employee_model = new QSqlTableModel(this,db_connection.db);
    employee_model->setTable("employee");
    mytablemodel = new table_model();



    ui->tableView_RTM->setModel(mytablemodel);
    employee_model->setHeaderData(0,Qt::Horizontal,QObject::tr("Employee Id"));
    employee_model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
    employee_model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
    employee_model->setHeaderData(3,Qt::Horizontal,QObject::tr("Gender"));
    employee_model->setHeaderData(4,Qt::Horizontal,QObject::tr("Age"));
    employee_model->setHeaderData(5,Qt::Horizontal,QObject::tr("Salary"));

    //employee_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    employee_model->select();

    QObject::connect(ui->savechanges_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::submitAll);

    QObject::connect(ui->reset_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::revertAll);

    QObject::connect(ui->add_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(add_employee_row()));
    QObject::connect(ui->remove_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(delete_employee_row()));

    /* Sorting through Headers */
    QSortFilterProxyModel *sort =  new QSortFilterProxyModel(this);
    sort->setDynamicSortFilter(true);

    //sort->setHeaderData(0,Qt::Horizontal,QObject::tr("Employee Id"));
    sort->setSourceModel(employee_model);
    //sort->setSourceModel(mytablemodel);





    ui->tableView_RTM->setModel(sort);


    //ui->tableView_RTM->setItemDelegate(myspinboxdelegate);
    //ui->tableView_RTM->setItemDelegateForColumn(0,mytabledelegate);
//    ui->tableView_RTM->setItemDelegateForColumn(3,mytabledelegate);

//    ui->tableView_RTM->setItemDelegateForColumn(1,mytabledelegate);

//    ui->tableView_RTM->setItemDelegateForColumn(2,mytabledelegate);


   // ui->tableView_RTM->setItemDelegate(checkbox_del);
    //ui->tableView_RTM->setItemDelegate(checkbox_dell);
    ui->tableView_RTM->setItemDelegateForColumn(0,myspinboxdelegate);
    ui->tableView_RTM->setItemDelegateForColumn(3,mycombobox_delegate);
    ui->tableView_RTM->setItemDelegateForColumn(4,myspinboxdelegate);
    ui->tableView_RTM->setItemDelegateForColumn(5,myspinboxdelegate);
    ui->tableView_RTM->setSortingEnabled(true);
    ui->tableView_RTM->setSelectionBehavior(QAbstractItemView::SelectRows);
   // ui->tableView_RTM->setColumnHidden(Employee_id,true);
    ui->tableView_RTM->setWindowTitle("Edit/Save Employee Table");
    ui->tableView_RTM->show();
}

//int employee_info::rowCount(const QModelIndex &parent) const
//{
//    return stringList.count(); //no of rows in the model to be same as no of strings in the string list
//}

//QVariant employee_info::data(const QModelIndex &index, int role) const
//{

//}

//bool employee_info::setdata(const QModelIndex &index, const QVariant &value, int role)
//{
//    if(index.isValid() && (role == Qt::EditRole ||role == Qt::DisplayRole)) {
//        employee_model[index]
//    }
//}



void employee_info::on_load_table_pushButton_clicked()
{
    load_emloyee_management_table();

//    Widget db_connection;
//   // db_connection.db_connection_open();

//    QSqlQuery* qry = new QSqlQuery(db_connection.db);

//    qry->prepare("SELECT * FROM employee");
//    if(qry->exec())
//    {
//        QSqlQueryModel * model = new QSqlQueryModel();
//        model->setQuery(*qry);

//      //db_connection.db_connection_close();
//        qDebug()<<(model->rowCount());
//    }else
//    {
//        qDebug()<<"Data Not Loaded from employee..!";
//    }


}

void employee_info::on_cancel_table_pushButton_clicked()
{
    qApp->exit();
   // employee_info::setEnabled(false);
    qDebug()<<"User Cancelled the employee Table view Tab..";
}

void employee_info::on_loadtable_tab3_pushButton_clicked()
{
    load_emloyee_management_table();
//    Widget db_connection;
//    //db_connection.db_connection_open();

//    qDebug()<< "entered ";

//    /*
//    QSqlRelationalTableModel rtm ;
//    rtm.setTable("employee");
//    QSqlRelation rel("employee_id","first_name","last_name","sex","age","salary");
//    rtm.setRelation(3, rel);
//    rtm.select();

//    ui->tableView_RTM->setModel(&rtm);
//    ui->tableView_RTM->setItemDelegate(new QSqlRelationalDelegate(&rtm));
//    ui->tableView_RTM->setWindowTitle("Table with resolved relation");
//    ui->tableView_RTM->show();
//    */

//    employee_model = new QSqlTableModel(this,db_connection.db);
//    employee_model->setTable("employee");


//    employee_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    employee_model->select();
//    // ui->tableView_RTM->setModel(model);
//    //connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(changetext()));
//    //connect(ui->pushButton,&QPushButton::clicked,this,&Widget::changetext);

//    QObject::connect(ui->savechanges_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::submitAll);

//    QObject::connect(ui->reset_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::revertAll);

//    QObject::connect(ui->add_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(add_employee_row()));
//    QObject::connect(ui->remove_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(delete_employee_row()));

////    QString emp_id = ui->search_employee_lineEdit->text();
////    QString whereid = "employee_id = %1";
////    QObject::connect(ui->search_employee_pushButton,&QPushButton::clicked,employee_model,
////                     &QSqlTableModel::setFilter(whereid.arg(emp_id)));

//    /* Sorting through Headers */
//    QSortFilterProxyModel *sort =  new QSortFilterProxyModel(this);
//    sort->setDynamicSortFilter(true);
//    sort->setSourceModel(employee_model);



//    ui->tableView_RTM->setModel(sort);
//   // ui->tableView_RTM->setStyleSheet("QTableView::item:alternate {background-color: #bfffbf;}");
//                                    // QTableView::item:alternate {background-color: #deffde;}");

//    ui->tableView_RTM->setSortingEnabled(true);
//    ui->tableView_RTM->setSelectionBehavior(QAbstractItemView::SelectRows);
//   // ui->tableView_RTM->setColumnHidden(Employee_id,true);
//    ui->tableView_RTM->setWindowTitle("Edit/Save Employee Table");
//    ui->tableView_RTM->show();

//    ///QSqlQuery query = QString("SELECT * FROM employee WHERE employee_id = %1").arg(emp_id);

//    for(int i =0; i < employee_model->rowCount(); ++i) {
//    QString name = employee_model->record(i).value("first_name").toString();
//    qDebug()<< "string is "<<name; }

    //db_connection.db_connection_close();
}


void employee_info::on_loadtable_user_pushButton_clicked()
{
    Widget db_connection;
    db_connection.db_connection_open();

    user_model = new QSqlTableModel(this,db_connection.db);
    user_model->setTable("user");

    user_model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    user_model->select();

    QObject::connect(ui->savechanges_user_pushButton,&QPushButton::clicked,user_model,&QSqlTableModel::submitAll);

    QObject::connect(ui->reset_user_pushButton,&QPushButton::clicked,user_model,&QSqlTableModel::revertAll);

//    QModelIndex index = ui->tableView_RTM->currentIndex();
//     setdatatype(index);

    ui->tableView_user->setModel(user_model);
    ui->tableView_user->setWindowTitle("Edit/Save User Table");
    ui->tableView_user->show();

    for(int i =0; i < user_model->rowCount(); ++i) {
    QString name = user_model->record(i).value("username").toString();
    qDebug()<< "Username is "<<name; }
}


/* Add Employee Dialog */

void employee_info::on_add_employee_pushButton_clicked()
{
    add_employee * dialog = new add_employee(this);

    connect(dialog,&add_employee::accepted,[=](){
        qDebug()<<"Dialog Accepted";
    });

    connect(dialog,&add_employee::rejected,[=](){
        qDebug()<<"Dialog Rejected";
    });

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void employee_info::on_cancel_tab3_pushButton_clicked()
{
    this->close();

}

void employee_info::on_cancel_user_pushButton_clicked()
{
    this->close();
}

void employee_info::add_employee_row()
{
    employee_model->select();
 //   ui->tableView_RTM->setItemDelegate());
    int row = employee_model->rowCount();
    employee_model->insertRow(row);
    QModelIndex index = employee_model->index(row,Employee_id);
    ui->tableView_RTM->setCurrentIndex(index);
    ui->tableView_RTM->edit(index);


}

void employee_info::delete_employee_row()
{
    QModelIndexList indexes = ui->tableView_RTM->selectionModel()->selectedRows();
    int rowcount = indexes.count();

    //QModelIndex index = ui->tableView_RTM->currentIndex();
    //if(!index.isValid()) { return; }

    for(int i = 0; i<rowcount; i++) {

       QModelIndex index = indexes.at(i);

    QSqlDatabase::database().transaction();
    QSqlRecord record= employee_model->record(index.row());
    int id = record.value(Employee_id).toInt();

    qDebug()<<"Employee id : "<<id;

//   int employee_num = 0;

    QSqlQuery qry;

//    qry (QString("SELECT COUNT(*) FROM employee"
//                           "WHERE employee_id = %1").arg(id));

//    if (qry.next())
//    {
//        employee_num = qry.value(0).toInt();    // value - value of field index at current record
//        qDebug()<<"Employee Num : "<<employee_num;
//    }

//   if(employee_num>0) {

        int r = QMessageBox::warning(this,tr("Delete Employee Detail"),tr(" Delete '%1 %2' details from the database? ")
                .arg(record.value(employee_first_name).toString()).arg(record.value(employee_last_name).toString()),
                QMessageBox::Yes | QMessageBox::No);

        if(r == QMessageBox:: No){
            QSqlDatabase::database().rollback();
            return;
        }else
        {
            qry.exec(QString("DELETE FROM employee"
                             "WHERE employee_id = %1").arg(id));
        }

  //  }

    employee_model->removeRow(index.row());
    employee_model->submitAll();
    QSqlDatabase::database().commit();
    }

    ui->tableView_RTM->setFocus();


}



void employee_info::on_search_employee_pushButton_clicked()
{

    ui->search_employee_lineEdit->setPlaceholderText("Enter Employee Detail");

    switch (ui->search_employee_comboBox->currentIndex()) {

    case Employee_None: {
        break; }

    case Employee_Id: {
        ui->search_employee_lineEdit->setPlaceholderText("Enter Employee Id");
        qDebug()<<"Search Combo box id index is : "<<ui->search_employee_comboBox->currentIndex();
        int emp_id = ui->search_employee_lineEdit->text().toInt();
        QString whereid = "employee_id LIKE '%\%1%' ";
        employee_model->setFilter(whereid.arg(emp_id));

        break; }

    case Employee_name: {
        ui->search_employee_lineEdit->setPlaceholderText("Enter Employee First Name");
        qDebug()<<"Search Combo box name index is : "<<ui->search_employee_comboBox->currentIndex();
        QString emp_name = ui->search_employee_lineEdit->text();
        QString wherename = "concat(first_name,' ',last_name) LIKE '%\%1%' ";
        employee_model->setFilter(wherename.arg(emp_name));

        break; }

    case Employee_Age: {
        ui->search_employee_lineEdit->setPlaceholderText("Enter Employee Age");
        qDebug()<<"Search Combo box age index is : "<<ui->search_employee_comboBox->currentIndex();
        int emp_age = ui->search_employee_lineEdit->text().toInt();
        QString whereage = "age LIKE '%\%1%' ";
        employee_model->setFilter(whereage.arg(emp_age));

        break; }

    case Employee_Gender: {
        ui->search_employee_lineEdit->setPlaceholderText("Enter Employee Gender");
        qDebug()<<"Search Combo box gender index is : "<<ui->search_employee_comboBox->currentIndex();
        QString emp_gender = ui->search_employee_lineEdit->text();
        QString wheregender = "gender LIKE '%\%1%' ";
        employee_model->setFilter(wheregender.arg(emp_gender));

        break; }

    case Employee_Salary: {
        ui->search_employee_lineEdit->setPlaceholderText("Enter Employee Salary");
        qDebug()<<"Search Combo box salary index is : "<<ui->search_employee_comboBox->currentIndex();
        int emp_salary = ui->search_employee_lineEdit->text().toInt();
        QString wheresalary = "salary LIKE '%\%1%' ";
        employee_model->setFilter(wheresalary.arg(emp_salary));

        break; }

    default:
        break;
    }

//    if(ui->search_employee_comboBox->currentText()== "Employee Id") {
//    int emp_id = ui->search_employee_lineEdit->text().toInt();
//    QString whereid = "employee_id LIKE '%\%1' ";
//    employee_model->setFilter(whereid.arg(emp_id));
//    }



    employee_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    employee_model->select();

    ui->tableView_RTM->setModel(employee_model);
    ui->tableView_RTM->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView_RTM->setColumnHidden(Employee_id,true);
    ui->tableView_RTM->show();


//    Widget db_connection;
//    //db_connection.db_connection_open();

//    qDebug()<< "entered Search ";

//    int emp_id = ui->search_employee_lineEdit->text().toInt();
//    bool Ok;
//    emp_id.toInt(&Ok);

//    QString whereid = 'employee_id = '%"%1"%';

//    QSqlQuery *query ;
//    query->prepare(QString("SELECT * FROM employee WHERE employee_id = %1").arg(emp_id));

//    employee_model = new QSqlTableModel(this,db_connection.db);
//    employee_model->QSqlQueryModel::setQuery(*query);


//    employee_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    employee_model->select();

//    ui->tableView_RTM->setModel(employee_model);
//    ui->tableView_RTM->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableView_RTM->setColumnHidden(employee_id,true);
    //    ui->tableView_RTM->show();
}



void employee_info::on_tableView_RTM_doubleClicked(const QModelIndex &index)
{
    QModelIndex i = index;
      if(!i.isValid()) { return; }
    QString id = QString::number(employee_model->record(i.row()).value(0).toInt());

    QString gender = employee_model->record(i.row()).value(3).toString();
    QString age = QString::number( employee_model->record(i.row()).value(4).toInt());
    QString salary = QString::number(employee_model->record(i.row()).value(5).toInt());
    QString first_name = employee_model->record(i.row()).value(1).toString();
    QString last_name = employee_model->record(i.row()).value(2).toString();

    qDebug()<<"employee id selected"<<id<<"first name is "<<first_name<<"gender is"<<gender<<"age is "<<age <<","<<salary
           <<"column is "<<index.column();

}

void employee_info::on_add_user_pushButton_clicked()
{
    user_model->select();
 //   ui->tableView_RTM->setItemDelegate());
    int row = user_model->rowCount();
    user_model->insertRow(row);
    QModelIndex index = user_model->index(row,0);  //user id col = 0
    ui->tableView_user->setCurrentIndex(index);
    ui->tableView_user->edit(index);
}

void employee_info::on_remove_user_pushButton_2_clicked()
{
    QModelIndexList indexes = ui->tableView_user->selectionModel()->selectedRows();
    int rowcount = indexes.count();

    for(int i = 0; i<rowcount; i++) {

    QModelIndex index = indexes.at(i);

    QSqlDatabase::database().transaction();
    QSqlRecord record= user_model->record(index.row());
    int id = record.value(0).toInt();  // user_id = 0

    qDebug()<<"User id : "<<id;

    QSqlQuery qry;

        int r = QMessageBox::warning(this,tr("Delete User"),tr(" Delete '%1' details from the database? ")
                .arg(record.value(1).toString()),
                QMessageBox::Yes | QMessageBox::No);

        if(r == QMessageBox:: No){
            QSqlDatabase::database().rollback();
            return;
        }else
        {
            qry.exec(QString("DELETE FROM user"
                             "WHERE user_id = %1").arg(id));
        }

    user_model->removeRow(index.row());
    user_model->submitAll();
    QSqlDatabase::database().commit();
    }

    ui->tableView_user->setFocus();

}

void employee_info::activate_user_functions(QString text)
{
    qDebug()<<"I have been called by admin";
   // employee_info();
    ui->add_user_pushButton->setEnabled(true);
    ui->remove_user_pushButton_2->setEnabled(true);
    ui->savechanges_user_pushButton->setEnabled(true);
}


