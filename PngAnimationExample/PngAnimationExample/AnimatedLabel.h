#pragma once

#include <QLabel>
#include "ui_AnimatedLabel.h"
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <QPixmap>


class AnimatedLabel : public QLabel
{
    Q_OBJECT

public:
    AnimatedLabel(const QString &image, const int imageCount,
                  QWidget *parent = Q_NULLPTR);
    ~AnimatedLabel();

private slots:
    void changeImage();

private:
    QList<QPixmap> pixmaps;
    int currentPixmap;
    QTimer timer;

  private:
    Ui::AnimatedLabel ui;
};
