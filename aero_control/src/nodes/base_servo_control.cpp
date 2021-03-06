//============================================================================
// Name        : base_servo_control.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

/**
 * @file base_servo_control.cpp
 *
 * @date   Feb 20, 2013
 * @author parallels
 * @brief \todo
 */

//License File
#include <aero_control/base_servo_control.h>

using namespace aero_control;

BaseServoController::BaseServoController(ros::NodeHandle nh, ros::NodeHandle param_nh) {

	std::string desired_position("desired_position"); ///String containing the topic name for goal position
	std::string workspace_position("workspace_position"); ///String containing the topic name for workspace_position
	std::string base_velocity("base_velocity"); ///String containing the topic name for base_velocity
	std::string aero_state("aero_state"); ///String containing the topic name for AeroState
	std::string aero_state_transition("aero_state_transition"); ///String containing the topic name for AeroStateTransition

	//Grab the topic parameters, print warnings if using default values
	if (!param_nh.getParam(desired_position, desired_position))
		ROS_WARN(
				"Parameter <%s> Not Set. Using Default Desired Position Topic <%s>!", desired_position.c_str(), desired_position.c_str());
	if (!param_nh.getParam(base_velocity, base_velocity))
		ROS_WARN(
				"Parameter <%s> Not Set. Using Default Base Velocity Topic <%s>!", base_velocity.c_str(), base_velocity.c_str());

	if (!param_nh.getParam(workspace_position, workspace_position))
		ROS_WARN(
				"Parameter <%s> Not Set. Using Default Workspace Position Topic <%s>!", workspace_position.c_str(), workspace_position.c_str());

	if (!param_nh.getParam(aero_state, aero_state))
		ROS_WARN(
				"Parameter <%s> Not Set. Using Default Aero State Topic <%s>!", aero_state.c_str(), aero_state.c_str());

	if (!param_nh.getParam(aero_state_transition, aero_state_transition))
		ROS_WARN(
				"Parameter <%s> Not Set. Using Default Aero State Transition Topic <%s>!", aero_state_transition.c_str(), aero_state_transition.c_str());

//Print out received topics
	ROS_DEBUG("Using Desired Position Topic Name: <%s>", desired_position.c_str());
	ROS_DEBUG("Using Base Velocity Topic Name: <%s>", base_velocity.c_str());
	ROS_DEBUG("Using Workspace Position Topic Name: <%s>", workspace_position.c_str());
	ROS_DEBUG("Using Aero State Topic Name: <%s>", aero_state.c_str());
	ROS_DEBUG("Using Aero State Transition Topic Name: <%s>", aero_state_transition.c_str());

	ROS_INFO("Starting Up Base Servo Controller...");

	this->active_state = false;
	this->previous_state = aero_srr_msgs::AeroState::STARTUP;
	in_range_time = ros::Time().now();
	PID_start_time = ros::Time().now();

	/* Messages */
	this->desired_position_sub = nh.subscribe(desired_position, 1,
			&BaseServoController::DesiredPositionMSG, this);
	this->aero_state_sub = nh.subscribe(aero_state, 1, &BaseServoController::AeroStateMSG, this);
	this->workspace_postion_pub = nh.advertise<geometry_msgs::PoseStamped>(workspace_position, 1,
			true);
	this->base_velocity_pub = nh.advertise<geometry_msgs::Twist>(base_velocity, 2);
	/* Services */
	this->aero_state_transition_srv_client =
			nh.serviceClient<aero_srr_msgs::StateTransitionRequest>(aero_state_transition);
	/* Timers */
	this->error_update_timer = nh.createTimer(ros::Duration(0.1),
			&BaseServoController::ErrorUpdateTimerCallback, this);

	this->state_timeout_timer = nh.createTimer(ros::Duration(1),
			&BaseServoController::StateTimeoutTimerCallback, this);

	this->error_update_timer.stop();
	this->state_timeout_timer.stop();

	error_update_timer_flag = false;
	last_position_time = ros::Time().now();

	PID_X = new pid::PIDController(1, 0, 0, pos_err.x_err);
	PID_Y = new pid::PIDController(1, 0, 0, pos_err.y_err);

	linear_gain = 1;
	rotational_gain = 1;




	x_change = 0;
	y_change = 0;

	 forward_vel= 0;

	 rotational_vel= 0;

	this->workspace_pose.pose.position.x = 0.7;

	this->workspace_pose.pose.position.y = 0.1;
	this->workspace_pose.pose.position.z = 0;
	tf::Quaternion q;

	q.setRPY(0, 0, 0);

	tf::quaternionTFToMsg(q, workspace_pose.pose.orientation);
	workspace_pose.header.frame_id = "/base_footprint";

	workspace_pose.header.stamp = ros::Time::now();

	this->workspace_postion_pub.publish(this->workspace_pose);
	dr_call = boost::bind(&BaseServoController::PIDConfigCallback, this, _1, _2);
	dr_server.setCallback(dr_call);

}

