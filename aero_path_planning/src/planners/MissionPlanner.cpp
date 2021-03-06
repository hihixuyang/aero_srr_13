/**
 * @file   MissionPlanner.cpp
 *
 * @date   May 10, 2013
 * @author parallels
 * @brief  \TODO
 */

//*********** SYSTEM DEPENDANCIES ****************//
#include <boost/foreach.hpp>
#include <vector>
#include <aero_srr_msgs/StateTransitionRequest.h>
//************ LOCAL DEPENDANCIES ****************//
#include <aero_path_planning/planners/MissionPlanner.h>
//***********    NAMESPACES     ****************//

using namespace aero_path_planning;

MissionPlanner::MissionPlanner(ros::NodeHandle& nh, ros::NodeHandle& p_nh):
				OoI_manager_(1.0),
				searching_(false),
				naving_(false),
				homeing_(false),
				recieved_path_(false),
				nh_(nh),
				p_nh_(p_nh),
				transformer_(nh),
				dr_server_(p_nh)
{
	geometry_msgs::Pose mission_goal;
	double scaler = 1.0;
	mission_goal.position.x = 10.0;
	mission_goal.position.y = 0.0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 20.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 30.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 40.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 50.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 60.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 70.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 70.0/scaler;
	mission_goal.position.y = 5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 75.0/scaler;
	mission_goal.position.y = -5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 80.0/scaler;
	mission_goal.position.y = 5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 80.0/scaler;
	mission_goal.position.y = -5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 75.0/scaler;
	mission_goal.position.y = 5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 70.0/scaler;
	mission_goal.position.y = -5;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);
	mission_goal.position.x = 70.0/scaler;
	mission_goal.position.y = 0;
	mission_goal.orientation.w = 1;
	this->mission_goals_.push_back(mission_goal);

	ROS_INFO_STREAM("Misison Planner Starting Up...");
	this->loadParam();
	this->registerTopics();
	this->updateMissionGoal();
	this->registerTimers();
	ROS_INFO_STREAM("Mission Planner Running!");
}

void MissionPlanner::loadParam()
{
	ROS_INFO_STREAM("Mission Planner Loading Parameters...");
	this->local_frame_        = "/base_footprint";
	this->global_frame_       = "/world";
	this->path_topic_         = "aero/global/path";
	this->state_topic_        = "/state";
	this->mission_goal_topic_ = "/mission_goal";
	this->path_goal_topic_    = "/path_goal";
	this->ooi_topic_          = "/ObjectPose2";
	this->state_request_topic_= "/aero/supervisor/state_transition_request";
	this->path_threshold_     = 1.0;
	this->nav_threshold_      = 2.5;
	this->dist_threshold_     = 0.25;
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "local_frame", this->local_frame_, this->local_frame_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "global_frame", this->global_frame_, this->global_frame_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "state_topic", this->state_topic_, this->state_topic_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "path_topic", this->path_topic_, this->path_topic_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "path_threshold", this->path_threshold_, this->path_threshold_<<"m");
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "nav_threshold", this->nav_threshold_, this->nav_threshold_<<"m");
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "mission_goal_topic", this->mission_goal_topic_, this->mission_goal_topic_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "path_goal_topic", this->path_goal_topic_, this->path_goal_topic_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "ooi_topic", this->ooi_topic_, this->ooi_topic_);
	AERO_PATH_PLANNING_LOAD_PARAM(this->p_nh_, "state_transition_request_topic", this->state_request_topic_, this->state_request_topic_);

}

