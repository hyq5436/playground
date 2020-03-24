#include "VoicePanel.h"
#include "ui_VoicePanel.h"
#include <QResizeEvent>

VoicePanel::VoicePanel(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::VoicePanel();
	ui->setupUi(this);

	// 加载图片资源
	QPixmap* voiceBackground = new QPixmap("Resources/voice_background.png");
	int	  backgroundWidth = this->width() * 0.8;
	int	  backgroundHeight = backgroundWidth * 0.50;
	ui->background->setFixedSize(backgroundWidth, backgroundHeight);
	ui->background->setPixmap(voiceBackground->scaled(QSize(backgroundWidth, backgroundHeight), Qt::KeepAspectRatio,
													  Qt::SmoothTransformation));
	this->setStyleSheet("QWidget { background-color: white; }");

	ui->btnStart->setStyleSheet("QPushButton#btnStart { background-color: #30BA9A; color: #f7f7f7; }");
	ui->tipLabel->setStyleSheet("QLabel#tipLabel { color: #999999; }");
}

VoicePanel::~VoicePanel()
{
	delete ui;
}

void VoicePanel::resizeEvent(QResizeEvent *event)
{
	// 加载图片资源
	QPixmap* voiceBackground = new QPixmap("Resources/voice_background.png");
	int	  backgroundWidth = event->size().width() * 0.6;
	int	  backgroundHeight = backgroundWidth * 0.50;
	ui->background->setFixedSize(backgroundWidth, backgroundHeight);
	ui->background->setPixmap(voiceBackground->scaled(QSize(backgroundWidth, backgroundHeight), Qt::KeepAspectRatio,
		Qt::SmoothTransformation));
}
