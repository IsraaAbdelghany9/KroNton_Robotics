#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "turtle_velocity_publisher");
  ros::NodeHandle handle;

  ros::Publisher vel_pub = handle.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 50);
  
  // Create the twist message
  geometry_msgs::Twist msg;
  msg.linear.x = 0.5;  // Linear velocity in m/s
  msg.angular.z = 0.0;  // Angular velocity in rad/s

  ros::Rate rate(10);  // Publish at 10 Hz

  while (ros::ok())
  {
    vel_pub.publish(msg);
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}