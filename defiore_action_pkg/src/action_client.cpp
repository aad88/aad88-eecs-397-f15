//Alex DeFiore
//aad88

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <defiore_action_pkg/sineAction.h>
#include <iostream>
using namespace std;

//function to access result upon goal completion
void doneCb(const actionlib::SimpleClientGoalState& state, const defiore_action_pkg::sineResultConstPtr& result) {

  ROS_INFO(" doneCb: server responded with state [%s]", state.toString().c_str());
  if(result->result){
    ROS_INFO("successful goal completion");
  } else {
    ROS_INFO("goal failed");
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "action_client_node"); //name and start this node

  //goal object compatible with sine action
  defiore_action_pkg::sineGoal goal;

  //use name of action server, with true argument to run as a separate thread
  actionlib::SimpleActionClient<defiore_action_pkg::sineAction> action_client("action_server_node", true);

  //attempt to connect to the server
  ROS_INFO("waiting for server: ");
  bool server_exists = action_client.waitForServer(ros::Duration(5.0));//wait up to 5 seconds

  if(!server_exists) {
    ROS_WARN("could not connect to server: halting");
    return 0;//bail
  }


  ROS_INFO("connected to action server");//if not connected, bailed before this point


  while(ros::ok()) {
    std_msgs::Float64 amplitude, frequency;
    std_msgs::Int32 cycles;

    cout<<endl;
    cout << "enter amplitude: ";
    cin>>amplitude.data;

    cout<<endl;
    cout << "enter frequency: ";
    cin>>frequency.data;

    cout<<endl;
    cout << "enter number of cycles: ";
    cin>>cycles.data;

    goal.freq = frequency.data;
    goal.amp = amplitude.data;
    goal.cycles = cycles.data;

    action_client.sendGoal(goal, &doneCb); //directs to doneCb on completion

    float time = cycles.data / frequency.data;
    time = time + 10.0; //calculate expected time with buffer

    bool finished_before_timeout = action_client.waitForResult(ros::Duration(time));

    if(!finished_before_timeout){
      ROS_WARN("giving up waiting on result");
      return 0;
    }
    ros::spinOnce();
  }//end while

  return 0;
}

