#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_broadcaster.h>

class OdomTF {

public:
	OdomTF() {
		sub = n.subscribe("/odom", 1, &OdomTF::callback, this);
	}

	void callback(const nav_msgs::Odometry::ConstPtr& msg) {
		// set header
        transformStamped.header.stamp = ros::Time::now();
        transformStamped.header.frame_id = "odom";
        transformStamped.child_frame_id = "base_footprint";
        // set x,y
        transformStamped.transform.translation.x = msg->pose.pose.position.x;
        transformStamped.transform.translation.y = msg->pose.pose.position.y;
        transformStamped.transform.translation.z = msg->pose.pose.position.z;
        // set theta
        transformStamped.transform.rotation.x = msg->pose.pose.orientation.x;
        transformStamped.transform.rotation.y = msg->pose.pose.orientation.y;
        transformStamped.transform.rotation.z = msg->pose.pose.orientation.z;
        transformStamped.transform.rotation.w = msg->pose.pose.orientation.w;
        // send transform
        br.sendTransform(transformStamped);
	}

private:
	ros::NodeHandle n;
    tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped transformStamped;
    ros::Subscriber sub;

};

int main(int argc, char **argv) {
	ros::init(argc, argv, "tf_broadcast");
	OdomTF odom_tf;
	ros::spin();
	return 0;
}
