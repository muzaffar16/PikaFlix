// movies.cpp

#include "popupmoviedetails.h"
#include "movies.h"
#include "ui_movies.h"
#include "home.h"
#include <QString>
#include <QPixmap>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QSet>
#include <QMessageBox>

QString type;
QString category;

movies::movies(QString t, QString c, QWidget *parent) : QDialog(parent), ui(new Ui_movies), P(nullptr)
{
    ui->setupUi(this);

    QString buttonStyle = "QPushButton {"
                          "    background-color: #2e2f30;"
                          "    border: 2px solid rgb(49, 45, 46);"
                          "    border-radius: 30px;"
                          "    color: white;"
                          "    font-weight: bold;"
                          "    font-size: 11pt;"
                          "}"
                          "QPushButton:hover {"
                          "    border: 2px solid rgb(255, 87, 87);"
                          "}";

    ui->p_1->setStyleSheet(buttonStyle);
    ui->p_2->setStyleSheet(buttonStyle);
    ui->p_3->setStyleSheet(buttonStyle);
    ui->p_4->setStyleSheet(buttonStyle);
    ui->p_5->setStyleSheet(buttonStyle);
    ui->p_6->setStyleSheet(buttonStyle);
    ui->p_7->setStyleSheet(buttonStyle);
    ui->p_8->setStyleSheet(buttonStyle);
    ui->p_9->setStyleSheet(buttonStyle);
    ui->p_10->setStyleSheet(buttonStyle);

    type = t;
    category = c;

    if (c == " ")
    {
        displayMovies();
    }
    else
    {
        displayMoviesByCategory();
    }

    ui->previous->hide();
    ui->next->show();
}

movies::~movies()
{
    delete ui;
}

int movieIndex = 0;
QSet<QString> uniquePaths;
Movie *record = new Movie[10];
int recordIndex = 0;

void movies::displayMovies()
{
    for (int i = 0; i < 10; i++)
    {
        record[i] = Movie();
    }
    recordIndex = 0;
    for (int i = 1; i <= 10; ++i)
    {
        QString labelName = "m_" + QString::number(i);
        QLabel *currentLabel = findChild<QLabel *>(labelName);
        QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(i));

        if (currentLabel && currentButton)
        {
            currentLabel->clear();
            currentButton->hide();
        }
        else
        {
            qCritical() << "Label or Button not found: " << labelName;
        }
    }

    QFile file("moviesDetail.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open txt File!";
        return;
    }

    QTextStream stream(&file);
    QString n, p, t, c;

    for (int i = 0; i < movieIndex; ++i)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();
    }

    int labelIndex = 1;
    while (!stream.atEnd() && labelIndex <= 10)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();

        if (t == type)
        {
            Movie m(n, p, t, c);
            if (recordIndex < 10)
            {
                record[recordIndex] = m;
                recordIndex++;
            }
            else
            {
                recordIndex = 0;
            }

            QString labelName = "m_" + QString::number(labelIndex);
            QLabel *currentLabel = findChild<QLabel *>(labelName);
            QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(labelIndex));

            if (currentLabel && currentButton)
            {
                QPixmap pix(m.getMoviePath());

                if (!pix.isNull())
                {
                    if (!uniquePaths.contains(m.getMoviePath()))
                    {
                        currentLabel->setPixmap(pix.scaled(100, 150, Qt::KeepAspectRatio));
                        uniquePaths.insert(m.getMoviePath());

                        // Update the visibility of the button based on the movie_name
                        if (!m.getMovieName().isEmpty())
                        {
                            currentButton->show();
                        }
                        else
                        {
                            currentButton->hide();
                        }
                    }
                    else
                    {
                       // QPixmap pix1("D:/3rd Sem/DS Theory/pikaFlix/not found.png");
                       // currentLabel->setPixmap(pix1.scaled(100, 150, Qt::KeepAspectRatio));
                    }
                }
                else
                {
                    qCritical() << "Failed to load movie picture for label " << labelName;
                }

                labelIndex++;
            }
            else
            {
                qCritical() << "Label or Button not found: " << labelName;
                break;
            }
        }
    }

    file.close();

    movieIndex += labelIndex - 1;

    if (stream.atEnd())
    {
        ui->next->hide();
    }
    else
    {
        ui->next->show();
    }
}

