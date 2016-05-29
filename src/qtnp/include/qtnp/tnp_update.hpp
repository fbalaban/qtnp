/**
 * @file /include/qtnp/tnp_update.hpp
 *
 * @brief Triangulation and planning functions
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Ifdefs
*****************************************************************************/
#ifndef qtnp_TNP_UPDATE_HPP_
#define qtnp_TNP_UPDATE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include "boost/ref.hpp"
#include "rviz_objects.hpp"
#include "cdt_types.hpp"

#include "qtnp/InitialCoordinates.h"
#include "qtnp/Coordinates.h"
#include "qtnp/Placemarks.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

/*****************************************************************************
** Types
*****************************************************************************/

// custom callback function for ROS listener
// -------------------------------------------- //
// http://answers.ros.org/question/11810/how-to-pass-arguments-tofrom-subscriber-callback-functions/
typedef const boost::function< void(const InitialCoordinates::ConstPtr &)> path_plan_callback;
typedef const boost::function< void(const Placemarks::ConstPtr &)> poly_def_callback;

// Custom vectors for path planning mainly
typedef std::pair<CDT::Face_handle ,float> Distance_Entry;
typedef std::vector<Distance_Entry> Distance_Vector;
typedef std::vector<CDT::Face_handle> Face_Handle_Vector;

// struct for the given area (kml) extremes. TODO: put area related structs in different file if a lot are gathered.
struct Area_extremes {
    double min_lat;
    double min_lon;
    double max_lat;
    double max_lon;
};

/*****************************************************************************
** Class
*****************************************************************************/
class Tnp_update {
  public:

    // the constructor takes always a reference to the visualization objects
    Tnp_update(Rviz_objects& rvizReference) : rviz_objects_ref(rvizReference){}

    void polygon_def_callback(const Placemarks::ConstPtr& msg);
    void perform_polygon_definition(std::vector<Coordinates> placemarks_array, double angle_cons, double edge_cons);

    void path_planning_callback(const InitialCoordinates::ConstPtr& msg);
    void path_planning_coverage();
    void path_planning_to_goal();
    void partition();

    void initialize_mesh(CDT &cdt);
    void hop_cost_attribution(CDT &cdt);
    void coverage_cost_attribution(CDT &cdt);
    void shortest_path_coverage(CDT &cdt, CDT::Face_handle &starter_face, int agent, int target_face_id);
    void complete_path_coverage(CDT &cdt, CDT::Face_handle &starter_face, int uav_id);

    //void wrapper_path_planning_callback(void* pt2Object, const InitialCoordinates::ConstPtr& msg);
    //void wrapper_polygon_def_callback(void* pt2Object, const Placemarks::ConstPtr& msg);

    void init();

  private:

    // a reference to the rviz objects, responsible for visualization
    Rviz_objects &rviz_objects_ref;

    CDT cdt;
    CDT_Point_2_vector cdt_polygon_edges;
    Area_extremes area_extremes;

};

} // namespace qtnp

#endif /* qtnp_TNP_UPDATE_HPP_ */
