#include "ros/ros.h"
#include "std_msgs/Int32.h"

int main(int argc,char **argv)
{
    ros::init(argc , argv ,"Publisher_int_1");

    ros::NodeHandle handle;

    ros::Publisher pub=handle.advertise<std_msgs::Int32>("Int_1_topic",100);

    ros::Rate loop_rate(10);

    std_msgs::Int32 number;
    int counter=0;

    while (ros::ok())
    {
        number.data=counter;
        counter++;
        pub.publish(number);
        ROS_INFO("the counter is %d",number.data);
        ros::spinOnce;
        loop_rate.sleep();
    }
    
    
    
    return 0;
}


