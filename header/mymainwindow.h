#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

#include<QSqlTableModel>
#include<delegate.h>
#include<combobox_delegate.h>
#include<table_model.h>
#include<checkbox_delegate.h>
#include<checkbox_delegate2.h>
#include<semaphore.h>

namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = 0);
    ~myMainWindow();

    class Widget* login_dialog;



private slots :

    //void add_employee_row();
   // void delete_employee_row();

    void on_loadtable_tab3_pushButton_clicked();

    void on_loadtable_user_pushButton_clicked();

    void on_add_employee_pushButton_clicked();

    void on_remove_row_pushButton_clicked();

    void on_search_employee_pushButton_clicked();

    void on_add_user_pushButton_clicked();

    void on_remove_user_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionLog_Out_triggered();

    void on_actionAdd_Employee_triggered();

    void on_actionRemove_Employee_triggered();

    void on_actionExport_Table_triggered();

    void on_actionSave_Changes_triggered();

 // void on_savechanges_tab3_pushButton_clicked();

    void on_refresh_actionAbout_triggered();

    void on_actionExit_triggered();

public slots:

    //void activate_user_functions(QString text);
    void login_dialog_appear();

private:
    Ui::myMainWindow *ui;

    QSqlTableModel* employee_model;
    QSqlTableModel* user_model;

    enum {
        Employee_id = 0,
        employee_first_name = 1,
        employee_last_name = 2,
        employee_sex = 3,
        employee_age = 4,
        employee_salary = 5
    };

    enum EMPLOYEE_COMBO_BOX{
        Employee_None,
        Employee_Id,
        Employee_name,
        Employee_Age ,
        Employee_Gender,
        Employee_Salary
    };

    void load_emloyee_management_table();

    delegate *myspinboxdelegate;
    combobox_delegate *mycombobox_delegate;
    table_model *mytablemodel;
    checkbox_delegate * checkbox_dell;

};

#endif // MYMAINWINDOW_H
