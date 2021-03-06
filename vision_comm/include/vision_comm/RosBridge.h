/*
 * RosBridge.h
 *
 *  Created on: Jan 25, 2013
 *      Author: bpwiselybabu
 */

#ifndef ROSBRIDGE_H_
#define ROSBRIDGE_H_

#include "IOImages.h"
#include <vision_comm/IOImages.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

class RosBridge: public IOImages {

	ros::NodeHandle 					nh_;
	image_transport::ImageTransport 	it_;
	image_transport::CameraSubscriber 		subImg_;
	image_transport::Publisher 			pub_;
	bool 								newimg_;

	std::string 			frame_id_;

	void imageCb(const sensor_msgs::ImageConstPtr& msg,const sensor_msgs::CameraInfoConstPtr& cam_info);
public:
	RosBridge(std::string img, std::string out);
	RosBridge(std::string out, cv::Mat *img);
	RosBridge(cv::Mat *img,std::string topic_out);
	cv::Mat* getNextFrame();
	void publishFrame();
	std::string frame_id()
	{
             return(frame_id_);
	}
	virtual ~RosBridge();
};

#endif /* ROSBRIDGE_H_ */
