#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QFile>
#include<QDir>
#include<QTextStream>
#include "movies.h"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_back_clicked();
    bool isUnique(QString );
    void on_addMovie_clicked();

    void on_removeMovie_clicked();

    void on_newMovie_clicked();

    void on_removeButton_clicked();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
