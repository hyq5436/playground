#pragma once

#include <QWidget>
namespace Ui { class VoicePanel; };

class VoicePanel : public QWidget
{
	Q_OBJECT

public:
	VoicePanel(QWidget *parent = Q_NULLPTR);
	~VoicePanel();

	void resizeEvent(QResizeEvent *event) override;
private:
	Ui::VoicePanel *ui;
};
