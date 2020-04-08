#pragma execution_character_set("utf-8")

#include "PushButtonWithMenuDemo.h"
#include <QMenu>

PushButtonWithMenuDemo::PushButtonWithMenuDemo(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setStyleSheet("background-color: #37383e;");
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:5px;border-radius:3px;color:%1;background:%2;%3}")
        .arg(QString("#F7F7F7"))
        .arg(QString("#30BA9A"))
        .arg(QString::fromLocal8Bit(" font-family:'Microsoft YaHei';")));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(QString("#F7F7F7")).arg(QString("#30BA9A")));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(QString("#F7F7F7")).arg(QString("#30BA9A")));
    ui.pushButton->setStyleSheet(qss.join(""));

    QMenu *menu = new QMenu(ui.pushButton);
    QActionGroup* group = new QActionGroup(menu);
    auto* act1 = new QAction("视频会议通道一", group);
    auto* act2 = new QAction("视频会议通道二", group);
    act1->setCheckable(true);
    act2->setCheckable(true);
    menu->addAction(act1);
    menu->addAction(act2);
    act2->setChecked(true);
    group->setExclusive(true);
    ui.pushButton->addMenu(menu);
    //ui.pushButton->setMenu(menu);
}
