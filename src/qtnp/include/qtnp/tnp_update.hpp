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

#include "mavros_msgs/WaypointList.h"

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
    void path_planning_coverage(std::pair<int, std::pair<double, double> > uas);
    void path_planning_to_goal(int uas, double lat, double lon);
    void partition(std::vector<std::pair<std::pair<double, double>, int> > uas_coords_with_percentage);

    void hop_cost_attribution(std::vector<std::pair<int, int> > id_cell_count);
    void coverage_cost_attribution();
    void path_to_goal(int uas, int goal_cell_id);
    void complete_path_coverage(std::pair<int, std::pair<double,double> > uas);

    void clear_aux();
    std::vector<int> count_agent_cells();
    int count_adjacent_cells(int from_agent, int to_agent);
    int get_max_coverage_depth_against_other(int from_agent, int to_agent);
    int get_lowest_coverage_depth_against_other(int from_agent, int to_agent);

    void exchange_agent_on_border_cells(int from_agent, int to_agent, int cells);

    int coordinates_to_cdt_cell_id(double lat, double lon);
    bool are_neighbors (int a, int b);
    std::vector<int> find_path(int a, int b);
    int find_neighbor(std::vector<int> &move_path, std::vector<int> &dead_end);
    void move_cells(std::pair<int, int> &mapA, std::pair<int,int> &mapB, std::vector<int> path);
    int move(int cells, std::vector<int> path);
    void moveCOV(int cells, std::vector<int> path);

    void make_mavros_waypoint_list(std::pair<double, double> uas_coords, std::vector<std::pair<double, double> > path);
    mavros_msgs::WaypointList get_waypoint_list(){ return m_waypoint_list; }

    void mesh_coloring();
    void init();

  private:

    // a reference to the rviz objects, responsible for visualization
    Rviz_objects &rviz_objects_ref;

    CDT cdt;
    CDT_Point_2_vector cdt_polygon_edges;
    Area_extremes area_extremes;

    mavros_msgs::WaypointList m_waypoint_list;

};

} // namespace qtnp

#endif /* qtnp_TNP_UPDATE_HPP_ */
