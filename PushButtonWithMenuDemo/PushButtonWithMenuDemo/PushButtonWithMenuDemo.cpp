#pragma execution_character_set("utf-8")

#include <QLabel>
#include <QMenu>
#include "CommonFun.h"
#include "PushButtonWithMenuDemo.h"
#include "LiveFloatWindow.h"
#include "FloatWindowTopLayer.h"

PushButtonWithMenuDemo::PushButtonWithMenuDemo(QWidget* parent)
    : QDialog(parent) {
    ui.setupUi(this);
    setStyleSheet("background-color: #37383e;");
    //setStyleSheet("background-color: white;");
    QStringList qss;
    qss.append(
        QString("QPushButton{border-style:none;padding:5px;border-radius:3px;"
                "color:%1;background:%2;%3}")
            .arg(QString("#F7F7F7"))
            .arg(QString("#30BA9A"))
            .arg(QString::fromLocal8Bit(" font-family:'Microsoft YaHei';")));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}")
                   .arg(QString("#F7F7F7"))
                   .arg(QString("#30BA9A")));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}")
                   .arg(QString("#F7F7F7"))
                   .arg(QString("#30BA9A")));
    ui.pushButton->setStyleSheet(qss.join(""));

    QMenu* menu = new QMenu(ui.pushButton);
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
    // ui.pushButton->setMenu(menu);

    //
    ui.pushButton_2->setData(QChar(0xf64d), QString("麦克风"));
    QString menuStyleSheet = QString(
        " QMenu {"
        "      background-color: #37383e;"
        "      border: none;"
        "      font: 12px 'Microsoft YaHei';"
        "      color: #FFFFFF;"
        "  }"
        ""
        "  QMenu::item {"
        "      background-color: transparent;"
        "  }"
        ""
        "  QMenu::item:selected {"
        "      background-color: #2E2E34;"
        "  }");
    QMenu* moreMenu = new QMenu(ui.btnShowMenu);
    moreMenu->setStyleSheet(menuStyleSheet);
    moreMenu->addAction(new QAction("邀请人员"));
    moreMenu->addAction(new QAction("设置"));
    moreMenu->addAction(new QAction("反馈"));
    moreMenu->addAction(new QAction("结束主讲"));
    moreMenu->addAction(new QAction("退出"));
    ui.btnShowMenu->setMenu(moreMenu);

    QLabel* pLblSharing = new QLabel(this);
    pLblSharing->setText("共享中");
    pLblSharing->setStyleSheet(
        QString("QLabel {"
                "margin-left: 7px;"
                "padding-left: 2px;"
                "padding-top: 2px;"
                "padding-right: 2px;"
                "padding-bottom: 1px;"
                "font: 12px 'Microsoft YaHei';"
                "color: #FFFFFF;"
                "background-color: #F5A623;"
                "border-top-left-radius: 2px;"
                "border-top-right-radius: 0px;"
                "border-bottom-right-radius: 6px;"
                "border-bottom-left-radius: 0px;"
                "}"));
    pLblSharing->show();

    ui.hostStatusContainer->setStyleSheet(
        QString("QFrame#hostStatusContainer{"
                "border: 1px solid transparent;"
                "background-color: rgba(0,0,0,0.30);"
                "border-top-left-radius: 0px;"
                "border-top-right-radius: 10px;"
                "border-bottom-right-radius: 10px;"
                "border-bottom-left-radius: 0px;"
                "};"));
    ui.lblName->setStyleSheet(
        QString("QLabel {"
                "background-color: transparent;"
                "color: #FFFFFF;"
                "font: 12px 'Microsoft YaHei';"
                "};"));
    ui.lblMicStatus->setStyleSheet(
        QString("QLabel {"
                "background-color: transparent;"
                "color: #FFFFFF;"
                "};"));
    QFont iconFont = CommonFun::getIconFont();
    iconFont.setPixelSize(18);
    ui.lblMicStatus->setFont(iconFont);
    ui.lblMicStatus->setText(QChar(0xf64d));
    
#if 0
    ui.lblMicStatus->setPixmap(CommonFun::getIconFontPixmap(QChar(0xf64d),
                                                            QColor("#FFFFFF"),
                                                            QSize(30, 30), 24)
                                   .scaled(QSize(20, 20)));
#endif
    ui.hostMicStatus->setHostName("老婆老伯");
    ui.hostMicStatus->setIcon(QChar(0xf64d));

    ui.btnClose->setStyleSheet(
        QString("QPushButton#btnClose {"
                "background-color: rgba(0,0,0,0.80);"
                "border-radius: 8px;"
                "color: white;"
                "};"));
    iconFont.setPixelSize(8);
    ui.btnClose->setFixedSize(16, 16);
    ui.btnClose->setFont(iconFont);
    ui.btnClose->setText(QChar(0xF62C));


    connect(ui.btnShow, &QPushButton::clicked, this, [this]() {
        auto* pFloatWindow = new LiveFloatWindow(this);
        pFloatWindow->show();
        pFloatWindow->resize(174, 119);
        pFloatWindow->setPhoto(
            CommonFun::getRoundedImage("Resources/head.png", 30));
    });
}
