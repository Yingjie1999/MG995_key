#ifndef VWBOTROSDRIVER_H_
#define VWBOTROSDRIVER_H_

#include <string>
#include <queue>

#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <tf/tf.h>
#include <std_msgs/Bool.h>
#include <MG995_control/MG994SerialHardware.h>

namespace vwpp
{
    class MG995RosDriver
    {
    public:
        MG995RosDriver();
        virtual ~MG995RosDriver();
        void cmd_vel_stamped_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
        void MG995_control_cb(const std_msgs::Bool::ConstPtr& msg);

    private:

        MG995SerialHardware* vwbot_serial_hardware;
        std::queue<MG995SerialHardware::Velocity2D> que_vwbot_vel2d_data_;


        std::string node_name;
        std::string model;
        std::string port;
        int baud;
        int msg_length;

        std::string frame_id;
        std::string cmd_key_topic;
        geometry_msgs::TwistStamped cmd_vel_stamped_;

        ros::NodeHandle nh;
        ros::Subscriber cmd_vel_sub;
        ros::Subscriber MG995_sub;
    };

} // namespace vwpp

#endif
