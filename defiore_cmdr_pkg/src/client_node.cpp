//Alex DeFiore
//aad88

#include <ros/ros.h>
#include <defiore_cmdr_pkg/sin.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv)
{//initialize node
  ros::init(argc, argv, "client_node");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<defiore_cmdr_pkg::sin>("sin");
  
  //make service call
  defiore_cmdr_pkg::sin srv;
  //srv.request.amplitude = atoll(argv[0]);
  //srv.request.frequency = atoll(argv[1]);

  std_msgs::Float64 amplitude;
  std_msgs::Float64 frequency;

  while(ros::ok()) {
    cout<<endl;
    cout << "enter amplitude: ";
    cin>>amplitude.data;

    cout<<endl;
    cout << "enter frequency: ";
    cin>>frequency.data;

    srv.request.frequency = frequency.data;
    srv.request.amplitude = amplitude.data;
   
    if(client.call(srv)) {
      
    }
    else{
      ROS_ERROR("Failed to change amplitude and frequency");
      return 1;
    }
  }

  return 0;
}
