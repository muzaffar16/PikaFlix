#ifndef USER_H
#define USER_H

#include "user.h"
#include <QApplication>
#include<QString>
#include <QMessageBox>
#include "QFile"

class user{

    QString Fname;
    QString Lname;
    QString ID;
    QString Pass;

public:
    user(){
        Fname=" ";
        Lname=" ";
        ID=" ";
        Pass=" ";
    }
    user(QString f,QString l, QString id, QString p){
        Fname = f;
        Lname = l;
        ID =id;
        Pass =p;
    }

    QString get_Fname(){
        return Fname;
    }
    QString get_Lname(){
        return Lname;
    }
    QString get_ID(){
        return ID;
    }
    QString get_Pass(){
        return Pass;
    }

};

#endif // USER_H