void MissionPlanner::registerTopics()
{
	ROS_INFO_STREAM("Mission Planner Registering Topics...");
	this->state_sub_        = this->nh_.subscribe(this->state_topic_, 1,  &MissionPlanner::stateCB, this);
	this->path_sub_         = this->nh_.subscribe(this->path_topic_, 1, &MissionPlanner::pathCB, this);
	this->mission_goal_pub_ = this->nh_.advertise<geometry_msgs::PoseStamped>(this->mission_goal_topic_, 1, true);
	this->path_goal_pub_    = this->nh_.advertise<geometry_msgs::PoseStamped>(this->path_goal_topic_, 1, true);
	this->ooi_sub_          = this->nh_.subscribe(this->ooi_topic_, 1, &MissionPlanner::ooiCB, this);
	this->dr_server_.setCallback(boost::bind(&MissionPlanner::drCB, this, _1, _2));
	this->state_request_client_ = this->nh_.serviceClient<aero_srr_msgs::StateTransitionRequest>(this->state_request_topic_);
}

void MissionPlanner::registerTimers()
{
	ROS_INFO_STREAM("Mission Planner Registering Timers...");
	this->goal_timer_ = this->nh_.createTimer(ros::Duration(1.0/10.0), &MissionPlanner::goalCB, this);
	this->mission_timeout_ = this->nh_.createTimer(ros::Duration(60*20), &MissionPlanner::timeoutCB, this, true);
}

void MissionPlanner::drCB(const MissionPlannerConfig& config, uint32_t level)
{
	this->local_frame_   = config.local_frame;
	this->global_frame_  = config.global_frame;
	this->path_threshold_= config.path_threshold;
	if(!config.mission_goal_topic.compare(this->mission_goal_topic_))
	{
		this->mission_goal_topic_ = config.mission_goal_topic;
		this->mission_goal_pub_.shutdown();
		this->mission_goal_pub_ = this->nh_.advertise<geometry_msgs::PoseStamped>(this->mission_goal_topic_, 1, true);
	}
	if(!config.path_goal_topic.compare(this->path_goal_topic_))
	{
		this->path_goal_topic_ = config.path_goal_topic;
		this->path_goal_pub_.shutdown();
		this->path_goal_pub_    = this->nh_.advertise<geometry_msgs::PoseStamped>(this->path_goal_topic_, 1, true);
	}
}

void MissionPlanner::pathCB(const nav_msgs::PathConstPtr& message)
{
	ROS_INFO_STREAM("Mission Planner Recieved new Carrot Path!");
	this->recieved_path_ = true;
	this->carrot_path_.clear();
	BOOST_FOREACH(std::vector<geometry_msgs::PoseStamped>::value_type pose, message->poses)
	{
		this->carrot_path_.push_back(pose);
	}
	this->updateGoal();
}

void MissionPlanner::ooiCB(const geometry_msgs::PoseArrayConstPtr& message)
{
	if(this->searching_)
	{
		tf::Point temp_point;
		BOOST_FOREACH(std::vector<geometry_msgs::Pose>::value_type pose, message->poses)
		{
			tf::pointMsgToTF(pose.position, temp_point);
			this->OoI_manager_.addOoI(temp_point);
		}

		ROS_INFO_STREAM("Added new detections, current detection state:\n"<<this->OoI_manager_);
	}
}

void MissionPlanner::timeoutCB(const ros::TimerEvent& event)
{
	this->requestHome();
}

bool MissionPlanner::reachedNextGoal(const geometry_msgs::PoseStamped& worldLocation, const double threshold) const
{
	tf::Point world_point;
	tf::Point goal_point;
	tf::pointMsgToTF(worldLocation.pose.position, world_point);
	tf::pointMsgToTF(this->carrot_path_.front().pose.position, goal_point);
	double dist = world_point.distance(goal_point);
	ros::Duration timeout (this->time_out_start_ - ros::Time::now());
	//ROS_INFO_STREAM_THROTTLE(1, "\nMission Planner: At position:"<<worldLocation.pose.position<<"\nGoal position:"<<this->carrot_path_.front().pose.position<<"\nDistance to Goal:="<<dist);
	return dist<threshold || timeout>ros::Duration(90);
}

