//Alex DeFiore
//aad88
//minimal_commander node

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <defiore_cmdr_pkg/sin.h>

#define PI 3.14159265

std_msgs::Float64 amp;
std_msgs::Float64 freq;

bool callback(defiore_cmdr_pkg::sinRequest &request, defiore_cmdr_pkg::sinResponse &response){
  ROS_INFO("in callback");
  if(request.amplitude>=0 && request.frequency>=0){
    //if valid values for amp and freq, transfer from service to node
    amp.data = request.amplitude;
    freq.data = request.frequency;
    return true;
  }
  return false;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "minimal_commander1");//the name of this node will be minimal_commander1
  ros::NodeHandle n; //start creating publisher
  ros::Publisher my_publisher_object = n.advertise<std_msgs::Float64>("vel_cmd",1);
  //publishing to vel_cmd
  //buffer size 1

  ros::ServiceServer service = n.advertiseService("sin", callback);
  
  std_msgs::Float64 sinusoidal;
  //create variable for sinusoidal output
  
  std_msgs::Float64 time;
  //create variable to make the sinusoidal output time dependent
  
  ros::Rate naptime(1.0);
  //sleep timer for 1Hz repetition rate
  
  amp.data = 3.0;
  freq.data = 1.0;
  sinusoidal.data = 0.0;
  time.data = 0.0;
  //set starting values for variables
  
  while(ros::ok()){//infinite loop while ros is working
	  
	  time.data = time.data + 0.01; //increment by 0.01 every iteration
	  sinusoidal.data = amp.data * sin(2*PI*freq.data*time.data);
	  my_publisher_object.publish(sinusoidal);
	  //publish the sinusoidal function based on amplitude, frequency, and time to the topic vel_cmd
	  
	  naptime.sleep();
	  //makes the loop sleep for the rest of this time period to maintain even loop frequency
  }
}
