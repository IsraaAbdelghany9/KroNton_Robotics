#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"

ros::Publisher divided_pub;
ros::Subscriber divided_sub;
std_msgs::Float32 divided_msg;
float input_num;

void int_callback(const std_msgs::Int32 &number)
{
    input_num= number.data;
    //another way to display message
    //std::cout<<"the number is "<<number.data <<std::endl; 
}


int main(int argc,char **argv)
{
    ros::init(argc , argv ,"Divider_node");

    ros::NodeHandle handle;

    divided_sub= handle.subscribe("Int_1_topic", 100 ,int_callback);
    divided_pub= handle.advertise<std_msgs::Int32>("Divided_value",100);

    ros::Rate loop_rate(10);


    while (ros::ok())
    {
        divided_msg.data = input_num/2;
        divided_pub.publish(divided_msg);
        ROS_INFO("the counter is %f",divided_msg.data);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    
    
    return 0;
}


