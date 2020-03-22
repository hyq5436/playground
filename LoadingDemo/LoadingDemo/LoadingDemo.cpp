#include "LoadingDemo.h"
#include "LoadingWidget.h"

#include <QPushButton>
#include <QVBoxLayout>

LoadingDemo::LoadingDemo(QWidget* parent) : QWidget(parent) {
    ui.setupUi(this);

    QPushButton* pButton = new QPushButton(this);
    connect(pButton, &QPushButton::clicked, this,
            &LoadingDemo::showLoadingDialog);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(pButton);
    setLayout(layout);
}

void LoadingDemo::showLoadingDialog() {
    QVBoxLayout* layout = new QVBoxLayout();
    QWidget* pLoadingWidget = new LoadingWidget();
    layout->setMargin(4);
    layout->addWidget(pLoadingWidget);

    QWidget* pContainer = new QWidget();
    pContainer->setAttribute(Qt::WA_TranslucentBackground);
    pContainer->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    pContainer->setLayout(layout);
    pContainer->setFixedSize(400, 400);
    

    //pContainer->setWindowModality(Qt::ApplicationModal);
    pContainer->show();
}
