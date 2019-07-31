//
// Created by song on 19-7-31.
//

#include <ros/ros.h>
#include <MG995_control/MG995RosDriver.h>
#include <MG995_control/utils.h>

using namespace std;
using namespace vwpp;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "vwbot_bringup_node");

    MG995RosDriver MG995_ros_driver;

    int communication_hz = 100;
    ros::NodeHandle nh("~");
    if (nh.hasParam("communication_hz"))
    {
        nh.getParam("communication_hz", communication_hz);
        ROS_INFO("%s use the communication rate: %d Hz", ros::this_node::getName().c_str(), communication_hz);
    }
    else
    {
        ROS_WARN("%s use the default communication rate %d Hz", ros::this_node::getName().c_str(), communication_hz);
    }

    ros::Rate loop_rate(communication_hz);
    while (ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }

    // Stop continous and close device
    ROS_WARN("Wait 0.1s");
    ros::Duration(0.1).sleep();

    return 0;
}
