//Alex DeFiore
//aad88
//minimal_commander node

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>

#define PI 3.14159265

int main(int argc, char **argv){
  ros::init(argc, argv, "minimal_commander1");//the name of this node will be minimal_commander1
  ros::NodeHandle n; //start creating publisher
  ros::Publisher my_publisher_object = n.advertise<std_msgs::Float64>("vel_cmd",1);
  //publishing to vel_cmd
  //buffer size 1
  
  std_msgs::Float64 amplitude;
  std_msgs::Float64 frequency;
  //create variables for amplitude and frequency
  
  std_msgs::Float64 sinusoidal;
  //create variable for sinusoidal output
  
  std_msgs::Float64 time;
  //create variable to make the sinusoidal output time dependent
  
  ros::Rate naptime(1.0);
  //sleep timer for 1Hz repetition rate
  
  amplitude.data = 1.0;
  frequency.data = 3.0;
  sinusoidal.data = 0.0;
  time.data = 0.0;
  //set starting values for variables
  
  while(ros::ok()){//infinite loop while ros is working
	  
	  time.data = time.data + 0.001; //increment by 0.001 every iteration
	  sinusoidal.data = amplitude.data * sin(2*PI*frequency.data*time.data);
	  my_publisher_object.publish(sinusoidal);
	  //publish the sinusoidal function based on amplitude, frequency, and time to the topic vel_cmd
	  
	  naptime.sleep();
	  //makes the loop sleep for the rest of this time period to maintain even loop frequency
  }
}
