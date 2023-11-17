#include "ros/ros.h"
#include "std_msgs/Int32.h"




int main(int argc,char **argv)
{
    ros::init(argc , argv ,"Publisher_Int32_node");

    ros::NodeHandle handle;

    ros::Publisher Publisher_Int32_node = handle.advertise<std_msgs::Int32>("/Publisher_Subscriper_Int32",100);

    ros::Rate loop_rate(10);

    int counter =20;

    std_msgs::Int32 msg;

    while (ros::ok() && counter <= 100)
    {

        msg.data = counter;

        Publisher_Int32_node.publish(msg);

        ROS_INFO("The counter now is = %d",msg.data);

        ros::spinOnce();

        loop_rate.sleep();

        counter++;
    }


}