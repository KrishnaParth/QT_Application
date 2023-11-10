#include "mymainwindow.h"
#include "ui_mymainwindow.h"


#include<widget.h>
#include"add_employee.h"
#include<pthread.h>
#include<QMutex>

extern sem_t* sem;
//extern const char sem_name[];


myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
 //   pthread_mutex_t mutex;
//    QMutex mutex;

//    //mutex.lock();
//    if(mutex.try_lock())
//    {
//            qDebug()<<"mutex is locked";
//    }
//            else {
//            qDebug()<<"mutex is not locked";
//    }

//    pthread_mutex_init(&mutex, NULL);

//    pthread_mutex_lock(&mutex);

    ui->setupUi(this);

 //   pthread_mutex_unlock(&mutex);

    Widget db_connection;
    //db_connection.login_dialog_appear();

    if(db_connection.db_connection_open()) {
       // qDebug()<<" Database Connected Successfully with Employee_Info...";
    }
    else
    {
       // qDebug()<<"Error : Failed to open Database in Employee_Info ";
    }

    /*Creating table in database */

    if(db_connection.db_connection_open()) {

       // qDebug()<<" Database Connected Successfully with Employee_Info to add table...";

        //Creating Table user

        db_connection.db_connection_open(); //to make connection with database

        QSqlQuery qry("CREATE TABLE IF NOT EXISTS employee ( "
                      "employee_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
                      "first_name VARCHAR(20) NOT NULL ,"
                      "last_name VARCHAR(20) NOT NULL ,"
                      "gender VARCHAR(20) NOT NULL ,"
                      "age VARCHAR(20) NOT NULL ,"
                      "salary INT NOT NULL )");
}
       login_dialog_appear();

      ui->add_user_pushButton->setEnabled(true);
      ui->remove_user_pushButton_2->setEnabled(true);
      ui->savechanges_user_pushButton->setEnabled(true);
      ui->search_employee_comboBox->setCurrentIndex(0);
      ui->search_employee_comboBox->setStyleSheet("QComboBox {background-color : pink ;}");

      ui->add_row_pushButton->setVisible(false);
      ui->add_row_pushButton->setEnabled(false);

//      QObject::connect(ui->savechanges_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::submitAll);

//      QObject::connect(ui->reset_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::revertAll);

//      QObject::connect(ui->add_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(add_employee_row()));
//      QObject::connect(ui->remove_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(delete_employee_row()));

       //mutex.unlock();
}

myMainWindow::~myMainWindow()
{
    delete ui;
    sem_post(sem);
 //   sem_unlink(sem_name);
 //   sem_destroy(sem);  //only for unnamed semaphore
}

