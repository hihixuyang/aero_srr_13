/*
 * SyncStage.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: srr
 */

#include <object_locator/vision_pipeline/SyncStage.h>
#include <pluginlib/class_list_macros.h>
#include <sensor_msgs/image_encodings.h>

PLUGINLIB_DECLARE_CLASS(object_locator, SyncStage, object_locator::SyncStage,
		nodelet::Nodelet)

namespace enc = sensor_msgs::image_encodings;
using namespace object_locator;

void SyncStage::onInit()
{
	loadParams();
	registerTopics();
}

void SyncStage::loadParams()
{
	this->sync_input_topic_  ="/stereo_camera/stereo_sync";
	this->left_input_topic_  ="/stereo_camera/left/image_rect_color";
	this->right_input_topic_ ="/stereo_camera/right/image_rect_color";
	this->disparity_input_topic_ ="/stereo_camera/disparity";
	this->output_topic_="sync_stage/rect_pair";
	this->it_ = new image_transport::ImageTransport(this->getNodeHandle());
	gotLeft_ = false;
	gotRight_ = false;
	gotDisparity_ = false;

}

void SyncStage::registerTopics()
{
//	this->raw_image_sub_  = this->getNodeHandle().subscribe(this->sync_input_topic_,2,&SyncStage::imageCb,this);
	this->image_left_ = it_->subscribe(this->left_input_topic_,2,&SyncStage::leftImageCb,this);
	this->image_right_ = it_->subscribe(this->right_input_topic_,2,&SyncStage::rightImageCb,this);
//	this->disparity_ = this->getNodeHandle().subscribe(this->disparity_input_topic_,2,&SyncStage::disparityImageCb,this);
	this->sync_image_pub_ = this->getNodeHandle().advertise<object_locator::SyncImageMsg>(this->output_topic_,2);
}

void SyncStage::imageCb(const object_locator::SyncImageMsgConstPtr& msg)
{
	raw_images_ = *msg;
	gotLeft_ = true;
	gotImages();



}
//
void SyncStage::leftImageCb(const sensor_msgs::ImageConstPtr& msg)
{
	left_image_ = *msg;
//	left_info_  = *cam_info;
	gotLeft_ = true;
	gotImages();
}

void SyncStage::rightImageCb(const sensor_msgs::ImageConstPtr& msg)
{
	right_image_ = *msg;
//	right_info_  = *cam_info;
	gotRight_ = true;
	gotImages();
}

void SyncStage::disparityImageCb(const sensor_msgs::ImageConstPtr& msg)
{
	disparity_image_     = *msg;
//	NODELET_INFO_STREAM("encoding = " << disparity_image_.encoding);
	gotDisparity_ = true;
	gotImages();
}

void SyncStage::gotImages()
{
//	NODELET_INFO_STREAM("gotimages");
	if(gotLeft_ && gotRight_)
	{
//		cv_bridge::CvImagePtr left,right;
//		try {
//			left = cv_bridge::toCvCopy(left_image_, enc::MONO8);
//		} catch (cv_bridge::Exception& e) {
//			NODELET_ERROR("cv_bridge exception: %s", e.what());
//			return;
//		}
//		try {
//			right = cv_bridge::toCvCopy(right_image_, enc::MONO8);
//		} catch (cv_bridge::Exception& e) {
//			NODELET_ERROR("cv_bridge exception: %s", e.what());
//			return;
//		}
//		std::stringstream s,d;
//		s << "/home/srr/ObjectDetectionData/Left.jpg";
//		d << "/home/srr/ObjectDetectionData/Right.jpg";
//		cv::imwrite(s.str(), left->image);
//		cv::imwrite(d.str(), right->image);
		object_locator::SyncImageMsg msg;
		generateSyncMsg(msg);
		this->sync_image_pub_.publish(msg);
		gotLeft_ = false;
		gotRight_ = false;
//		gotDisparity_ = false;
	}
	else
	{
		NODELET_ERROR("Not Synced");
	}


}

void SyncStage::generateSyncMsg(object_locator::SyncImageMsg& msg)
{
//	msg.images  		   = raw_images_;
	msg.left_image  = left_image_;
//	msg.left_info   = left_info_;
	msg.right_image = right_image_;
//	msg.right_info  = right_info_;
//	msg.disparity_image  = disparity_image_;

}
