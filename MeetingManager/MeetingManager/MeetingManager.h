#pragma once

#include <QtWidgets/QWidget>
#include "ui_MeetingManager.h"

class MeetingManager : public QWidget
{
    Q_OBJECT

public:
    MeetingManager(QWidget *parent = Q_NULLPTR);

private:
    void addMeetingType();

private:
    Ui::MeetingManagerClass ui;
};
