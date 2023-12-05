#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

ros::Publisher cmd_vel_pub;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    float front_distance = msg->ranges[0];  // Distance in front of the robot
    float right_distance = msg->ranges[90];  // Distance at the right side of the robot
    float left_distance = msg->ranges[-90];  // Distance at the left side of the robot

    geometry_msgs::Twist cmd_vel_msg;

    if (front_distance > 2.0) {
        // No obstacle in front, move forward
        cmd_vel_msg.linear.x = 0.1;  // Set linear velocity for forward movement
        cmd_vel_msg.angular.z = 0.0;  // Set angular velocity for turning
    } 
    else if(front_distance < 2.0)
    {
        // Obstacle in front, avoid it
        if (right_distance > left_distance) {
            // Obstacle is closer on the right side, turn left
            cmd_vel_msg.linear.x = 0.1;  // Set linear velocity for stopping
            cmd_vel_msg.angular.z = 0.5;  // Set angular velocity for left turn
            
        } 
        else {
            // Obstacle is closer on the left side, turn right
            cmd_vel_msg.linear.x = -0.1;  // Set linear velocity for stopping
            cmd_vel_msg.angular.z = -0.5;  // Set angular velocity for right turn
        }
    }

    cmd_vel_pub.publish(cmd_vel_msg);
}

int main(int argc, char** argv) {

    //node initializatiton 
    ros::init(argc, argv, "robot_controller");

    //node handle
    ros::NodeHandle handle;


    cmd_vel_pub = handle.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ros::Subscriber laser_sub = handle.subscribe("/scan", 100, laserScanCallback);

    ros::Rate loop_rate(10);

    ros::spin();

    loop_rate.sleep();

    return 0;
}