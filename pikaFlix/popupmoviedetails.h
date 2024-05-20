#ifndef POPUPMOVIEDETAILS_H
#define POPUPMOVIEDETAILS_H

#include <QDialog>
#include "movies.h"

namespace Ui {
class popupMovieDetails;
}

class popupMovieDetails : public QDialog
{
    Q_OBJECT

public:
    explicit popupMovieDetails(QString name,QString path, QString type,QString Category,QWidget *parent = nullptr);
    ~popupMovieDetails();

private:
    Ui::popupMovieDetails *ui;
private slots:
    void display();
};

#endif // POPUPMOVIEDETAILS_H
