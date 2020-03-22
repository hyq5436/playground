#include "LoadingWidget.h"

#include <QGraphicsDropShadowEffect>
#include <QMovie>

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_AlwaysStackOnTop);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    //实例阴影shadow
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(4);
    shadow->setOffset(0, 2);
    shadow->setColor(QColor("#999999"));
    ui.content->setGraphicsEffect(shadow);
    ui.content->setStyleSheet("QFrame{ background-color: white; border-radius: 8px; }");

    m_pLoadingMovie = new QMovie("Resources/pcloading.gif");
    ui.loadingMovieLabel->setMovie(m_pLoadingMovie);
    m_pLoadingMovie->start();

    ui.loadingContentLabel->setStyleSheet(QString("QLabel {font: 14x 'Microsoft Yahei'; }"));
    ui.loadingContentLabel->setText(QString("creating living..."));
}


void LoadingWidget::setLoadingText(const QString& text) {
    ui.loadingContentLabel->setText(text);
}

void LoadingWidget::showWindow(const QString text) {
    if (!text.isEmpty()) {
        setLoadingText(text);
    }

    m_pLoadingMovie->start();
    this->show();
}

void LoadingWidget::closeWindow() {
    m_pLoadingMovie->stop();
    this->close();
}
