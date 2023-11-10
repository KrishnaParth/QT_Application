#include "widget.h"
#include "ui_widget.h"
#include"employee_info.h"
#include<QDebug>
#include<QDialog>
#include<QtXml/QDomDocument>
#include<QtCore>
#include<QXmlStreamReader>





Widget* login_dialog;



Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QPalette pal = QPalette();
//    pal.setColor(QPalette::Window, Qt::black);

//    Widget.setAutoFillBackground(true);
//    Widget.setPalette(pal);

//    Widget.show();

    /* Adding image to label */

    QPixmap pix("kodiak.png");
    ui->label_pic->setPixmap(pix);

    ui->remember_username_passwd_checkBox->setChecked(setting.value("checkstate").toBool());
    if(setting.value("checkstate").toBool()==true){
        //login_file_read();
      login_xml_read();
    }

    /*Creating table in database */

    if(db_connection_open()) {
        ui->messagelabel->setText(" Database Connected Successfully...");

        //Creating Table user

        db_connection_open(); //to make connection with database

        QSqlQuery qry("CREATE TABLE IF NOT EXISTS user ( "
                      "user_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, "
                      "username VARCHAR(20) NOT NULL UNIQUE,"
                      "phone VARCHAR(20) NOT NULL UNIQUE,"
                      "email VARCHAR(20) NOT NULL UNIQUE,"
                      "password VARCHAR(20) NOT NULL )");

/*
         qry.exec("INSERT INTO user (username,phone,email,password) "
                 " VALUES ('kp123','9876543210', 'kp@gmail.com', '1234')");


        qry.exec("INSERT INTO user (username,phone,email,password,salary) "
                 " VALUES (:username , :phone, :email , :password , :salary )");

        qry.bindValue("username","kp123");
        qry.bindValue("phone","9876543210");
        qry.bindValue("email","kp@gmail.com");
        qry.bindValue("password","1234");
        qry.bindValue("salary","22000");

*/


        if(!qry.isActive()) { qWarning() << "Error query not running: " <<qry.lastError().text();}

    } else
    {
        ui->messagelabel->setText(" Failed to open the Database! ");
    }


    // setting up validators

    QRegExp psswrd("[0-9]{5,5}");
    QRegExpValidator* x_psswrd = new QRegExpValidator( psswrd,this );

    ui->username_lineEdit->setPlaceholderText( tr("Enter Username"));
    ui->password_lineEdit->setPlaceholderText( tr("Enter Password"));
    ui->password_lineEdit->setValidator(x_psswrd);


//[A-Za-z]{0,1}+@([0-9]{3,5})$

  //  "(^[a-zA-Z]{1}[0-9]{1}[a-zA-Z]{1}[ ]{1}[0-9]{1}[a-zA-Z]{1}[0-9]{1}$)"

    QRegExp usrnm("\[a-zA-Z]{2}@\[0-9]{3}");
    QRegExpValidator* x_usrnm = new QRegExpValidator( usrnm,this );
    ui->username_lineEdit->setValidator(x_usrnm);

//    ui->username_lineEdit->setText("kp@123");
//    ui->password_lineEdit->setText("12345");

//    if(ui->remember_username_passwd_checkBox->isChecked()) {
//        emit remember_up();
//    }

    //connect(ui->remember_username_passwd_checkBox,@QCheckBox,this,SLOT(remembered_username_password()));


}

Widget::~Widget()
{
    delete ui;
}

/* checks if user is admin or not */

void Widget::check_user_role(QString username)
{
    QString user_name = username;
//    user_name = ui->username_lineEdit->text();
//    passwd = ui->password_lineEdit->text();
    qDebug()<<"role username is : "<<user_name;
    int role_id;
    QSqlQuery query;
    query.prepare("SELECT role_id FROM user "
                  "WHERE username = '"+ user_name +"' ");   //AND password = '"+ passwd +"'

    if(query.exec())
    {
        while(query.next() ){
        role_id = query.value(0).toInt();
        qDebug()<<"role_id is : "<<role_id;}
    }
    else {
        qDebug()<<"error in role func"<<query.lastError().text();
    }


    if(role_id == 1)
    {
        qDebug()<<"emiting signal";
        emit admin_logged_in("admin logged in");
//        employee_info* employee = new employee_info();
//        connect(this,SIGNAL(admin_logged_in(QString)),employee,SLOT(activate_user_functions(QString)));

        //connect(this,SIGNAL(user_logged_in(const QString)),employee,SLOT(check_user_role(const QString)));
    }
//    else
//    {
//        return;
// //            employee_info::ui->add_user_pushButton->setEnabled(false);
// //            ui->remove_user_pushButton_2->setEnabled(false);
// //            ui->savechanges_user_pushButton->setEnabled(false);

//    }
}



