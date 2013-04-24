/*
 * test_tf_tree.cpp
 *
 *  Created on: Mar 25, 2013
 *      Author: srr
 */


#include<ros/ros.h>
#include<tf/transform_broadcaster.h>

class TestTF
{
public:
	TestTF(ros::NodeHandle& nh)
{
		timer = nh.createTimer(ros::Duration(1.0/100.0), &TestTF::broadcastTimer, this);
}

	void broadcastTimer(const ros::TimerEvent& event)
	{
		tf::Transform camera, armbase;
		camera.setOrigin(tf::Vector3(1.8161, 0, 0.6858));
		tf::Quaternion cam_q;
		cam_q.setEuler((-3.14159/2.0)+(-3.14159/6),0, 3*(-3.14159/2.0));
//		cam_q.setEuler(0.0,0.0,0.0);
		camera.setRotation(cam_q);
		broadcastCam.sendTransform(tf::StampedTransform(camera, ros::Time::now(),  "/world", "/stereo_bottom/center"));


		armbase.setOrigin(tf::Vector3(0, 0, .1229));
		armbase.setRotation(tf::Quaternion(0, 0, 0));
		broadcastArm.sendTransform(tf::StampedTransform(armbase, ros::Time::now(),  "/world", "/arm_base"));
	}

private:
	ros::Timer timer;
	tf::TransformBroadcaster broadcastCam;
	tf::TransformBroadcaster broadcastArm;
};



int main(int argc, char **argv)
{
	ros::init(argc, argv, "test_tf_tree");
	ros::NodeHandle nh;
	TestTF tf_node(nh);
	ros::spin();
}