void MissionPlanner::goalCB(const ros::TimerEvent& event)
{
	ROS_INFO_STREAM_THROTTLE(5, "Mission Planner: Currently "<<this->mission_goals_.size()<<" Mission Goals Remaining!");
	geometry_msgs::PoseStamped current_point;

	if(this->calcRobotPointWorld(current_point))
	{
		//We're following a path...
		if(!this->carrot_path_.empty())
		{
			if(this->reachedNextGoal(current_point, this->dist_threshold_))
			{
				this->carrot_path_.pop_front();
				this->updateGoal();
			}
		}
		//We're advancing mission goals or mission states
		else
		{
			//Means we're at an OoI, attepmt to collect
			if(this->naving_&& this->recieved_path_)
			{
				ROS_INFO_STREAM("Reached the Object of Interest, attempting to Collect!");
				this->requestCollect();
			}
			//We've got more mission goals
			ROS_INFO_STREAM_THROTTLE(5,"I have completed my current path!");
			if(!this->mission_goals_.empty() && this->recieved_path_)
			{
				ROS_INFO_STREAM("Reached a Mission Goal, Moving to the next one!");
				this->updateMissionGoal();
			}
			//We need to transition mission states
			else
			{
				//Means we've reached the end of the search pattern, start going to objects of interest
				if(this->searching_&&this->recieved_path_)
				{
					this->requestNavObj();
				}
				//Means we've reached the end of the detections, go home
				else if(this->naving_&&this->recieved_path_)
				{
					if(this->last_collect_)
					{
						ROS_INFO_STREAM("Mission Planner: Finised My Mission, Heading Home!");
						this->requestHome();
					}
				}
			}
		}
	}
}

void MissionPlanner::updateGoal() const
{
	if(!this->carrot_path_.empty())
	{
		geometry_msgs::PoseStamped goal_pose(this->carrot_path_.front());
		this->path_goal_pub_.publish(goal_pose);
		this->time_out_start_ = ros::Time::now();
	}

}

bool MissionPlanner::calcRobotPointWorld(geometry_msgs::PoseStamped& point) const
{
	bool success = true;
	geometry_msgs::PoseStamped robot_pose;
	robot_pose.header.frame_id    = this->local_frame_;
	robot_pose.header.stamp       = ros::Time::now();
	robot_pose.pose.orientation.w = 1;

	//look up the robot's position in the world frame
	try
	{
		this->transformer_.waitForTransform(this->global_frame_, robot_pose.header.frame_id, robot_pose.header.stamp, ros::Duration(0.1));
		this->transformer_.transformPose(this->global_frame_, robot_pose, point);
	}
	catch(std::exception& e)
	{
		ROS_ERROR_STREAM_THROTTLE(1, e.what());
		success = false;
	}
	return success;
}

void MissionPlanner::stateCB(const aero_srr_msgs::AeroStateConstPtr& message)
{
	geometry_msgs::Pose home;
	typedef aero_srr_msgs::AeroState state_t;
	switch(message->state)
	{
		case state_t::ERROR:
		case state_t::MANUAL:
		case state_t::PAUSE:
		case state_t::SAFESTOP:
		case state_t::SHUTDOWN:
		case state_t::COLLECT:
		case state_t::PICKUP:
			this->pause(true);
			break;
		case state_t::SEARCH:
			this->pause(false);
			ROS_INFO_STREAM("Mission Planner is Searching!");
			this->searching_ = true;
			this->naving_    = false;
			this->homeing_   = false;
			this->dist_threshold_ = this->path_threshold_;
			break;
		case state_t::NAVOBJ:
			ROS_INFO_STREAM("Missiong Planner is Naving to Objects!");
			this->pause(false);
			//Only generate the goal list once
			if(!this->naving_)
			{
				this->generateDetectionGoalList();
			}
			this->searching_ = false;
			this->naving_    = true;
			this->homeing_   = false;
			this->dist_threshold_ = this->nav_threshold_;
			break;
		case state_t::HOME:
			ROS_INFO_STREAM("Mission Planner is Homing!");
			this->pause(false);
			this->searching_ = false;
			this->naving_    = false;
			this->homeing_   = true;
			this->dist_threshold_ = this->nav_threshold_;
			this->mission_goals_.clear();
			home.orientation.w = 1;
			this->mission_goals_.push_back(home);
			break;
		default:
			ROS_ERROR_STREAM("Received Unkown State: "<<*message);
			break;
	}
}


