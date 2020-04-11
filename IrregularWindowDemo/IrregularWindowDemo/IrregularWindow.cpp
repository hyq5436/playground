#include "IrregularWindow.h"
#include "ui_IrregularWindow.h"

IrregularWindow::IrregularWindow(QWidget *parent)
    : QFrame(parent)
{
    ui = new Ui::IrregularWindow();
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->widget->setStyleSheet("background-color: red;");
    ui->stackedWidget->setStyleSheet("background-color: blue;");
    connect(ui->btnClose, &QPushButton::pressed, [this]() {
        this->close();
    });
}

IrregularWindow::~IrregularWindow()
{
}
