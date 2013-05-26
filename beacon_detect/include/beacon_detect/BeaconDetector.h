/*
 * BeaconDetector.h
 *
 *  Created on: May 6, 2013
 *      Author: bpwiselybabu
 */

#ifndef BEACONDETECTOR_H_
#define BEACONDETECTOR_H_
#include <opencv2/opencv.hpp>

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/PoseStamped.h>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

/* Headers April tag */
#include <AprilTags/TagDetector.h>
#include <AprilTags/Tag36h11.h>
#include <Eigen/Geometry>

/*Headers Aero */
#include <aero_srr_msgs/AeroState.h>

class BeaconDetector {
	//variables
	std::string 	cam_topic_;								//the camera topic name
	double 			tag_size_;								//need it so you can calculate the tf
	std::string 	robot_topic_;							//the topic that will send the robot state message
	cv::Mat			colorImg_;								//the Mat the defines the color image
	std::string 	parent_frame_;							//the name of the parent frame in the tf tree
	std::string 	sys_msgs_;								//the topic in which the system message for the status is broadcast
	cv::Mat			intrinsic_;								//the intrinsic parameter of the camera
	bool			newimg_;								//if the image is new and needs beacon detect to process it
	bool 			histeq_;								//if set to true, histogram equalization on the images is done
	bool			show_;									//if set to true, the results of the detected tag is displayed on screen
	bool			active_;								//determine if the beacon detector must be active use he topic

	//ros handles
	tf::TransformBroadcaster 			br_;							//the TF broadcaseter for ROS
	tf::TransformListener				tf_lr_;							//the TF listener so the node can extract the robot tf tree
	ros::NodeHandle						nh_;							//global node handle;
	image_transport::ImageTransport 	it_;							//the image transport handle
	image_transport::CameraSubscriber 	subImg_;						//the camera subscriber
	image_transport::Publisher 			pub_;							//a image publisher
	ros::Publisher 						pose_pub_;						//to publish pose of home

	//boost thread
	boost::mutex						imglock_;						//mutext to sync the image callback with the detector thread
	boost::thread						detector_thread_;				//boost detector thread handle

	std::vector<AprilTags::TagDetection> 	detections_;					//the extracted tags
	vector<pair<int,string> > 				constellation_;

	void imageCb(const sensor_msgs::ImageConstPtr& msg,const sensor_msgs::CameraInfoConstPtr& cam_info);
	void systemCb(const aero_srr_msgs::AeroStateConstPtr& status);

public:
	//initalization functions
	BeaconDetector();
	/*
	 * Function that will initialize all the ros parameters
	 */
	void getRosParam();
	/*
	 * This function is used to extract the constellation information from the config file
	 */
	void initConfiguration(string fname);

	//beacon detection functions
	/*
	 * this function is used to check if the detected tag is part of the home constellation
	 * and return the corresponding tag id
	 */
	string checkInConst(AprilTags::TagDetection tag);
	/*
	 * this function histogram equalizes the color image
	 */
	void histEq(cv::Mat &frame);
	/**
	 * this function is performs the actual detection of the beacons
	 */
	void detectBeacons();
	/**
	 * this function is used to display the result on an image
	 */
	void showResult();
	/*
	 * This function calculated the stamped pose for the robot to correct give the tag id
	 */
	geometry_msgs::Pose getRobotPose(string tag);

	virtual ~BeaconDetector();
};

#endif /* BEACONDETECTOR_H_ */
