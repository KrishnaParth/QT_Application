#ifndef ADD_EMPLOYEE_H
#define ADD_EMPLOYEE_H

#include <QDialog>

namespace Ui {
class add_employee;
}

class add_employee : public QDialog
{
    Q_OBJECT

public:
    explicit add_employee(QWidget *parent = 0);
    ~add_employee();

private slots:
    void on_save_tab_pushButton_clicked();

    void on_cancel_tab_pushButton_clicked();

private:
    Ui::add_employee *ui;

};

#endif // ADD_EMPLOYEE_H
