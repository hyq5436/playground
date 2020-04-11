#pragma once

#include <QFrame>
namespace Ui { class ShareDesktopToolbar; };

class QPropertyAnimation;
class ShareDesktopToolbar : public QFrame
{
    Q_OBJECT

public:
    ShareDesktopToolbar(QWidget *parent = Q_NULLPTR);
    ~ShareDesktopToolbar();

    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
    void hideToolbar();

private slots:
    void onFadeOutFinished();

private:
    Ui::ShareDesktopToolbar *ui;
    QPropertyAnimation* mpFadeIn;
    QPropertyAnimation* mpFadeOut;
};
