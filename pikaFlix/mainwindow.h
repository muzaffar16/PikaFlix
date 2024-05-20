#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QFile>
#include<QDir>
#include<QTextStream>
#include "user.h"
#include "home.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
 //   bool isUnique(QString , QString );

    ~MainWindow();

private slots:
    void on_login_clicked();

    void on_gotoLoginPage_clicked();

    void on_gotoSignupPage_clicked();
    bool isUnique(QString , QString  );
    bool verify(QString , QString  );
    void on_signup_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
