#ifndef REGISTRATION_WINDOW_H
#define REGISTRATION_WINDOW_H

#include <QDialog>
#include "widget.h"

namespace Ui {
class Registration_Window;
}

class Registration_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Registration_Window(QWidget *parent = 0);
    ~Registration_Window();

private slots:
    void on_register_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Registration_Window *ui;
};

#endif // REGISTRATION_WINDOW_H
