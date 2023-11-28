#include "ros/ros.h"
#include "std_msgs/String.h"


void callback(const std_msgs::String &msg)
{
    ROS_INFO("I heard: [%s]",msg.data.c_str());

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Subscriber_String_node");

    ros::NodeHandle handle;
    ros::Subscriber sub=handle.subscribe("Publisher_Subscriber_String_Topic",100,callback);
    ros::spin();
    // ros::shutdown();
    return 0;
}
