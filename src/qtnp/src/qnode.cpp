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
#include "../include/qtnp/rviz_objects.hpp"
#include "../include/qtnp/tnp_update.hpp"

#include "mavros/mavros.h"
#include "mavros_msgs/WaypointList.h"
#include "mavros_msgs/WaypointPush.h"


/*****************************************************************************
** Implementation (includes two wrapper functions to overload the subscribers callbacks)
*****************************************************************************/

static void wrapper_path_planning_callback(void *pt2Object, const qtnp::InitialCoordinates::ConstPtr &msg){
    //explicitly cast to a pointer to class Tnp_update
    qtnp::Tnp_update *update = (qtnp::Tnp_update*) pt2Object;
    // and call the member function
    update->path_planning_callback(msg);
}
static void wrapper_polygon_def_callback(void *pt2Object, const qtnp::Placemarks::ConstPtr &msg){
    //explicitly cast to a pointer to class Tnp_update
    qtnp::Tnp_update *update = (qtnp::Tnp_update*) pt2Object;
    // and call the member function
    update->polygon_def_callback(msg);
}

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

    // when a path is requested, for agent i
    path_plan_callback bound_path_planning_callback = boost::bind(&wrapper_path_planning_callback, &tnp_update, _1); //--
    // when a new polygon is defined by a kml file
    poly_def_callback bound_polygon_def_callback = boost::bind(&wrapper_polygon_def_callback, &tnp_update, _1); //--

    ros::NodeHandle n;

    init_publishers(n);
    // subscribing to the tnp_release_spot, waiting for lon,lat and agent id in order to publish to the guys below
    home_spot_sub = n.subscribe("tnp_release_spot", 1000, bound_path_planning_callback);
    // define_poly. first step of node
    polygon_def_sub = n.subscribe("tnp_polygon_def", 1000, bound_polygon_def_callback);

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

    // when a path is requested, for agent i
    path_plan_callback bound_path_planning_callback = boost::bind(&wrapper_path_planning_callback, &tnp_update, _1); //--
    // when a new polygon is defined by a kml file
    poly_def_callback bound_polygon_def_callback = boost::bind(&wrapper_polygon_def_callback, &tnp_update, _1); //--

    ros::NodeHandle n;

    init_publishers(n);

    // subscribing to the tnp_release_spot (lon,lat, agent_id) for service calls
    home_spot_sub = n.subscribe("tnp_release_spot", 1000, bound_path_planning_callback);
    // subscribing to kml area definition for service calls
    polygon_def_sub = n.subscribe("tnp_polygon_def", 1000, bound_polygon_def_callback);

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
          rviz_objects.set_polygon_ready(false);
        }

        if (rviz_objects.is_planning_ready()){
          triangulation_mesh_pub.publish(rviz_objects.get_triangulation_mesh());
          path_pub.publish(rviz_objects.get_path());
          std::cout << "Number of waypoints: " << rviz_objects.get_number_of_waypoints() << std::endl;
          // waypoints_s_client.publish(this->tnp_update.get_waypoint_list());
          mavros_msgs::WaypointPush push_srv;
          push_srv.request.waypoints = tnp_update.get_waypoint_list().waypoints;

          std::vector<mavros_msgs::Waypoint> the_list = tnp_update.get_waypoint_list().waypoints;
          for (std::vector<mavros_msgs::Waypoint>::iterator it = the_list.begin();
               it != the_list.end(); it++){
              std::cout << "lat: " << it->x_lat << "lat: " << it->y_long << std::endl;
          }

          waypoints_s_client.call(push_srv);

          // TODO define data file or log
          //dataFile << rviz_objects.get_number_of_waypoints() << " ";
          rviz_objects.set_planning_ready(false);
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

    // Add your ros communications here.
    // this is just a string chatter
    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    // publishing the edges of the initial area
    edges_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
    // publishing the vertices of the initial area
    polygon_pub = n.advertise<geometry_msgs::PolygonStamped>("visualization_polygon", 10);
    // publishing the mesh
    triangulation_mesh_pub = n.advertise<visualization_msgs::Marker>("triangulation_mesh", 300);
    // publishing the centers of each cell of the triangulation (waypoints)
    center_pub = n.advertise<visualization_msgs::Marker>("center_points", 150);
    // publishing the produced path(s)(?)
    path_pub = n.advertise<nav_msgs::Path>("path_planning", 150);
    // publishing waypoint lists in mavros nodes
    // waypoints_pub = n.advertise<mavros_msgs::WaypointList>("mavros/mission/waypoints", 150);
    waypoints_s_client = n.serviceClient<mavros_msgs::WaypointPush>("/mavros/mission/push");
}

}  // namespace qtnp
