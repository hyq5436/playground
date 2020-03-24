#pragma once

#include <QFrame>
namespace Ui { class VoiceLaunchWidget; };

class VoiceLaunchWidget : public QFrame
{
	Q_OBJECT

public:
	VoiceLaunchWidget(QWidget *parent = Q_NULLPTR);
	~VoiceLaunchWidget();

	void resizeEvent(QResizeEvent *event) override;

private:
	Ui::VoiceLaunchWidget *ui;
};
