#include "admin.h"
#include "ui_admin.h"
#include "movies.h"
#include "mainwindow.h"
#include "home.h"
#include <QPixmap>


admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    QPixmap pix("D:/3rd Sem/DS Theory/pikaFlix/4.png");
    ui->label->setPixmap(pix);
    QPixmap pix1("D:/3rd Sem/DS Theory/pikaFlix/5.png");
    QPixmap pix2("D:/3rd Sem/DS Theory/pikaFlix/6.png");
    ui->removeLabel->setPixmap(pix2);

//    ui->->setStyleSheet("QTextEdit { background-color: #2e2f30; border: 2px solid rgb(49, 45, 46); border-radius: 20px;color: white; font-weight: bold;font-size: 11pt; }");
    ui->add->setPixmap(pix1);

    ui->removeLabel->hide();
    ui->moviesForRemove->hide();
    ui->removeButton->hide();
    ui->name->hide();
    ui->category->hide();
    ui->type->hide();
    ui->newMovie->hide();
    ui->path->hide();
    ui->add->hide();


}

admin::~admin()
{
    delete ui;
}

void admin::on_back_clicked()
{
   // home *h=new home();
   // hide();
   // h->show();
    ui->addMovie->show();
    ui->removeMovie->show();
    ui->name->hide();
    ui->category->hide();
    ui->type->hide();
    ui->newMovie->hide();
    ui->path->hide();
    ui->add->hide();
    ui->label->show();
    ui->removeLabel->hide();
    ui->moviesForRemove->hide();
    ui->removeButton->hide();

}


void admin::on_addMovie_clicked()
{
    ui->removeLabel->hide();
    ui->moviesForRemove->hide();
    ui->removeButton->hide();
    ui->add->show();
    ui->label->hide();
    ui->addMovie->hide();
    ui->removeMovie->hide();
    ui->name->show();
    ui->category->show();
    ui->type->show();
    ui->newMovie->show();
    ui->path->show();
}


void admin::on_removeMovie_clicked()
{
     ui->addMovie->hide();
     ui->removeMovie->hide();
    ui->name->hide();
    ui->category->hide();
    ui->type->hide();
    ui->newMovie->hide();
    ui->path->hide();
    ui->add->hide();
    ui->label->hide();
    ui->removeLabel->show();
    ui->moviesForRemove->show();
    ui->removeButton->show();
}

bool admin ::isUnique(QString name){
    QFile file("moviesDetail.txt");
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

        QString n;
        QString p;
        QString t;
        QString c;
        stream>>n>>p>>t>>c;
            if (name==n) {
                file.close();
                return false;
            }
        }
    file.close();
        return true;
}
void admin::on_newMovie_clicked()
{
    QString name =ui->name->text();
    QString path =ui->path->text();
    QString type = ui->type->text();
    QString category=ui->category->text();
      QFile File("moviesDetail.txt");

    if(isUnique(name)){
          Movie *m=new Movie(name, path, type,category);
    if(!File.open((QIODevice::ReadWrite) | (QIODevice :: Append)))
    {
        QMessageBox :: warning(this,"New movie(1)", "Cannot open txt File!");
        return;
    }

    QTextStream stream(&File);
    stream<<m->getMovieName()+"\n";
    stream<<m->getMoviePath()+"\n";
    stream<<m->getMovieType()+"\n";
    stream<<m->getMovieCategory()+"\n";
     QMessageBox::information(this, "home", "Movie Added Successfully");
    }else{
     QMessageBox::information(this, "home", "Movie Already Added");
    }
    File.close();

}


void admin::on_removeButton_clicked()
{
    QString name = ui->moviesForRemove->text();
    QFile file("moviesDetail.txt");
    bool found = false;

    if (!file.exists()) {
     QMessageBox::information(this, "home", "File does not exist");
     return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
     qCritical() << "Cannot open txt File!";
     return;
    }

    QFile temp("temp.txt");
    if (!temp.open(QIODevice::WriteOnly)) {
     qCritical() << "Cannot open temp.txt for writing";
     file.close();
     return;
    }

    QTextStream t(&temp);
    QTextStream stream(&file);

    while (!stream.atEnd()) {
     QString n, p, te, c;
     stream >> n >> p >> te >> c;
     if (name == n) {
        found = true;
     } else {
        t << n + "\n" << p + "\n" << te + "\n" << c + "\n";
     }
    }

    file.close();
    temp.close();

    if (found) {
     // Replace the original file with the temp file
     if (!QFile::remove("moviesDetail.txt") || !QFile::rename("temp.txt", "moviesDetail.txt")) {
        qCritical() << "Error replacing the original file";
        QMessageBox::critical(this, "Error", "Failed to remove the movie");
     } else {
        QMessageBox::information(this, "home", "Movie Removed Successfully");
     }
    } else {
     QMessageBox::information(this, "home", "Movie not found");
    }
}


