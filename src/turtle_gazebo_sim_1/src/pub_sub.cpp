#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

ros::Publisher cmd_vel_pub;
float front_distance;
float right_distance;
float left_distance;

float front_distance_pos_3;
float front_distance_neg_3;
geometry_msgs::Twist cmd_vel_msg;

signed int i;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {

    front_distance = msg->ranges[0];  // Distance in front of the robot
    front_distance_pos_3 = msg->ranges[45];  // Distance in front_right of the robot
    front_distance_neg_3 = msg->ranges[315];  // Distance in front_left of the robot

    // ROS_INFO("front_distance_pos_3 = %f , front_distance_neg_3 =%f , front_distance =%f",& msg->ranges[3] ,& front_distance_neg_3 ,& front_distance);
    
    //&& front_distance_pos_3 > 0.5 && front_distance_neg_3 > 0.5 
    i = 0;

    if ((front_distance > 1.5) && (front_distance_pos_3 > 0.3) && (front_distance_neg_3 > 0.3 )  )
    {
        // No obstacle in front, move forward
        cmd_vel_msg.linear.x = 0.2;  // Set linear velocity for forward movement
        cmd_vel_msg.angular.z = 0.0;  // Set angular velocity for turning
    
    } 
    else 
    {
        for ( i=0;i<=45;i++)
        {
            right_distance = msg->ranges[i];  // Distance at the right side of the robot
            ROS_INFO(" i = %d ",i);
            if (right_distance > 1.5)
            {

                cmd_vel_msg.linear.x = 0.1;  // Set linear velocity 
                cmd_vel_msg.angular.z = 0.5;  // Set angular velocity for right turn
                cmd_vel_pub.publish(cmd_vel_msg);
                break;

            }
            else if (i == 45 )
            {
                for ( i=359 ;i >= 315 ;i--)
                {
                    ROS_INFO("i =%d", i);

                    left_distance = msg->ranges[i];  // Distance at the right side of the robot

                    if (left_distance > 1.5)
                    {

                        // Obstacle is closer on the right side, turn left
                        cmd_vel_msg.linear.x = 0.1;  // Set linear velocity 
                        cmd_vel_msg.angular.z = -0.5;  // Set angular velocity for left turn
                        cmd_vel_pub.publish(cmd_vel_msg);
                        break;

                    }

                }

            }

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


    ros::spin();



    return 0;
}