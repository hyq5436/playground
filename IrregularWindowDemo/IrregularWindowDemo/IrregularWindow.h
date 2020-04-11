#pragma once

#include <QFrame>
namespace Ui { class IrregularWindow; };

class IrregularWindow : public QFrame
{
    Q_OBJECT

public:
    IrregularWindow(QWidget *parent = Q_NULLPTR);
    ~IrregularWindow();

private:
    Ui::IrregularWindow *ui;
};
