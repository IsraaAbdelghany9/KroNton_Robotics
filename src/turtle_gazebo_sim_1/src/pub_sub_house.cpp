#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

ros::Publisher cmd_vel_pub;
float front_distance;
float right_distance;
float left_distance;

float front_distance_pos_45;
float front_distance_neg_315;
float front_distance_pos_20;
float front_distance_neg_340;
geometry_msgs::Twist cmd_vel_msg;

signed int i ,i_prev;
signed int j , j_prev;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {

    front_distance = msg->ranges[0];  // Distance in front of the robot
    front_distance_pos_45 = msg->ranges[45];  // Distance in front_right of the robot
    front_distance_neg_315 = msg->ranges[315];  // Distance in front_left of the robot
    front_distance_pos_20 = msg->ranges[20];
    front_distance_neg_340 = msg->ranges[340];

    i , i_prev = 0;
    j =0 ;
    j_prev = 0;

    if ((front_distance > 1.5) && (front_distance_pos_45 > 0.5) && (front_distance_neg_315 > 0.5 ) && (front_distance_pos_20 > 0.5 ) && (front_distance_neg_340 > 0.5 ) )
    {
        // No obstacle in front, move forward
        cmd_vel_msg.linear.x = 0.3;  // Set linear velocity for forward movement
        cmd_vel_msg.angular.z = 0.0;  // Set angular velocity for turning = 0
    
    } 
    else 
    {
        for ( i=0;i<=45;i++)
        {
            right_distance = msg->ranges[i];  // Distance at the right side of the robot
            ROS_INFO(" i = %d ",i);
            

            if (right_distance > 1.5)
            {

                cmd_vel_msg.linear.x = 0.3;  // Set linear velocity 
                cmd_vel_msg.angular.z = 0.5;  // Set angular velocity for right turn
                cmd_vel_pub.publish(cmd_vel_msg);
                break;

            }
            else if (i == 45 )
            {
                j_prev = 0;
                for ( j=359 ;j >= 315 ;j--)
                {
                    ROS_INFO("j =%d , the velovity is %f , the rotation is %f", j , cmd_vel_msg.linear.x ,cmd_vel_msg.angular.z );

                    left_distance = msg->ranges[j];  // Distance at the left side of the robot

                    
                    if (left_distance > 1.5)
                    {

                        // Obstacle is closer on the right side, turn left
                        cmd_vel_msg.linear.x = 0.0;  // Set linear velocity 
                        cmd_vel_msg.angular.z = -0.5;  // Set angular velocity for left turn
                        cmd_vel_pub.publish(cmd_vel_msg);
                        break;

                    }

                    if (j == j_prev)
                    {
                        // hit obstacle move backward
                        cmd_vel_msg.linear.x = -0.3;  // Set linear velocity 
                        cmd_vel_msg.angular.z = -0.1;  // Set angular velocity for left turn
                        cmd_vel_pub.publish(cmd_vel_msg);
                        break;    

                    }
                    j_prev = j;

                }

            }
            if (i == i_prev)
            {
                // hit obstacle move backward
                cmd_vel_msg.linear.x = -0.3;  // Set linear velocity 
                cmd_vel_msg.angular.z = -0.1;  // Set angular velocity for left turn
                cmd_vel_pub.publish(cmd_vel_msg);
                
            }
            i_prev = i;


        }

        
        
    }


    cmd_vel_pub.publish(cmd_vel_msg);
}

int main(int argc, char** argv) {

    //node initializatiton 
    ros::init(argc, argv, "robot_controller_house");

    //node handle
    ros::NodeHandle handle;


    cmd_vel_pub = handle.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ros::Subscriber laser_sub = handle.subscribe("/scan", 100, laserScanCallback);


    ros::spin();



    return 0;
}

