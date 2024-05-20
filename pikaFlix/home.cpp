// home.cpp

#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent) :
    ui(new Ui::home),
    slideshowTimer(new QTimer(this)),
    h()
{
    ui->setupUi(this);

    QPixmap pix("D:/3rd Sem/DS Theory/pikaFlix/7.png");
    ui->label->setPixmap(pix);

    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/8Gxv8gSFCU0XGDykEGv7zR1n2ua.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/AnfXxsoLBS6JDpu65vHsEvEcWSA.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/e7Jvsry47JJQruuezjU2X1Z6J77.jpg");
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/g9aDZSqH5KmsHbMurhni5d2wq6q.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/hTP1DtLGFamjfu8WqjnuQdP1n4i.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/lCawCmTJhKT7c2ZOzLBTXDIR8JS.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/mBaXZ95R2OxueZhvQbcEWy2DqyO.jpg");
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/nHROk2C6bv8LqtvyYd0tCMURbxC.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/uwrQHMnXD2DA1rvaMZk4pavZ3CY.jpg" );
    picturePaths.append("C:/Users/Muzzafar/Desktop/pikaflix/homePage/movies poster/vBZ0qvaRxqEhZwl6LWmruJqWE8Z.jpg");

    connect(slideshowTimer, &QTimer::timeout, this, &home::changePicture);
    slideshowTimer->start(5000);
    changePicture();
}

home::~home() {
    slideshowTimer->stop();
    delete ui;
}

void home::changePicture() {
    QString currentImagePath = picturePaths.getCurrentValue();

    if (!currentImagePath.isEmpty()) {
        ui->moviesPosterLabel->setPixmap(QPixmap(currentImagePath));
        picturePaths.moveToNext();
    }
}

void home::on_hollywood_clicked() {
    movies *m = new movies("hollywood"," ");
    hide();
    m->show();
}

void home::on_bollywood_clicked() {
    movies *m = new movies("bollywood"," ");
    hide();
    m->show();
}

void home::on_trending_clicked() {
    movies *m=new movies(" ","trending");
    hide();
    m->show();
}

void home::on_series_clicked() {
    movies *m = new movies("series"," ");
    hide();
    m->show();
}

void home::on_latest_clicked() {
    movies *m=new movies(" ","latest");
    hide();
    m->show();
}

void home::on_upcoming_clicked() {
    movies *m=new movies(" ","upcoming");
    hide();
    m->show();
}

void home::on_search_clicked() {
    QString name = ui->movieName->text();
    movie* m = h.search(name);

    if (m != nullptr && m->getMovieName() != " ") {
        popupMovieDetails* p = new popupMovieDetails(m->getMovieName(), m->getMoviePath(), m->getMovieType(), m->getMovieCategory());
        p->show();
    } else {
        QMessageBox::information(this, "home", "Movie Not Found");
    }
}
