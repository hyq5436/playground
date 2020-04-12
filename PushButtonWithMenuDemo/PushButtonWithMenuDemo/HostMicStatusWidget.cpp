#include "HostMicStatusWidget.h"
#include "CommonFun.h"
#include <QFont>

namespace {
const int HOST_MIC_STATUS_HEIGHT = 20;
const int HOST_MIC_STATUS_LEFT_PADDING = 7;
const int HOST_MIC_STATUS_RIGHT_PADDING = 7;
const int HOST_MIC_STATUS_SPACING = 4;
const int HOST_MIC_STATUS_MIC_WIDTH = 20;

}

QSize HostMicStatusWidget::sizeHint() const
{
    int iWidth = HOST_MIC_STATUS_LEFT_PADDING + HOST_MIC_STATUS_RIGHT_PADDING +
                 ui.lblName->fontMetrics().width(ui.lblName->text());
    if (m_bUseIconFont)
    {
        iWidth += HOST_MIC_STATUS_SPACING;
    }
    iWidth += HOST_MIC_STATUS_MIC_WIDTH;
    return QSize(iWidth, QFrame::sizeHint().height());
}
HostMicStatusWidget::HostMicStatusWidget(QWidget *parent)
    : QFrame(parent), m_bUseIconFont(true)
{
    ui.setupUi(this);
    layout()->setContentsMargins(HOST_MIC_STATUS_LEFT_PADDING, 0, HOST_MIC_STATUS_RIGHT_PADDING, 0);

    setFixedHeight(HOST_MIC_STATUS_HEIGHT);
    QString styleSheet = QString(
        "HostMicStatusWidget{"
        "border: none;"
        "background-color: rgba(0,0,0,0.30);"
        "border-top-left-radius: 0px;"
        "border-top-right-radius: %1px;"
        "border-bottom-right-radius: %1px;"
        "border-bottom-left-radius: 0px;"
        "};").arg(HOST_MIC_STATUS_HEIGHT/2);
    setStyleSheet(styleSheet);

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
    iconFont.setPixelSize(16);
    ui.lblMicStatus->setFont(iconFont);
}

HostMicStatusWidget::~HostMicStatusWidget()
{
}

void HostMicStatusWidget::setHostName(const QString& name) {
    ui.lblName->setText(name);
    adjustSize();
}

void HostMicStatusWidget::setIcon(QChar icon) {
    m_bUseIconFont = true;
    layout()->setSpacing(HOST_MIC_STATUS_SPACING);
    ui.lblMicStatus->setText(icon);
    adjustSize();
}

void HostMicStatusWidget::setIcon(QPixmap image) {
    m_bUseIconFont = false;
    layout()->setSpacing(0);
    ui.lblMicStatus->setPixmap(image);
    adjustSize();
}
