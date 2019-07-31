//
// Created by song on 19-7-31.
//

#include <MG995_control/MG995RosDriver.h>

using namespace std;
using namespace vwpp;

MG995RosDriver::MG995RosDriver():
        nh(ros::NodeHandle("~")),
        model("VWBOT_G1"),
        port("/dev/ttyUSB0"),
        baud(115200),
        frame_id("master"),
        msg_length(40),
        cmd_key_topic("/cmd_vel_stamped")
{
    this->node_name = ros::this_node::getName();

    if (nh.hasParam("model"))
    {
        nh.getParam("model", this->model);
        ROS_INFO("%s, use model %s", this->node_name.c_str(), this->model.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default model %s", this->node_name.c_str(), this->model.c_str());
    }


    if (nh.hasParam("port"))
    {
        nh.getParam("port", this->port);
        ROS_INFO("%s, use port %s", this->node_name.c_str(), this->port.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default port %s", this->node_name.c_str(), this->port.c_str());
    }

    if (nh.hasParam("baud"))
    {
        nh.getParam("baud", this->baud);
        ROS_INFO("%s, use baud %d", this->node_name.c_str(), this->baud);
    }
    else
    {
        ROS_WARN("%s, use the default baud %d", this->node_name.c_str(), this->baud);
    }

    if (nh.hasParam("msg_length"))
    {
        nh.getParam("msg_length", this->msg_length);
        ROS_INFO("%s, msg_length %d", this->node_name.c_str(), this->msg_length);
    }
    else
    {
        ROS_WARN("%s, use the default msg_length %d", this->node_name.c_str(), this->msg_length);
    }

    this->vwbot_serial_hardware = new MG995SerialHardware(this->model,
                                                          this->port,
                                                          this->baud,
                                                          this->msg_length);

    if (nh.hasParam("frame_id"))
    {
        nh.getParam("frame_id", this->frame_id);
        ROS_INFO("%s, use frame_id %s", this->node_name.c_str(), this->frame_id.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default frame_id %s", this->node_name.c_str(), this->frame_id.c_str());
    }

    // TODO: Consider add to the initial list.
//    std::string cmd_vel_sub_topic_name = "/cmd_vel_stamped";
      std::string MG995_topic_name = "/MG995_key";
    if (nh.hasParam("MG995_topic"))
    {
        nh.getParam("MG995_topic", MG995_topic_name);
        ROS_INFO("%s, use cmd_vel topic name %s", this->node_name.c_str(), MG995_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default cmd_vel topic name %s", this->node_name.c_str(), MG995_topic_name.c_str());
    }

    this->cmd_vel_sub = nh.subscribe<std_msgs::Bool>(MG995_topic_name, 1, &MG995RosDriver::MG995_control_cb, this);

}



MG995RosDriver::~MG995RosDriver()
{
    delete this->vwbot_serial_hardware;
}

//void MG995RosDriver::cmd_vel_stamped_cb(const geometry_msgs::TwistStamped::ConstPtr& msg)
//{
//
//    MG995SerialHardware::Velocity2D vwbot_cmd_vel;
//    float MG995_key;
//    vwbot_cmd_vel.x = msg->twist.linear.x;
//    vwbot_cmd_vel.y = msg->twist.linear.y;
//    vwbot_cmd_vel.yaw = msg->twist.angular.z;
//    MG995_key = msg->header.seq;
//    if (this->vwbot_serial_hardware->sendMessage_velocity(vwbot_cmd_vel) != 1)
//    {
//        ROS_ERROR("%s, Send Message failed!", this->node_name.c_str());
//    }
//    if(this->vwbot_serial_hardware->sendMessage_key(MG995_key)!=1)
//    {
//        ROS_ERROR("%s,Send Message Failed!", this->node_name.c_str());
//    }
//}

void MG995RosDriver::MG995_control_cb(const std_msgs::Bool::ConstPtr &msg)
{
    bool key;
    key = msg->data;
    if(this->vwbot_serial_hardware->sendMessage_key(key)!=1)
    {
        ROS_ERROR("%s,Send Message Failed!",this->node_name.c_str());
    }
}
