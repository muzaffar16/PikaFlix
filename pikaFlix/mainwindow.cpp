#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QMainWindow>
#include <QPixmap>
#include "user.h"
#include "home.h"
#include "admin.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("D:/3rd Sem/DS Theory/pikaFlix/8.png");
    ui->SignUpPage->setPixmap(pix);
    QPixmap pix1("D:/3rd Sem/DS Theory/pikaFlix/1.png");
    ui->loginAndSignupLabel->setPixmap(pix1);
    QPixmap pix2("D:/3rd Sem/DS Theory/pikaFlix/2.png");
    ui->LoginPage->setPixmap(pix2);

    ui->ID->setStyleSheet("QLineEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold;font-size: 11pt; }");
    ui->pass->setStyleSheet("QLineEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold;font-size: 11pt; }");
    ui->login->setStyleSheet("QPushButton { background-color: #ff5858; border: 2px solid rgb(255, 87, 87); border-radius: 20px; color: white;  font-weight: bold; font-size: 11pt; } QPushButton:hover{border: 2px solid rgb(255,255,255}");
    ui->gotoLoginPage->setStyleSheet("QPushButton { background-color:  #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px; color: white;  font-weight: bold; font-size: 11pt; } QPushButton:hover{border: 2px solid rgb(255, 87, 87)}");
    ui->gotoSignupPage->setStyleSheet("QPushButton { background-color:  #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px; color: white;  font-weight: bold; font-size: 11pt; } QPushButton:hover{border: 2px solid rgb(255, 87, 87)}");

    ui->ID->hide();
    ui->pass->hide();
    ui->login->hide();
    ui->firstname->hide();
    ui->LastName->hide();
    ui->ConfirmPass->hide();
    ui->SetId->hide();
    ui->SetPass->hide();
    ui->signup->hide();
    ui->LoginPage->hide();
    ui->SignUpPage->hide();
    ui->back->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    home *h;
    h = new home (this);
    QString id = ui->ID->text();

    // Set the echo mode to Password before reading the password
    ui->pass->setEchoMode(QLineEdit::Password);
    QString pass = ui->pass->text();

    if (id == "admin" && pass == "pass") {
        admin *a = new admin();
        hide();
        a->show();
        return;
    }

    if (verify(id, pass)) {
        // QMessageBox::information(this, "home", "login successfully");
        hide();
        h->show();
    } else {
        QMessageBox::information(this, "home", "Enter Valid ID and Password");
    }
}



void MainWindow::on_gotoLoginPage_clicked()
{
    ui->gotoLoginPage->hide();
    ui->gotoSignupPage->hide();
    ui->loginAndSignupLabel->hide();
     ui->LoginPage->show();
    ui->SignUpPage->hide();
    ui->ID->show();
    ui->login->show();
    ui->pass->show();
    ui->back->show();


}


void MainWindow::on_gotoSignupPage_clicked()
{
    ui->gotoLoginPage->hide();
    ui->loginAndSignupLabel->hide();
    ui->LoginPage->hide();
    ui->SignUpPage->show();
    ui->gotoSignupPage->hide();
    ui->firstname->show();
    ui->LastName->show();
    ui->ConfirmPass->show();
    ui->SetId->show();
    ui->SetPass->show();
    ui->signup->show();
    ui->back->show();
}
bool MainWindow::verify(QString id, QString pass) {
    QFile file("userPass.txt");
    if (!file.exists()) {
         file.close();  // Close the file if it doesn't exist
         return true;
    }

    if (!file.open(QIODevice::ReadOnly)) {
         qCritical() << "Cannot open txt File!";
         return false;
    }

    QTextStream stream(&file);
    while (!stream.atEnd()) {
         QString line = stream.readLine();
         QStringList parts = line.split("|",Qt::SkipEmptyParts);


         if (parts.size() >= 2) {
             QString storedId = parts.at(0).trimmed();
             QString storedPass = parts.at(1).trimmed();

             if (storedId == id && storedPass == pass) {
                 file.close();
                 return true;  // Both id and pass match, indicating not unique
             }
         }
    }

    file.close();
    return false;  // No matching id and pass found, indicating unique
}

 bool MainWindow::isUnique(QString id, QString pass){
    QFile File("userPass.txt");
    if(!File.exists())
    {
        return true;
    }
    if(!File.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open txt File!";
        return false;
    }

    QTextStream stream(&File);
    while(!stream.atEnd())
    {
        QString Line = stream.readLine();
        if(Line.section("|",0,0) == id)
        {
            return false;
        }
    }

    File.close();
    return true;
}
void MainWindow::on_signup_clicked()
{
    QString Fname = ui->firstname->text();
    QString Lname = ui->LastName->text();
    QString ID = ui->SetId->text();
    QString pass = ui->SetPass->text();
    QString cPass= ui->ConfirmPass->text();
    ui->SetPass->setEchoMode(QLineEdit::Password);
    ui->ConfirmPass->setEchoMode(QLineEdit::Password);

    if(pass !=cPass){
        QMessageBox::information(this, "home", "Enter Valid Password");
    }else if(!isUnique(ID,pass)){
        QMessageBox::information(this, "home", "ID Already Exisit");
    }else{
       // user *u=new user()
         user a(Fname,Lname,ID,pass);

        QFile File("userPass.txt");
         QFile File1("data.txt");
        if(!File.open((QIODevice::ReadWrite) | (QIODevice :: Append)))
        {
            QMessageBox :: warning(this,"New User(1)", "Cannot open txt File!");
            return;
        }

        QTextStream stream(&File);
        stream << a.get_ID() + "|";
        stream << a.get_Pass() + "\n";

        QTextStream stream1(&File1);
        if(!File1.open((QIODevice::ReadWrite) | (QIODevice :: Append)))
        {
            QMessageBox :: warning(this,"New User(1)", "Cannot open txt File!");
            return;
        }
        stream1<<a.get_ID() +"\n";
        stream1<<a.get_Fname()+"\n";
        stream1<<a.get_Lname()+"\n";
        stream1<<a.get_Pass()+"\n";

        File1.close();
        File.close();
    }


}


void MainWindow::on_back_clicked()
{
    ui->ID->hide();
    ui->pass->hide();
    ui->login->hide();
    ui->firstname->hide();
    ui->LastName->hide();
    ui->ConfirmPass->hide();
    ui->SetId->hide();
    ui->SetPass->hide();
    ui->signup->hide();
    ui->LoginPage->hide();
    ui->SignUpPage->hide();
    ui->back->hide();
    ui->gotoLoginPage->show();
    ui->gotoSignupPage->show();
    ui->loginAndSignupLabel->show();

}

