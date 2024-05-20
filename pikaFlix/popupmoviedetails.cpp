#include "popupmoviedetails.h"
#include "ui_popupmoviedetails.h"
#include <QPixmap>

QString n,p,t,c;

popupMovieDetails::popupMovieDetails(QString name,QString path, QString type,QString Category, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popupMovieDetails)
{
    ui->setupUi(this);

    n=name;
    p=path;
    t=type;
    c=Category;
     QPixmap pix("D:/3rd Sem/DS Theory/pikaFlix/9.jpg");
    ui->label->setPixmap(pix);

    display();
}
void popupMovieDetails::display()
{
    if (ui->textEdit && ui->textEdit_2 && ui->textEdit_3) {
         // Set styles for textEdit
         ui->textEdit->setStyleSheet("QTextEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold;font-size: 11pt; }");
         ui->textEdit->setReadOnly(true);

         // Set styles for textEdit_2
         ui->textEdit_2->setStyleSheet("QTextEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold; font-size: 14pt;}");
         ui->textEdit_2->setReadOnly(true);

         // Set styles for textEdit_3
         ui->textEdit_3->setStyleSheet("QTextEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold;font-size: 14pt; }");
         ui->textEdit_3->setReadOnly(true);

         ui->textEdit->setText(n);
         ui->textEdit_2->setText(t);
         ui->textEdit_3->setText(c);
    }
    QPixmap pix1(p);
    ui->pathDisplay->setPixmap(pix1.scaled(500, 250, Qt::KeepAspectRatio));
}


popupMovieDetails::~popupMovieDetails()
{
    delete ui;
}
