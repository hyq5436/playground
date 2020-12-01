#ifndef CHART3DWIDGET_H
#define CHART3DWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Chart3DWidget; }
QT_END_NAMESPACE

class Chart3DWidget : public QWidget
{
    Q_OBJECT

public:
    Chart3DWidget(QWidget *parent = nullptr);
    ~Chart3DWidget();

    void paintEvent(QPaintEvent*) override;
private:
    Ui::Chart3DWidget *ui;

};
#endif // CHART3DWIDGET_H