void myMainWindow::login_dialog_appear()
{

    login_dialog = new Widget(this);

    QBoxLayout* layout = new QBoxLayout (QBoxLayout::LeftToRight);
    layout->setAlignment(login_dialog, Qt::AlignCenter);

    connect(login_dialog,&Widget::accepted,[=](){
        //qDebug()<<"Dialog has been Accepted";
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

void myMainWindow::load_emloyee_management_table()
{
    myspinboxdelegate = new delegate(this);
    mycombobox_delegate = new combobox_delegate(this);
    checkbox_dell = new checkbox_delegate(this);

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

    employee_model->select();

    QObject::connect(ui->savechanges_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::submitAll);

    QObject::connect(ui->reset_tab3_pushButton,&QPushButton::clicked,employee_model,&QSqlTableModel::revertAll);

//    QObject::connect(ui->add_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(add_employee_row()));
//    QObject::connect(ui->remove_row_pushButton,SIGNAL(clicked(bool)),this,SLOT(delete_employee_row()));

    /* Sorting through Headers */
    QSortFilterProxyModel *sort =  new QSortFilterProxyModel(this);
    sort->setDynamicSortFilter(true);

    sort->setSourceModel(employee_model);
   // sort->sort(0,Qt::AscendingOrder);


    ui->tableView_RTM->setModel(sort);
    ui->tableView_RTM->sortByColumn(0,Qt::AscendingOrder);

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

void myMainWindow::on_loadtable_tab3_pushButton_clicked()
{
    load_emloyee_management_table();
}

void myMainWindow::on_loadtable_user_pushButton_clicked()
{
    Widget db_connection;
    db_connection.db_connection_open();

    user_model = new QSqlTableModel(this,db_connection.db);
    user_model->setTable("user");

    user_model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    user_model->select();

    QObject::connect(ui->savechanges_user_pushButton,&QPushButton::clicked,user_model,&QSqlTableModel::submitAll);

    QObject::connect(ui->reset_user_pushButton,&QPushButton::clicked,user_model,&QSqlTableModel::revertAll);

    ui->tableView_user->setModel(user_model);
    ui->tableView_user->setWindowTitle("Edit/Save User Table");
    ui->tableView_user->show();

    for(int i =0; i < user_model->rowCount(); ++i) {
    QString name = user_model->record(i).value("username").toString();
    qDebug()<< "Username is "<<name; }
}

void myMainWindow::on_add_employee_pushButton_clicked()
{
    add_employee * dialog = new add_employee(this);

    connect(dialog,&add_employee::accepted,[=](){
       // qDebug()<<"Dialog Accepted";
    });

    connect(dialog,&add_employee::rejected,[=](){
        //qDebug()<<"Dialog Rejected";
    });

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void myMainWindow::on_remove_row_pushButton_clicked()
{
    QModelIndexList indexes = ui->tableView_RTM->selectionModel()->selectedRows();
    int rowcount = indexes.count();

    for(int i = 0; i<rowcount; i++) {

       QModelIndex index = indexes.at(i);

    QSqlDatabase::database().transaction();
    QSqlRecord record= employee_model->record(index.row());
    int id = record.value(Employee_id).toInt();

    qDebug()<<"Employee id : "<<id;

    QSqlQuery qry;


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


    employee_model->removeRow(index.row());
    employee_model->submitAll();
    QSqlDatabase::database().commit();
    }

    ui->tableView_RTM->setFocus();

}

void myMainWindow::on_search_employee_pushButton_clicked()
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

        employee_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        employee_model->select();

        ui->tableView_RTM->setModel(employee_model);
        ui->tableView_RTM->setSelectionBehavior(QAbstractItemView::SelectRows);
        //ui->tableView_RTM->setColumnHidden(Employee_id,true);
        ui->tableView_RTM->show();
}
}

void myMainWindow::on_add_user_pushButton_clicked()
{
    user_model->select();
 //   ui->tableView_RTM->setItemDelegate());
    int row = user_model->rowCount();
    user_model->insertRow(row);
    QModelIndex index = user_model->index(row,0);  //user id col = 0
    ui->tableView_user->setCurrentIndex(index);
    ui->tableView_user->edit(index);
}

void myMainWindow::on_remove_user_pushButton_2_clicked()
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

void myMainWindow::on_pushButton_clicked()
{
    QString textdata;
    int rows = employee_model->rowCount();
    int column = employee_model->columnCount();

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<column; j++)
        {
            textdata += employee_model->data(employee_model->index(i,j)).toString();
            textdata += ", ";
        }
        textdata += "\n";
    }

    QString filters("CSV files (*.csv);; All files (*,*)");
    QString defaultFilter("CSV files (*.csv)");
    QString filename = QFileDialog::getSaveFileName(this,"Save Employee Data",QApplication::applicationDirPath(),
                                                   filters, &defaultFilter );    //"Employee Data (*.csv);;All Files(*)"
    QFile csvFile(filename);
   // QFile csvFile("/home/kodiak/Desktop/Krishna/documents/mytabledata.csv");


    if(csvFile.open( QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream out(&csvFile);
        out <<textdata;

        csvFile.close();

       //QMessageBox::information(this,"Successful","Data has been Exported Successfully");
    }
}

void myMainWindow::on_pushButton_2_clicked()
{
//    Widget db_connection;
//    employee_model = new QSqlTableModel(this,db_connection.db);
//    employee_model->setTable("employee");

//    QSqlDatabase::database().transaction();
//    QSqlQuery qry;

//    QString import = QString("LOAD DATA INFILE "
//                             "/home/kodiak/Desktop/Krishna/documents/importintotable.csv"
//                             "INTO TABLE employee"
//                             "FIELDS TERMINATED BY ',' "
//                             "LINES TERMINATED BY '\n' ");
//    qry.prepare(import);

//    // "(employee_id,first_name,last_name,gender,age,salary)"

////    qry.prepare("LOAD DATA INFILE "
////                "'/home/kodiak/Desktop/Krishna/documents/importintotable.csv'"
////                "INTO TABLE employee");

//    if(qry.exec(import))
//    {
//        QMessageBox::information(this,"Successful","Data has been imported, Press Refresh to see ");
//    }
//    else
//    {
//        QMessageBox::warning(this,"Error", "Something's Wrong, Please Check");
//    }

    QSqlDatabase::database().transaction();

    QString filename = QFileDialog::getOpenFileName(this,"Choose File");
    if(filename.isEmpty()) {return;}

    QFile file(filename);
    //if(!file.open(QIODevice::ReadOnly )) { qDebug()<<"CSV  disnt open"; }
    if(file.open(QIODevice :: ReadOnly))
    {
        qDebug()<<"csv open";
        QSqlQuery qry;
        QTextStream ts(&file);
       QString readline =ts.readLine();
       QStringList listval = ts.readLine().split(";") ; //, QString::SkipEmptyParts);

       int cter =0;
       while(!ts.atEnd())
       {

           QString readline =ts.readLine();
           QStringList listval = ts.readLine().split(";") ;
           cter +=1;


           qDebug()<<"Hi";
           QString req = "INSERT INTO employee "
                         "(employee_id,first_name,last_name,gender,age,salary) VALUES(' ";
           QStringList line = ts.readLine().split(" ", QString::SkipEmptyParts); //.split(',');
           //line = line.split(" ", QString::SkipEmptyParts);

           for(int i=0; i<line.length(); ++i)
           {
               req.append(line.at(i));
               req.append(" ' ");
               req.append(",");

           }
           req.chop(1);
           req.append(");");
         //  qry.exec(req);
           if(qry.exec(req)){  qDebug()<<"CSV imported"; }
                else { qDebug()<<"Query csv didnt executed";
       }
       }


//        while(!ts.atEnd())
//        {
//            qDebug()<<"Hi";
//            QString req = "INSERT INTO employee "
//                          "(employee_id,first_name,last_name,gender,age,salary) VALUES(' ";
//            QStringList line = ts.readLine().split(" ", QString::SkipEmptyParts); //.split(',');
//            //line = line.split(" ", QString::SkipEmptyParts);

//            for(int i=0; i<line.length(); ++i)
//            {
//                req.append(line.at(i));
//                req.append(" ' ");
//                req.append(",");

//            }
//            req.chop(1);
//            req.append(");");
//          //  qry.exec(req);
//            if(qry.exec(req)){  qDebug()<<"CSV imported"; }
//                 else { qDebug()<<"Query csv didnt executed";
//        }
//        }
        file.close();
    }else{ qDebug()<<"CSV  disnt open"; }
}

void myMainWindow::on_actionLog_Out_triggered()
{
    login_dialog_appear();
}

void myMainWindow::on_actionAdd_Employee_triggered()
{
    on_add_employee_pushButton_clicked();
}

void myMainWindow::on_actionRemove_Employee_triggered()
{
    on_remove_row_pushButton_clicked();
}

void myMainWindow::on_actionExport_Table_triggered()
{
    on_pushButton_clicked();
}

void myMainWindow::on_actionSave_Changes_triggered()
{
   employee_model->submitAll();
}

void myMainWindow::on_refresh_actionAbout_triggered()
{
    on_loadtable_tab3_pushButton_clicked();
}

void myMainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