BaseServoController::~BaseServoController() {
	delete PID_X;
	delete PID_Y;
}

void BaseServoController::BaseServoStart(void) {

	if (this->active_state == true) {
		if (error_update_timer_flag == false) {
			this->error_update_timer.start();
			this->error_update_timer_flag = true;
			this->PID_start_time = ros::Time().now();
			ROS_INFO("STARTING LOOP For Real");

		}
	}
}

void BaseServoController::BaseServoStop(void) {

	ROS_INFO("STOPPING LOOP");

	this->error_update_timer.stop();
	error_update_timer_flag = false;
	geometry_msgs::Twist base_velocity_msg;

	base_velocity_msg.linear.x = 0;

	base_velocity_msg.angular.z = 0;

	base_velocity_pub.publish(base_velocity_msg);

}

void BaseServoController::PIDConfigCallback(aero_control::BaseServoPIDConfig &config,
		uint32_t level) {
//	PID_X->SetPID(config.x_linear_P, config.x_linear_I, config.x_linear_D);
//	linear_gain = config.x_gain;
//	PID_Y->SetPID(config.y_linear_P, config.y_linear_I, config.y_linear_D);
//	rotational_gain = config.y_gain;
//
//	this->workspace_pose.pose.position.x = config.Workspace_X_Position;
//	this->workspace_pose.pose.position.y = config.Workspace_Y_Position;
//	workspace_pose.header.stamp = ros::Time::now();
//	this->workspace_postion_pub.publish(this->workspace_pose);
}

void BaseServoController::ErrorUpdateTimerCallback(const ros::TimerEvent&) {
	UpdateError();

	//if we don't see anything then stop moving
	if ((ros::Time().now().toSec() - last_position_time.toSec()) > 0.5) {
		BaseServoStop();
	}

	workspace_pose.header.stamp = ros::Time::now();
	this->workspace_postion_pub.publish(this->workspace_pose);
}

void BaseServoController::StateTimeoutTimerCallback(const ros::TimerEvent&) {
	//if timeout, go back to searching
	if (ros::Time().now().toSec() - last_position_time.toSec() > 20
			|| ros::Time().now().toSec() - PID_start_time.toSec() > 120) {
		aero_srr_msgs::StateTransitionRequest state_transition;

		state_transition.request.requested_state.state = previous_state;
		state_transition.request.requested_state.header.stamp = ros::Time().now();
		aero_state_transition_srv_client.call(state_transition);
	}

}

void BaseServoController::DesiredPositionMSG(
		const geometry_msgs::PoseStampedConstPtr& object_pose) {
	try {
		tf_listener.waitForTransform("/base_footprint", object_pose->header.frame_id,
				object_pose->header.stamp, ros::Duration(1.0));
		tf_listener.transformPose("/base_footprint", *object_pose, this->desired_pose);

		last_position_time = ros::Time().now();

		x_change = 0;
		y_change = 0;


		BaseServoStart();
	} catch (std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(1, e.what());
	}
}