void MissionPlanner::updateMissionGoal()
{
	if(!this->mission_goals_.empty())
	{
		geometry_msgs::PoseStampedPtr message(new geometry_msgs::PoseStamped());
		message->pose            = this->mission_goals_.front();
		message->header.frame_id = this->global_frame_;
		message->header.stamp    = ros::Time::now();
		ROS_INFO_STREAM("Upating Mission Goal to:"<<(*message));
		this->mission_goal_pub_.publish(message);
		this->mission_goals_.pop_front();
		this->recieved_path_ = false;
	}
}

void MissionPlanner::generateDetectionGoalList()
{
	ROS_INFO_STREAM("Generating goals off of Objects of Interest! The final list was:\n"<<this->OoI_manager_);
	this->mission_goals_.clear();
	tf::Point temp_point;
	geometry_msgs::Pose temp_pose;
	temp_pose.orientation.w = 1.0;
	while(!this->OoI_manager_.empty())
	{
		try
		{
			ObjectOfInterestManager::ObjectOfInterestEntry detection(this->OoI_manager_.getNearestNeighbor(temp_point));
			tf::pointTFToMsg(detection, temp_pose.position);
			this->OoI_manager_.removeOoI(detection);
			ROS_INFO_STREAM("I'm adding the following detection to Mission Goals:\n"<<temp_pose.position);
			this->mission_goals_.push_back(temp_pose);
		}
		catch(bool e)
		{
			ROS_ERROR("Something went wrong with getting a neighbor!");
		}
	}
}

void MissionPlanner::requestCollect()
{
	ROS_INFO_STREAM("Mission Planner Requesting Transition to COLLECT...");
	aero_srr_msgs::AeroState request;
	request.state = aero_srr_msgs::AeroState::COLLECT;
	this->requestStateTransition(request);
}

void MissionPlanner::requestNavObj()
{
	ROS_INFO_STREAM("Mission Planner Requesting Transition to NAVOBJ...");
	aero_srr_msgs::AeroState request;
	request.state = aero_srr_msgs::AeroState::NAVOBJ;
	this->requestStateTransition(request);
}

void MissionPlanner::requestHome()
{
	ROS_INFO_STREAM("Mission Planner Requesting Transition to HOME...");
	aero_srr_msgs::AeroState request;
	request.state = aero_srr_msgs::AeroState::HOME;
	this->requestStateTransition(request);
}

void MissionPlanner::requestStateTransition(aero_srr_msgs::AeroState& requested_state)
{
	aero_srr_msgs::StateTransitionRequestRequest request;
	aero_srr_msgs::StateTransitionRequestResponse response;
	request.requested_state = requested_state;
	if(this->state_request_client_.call(request, response))
	{
		if(response.success)
		{
			ROS_INFO_STREAM("Mission Planner Succesfully Moved to "<<(int)requested_state.state<<" !");
		}
		else
		{
			ROS_ERROR_STREAM("Mission Planner could not transition to "<<(int)requested_state.state<<": "<<response.error_message);
		}
	}
	else
	{
		ROS_ERROR_STREAM("Something went wrong trying to request state change!");
	}
}

void MissionPlanner::pause(bool enable)
{
	if(enable)
	{
		ROS_INFO_STREAM("Mission Planner Paused!");
		this->goal_timer_.stop();
	}
	else
	{
		ROS_INFO_STREAM("Mission Planner Freed!");
		this->goal_timer_.start();
	}
}
