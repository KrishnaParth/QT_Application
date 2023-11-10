#ifndef EMPLOYEE_INFO_H
#define EMPLOYEE_INFO_H

#include <QDialog>
#include "widget.h"
#include<QAbstractTableModel>
#include<QObject>
#include<delegate.h>
#include<table_model.h>
#include<combobox_delegate.h>
#include<QSortFilterProxyModel>
#include<checkbox_delegate.h>
#include<checkbox_delegate2.h>


namespace Ui {
class employee_info;
}



class employee_info : public QDialog
{

    Q_OBJECT


public:

    class Widget* login_dialog;

    explicit employee_info(QWidget *parent = 0);
    ~employee_info();

private:

    void load_emloyee_management_table();
    //QStringList stringList; //internal data source
    delegate *myspinboxdelegate;
    combobox_delegate *mycombobox_delegate;
    table_model *mytablemodel;
    //checkbox_delegate2 *checkbox_del;
    checkbox_delegate * checkbox_dell;



private slots:
    //void on_save_tab_pushButton_clicked();

    //void on_cancel_tab_pushButton_clicked();

    void on_load_table_pushButton_clicked();

    void on_cancel_table_pushButton_clicked();

    //void on_pushButton_clicked();

    void on_loadtable_tab3_pushButton_clicked();

    //void on_cancel_tab3_pushButton_clicked();

    //void on_savechanges_tab3_pushButton_clicked();

    void on_loadtable_user_pushButton_clicked();

    void on_add_employee_pushButton_clicked();

    //void on_tab_destroyed();

    void on_cancel_tab3_pushButton_clicked();

    void on_cancel_user_pushButton_clicked();

    void add_employee_row();
    void delete_employee_row();

    void on_search_employee_pushButton_clicked();

    //void employee_table_item_changed(const QModelIndex &index);

    //void on_tableView_RTM_entered(const QModelIndex &index);

    void on_tableView_RTM_doubleClicked(const QModelIndex &index);

    void on_add_user_pushButton_clicked();

    void on_remove_user_pushButton_2_clicked();

public slots:
    //void check_user_role(const QString username);

    void activate_user_functions(QString text);
    void login_dialog_appear();
private:
    Ui::employee_info *ui;

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

#endif // EMPLOYEE_INFO_H
