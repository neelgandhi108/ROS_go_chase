#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//Include the ball_chaser "DriveToTarget" header file
#include "ball_chaser/DriveToTarget.h"

#include <std_msgs/Float64.h>

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
                          ball_chaser::DriveToTarget::Response& res){    
    
    geometry_msgs::Twist motor_command;
    ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular:%1.2f", (float)req.linear_x, (float)req.angular_z);

  
    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;
  
    motor_command_publisher.publish(motor_command);

    ros::Duration(0.5).sleep();

    res.msg_feedback = "Motor Command Set - linear_x: "+ std::to_string(req.linear_x) + " angular_z: " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "drive_bot");

  
    ros::NodeHandle nh;

   
    motor_command_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    

    ros::ServiceServer drive_robot_srv = nh.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send motor commands");

  
    ros::spin();

    return 0;
}
