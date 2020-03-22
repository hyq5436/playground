#pragma once

#include <QtWidgets/QWidget>
#include "ui_LoadingWidget.h"

class LoadingWidget : public QWidget
{
    Q_OBJECT

public:
    LoadingWidget(QWidget *parent = Q_NULLPTR);

    void setLoadingText(const QString& text);

public slots:
    void showWindow(const QString text = "");
    void closeWindow();

private:
    Ui::LoadingWidgetClass ui;

    QMovie* m_pLoadingMovie;

};
