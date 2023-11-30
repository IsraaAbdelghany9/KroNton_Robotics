#include "ros/ros.h"
#include"std_msgs/String.h"
#include <iostream>


int main(int argc , char **argv)
{
    //ros node initialization 
    ros::init(argc , argv ,"Publisher_String_node");

    //Ros handle creation 
    //allow ros
    //access point allow node to communicate with ros system
    ros::NodeHandle handle;

    //create ros publisher 
    //Publisher_int_node is the name of the topic
    //advertise is like publish
    ros::Publisher Publisher_String_node = handle.advertise<std_msgs::String>("/Publisher_Subscriber_String_Topic",100);

    //loop rate 
    //publish with speed 10 Hz is 10 data per second
    //should be customize with the ros Subscriber  
    ros::Rate loop_rate(1);

    //counter
    int count =0;

    while(ros::ok())
    {
        std_msgs::String msg;

        std::stringstream ss;

        ss<<"Hello World\t"<<count;

        msg.data = ss.str();

        ROS_INFO("%s",msg.data.c_str());

        Publisher_String_node.publish(msg);

        ros::spinOnce();

        loop_rate.sleep(); 

        count++;       

    }
return(0);
}