#include "ros/ros.h"
#include "custom_msg_pkg/Age.h"


int main(int argc,char **argv)
{
    ros::init(argc , argv ,"Age_publisher_node");

    ros::NodeHandle handle;

    ros::Publisher age_pub = handle.advertise<custom_msg_pkg::Age>("/Age_topic",100);

    ros::Rate loop_rate(10);

//   int counter =20;


    while (ros::ok())
    {
        custom_msg_pkg::Age age_msg;

        age_msg.years=1970;
        age_msg.months=10;
        age_msg.days=4;

        age_pub.publish(age_msg);

        ROS_INFO("The age now is = %f days is %f",age_msg.years,age_msg.days);

        ros::spinOnce();

        loop_rate.sleep();

    }


}