#pragma once

#include <QFrame>
#include "ui_HostMicStatusWidget.h"

class HostMicStatusWidget : public QFrame
{
    Q_OBJECT

public:
    HostMicStatusWidget(QWidget *parent = Q_NULLPTR);
    ~HostMicStatusWidget();

    void setHostName(const QString& name);
    void setIcon(QChar icon);
    void setIcon(QPixmap image);

    QSize sizeHint() const override;

private:
    Ui::HostMicStatusWidget ui;
    bool m_bUseIconFont;
};
