// movies.h

#ifndef MOVIES_H
#define MOVIES_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QTextStream>

class Movie {
private:
    QString movieName;
    QString path;
    QString type;
    QString category;

public:
    Movie() {
        movieName=" ";
    }
    Movie(QString n, QString p, QString t, QString c) : movieName(n), path(p), type(t), category(c) {}

    QString getMovieName() { return movieName; }
    QString getMoviePath() { return path; }
    QString getMovieType() { return type; }
    QString getMovieCategory() { return category; }
};

class Ui_movies;

class movies : public QDialog
{
    Q_OBJECT

public:
    explicit movies(QString t,QString c, QWidget *parent = nullptr);
    ~movies();

private slots:
    void on_home_clicked();
    void displayMovies();
    void displayPrevMovies();
    void displayMoviesByCategory();
    void displayPrevMoviesByCategory();
    void on_next_clicked();
    void on_previous_clicked();

    void on_p_1_clicked();
    void on_p_2_clicked();
    void on_p_3_clicked();
    void on_p_4_clicked();
    void on_p_5_clicked();
    void on_p_6_clicked();
    void on_p_7_clicked();
    void on_p_8_clicked();
    void on_p_9_clicked();
    void on_p_10_clicked();
    void on_p_clicked(int buttonIndex);

private:
    Ui_movies *ui;

    class Node
    {
    public:
        Movie m;
        Node *next;
        Node(Movie n)
        {
            m = n;
            next = nullptr;
        }
    };

    class LinkedList
    {
    public:
        int cnt;
        Node *head;
        Node *tail;

        LinkedList()
        {
            head = nullptr;
            tail = nullptr;
            cnt = 0;
        }

        void insert(Movie m)
        {
            Node *temp = new Node(m);
            if (head == nullptr)
            {
                cnt++;
                head = temp;
                tail = temp;
                return;
            }
            temp->next = head;
            head = temp;
            cnt++;
        }

        void deleteList()
        {
            Node *temp = head;
            Node *nextNode = nullptr;

            while (temp != nullptr)
            {
                nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }

            head = nullptr;
            tail = nullptr;
            cnt = 0;
        }
    };

    LinkedList l;
    Node *P;

};

#endif // MOVIES_H
