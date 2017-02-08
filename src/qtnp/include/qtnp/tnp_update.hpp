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
#include "uas_model.hpp"

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
// TODO refactor cdt to m_cdt
class Tnp_update {
  public:

    static int globalCounter;
    // the constructor takes always a reference to the visualization objects
    Tnp_update(Rviz_objects& rvizReference) : rviz_objects_ref(rvizReference){}

    void perform_cdt(CDT &l_cdt, double angle_cons, double edge_cons);
    void initialize_cdt_struct(int agent_id, CDT &l_cdt, int initialize_base);
    void initialize_starting_positions(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas);
    void report_initial_partitioning(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas);

    void set_instance_uas_vector(std::vector<qtnp::Uas_model> &uas);

    void perform_polygon_definition(std::vector<Coordinates> placemarks_array,
                                    double angle_cons,
                                    double edge_cons,
                                    int lloyd_iterations);

    void path_planning_coverage(int uas, int mountain_sensitivity);
    void path_planning_to_goal(int uas, double lat, double lon);
    void partition(std::vector<Uas_model> &uas);

    void seperate_cdts(CDT &l_cdt, std::vector<Uas_model> &uas);
    CDT find_new_cdt_constrains(CDT &l_cdt, int agent_id);
    void replenish(std::vector<qtnp::Uas_model> &uas);
    void replenish_revisited(CDT &l_cdt, std::vector<Uas_model> &uas);

    void isotropic_cost_attribution(CDT &l_cdt);
    void isotropic_initial_partition(CDT &l_cdt, std::vector<qtnp::Uas_model > &uas);
    void hop_cost_attribution(std::vector<std::pair<int, int> > id_cell_count);
    void coverage_cost_attribution(CDT &l_cdt);
    void path_to_goal(int uas, int goal_cell_id);
    void complete_path_coverage(int uas, int mountain_sensitivity);

    void clear_aux(CDT &l_cdt);
    void clear_rviz_objects();

    std::vector<int> count_agent_cells(CDT &l_cdt);
    int count_adjacent_cells(int from_agent, int to_agent);
    int get_max_coverage_depth_against_other(int from_agent, int to_agent);
    int get_lowest_coverage_depth_against_other(int from_agent, int to_agent);

    void exchange_agent_on_border_cells(int from_agent, int to_agent, int cells);

    int coordinates_to_cdt_cell_id(double lat, double lon);
    bool are_neighbors (int a, int b);
    std::vector<int> find_path(int a, int b);
    int find_neighbor(std::vector<int> &move_path, std::vector<int> &dead_end);
    void move_cells(qtnp::Uas_model &toUAS, std::pair<int,int> &from_unassigned, std::vector<int> path);
    int moveAWP(int cells, std::vector<int> path);
    void moveCOV(Uas_model &Uas, int cells, std::vector<int> path);

    void make_mavros_waypoint_list(int uas, std::vector<std::pair<double, double> > path);
    mavros_msgs::WaypointList get_waypoint_list(){ return m_waypoint_list; }

    void mesh_coloring();
    void init();

    void set_lloyd_iter(int iterations){ lloyd_iter = iterations;}
    int get_lloyd_iter(){ return lloyd_iter; }

  private:

    // a reference to the rviz objects, responsible for visualization
    Rviz_objects &rviz_objects_ref;

    CDT m_cdt; // initial/global cdt
    std::vector<CDT> m_sub_cdt_vector; //sub-areas

    std::vector<qtnp::Uas_model> m_uas_vector;

    CDT_Point_2_vector cdt_polygon_edges;
    Area_extremes area_extremes;

    mavros_msgs::WaypointList m_waypoint_list;

    int lloyd_iter;

};

} // namespace qtnp

#endif /* qtnp_TNP_UPDATE_HPP_ */
