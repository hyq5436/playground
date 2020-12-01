#ifndef CHART3D_H
#define CHART3D_H

#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件

namespace chart3d_space {
class chart3d: public rviz::Panel
{
    Q_OBJECT
public:
    chart3d(QWidget* parent = 0);
    //void load(const rviz::Config& config) override;
    //void save(const rviz::Config& config) const override;

protected:
    // The ROS node handle.
    ros::NodeHandle nh_;
};

}
#endif // CHART3D_H
