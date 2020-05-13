# udacity-robond-p2

Go Chase It! - Project 2 of the Udacity Robotics Software Engineer Nanodegree

git clone:- https://github.com/neelgandhi108/ROS_go_chase.git

## Description

This project contains:

1. A two-wheeled robot model (URDF) which is equiped with a camera and a lidar.
2. A customized world supported by Gazebo. 
3. Two ROS packages: the `drive_bot` and the `ball_chaser` , which enable the robot to chase the ball based on the camera perception.

## Core Concepts

Concepts explored in this project:

- ROS publishers, subscribers, services and clients.
- URDF
- Gazebo modeling and world building
- Gazebo Plugins
- Rviz

## Tasks
Robot model

Lidar and camera sensors.
Gazebo plugins for the robot’s differential drive, lidar, and camera.
Housed inside the world
Significant changes from the sample taught in the project lesson.
Robot is stable when moving
Gazebo world

Same as the world designed in the Build My World project or a new world that you design on the building editor for this project.
Includes a white-colored ball
drive_bot requirements:

A ball_chaser/command_robot service.
Service accepts linear x and angular z velocities.
Service publishes to the the wheel joints.
Service returns the requested velocities.
process_image requirements:

Subscribes to the robot’s camera image.
A function to analyze the image and determine the presence and position of a white ball.
Requests a service to drive the robot towards a white ball (when present).
world.launch requirements:

Launch the world (which includes a white ball).
Launch the robot.
ball_chaser.launch requirements:

Run the drive_bot C++ node.
Run the process_image C++ node.
  

   

  