void Widget::on_login_pushButton_clicked()
{

   // employee_info role;
    QString user_name, passwd;
    user_name =ui->username_lineEdit->text();
    passwd = ui->password_lineEdit->text();


    //qDebug()<<"executing passwd"<<passwd;
//    user_name = ui->username_lineEdit->text();
//    QByteArray pswrdstring = ui->password_lineEdit->text().toLatin1();
//    QCryptographicHash hasher(QCryptographicHash::Sha1);
//    hasher.addData(pswrdstring);
//    QByteArray encrypted_psswrd = hasher.result();

//    qDebug()<<"encryoooo"<<encrypted_psswrd;

    if(!db_connection_open())
    {
        ui->messagelabel->setText(" Failed to open the Database! ");
        qDebug()<<"Error : Database is not Reachable";
    }

   db_connection_open();

   //emit user_logged_in("user_name");
   //QObject::connect(ui->login_pushButton,SIGNAL(clicked(bool)),this,SLOT(employee_info::check_user_role(user_name)));

   QSqlQuery query;

   query.prepare("SELECT username, password FROM user "
                 "WHERE username = '"+ user_name +"' AND password = '"+ passwd +"' ");

   if(query.exec())
   {
      // qDebug()<<"executing";
       int count = 0;
       while(query.next()){
           count++;
           qDebug()<<count;
       }
       if(count == 1){
             qDebug()<<user_name <<" is logged in";
             ui->messagelabel->setText(" User Logged in.. ");

             if(ui->remember_username_passwd_checkBox->isChecked() == true) {
                 //login_file_write();
                 login_xml_write();
             }

             this->hide();

             //check_user_role(user_name);

             /*Closing Connection with Database & Entering Employee Info Window */
           //  db_connection_close();


//             employee_info empinfo;
//             empinfo.setModal(true);
//             empinfo.exec();


       }else {
           QMessageBox::warning(this, "Invalid Login" , "Check Username & Password & try again!");
           ui->messagelabel->setText("Login Failed : Invalid Username & Password");
           qDebug()<<"Login Failed : Invalid Username & Password";
           db_connection_close();
       }
   }
   else {
       ui->messagelabel->setText("Error : Wrong SQLQuery");
       qDebug()<<"Error : Wrong SQLQuery";
   }
}

/*
   query.prepare("SELECT name, username, password FROM user "
                        "WHERE username = :username AND password = :password ");
       query.bindValue(":username",user_name);

       query.bindValue(":password",passwd);
       query.exec();

           if(query.exec())  {
               qDebug()<<"executing";
               if(query.size()>0) {
                   QString name = query.value(0).toString();
                   qDebug()<<name;
                   qDebug()<<name <<" is logged in";
               }
               else {
                    qDebug()<<"Login Failed : Invalid Username & Password";
               }
           }
}
*/

void Widget::on_cancel_pushButton_clicked()
{
   qApp->exit();

   qDebug()<<"User didn't Login";
}

void Widget::on_reg_pushButton_clicked()
{
    // Registration_Window * reg = new Registration_Window(this);
    //db_connection_close();
    //this->hide();

    this->hide();
    Registration_Window reg;
    reg.setModal(true);
    reg.exec();


}

void Widget::remembered_username_password()
{
    QString usrnm = ui->username_lineEdit->text();
    QString passwd = ui->password_lineEdit->text();

    ui->username_lineEdit->setText(usrnm);
    ui->password_lineEdit->setText(passwd);
}

void Widget::on_remember_username_passwd_checkBox_stateChanged(int arg1)
{
//    QString usrnm = ui->username_lineEdit->text();
//    QString passwd = ui->password_lineEdit->text();

//    ui->username_lineEdit->setText(usrnm);
//    ui->password_lineEdit->setText(passwd);


}



/* file read & write for "remember username & login" */