void movies::displayMoviesByCategory()
{
    for (int i = 0; i < 10; i++)
    {
        record[i] = Movie();
    }
    recordIndex = 0;
    for (int i = 1; i <= 10; ++i)
    {
        QString labelName = "m_" + QString::number(i);
        QLabel *currentLabel = findChild<QLabel *>(labelName);
        QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(i));

        if (currentLabel && currentButton)
        {
            currentLabel->clear();
            currentButton->hide();
        }
        else
        {
            qCritical() << "Label or Button not found: " << labelName;
        }
    }

    QFile file("moviesDetail.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open txt File!";
        return;
    }

    QTextStream stream(&file);
    QString n, p, t, c;

    for (int i = 0; i < movieIndex; ++i)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();
    }

    int labelIndex = 1;
    while (!stream.atEnd() && labelIndex <= 10)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();

        if (c == category)
        {
            Movie m(n, p, t, c);
            if (recordIndex < 10)
            {
                record[recordIndex] = m;
                recordIndex++;
            }
            else
            {
                recordIndex = 0;
            }

            QString labelName = "m_" + QString::number(labelIndex);
            QLabel *currentLabel = findChild<QLabel *>(labelName);
            QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(labelIndex));

            if (currentLabel && currentButton)
            {
                QPixmap pix(m.getMoviePath());

                if (!pix.isNull())
                {
                    if (!uniquePaths.contains(m.getMoviePath()))
                    {
                        currentLabel->setPixmap(pix.scaled(100, 150, Qt::KeepAspectRatio));
                        uniquePaths.insert(m.getMoviePath());

                        // Update the visibility of the button based on the movie_name
                        if (!m.getMovieName().isEmpty())
                        {
                            currentButton->show();
                        }
                        else
                        {
                            currentButton->hide();
                        }
                    }
                    else
                    {
                        labelIndex--;
                        recordIndex--;
                    }
                }
                else
                {
                    qCritical() << "Failed to load movie picture for label " << labelName;
                }

                labelIndex++;
            }
            else
            {
                qCritical() << "Label or Button not found: " << labelName;
                break;
            }
        }
    }

    file.close();

    movieIndex += labelIndex - 1;

    if (stream.atEnd())
    {
        ui->next->hide();
    }
    else
    {
        ui->next->show();
    }
}
void movies::displayPrevMovies()
{
    recordIndex = 0;
    int moviesPerPage = 10;

    int newStartIndex = movieIndex - moviesPerPage;
    if (newStartIndex < 0)
    {
        newStartIndex = 0;
    }

    movieIndex = newStartIndex;

    QFile file("moviesDetail.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open txt File!";
        return;
    }

    QTextStream stream(&file);
    QString n, p, t, c;

    for (int i = 0; i < movieIndex; ++i)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();
    }

    int labelIndex = 1;
    while (!stream.atEnd() && labelIndex <= 10)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();

        if (t == type)
        {
            Movie m(n, p, t, c);
            if (recordIndex < 10)
            {
                record[recordIndex] = m;
                recordIndex++;
            }
            else
            {
                recordIndex = 0;
                // qCritical() << "record array index out of bounds!";
            }

            QString labelName = "m_" + QString::number(labelIndex);
            QLabel *currentLabel = findChild<QLabel *>(labelName);
            QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(labelIndex));

            if (currentLabel)
            {
                QPixmap pix(m.getMoviePath());

                if (!pix.isNull())
                {
                    if (!uniquePaths.contains(m.getMoviePath()))
                    {
                        currentLabel->setPixmap(pix.scaled(100, 150, Qt::KeepAspectRatio));
                        uniquePaths.insert(m.getMoviePath());
                        // Update the visibility of the button based on the movie_name
                        if (!m.getMovieName().isEmpty())
                        {
                            currentButton->show();
                        }
                        else
                        {
                            currentButton->hide();
                        }
                    }
                }
                else
                {
                    qCritical() << "Failed to load movie picture for label " << labelName;
                }

                labelIndex++;
            }
            else
            {
                qCritical() << "Label not found: " << labelName;
                break;
            }
        }
    }

    file.close();

    ui->next->show();
    if (movieIndex == 0)
    {
        ui->previous->hide();
    }
    uniquePaths.clear();
}

