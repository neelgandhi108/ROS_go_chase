#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z)
{
    
    ROS_INFO_STREAM("Send motor command");
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv)){
        ROS_ERROR("Failed to call service /command_robot");
    }
}

void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    int green_channel_offset = 1;
    int blue_channel_offset = 2;
    
    int starting_pixel = img.data.size() / 3;
    int ending_pixel = img.data.size() *2 / 3; 
    int center_pixel = 0;
    int num_white_pixels = 0;
    for (unsigned int i = starting_pixel; i+2 < ending_pixel; i+=3){
        // find white pixel
        if (img.data[i] == white_pixel && img.data[i+green_channel_offset] == white_pixel && img.data[i+blue_channel_offset] == white_pixel){
            // identify the white ball direction
            center_pixel += (i % (3 * img.width)) / 3; 
            num_white_pixels += 1;
        }
    }

    if (num_white_pixels == 0){
        drive_robot(0,0.5); 

    }
    else{
        center_pixel /= num_white_pixels;
        
            if (center_pixel < img.width / 3){
                drive_robot(0.5,1); // turn left
            }
            else if (center_pixel > img.width * 2 / 3 ){
                drive_robot(0.5,-1); //turn right
            }
            else{
                drive_robot(1,0);
            }
     
    }
}

int main(int argc, char** argv)
{
   
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
    ros::spin();

    return 0;
}
