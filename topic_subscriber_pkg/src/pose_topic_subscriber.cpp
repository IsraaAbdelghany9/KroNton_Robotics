#include "ros/ros.h"
#include "turtlesim/Pose.h"

void callback(const turtlesim::Pose &msg)
{
    ROS_INFO("I got x=%f , y=%f , theta=%f " , msg.x ,msg.y , msg.theta);

}



int main(int argc, char * argv[])
{
    ros::init(argc, argv, "turtlesim_Pose_Subscriber_node");
    ros::NodeHandle handle;
    ros::Subscriber sub= handle.subscribe("/turtle1/pose",100,callback);
    ros::spin();
    return 0;
}
