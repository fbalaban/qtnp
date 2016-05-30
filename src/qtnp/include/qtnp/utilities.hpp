/**
 * @file /include/qtnp/utilities.hpp
 *
 * @brief Utility functions
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

/*****************************************************************************
** Namespaces
*****************************************************************************/
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>

#include "cdt_types.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/
typedef std::pair<CDT::Face_handle ,float> Distance_Entry;

namespace utilities {

/*****************************************************************************
** Implementation
*****************************************************************************/

inline double convert_range(double start_original, double end_original, double start_new, double end_new, double value){
    double scale = (double) (end_new - start_new) / (end_original - start_original);
    return (double)(start_new + ((value - start_original) * scale));
}

inline double smallest_distance(CDT::Point cgal_point1, CDT::Point cgal_point2, CDT::Point cgal_point3)
{
  double pleyraX = abs(cgal_point1.x() - cgal_point2.x());
  double pleyraY = abs(cgal_point1.y() - cgal_point2.y());
  double distance1 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  pleyraX = abs(cgal_point2.x() - cgal_point3.x());
  pleyraY = abs(cgal_point2.y() - cgal_point3.y());
  double distance2 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  pleyraX = abs(cgal_point3.x() - cgal_point1.x());
  pleyraY = abs(cgal_point3.y() - cgal_point1.y());
  double distance3 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  if (distance1 < distance2){
      if (distance1 < distance3){
          return distance1;
      }
      else {
          return distance3;
      }
  } else if (distance2 < distance3){
      return distance2;
  } else{
      return distance3;
  }
}

inline double biggest_distance(CDT::Point cgal_point1, CDT::Point cgal_point2, CDT::Point cgal_point3)
{
  double pleyraX = abs(cgal_point1.x() - cgal_point2.x());
  double pleyraY = abs(cgal_point1.y() - cgal_point2.y());
  double distance1 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  pleyraX = abs(cgal_point2.x() - cgal_point3.x());
  pleyraY = abs(cgal_point2.y() - cgal_point3.y());
  double distance2 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  pleyraX = abs(cgal_point3.x() - cgal_point1.x());
  pleyraY = abs(cgal_point3.y() - cgal_point1.y());
  double distance3 = sqrt(pow(pleyraX,2) + pow(pleyraY,2));

  if (distance1 > distance2){
      if (distance1 > distance3){
          return distance1;
      }
      else {
          return distance3;
      }
  } else if (distance2 > distance3){
      return distance2;
  } else{
      return distance3;
  }
}

inline geometry_msgs::Point face_points_to_center(CDT::Point point1, CDT::Point point2, CDT::Point point3){

  geometry_msgs::Point center;
  center.x =  ( (point1.x() + point2.x() + point3.x()) / 3);
  center.y =  ( (point1.y() + point2.y() + point3.y()) / 3);
  center.z = 0;

  return center;
}

inline geometry_msgs::Point cgal_point_to_ros_geometry_point(kernel_Point_2 cgal_point) {

  geometry_msgs::Point ros_point;
  ros_point.x = cgal_point.x();
  ros_point.y = cgal_point.y();
  ros_point.z = 0.0;

  return ros_point;
}

inline geometry_msgs::Point32 point_to_point_32(geometry_msgs::Point point) {

  geometry_msgs::Point32 point32;
  point32.x = point.x;
  point32.y = point.y;
  point32.z = point.z;

  return point32;
}

inline geometry_msgs::Point cgal_triangulation_point_to_ros_geometry_point(CDT::Point cgal_point, float elevation)
{
  geometry_msgs::Point ros_point;
  ros_point.x = cgal_point.x();
  ros_point.y = cgal_point.y();
  ros_point.z = elevation;

  return ros_point;
}

inline kernel_Point_2 ros_to_cgal_point(geometry_msgs::Point point){

  kernel_Point_2 cgal_point(point.x, point.y);/*
  cgal_point.x(point.x);
  cgal_point.y(point.y);*/

  return cgal_point;
}

// TODO: frame_id is hardcoded
inline geometry_msgs::PoseStamped build_pose_stamped(geometry_msgs::Point point_position){

  geometry_msgs::Pose pose;
  pose.position = point_position;
  pose.orientation.w = 0.0;

  geometry_msgs::PoseStamped pose_stamped;
  pose_stamped.pose = pose;
  pose_stamped.header.frame_id = "/my_frame";
  pose_stamped.header.stamp = ros::Time::now();

  return pose_stamped;

}

inline geometry_msgs::Point face_to_center(CDT &cdt, CDT::Face_handle face){

  // create a point for each of the edges of the face.
  CDT::Point point1 = cdt.triangle(face)[0];
  CDT::Point point2 = cdt.triangle(face)[1];
  CDT::Point point3 = cdt.triangle(face)[2];

  return utilities::face_points_to_center(point1, point2, point3);

}

inline double calculate_distance(geometry_msgs::Point center1, geometry_msgs::Point center2){

  return hypot(abs(center1.x - center2.x),abs(center1.y - center2.y));

}

inline bool distance_comparison (const Distance_Entry& i, const Distance_Entry& j) {
  if (i.first != j.first)
    return (i.second < j.second);
}

inline bool depth_comparison  (const Distance_Entry& i, const Distance_Entry& j) {
    return (i.first->info().depth < j.first->info().depth);
}

}
#endif // UTILITIES_HPP