void movies::displayPrevMoviesByCategory()
{
    recordIndex = 0;
    int moviesPerPage = 10;

    int newStartIndex = movieIndex - moviesPerPage;
    if (newStartIndex < 0)
    {
        newStartIndex = 0;
    }

    movieIndex = newStartIndex;

    QFile file("moviesDetail.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open txt File!";
        return;
    }

    QTextStream stream(&file);
    QString n, p, t, c;

    for (int i = 0; i < movieIndex; ++i)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();
    }

    int labelIndex = 1;
    while (!stream.atEnd() && labelIndex <= 10)
    {
        n = stream.readLine();
        p = stream.readLine();
        t = stream.readLine();
        c = stream.readLine();

        if (c == category)
        {
            Movie m(n, p, t, c);
            if (recordIndex < 10)
            {
                record[recordIndex] = m;
                recordIndex++;
            }
            else
            {
                recordIndex = 0;
                // qCritical() << "record array index out of bounds!";
            }

            QString labelName = "m_" + QString::number(labelIndex);
            QLabel *currentLabel = findChild<QLabel *>(labelName);
            QPushButton *currentButton = findChild<QPushButton *>("p_" + QString::number(labelIndex));

            if (currentLabel)
            {
                QPixmap pix(m.getMoviePath());

                if (!pix.isNull())
                {
                    if (!uniquePaths.contains(m.getMoviePath()))
                    {
                        currentLabel->setPixmap(pix.scaled(100, 150, Qt::KeepAspectRatio));
                        uniquePaths.insert(m.getMoviePath());
                        // Update the visibility of the button based on the movie_name
                        if (!m.getMovieName().isEmpty())
                        {
                            currentButton->show();
                        }
                        else
                        {
                            currentButton->hide();
                        }
                    }
                }
                else
                {
                    qCritical() << "Failed to load movie picture for label " << labelName;
                }

                labelIndex++;
            }
            else
            {
                qCritical() << "Label not found: " << labelName;
                break;
            }
        }
    }

    file.close();

    ui->next->show();
    if (movieIndex == 0)
    {
        ui->previous->hide();
    }
    uniquePaths.clear();
}

void movies::on_home_clicked()
{
    home *h = new home();
    hide();
    h->show();
    movieIndex = 0;
    uniquePaths.clear();
    recordIndex = 0;
}

void movies::on_next_clicked()
{
    if (type != " ")
    {
        displayMovies();
    }
    else
    {
        displayMoviesByCategory();
    }

    ui->previous->show();
    recordIndex = 0;
}

void movies::on_previous_clicked()
{
    movieIndex -= 10;

    if (movieIndex < 0)
    {
        movieIndex = 0;
    }

    uniquePaths.clear();
    if (type != " ")
    {
        displayPrevMovies();
    }
    else
    {
        displayPrevMoviesByCategory();
    }
    recordIndex = 0;
}

void movies::on_p_clicked(int buttonIndex)
{
    popupMovieDetails *p = new popupMovieDetails(record[buttonIndex - 1].getMovieName(), record[buttonIndex - 1].getMoviePath(), record[buttonIndex - 1].getMovieType(), record[buttonIndex - 1].getMovieCategory());
    if (record[buttonIndex - 1].getMovieName() != " ")
    {
        p->show();
    }
}

void movies::on_p_1_clicked()
{
    on_p_clicked(1);
}

void movies::on_p_2_clicked()
{
    on_p_clicked(2);
}

void movies::on_p_3_clicked()
{
    on_p_clicked(3);
}

void movies::on_p_4_clicked()
{
    on_p_clicked(4);
}

void movies::on_p_5_clicked()
{
    on_p_clicked(5);
}

void movies::on_p_6_clicked()
{
    on_p_clicked(6);
}

void movies::on_p_7_clicked()
{
    on_p_clicked(7);
}

void movies::on_p_8_clicked()
{
    on_p_clicked(8);
}

void movies::on_p_9_clicked()
{
    on_p_clicked(9);
}

void movies::on_p_10_clicked()
{
    on_p_clicked(10);
}
