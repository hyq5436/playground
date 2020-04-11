#include "ShareDesktopToolbar.h"
#include "ui_ShareDesktopToolbar.h"
#include <QPropertyAnimation>

ShareDesktopToolbar::ShareDesktopToolbar(QWidget *parent)
    : QFrame(parent)
{
    ui = new Ui::ShareDesktopToolbar();
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(QString("ShareDesktopToolbar { background-color: #37383e;}"));

    mpFadeIn = new QPropertyAnimation(this, "windowOpacity");
    mpFadeIn->setDuration(500);
    mpFadeIn->setStartValue(0.0);
    mpFadeIn->setEndValue(1.0);

    mpFadeOut = new QPropertyAnimation(this, "windowOpacity");
    mpFadeOut->setDuration(500);
    mpFadeOut->setStartValue(1.0);
    mpFadeOut->setEndValue(0.0);

    connect(mpFadeOut, SIGNAL(finished()), this, SLOT(onFadeOutFinished()));

}

ShareDesktopToolbar::~ShareDesktopToolbar()
{
    delete ui;
}

void ShareDesktopToolbar::showEvent(QShowEvent* event)
{
    mpFadeIn->start();
}

void ShareDesktopToolbar::hideEvent(QHideEvent* event)
{
    mpFadeOut->start();
}

void ShareDesktopToolbar::hideToolbar()
{
    mpFadeOut->start();
}
void ShareDesktopToolbar::onFadeOutFinished()
{
    hide();
}
