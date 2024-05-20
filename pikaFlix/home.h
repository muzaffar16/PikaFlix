// home.h

#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <QMainWindow>
#include <QPixmap>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include "movies.h"
#include "popupmoviedetails.h"
#include "QVector"

class Node {
public:
    QString data;
    Node* next;

    Node(const QString& d) {
        data = d;
        next = nullptr;
    }
};

class CircularLinkedList {
    Node* head;
    Node* current;

public:
    CircularLinkedList() {
        head = nullptr;
        current = nullptr;
    }

    ~CircularLinkedList() {
        Node* current = head;
        if (current) {
            do {
                Node* next = current->next;
                delete current;
                current = next;
            } while (current != head);
        }
    }

    void append(const QString& value) {
        Node* newNode = new Node(value);

        if (!head) {
            head = newNode;
            current = head;
            head->next = head;
        } else {
            newNode->next = head->next;
            head->next = newNode;
        }
    }

    QString getCurrentValue() {
        if (current) {
            return current->data;
        }
        return QString();
    }

    void moveToNext() {
        if (current) {
            current = current->next;
        }
    }
};

namespace Ui {
class home;
}

class movie {
private:
    QString movieName;
    QString path;
    QString type;
    QString category;

public:
    movie() : movieName(" "), path(" "), type(" "), category(" ") {}

    movie(QString n, QString p, QString t, QString c) : movieName(n), path(p), type(t), category(c) {}

    QString getMovieName() const { return movieName; }
    QString getMoviePath() const { return path; }
    QString getMovieType() const { return type; }
    QString getMovieCategory() const { return category; }
};

class hashTable {
private:
    QVector<movie*> m;
    int cnt;
    int tableSize;

public:
    hashTable() : tableSize(1000), cnt(0) {
        m.resize(1000, nullptr);
        buildHashTable();
    }

    ~hashTable() {
        qDeleteAll(m);
    }

    int hashIt(const QString& n) {
        QChar firstChar = n.toUpper()[0];
        int i = firstChar.toLatin1();
        return i % tableSize;
    }

    void insert(const movie& mov) {
        int index = hashIt(mov.getMovieName());

        while (m[index] != nullptr) {
            index = (index + 1) % tableSize;
        }

        m[index] = new movie(mov);
        cnt++;
    }

    void buildHashTable() {
        QFile file("moviesDetail.txt");

        if (!file.open(QIODevice::ReadOnly)) {
            qCritical() << "Cannot open txt File!";
            return;
        }

        QTextStream stream(&file);
        QString n, p, t, c;

        while (!stream.atEnd()) {
            n = stream.readLine();
            p = stream.readLine();
            t = stream.readLine();
            c = stream.readLine();
            movie mov(n, p, t, c);
            if(n!=" ")
            insert(mov);
        }

        file.close();
    }

    movie* search(const QString& name) {
        int index = hashIt(name);

        while (m[index] != nullptr) {
            if (m[index]->getMovieName() == name) {
                return m[index];
            }

            index = (index + 1) % tableSize;
        }

        return nullptr;
    }
};

class home : public QDialog
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_moviesPosterLabel_linkActivated(const QString &link);
    void changePicture();

    void on_hollywood_clicked();
    void on_bollywood_clicked();
    void on_trending_clicked();
    void on_series_clicked();
    void on_latest_clicked();
    void on_upcoming_clicked();
    void on_search_clicked();

private:
    Ui::home *ui;
    QTimer *slideshowTimer;
    hashTable h;
    CircularLinkedList picturePaths;
};

#endif // HOME_H
