/**
 * @file /src/rviz_objects.cpp
 *
 * @brief Rviz elements
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>

#include "../include/qtnp/rviz_objects.hpp"

namespace qtnp {

/*****************************************************************************
** Implementation
*****************************************************************************/

void Rviz_objects::init(){

  polygon_ready = false;
  planning_ready = false;

  // TODO: replace with constant or UI selection
  edges.header.frame_id = polygonStamped.header.frame_id = center_points.header.frame_id =
          triangulation_mesh.header.frame_id = path.header.frame_id = "/my_frame";

  edges.header.stamp = polygonStamped.header.stamp = center_points.header.stamp =
          triangulation_mesh.header.stamp = path.header.stamp = ros::Time::now();

  // TODO: replace with constant or UI selection
  edges.ns = center_points.ns = triangulation_mesh.ns = "cgal_rviz_namespace";

  edges.action = center_points.action = triangulation_mesh.action = visualization_msgs::Marker::ADD;

  edges.pose.orientation.w = center_points.pose.orientation.w = triangulation_mesh.pose.orientation.w = 1.0;

  edges.id = 0;
  center_points.id = 1; // TODO: different for different agent?
  triangulation_mesh.id = 2;

  edges.type = center_points.type = visualization_msgs::Marker::POINTS;
  triangulation_mesh.type = visualization_msgs::Marker::TRIANGLE_LIST;

  // POINTS markers use x and y scale for width/height respectively (how big the point is)
  // 1 means 1 meter so 0.5 is 50cm
  edges.scale.x = 5; // TODO: replace with constant or UI selection
  edges.scale.y = 5; // TODO: replace with constant or UI selection

  triangulation_mesh.scale.x = 1; // TODO: replace with constant or UI selection
  triangulation_mesh.scale.y = 1; // TODO: replace with constant or UI selection
  triangulation_mesh.scale.z = 1; // TODO: replace with constant or UI selection

  center_points.scale.x = 3; // TODO: replace with constant or UI selection
  center_points.scale.y = 3; // TODO: replace with constant or UI selection

  edges.color.g = center_points.color.r = 1.0f; // TODO: replace with constant or UI selection
  edges.color.a = center_points.color.a = 1.0f; // TODO: replace with constant or UI selection

  triangulation_mesh.color.b = 1.0f; // TODO: replace with constant or UI selection
  triangulation_mesh.color.a = 1.0f; // TODO: replace with constant or UI selection
}

void Rviz_objects::push_edge_point(geometry_msgs::Point point){

    this->edges.points.push_back(point);

}

void Rviz_objects::push_polygon_point(geometry_msgs::Point32 point){

    this->polygon.points.push_back(point);

}

void Rviz_objects::push_center_point(geometry_msgs::Point point){

    this->center_points.points.push_back(point);

}

void Rviz_objects::push_mesh_point(geometry_msgs::Point point){

    this->triangulation_mesh.points.push_back(point);

}

void Rviz_objects::push_mesh_cell_color(std_msgs::ColorRGBA color){

    this->triangulation_mesh.colors.push_back(color);

}

void Rviz_objects::push_path_point(geometry_msgs::PoseStamped point){

    this->path.poses.push_back(point);

}

void Rviz_objects::clear_path(){

    this->path.poses.clear();

}

}  // namespace qtnp
