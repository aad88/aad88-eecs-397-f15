//Alex DeFiore
//aad88


#include <actionlib/server/simple_action_server.h>
#include <ros/ros.h>
#include <defiore_action_pkg/sineAction.h>
#include <math.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>

#define PI 3.14159265

bool cycling = true;
class ActionServer {
protected:

  ros::NodeHandle nh_;

  //needs a simple action server with sineAction
  actionlib::SimpleActionServer<defiore_action_pkg::sineAction> as_;

  //message types for communication
  defiore_action_pkg::sineGoal goal_; //goal message received from client
  defiore_action_pkg::sineResult result_; //put results here to send back to client
  defiore_action_pkg::sineFeedback feedback_; //put feedback



public:
  ActionServer(); //define constructor outside of class definition

  ~ActionServer(void) {
  }
  //action interface
  void executeCB(const actionlib::SimpleActionServer<defiore_action_pkg::sineAction>::GoalConstPtr& goal);
};//end class


ActionServer::ActionServer() :
  as_(nh_, "action_server_node", boost::bind(&ActionServer::executeCB, this, _1), false)
  //initialize server with name "action_server" which clients will need to connect
{
  
  as_.start(); //start server running
}

//implement executeCB
void ActionServer::executeCB(const actionlib::SimpleActionServer<defiore_action_pkg::sineAction>::GoalConstPtr& goal) {
  
  std_msgs::Float64 amp;// = goal_.amp;
  std_msgs::Float64 freq;// = goal_.freq;
  std_msgs::Int32 cycles;// = goal_.cycles;

  amp.data = goal_.amp;
  freq.data = goal_.freq;
  cycles.data = goal_.cycles;


  ros::Publisher my_publisher_object = nh_.advertise<std_msgs::Float64>("vel_cmd",1); 
  //publishing to vel_cmd
  //publisher uses private nodehandle from action server
  //buffer size 1

  std_msgs::Float64 sinusoidal;
  //create variable for sinusoidal output
  
  std_msgs::Float64 time;
  //create variable to make the sinusoidal output time dependent
  
  ros::Rate naptime(100.0);
  //sleep timer for 100Hz repetition rate

  time.data = 0.0;
  std_msgs::Float64 max_time;
  max_time.data = cycles.data / freq.data; // determines time for which the function is cycling

  while(time.data <= max_time.data){
    sinusoidal.data = amp.data * sin(2*PI*freq.data*time.data);
    ros::spinOnce();
    my_publisher_object.publish(sinusoidal); //publish sine output to vel_cmd
    ROS_INFO("sin = %f", sinusoidal);
    time.data = time.data + 0.01; //increment time
    
  }

  sinusoidal.data = 0.0;//reset to zero

  result_.result = 1;
  as_.setSucceeded(result_);//tell client of sucessful completion of goal
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "action_server_node"); //name the node

  ROS_INFO("initiating the action server");

  ActionServer as_object; //create an instance of ActionServer

  ROS_INFO("going into spin");
  while(cycling){
    ros::spinOnce();
  }

  return 0;
}
