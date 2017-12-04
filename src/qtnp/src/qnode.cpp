/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>

#include "../include/qtnp/qnode.hpp"

#include "mavros/mavros.h"
#include "mavros_msgs/WaypointList.h"
#include "mavros_msgs/WaypointPush.h"
#include "mavros_msgs/WaypointClear.h"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

QNode::QNode(int argc, char** argv) :
	init_argc(argc),
    init_argv(argv),
    tnp_update(rviz_objects)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"qtnp");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.

    rviz_objects.init();

    ros::NodeHandle n;

    init_publishers(n);

	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"qtnp");
	if ( ! ros::master::check() ) {
		return false;
	}

    ros::start(); // explicitly needed since our nodehandle is going out of scope.

    rviz_objects.init();
    ros::NodeHandle n;

    init_publishers(n);
	start();
	return true;
}

void QNode::run() {

    //std::cout << "in run" << std::endl;

    ros::Rate loop_rate(1);
	int count = 0;
	while ( ros::ok() ) {

        // check if something has been called:
        if (rviz_objects.is_polygon_ready()){

          std_msgs::String msg;
          std::stringstream ss;
          ss << "Center points(waypoints): " << rviz_objects.get_center_points().points.size() <<
                ", CDT edges: " << rviz_objects.get_edges().points.size() ;
          msg.data = ss.str();
          chatter_publisher.publish(msg);
          log(Info,std::string("CDT: ")+msg.data);
          polygon_pub.publish(rviz_objects.get_polygonStamped());
          edges_pub.publish(rviz_objects.get_edges());
          center_pub.publish(rviz_objects.get_center_points());

          grid_marker_pub.publish(rviz_objects.get_grid_points());

          triangulation_mesh_pub.publish(rviz_objects.get_triangulation_mesh());
          rviz_objects.set_polygon_ready(false);
        }

        if (rviz_objects.is_planning_ready()){
          path_pub.publish(rviz_objects.get_path());
          std::cout << "Number of waypoints: " << rviz_objects.get_number_of_waypoints() << std::endl;
          // waypoints_s_client.publish(this->tnp_update.get_waypoint_list());
//          mavros_msgs::WaypointPush push_srv;
//          mavros_msgs::WaypointClear clear_wp;

//          for (int i=0; i< tnp_update.get_waypoint_list().waypoints.size(); i++){

//              push_srv.request.waypoints.push_back(tnp_update.get_waypoint_list().waypoints[i]);
//            waypoints_s_client.call(push_srv);
//            ros::Duration(0.3).sleep();

//          }

//          std::vector<mavros_msgs::Waypoint> the_list = push_srv.request.waypoints;
//          for (std::vector<mavros_msgs::Waypoint>::iterator it = the_list.begin();
//               it != the_list.end(); it++){
//              std::cout << "lat: " << it->x_lat << "lat: " << it->y_long << std::endl;
//          }
//            std::cout << "total:" << the_list.size() << std::endl;
//          waypoints_s_client.call(push_srv);

          // TODO define data file or log
          //dataFile << rviz_objects.get_number_of_waypoints() << " ";
          rviz_objects.set_planning_ready(false);
        }

        if (broadcasting_constraints){
            global_constraints_pub.publish(tnp_update.get_global_constraints());
        }

		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

void QNode::init_publishers(ros::NodeHandle n){

    // ROS communications
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    // publishing the edges of the initial area
    edges_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1000);
    // publishing the vertices of the initial area
    polygon_pub = n.advertise<geometry_msgs::PolygonStamped>("visualization_polygon", 1000);
    // publishing the mesh
    triangulation_mesh_pub = n.advertise<visualization_msgs::Marker>("triangulation_mesh", 30000);
    // publishing the centers of each cell of the triangulation (waypoints)
    center_pub = n.advertise<visualization_msgs::Marker>("center_points", 4500);
    // a dummy marker for grid visulizations
    grid_marker_pub = n.advertise<visualization_msgs::Marker>("dummy_grid_marker", 1000);
    // publishing the produced path(s)(?)
    path_pub = n.advertise<nav_msgs::Path>("path_planning", 1500);
    // publishing to airborne agents
    global_constraints_pub = n.advertise<qtnp_uav::CDTConstraints>("global_constraints", 100);
    // publishing waypoint lists in mavros nodes
    // waypoints_pub = n.advertise<mavros_msgs::WaypointList>("mavros/mission/waypoints", 150);
    // waypoints_s_client = n.serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push");
}

}  // namespace qtnp
