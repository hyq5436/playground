#include "widget.h"
#include "ui_widget.h"

#include <QLabel>
#include <QMovie>

Widget::Widget(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (0, 0 , 0, 255));
    //bgpal.setColor (QPalette::Background, Qt::transparent);
    //bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255));
    setPalette (bgpal);
    connect(ui->load, &QPushButton::clicked, this, &Widget::slot_load);
    connect(ui->stop, &QPushButton::clicked, this, &Widget::slot_stop);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slot_load()
{
    QLabel* loading = new QLabel(this);
    loading->setWindowOpacity(1);
    loading->setObjectName("loading");
    loading->setWindowFlag(Qt::FramelessWindowHint);
    loading->setAttribute(Qt::WA_TranslucentBackground);
    loading->setFixedSize(100, 100);
    QMovie* movie = new QMovie("D:/Source/Repos/qt_playground/GifLoadingDemo/loading.gif");
    movie->setParent(loading);
    loading->setMovie(movie);
    loading->show();
    movie->start();
}

void Widget::slot_stop()
{

    QLabel* loading = findChild<QLabel*>("loading");
    loading->movie()->stop();
    loading->close();
    loading->deleteLater();
}