void BaseServoController::AeroStateMSG(const aero_srr_msgs::AeroState& aero_state) {

	switch (aero_state.state) {

	case aero_srr_msgs::AeroState::COLLECT:
		this->PID_start_time = ros::Time().now();
		last_position_time = ros::Time().now();
		this->state_timeout_timer.start();
		this->active_state = true;
		break;
	case aero_srr_msgs::AeroState::SHUTDOWN:
		if (this->active_state == true) {
			this->active_state = false;

			BaseServoStop();
		}
		ros::shutdown();
		break;
	case aero_srr_msgs::AeroState::PAUSE:
		if (this->active_state == true) {
			this->active_state = false;

			BaseServoStop();
		}
		this->state_timeout_timer.stop();
		break;
	case aero_srr_msgs::AeroState::ERROR: //TODO Does this node need to do anything on error?
	default:
		if (this->active_state == true) {
			this->active_state = false;
			BaseServoStop();
		}

		previous_state = aero_state.state;
		break;
	}
}

void BaseServoController::UpdateError(void) {
	geometry_msgs::PoseStamped desired_error_pose;
	geometry_msgs::PoseStamped workspace_error_pose;
	try {
		tf_listener.waitForTransform("/base_footprint", this->desired_pose.header.frame_id,
				this->desired_pose.header.stamp, ros::Duration(0.1));
		tf_listener.transformPose("/base_footprint", this->desired_pose, desired_error_pose);

		workspace_pose.header.stamp = ros::Time::now();

		tf_listener.waitForTransform("/base_footprint", this->workspace_pose.header.frame_id,
				this->workspace_pose.header.stamp, ros::Duration(0.1));
		tf_listener.transformPose("/base_footprint", this->workspace_pose, workspace_error_pose);

		double dT = ros::Time::now().toSec()-PID_Time.toSec();

		x_change += forward_vel*dT*cos(rotational_vel*dT);
		y_change+=forward_vel*dT*sin(rotational_vel*dT);

		//x_change =0;
		//y_change=0;

		ROS_INFO("x_change = %f, y_change = %f",x_change,y_change);

		pos_err.x_err = desired_error_pose.pose.position.x-x_change - workspace_error_pose.pose.position.x;
		pos_err.y_err = desired_error_pose.pose.position.y-y_change - workspace_error_pose.pose.position.y;


		this->PID_Time = ros::Time::now();


		ROS_INFO("X_Err = %f, Y_Err = %f",pos_err.x_err,pos_err.y_err);

		if (pos_err.x_err < ErrorRange() && pos_err.y_err < ErrorRange()) {

			ROS_INFO("In Range");
			if (ros::Time().now().toSec() - in_range_time.toSec() > 5) {
				ROS_INFO("Moving on");

				aero_srr_msgs::StateTransitionRequest state_transition;

				state_transition.request.requested_state.state = aero_srr_msgs::AeroState::PICKUP;
				state_transition.request.requested_state.header.stamp = ros::Time().now();
				aero_state_transition_srv_client.call(state_transition);
			}
		} else {
			in_range_time = ros::Time().now();
		}

		UpdatePID();
	} catch (std::exception& e) {
		ROS_ERROR_STREAM_THROTTLE(1, e.what());
	}

}
void BaseServoController::UpdatePID(void) {


	forward_vel = PID_X->PIDUpdate(pos_err.x_err);
	forward_vel *= linear_gain;

	if (forward_vel > MaxLinearVel()) {
		forward_vel = MaxLinearVel();
	} else if (forward_vel < -MaxLinearVel()) {
		forward_vel = -MaxLinearVel();
	}


	rotational_vel = PID_Y->PIDUpdate(pos_err.y_err);
	rotational_vel *= rotational_gain;

	if (rotational_vel > MaxAngularVel()) {
		rotational_vel = MaxAngularVel();
	} else if (rotational_vel < -MaxAngularVel()) {
		rotational_vel = -MaxAngularVel();
	}



	geometry_msgs::Twist base_velocity_msg;

	ROS_INFO("Forward Vel = %f, Rotational Vel = %f",forward_vel,rotational_vel);

	base_velocity_msg.linear.x = forward_vel;

	base_velocity_msg.angular.z = rotational_vel;



	base_velocity_pub.publish(base_velocity_msg);

}

int main(int argc, char **argv) {

	/* Set up ROS */
	ros::init(argc, argv, "base_servo_control");
	ros::NodeHandle nh;
	ros::NodeHandle param_nh("~");

//create the arm object
	BaseServoController base_servo(nh, param_nh);

	ros::spin();
}

