#include "chart3d.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace chart3d_space {

chart3d::chart3d(QWidget* parent)
    : rviz::Panel(parent)
{
    QVBoxLayout *mainlayout=new QVBoxLayout;

    m_pChart = new Chart3DWidget(this);
    mainlayout->addWidget(m_pChart);
    mainlayout->setContentsMargins(0, 0, 0, 0);
    mainlayout->setSpacing(0);

    setLayout(mainlayout);
}

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(chart3d_space::chart3d, rviz::Panel)