void Widget::login_file_read()
{
//    QString line1;
//    QString line2;
    QString filecontent;

//    QString filename = QFileDialog::getOpenFileName(this,"Open File");
//    if(filename.isEmpty()) {return; }

    QFile file("/home/kodiak/Desktop/Krishna/documents/login.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text )) {return;}

     QTextStream in(&file);
     QString line1 = in.readLine();
     QString line2 = in.readLine();

     for(int i = 0; i<2; i++)
     {
         if(i==0){ui->username_lineEdit->setText(line1); }
         else {ui->password_lineEdit->setText(line2); }
     }

//     while(!line.isEmpty()) {
//         filecontent.append(line);
//         ui->username_lineEdit->setText(filecontent);
//         line = in.readLine(); //reading next line
//         ui->password_lineEdit->setText(filecontent);
//     }

     file.close();

}



void Widget::login_file_write()
{
//    QString filename = QFileDialog::getSaveFileName(this,"Save As");
//    if(filename.isEmpty()) { return; }
//    QFile file(filename);

    QFile file("/home/kodiak/Desktop/Krishna/documents/login.txt");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text )) { return; }

    QTextStream out(&file);
    out << ui->username_lineEdit->text()<< "\n";
    out << ui->password_lineEdit->text()<< "\n";

    file.close();
}

void Widget::on_remember_username_passwd_checkBox_clicked()
{

   // QCheckBox *checkbox = ui->remember_username_passwd_checkBox
    setting.setValue("checkstate",ui->remember_username_passwd_checkBox->isChecked());


}


void Widget::login_xml_read()
{
    QDomDocument document;

    QFile file("/home/kodiak/Desktop/Krishna/documents/MyLoginFile.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
        return ;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document ";

        }
        file.close();
    }

     QDomElement rootElement = document.firstChildElement();


     QDomElement user = rootElement.firstChildElement();

     QString username =  encryptdecrypt(user.attribute("Username"));
     QString password =  encryptdecrypt(user.attribute("Password"));

     ui->username_lineEdit->setText(username);
     ui->password_lineEdit->setText(password);

     //ui->username_lineEdit->setText(user.attribute("Username"));
    // ui->password_lineEdit->setText(user.attribute("Password"));





//    QDomDocument document;

//    QFile file("/home/kodiak/Desktop/Krishna/documents/MyLoginFile.xml");
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug()<<"Failed to open file";
//        return ;
//    }
//    else
//    {
//        if(!document.setContent(&file))
//        {
//            qDebug()<<"Failed to load document ";
//            return ;
//        }
//        file.close();
//    }
//   // get the root element
//    QDomElement root = document.firstChildElement();

//    login_xml_list_elements(root,"Book","Name");
//    qDebug()<<"\r\n More Advanced\r\n";

//    //get the chapters
//    QDomNodeList books = root.elementsByTagName("Book");
//    for(int i =0; i <books.count(); i++)
//    {
//        QDomNode booknode = books.at(i);
//        //convert to an element

//        if(booknode.isElement())
//        {
//            QDomElement book = booknode.toElement();
//            qDebug()<<"Chapters in"<<book.attribute("Name");
//            login_xml_list_elements(book,"Chapter","Name");
//        }
     //    }
}

void Widget::login_xml_write()
{
    QDomDocument document;
    //make the root element
    QDomElement root = document.createElement("Accounts");

    //add it to the document
    document.appendChild(root);

    //add some element
   // for(int i =0; i<10; i++){
        QDomElement account_details = document.createElement("Users");
        QString username = encryptdecrypt(ui->username_lineEdit->text());
        QString password = encryptdecrypt( ui->password_lineEdit->text());
        account_details.setAttribute("Username",username);
        account_details.setAttribute("Password",password);
        //account_details.setAttribute("Username",ui->username_lineEdit->text());
        //account_details.setAttribute("Password", ui->password_lineEdit->text());
        root.appendChild(account_details);
    //}

    QFile file("/home/kodiak/Desktop/Krishna/documents/MyLoginFile.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice ::Text))
    {
        qDebug()<<"Failed to open the file";
        return ;
    }
    else
    {
        QTextStream stream(&file);
        stream<<document.toString();
        file.close();
    }
}

void Widget::login_xml_list_elements(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);
    qDebug()<<"Total Items ="<<items.count();

    for(int i =0; i<items.count(); i++)
    {
        QDomNode itemnode = items.at(i);

        //convert to element
        if(itemnode.isElement())
        {
            QDomElement itemelement= itemnode.toElement();
            qDebug()<<itemelement.attribute(attribute);

        }
    }
}

QString Widget::encryptdecrypt(QString str)
{
    char key = 'T';                  //char key[3] = {'A', 'T' ,'O'};
    QString output = str;
    int len = str.size();

    for(int i =0; i<len; i++)
    {
        output[i] = str[i].toLatin1() ^ key;    // ^key[i % (sizeof(key)/sizeof(char))]
    }
    return output;
}
