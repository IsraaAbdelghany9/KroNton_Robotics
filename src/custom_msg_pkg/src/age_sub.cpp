#include <ros/ros.h>
#include "custom_msg_pkg/Age.h"
#include <ctime>

void callback(const custom_msg_pkg::Age &msg)
{

    ros::Time current_time = ros::Time::now();

    int years = current_time.sec / (365 * 24 * 60 * 60); // Approximate calculation assuming each year has 365 days
    int months = (current_time.sec % (365 * 24 * 60 * 60)) / (30 * 24 * 60 * 60); // Approximate calculation assuming each month has 30 days
    int days = (current_time.sec % (30 * 24 * 60 * 60)) / (24 * 60 * 60);

    ROS_INFO("Current date (ROS format): %d years, %d months, %d days", years, months, days);

}




int main(int argc, char * argv[])
{
    ros::init(argc, argv, "Age_Subsriber_node");
    ros::NodeHandle handle;
    ros::Subscriber sub= handle.subscribe("/Age_topic",100,callback);
    ros::spin();
    return 0;
}



