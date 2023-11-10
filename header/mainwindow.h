#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include <QDialog>
#include "widget.h"
#include<QAbstractTableModel>
//
#include<delegate.h>
#include<table_model.h>
#include<combobox_delegate.h>
#include<QSortFilterProxyModel>
#include<checkbox_delegate.h>
#include<checkbox_delegate2.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    class Widget* login_dialog;
    void login_dialog_appear();

private:
    Ui::MainWindow *ui;
    void load_emloyee_management_table();

    class delegate *myspinboxdelegate;
    class combobox_delegate *mycombobox_delegate;
    class table_model *mytablemodel;

private slots:
    void on_load_table_pushButton_clicked();

    void on_cancel_table_pushButton_clicked();

    void on_loadtable_tab3_pushButton_clicked();

    void on_loadtable_user_pushButton_clicked();

    void on_add_employee_pushButton_clicked();


    void on_cancel_tab3_pushButton_clicked();

    void on_cancel_user_pushButton_clicked();

    void add_employee_row();
    void delete_employee_row();

    void on_search_employee_pushButton_clicked();

    void on_tableView_RTM_doubleClicked(const QModelIndex &index);

    void on_add_user_pushButton_clicked();

    void on_remove_user_pushButton_2_clicked();

public slots:

    void activate_user_functions(QString text);

private:

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

};

#endif // MAINWINDOW_H
