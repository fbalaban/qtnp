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
#include "constants.hpp"

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

//http://paulbourke.net/geometry/transformationprojection/ - Hammer-Aitoff coordinates
inline double normalize_latitude(double latitude, double longitude){

  double z = std::sqrt(1 + std::cos(latitude)*std::cos(longitude/2));

  return (std::cos(latitude)*std::sin(longitude/2)) / z;

}
//http://paulbourke.net/geometry/transformationprojection/ - Hammer-Aitoff coordinates
inline double normalize_longitude(double latitude, double longitude){

  double z = std::sqrt(1 + std::cos(latitude)*std::cos(longitude/2));
  double x = (std::cos(latitude)*std::sin(longitude/2)) / z;

  return (std::sin(latitude) / z);
}

//inline double convert_range_for_lat(double lat_min, double lat_max, double to_new_min, double to_new_max, double angle){
//    double scale = (double) (to_new_max - to_new_min) / (lat_max - lat_min);
//    return (double)(start_new + ((value - start_original) * scale));
//}

//inline double convert_range_for_lon(double start_original, double end_original, double start_new, double end_new, double value){
//    double scale = (double) (end_new - start_new) / (end_original - start_original);
//    return (double)(start_new + ((value - start_original) * scale));
//}

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

inline kernel_Point_2  point_2_to_kernel(CGAL::Point_2<K> point_2){

  kernel_Point_2 kernel_point(point_2.x(), point_2.y());
  return kernel_point;

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

// TODO frame_id is hardcoded
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

/// \brief Calculates distance between two ROS rviz points
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

inline double latitudeDisplacement (double initialLatitude, double meters){

    return initialLatitude + (((meters/1000.0) / constants::r_earth) * (180/constants::PI));

}

inline double longitudeDisplacement(double initialLongitude, double displacedLatitude, double meters){

    return initialLongitude + ((((meters/1000.0) / constants::r_earth) * (180/constants::PI)) /
                               cos(displacedLatitude * (constants::PI/180)));

}

}
#endif // UTILITIES_HPP
