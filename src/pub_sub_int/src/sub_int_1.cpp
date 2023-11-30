#include "ros/ros.h"
#include "std_msgs/Int8.h"

void int_callback(const std_msgs::Int8 &number)
{
    ROS_INFO("the number is %d", number.data);
    //another way to display message
    //std::cout<<"the number is "<<number.data <<std::endl; 
}

int main (int argc , char **argv)
{
    ros::init(argc ,argv ,"Subscriber_int_1");

    ros::NodeHandle handle ;

    ros::Subscriber sub= handle.subscribe("Int_1_topic", 100 ,int_callback);

    ros::spin();


    return 0 ;
}