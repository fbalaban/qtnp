/**
/**
/**
 * @file /src/tnp_update.cpp
 *
 * @brief Triangulation and planning functions
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 
    Copyright (C) 2017 Fotios Balampanis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>

#include "../include/qtnp/tnp_update.hpp"

#include <std_msgs/String.h>


struct comp
{
    comp(int const& i) : _i(i) { }

    bool operator () (std::pair<int, int> const& p)
    {
        return (p.first == _i);
    }

    int _i;
};

inline double round( double val )
{
    if( val < 0 ) return ceil(val - 0.5);
    return floor(val + 0.5);
}

// Get current date/time, format is YYYY-MM-DD_HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H_%M_%S", &tstruct);

    return buf;
}

bool list_contains(int id, std::vector<std::pair<int,int> > list){

    std::vector<std::pair<int,int> >::iterator it = std::find_if(list.begin(), list.end(), comp(id));
    if (it != list.end()) return true;
    else return false;
}

void clear_list(std::vector<std::pair<int,int> > &list){

    for (int i=0; i<list.size(); i++){
        if (list[i].second == 0) {
            list.erase(list.begin()+i);
        }
    }
}

std::pair<int,int>& get_agent_pair_by_id(int id, std::vector<std::pair<int,int> > &map){

    std::vector<std::pair<int,int> >::iterator it = std::find_if(map.begin(), map.end(), comp(id));
    if (it != map.end()) return *it;
}


namespace qtnp {

    void Tnp_update::print_cdt_cells(const CDT &l_cdt){

        std::vector<int> cells;
        for (int i=0; i<9;i++){
            cells.push_back(0);
        }

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                      faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            if( (faces_iterator->is_in_domain()) && (faces_iterator->info().agent_id > 0)){
                //if cells[faces_iterator->info().agent_id] == 0;

                cells[faces_iterator->info().agent_id] += 1;

            }
        }
        for (int i=0; i<cells.size(); i++){
            std::stringstream ss;
            ss << "Agent " << i << " has: " << cells[i];
            ROS_INFO_STREAM(ss.str());
        }
    }

/*****************************************************************************
** Implementation
*****************************************************************************/

    // TODO V3 center points with cell ids var is a single var which contains ids and lat lon without any reference to which CDT belongs to
    // Change it so it constructs a center list based on CDT input because currently the list has up to 5000 ids for the cells

    int Tnp_update::coordinates_to_cdt_cell_id(double lat, double lon){

        std::vector<std::pair<int, geometry_msgs::Point> > id_center_list(this->rviz_objects_ref.get_center_points_with_cell_id());

        // TODO: they are upside down. if test file is correct, change lat, lon
        double cdt_lat = utilities::convert_range(this->area_extremes.min_lat,this->area_extremes.max_lat,
                                    constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lat_max,lon);//here
        double cdt_lon = utilities::convert_range(this->area_extremes.min_lon,this->area_extremes.max_lon,
                                    constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lon_max,lat); // and here

        kernel_Point_2 initial_position(cdt_lat, cdt_lon);

        int result_id(0);
        int comparison_id(0);

        //FIXME refactor conversion below, its a spaggeti shit
        for (int j=0; j<id_center_list.size(); j++){

            CGAL::Comparison_result result =
                    CGAL::compare_distance_to_point(
                        initial_position,
                          utilities::ros_to_cgal_point(id_center_list[j].second),
                            utilities::ros_to_cgal_point(id_center_list[j+1].second));

            if (result == CGAL::SMALLER){
                if (CGAL::compare_distance_to_point(
                            initial_position,
                              utilities::ros_to_cgal_point(id_center_list[j].second),
                                utilities::ros_to_cgal_point(id_center_list[comparison_id].second)) == CGAL::SMALLER){
                    comparison_id = j;
                    result_id = id_center_list[j].first;
                } else {
                    comparison_id = comparison_id;
                    result_id = id_center_list[comparison_id].first;
                }
            } else {
                if (CGAL::compare_distance_to_point(
                            initial_position,
                              utilities::ros_to_cgal_point(id_center_list[j].second),
                                utilities::ros_to_cgal_point(id_center_list[comparison_id].second)) == CGAL::SMALLER){
                    comparison_id = j;
                    result_id = id_center_list[j].first;
                } else {
                    comparison_id = comparison_id;
                    result_id = id_center_list[comparison_id].first;
                }

            }
        }
        return result_id;
    }

    // this is for the initial CDT partition, using member cdt
    std::vector<int> Tnp_update::find_path(int a, int b){

        std::vector<int> path;
        std::vector<int> blocked_path;
        bool found(false);
        path.push_back(a);

        int how_many_ones{0};
        int how_many_real{0};
        // TODO HERE INFINITE LOOP CANNOT FIND PATH, BLOCKED IF FULL --- ADDED CHECK FOR NOT PASSING THROUGH -1 (DONT KNOW IF MAKES SENSE)
        do {
            found = false;
            // TODO REMOVE THIS
            for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
              faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
                if (faces_iterator->info().agent_id == -1){
                    how_many_ones++;
                }
                if ( (faces_iterator->info().agent_id > 0)  && (faces_iterator->info().agent_id < 10) ){
                    how_many_real++;
                }
            }

            for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
              faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
                if (faces_iterator->info().agent_id == path[path.size()-1]){
                    for (int i=0; i<3; i++){
                        if (faces_iterator->neighbor(i)->info().agent_id == b) {
                            path.push_back(b);
                            return path;
                        } else if ( (faces_iterator->neighbor(i)->is_in_domain()) &&
                                !(std::find(path.begin(), path.end(), faces_iterator->neighbor(i)->info().agent_id) != path.end()) &&
                                (faces_iterator->neighbor(i)->info().agent_id != -1) &&
                                !(std::find(blocked_path.begin(), blocked_path.end(), faces_iterator->neighbor(i)->info().agent_id) != blocked_path.end() ) ){
                            path.push_back(faces_iterator->neighbor(i)->info().agent_id);
                            found = true;
                            break;
                        }
                    }
                }
                if (found) break;
            }
            how_many_ones = 0;
            how_many_real = 0;
            if ( (!found) && (path[path.size()-1] != a) ){
                blocked_path.push_back(path[path.size()-1]);
                path.erase(std::remove(path.begin(), path.end(), path[path.size()-1]), path.end());
            }

            mesh_coloring();
            rviz_objects_ref.set_polygon_ready(true);
        } while (true);
    }

    // counting cells in the initial cdt, for partitioning purposes.
    // TODO V2 should count area size, and probably have a sub_cdt for var
    std::vector<int> Tnp_update::count_agent_cells(CDT &l_cdt){

        std::vector<int> cells_per_agent;

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
          faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            if (faces_iterator->is_in_domain()){
                int agent = faces_iterator->info().agent_id;
                if (agent >= cells_per_agent.size()) {
                   for( int i=0; i < (agent - cells_per_agent.size() +1); i++){
                    cells_per_agent.push_back(0);
                    }
                }
                cells_per_agent[agent] = cells_per_agent[agent] + 1;
            }
        }

        return cells_per_agent;
    }

    // this is for the initial CDT partition, using member cdt
    bool Tnp_update::are_neighbors (int a, int b){
        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
          faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
            for (int i=0; i<3; i++){
                if ( (faces_iterator->info().agent_id == a) && (faces_iterator->neighbor(i)->info().agent_id == b) ) return true;
            }
        }
        return false;
    }

    // this is for the initial CDT partition, using member cdt
    // finds a neighbor in path, computing dead_end paths
    int Tnp_update::find_neighbor(std::vector<int> &move_path, std::vector<int> &dead_end){

        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
          faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
            if (faces_iterator->info().agent_id == move_path[move_path.size()-1]){
                for (int j=0; j<3; j++){
                    if (dead_end.empty()){
                        if (faces_iterator->neighbor(j)->is_in_domain() &&
                            !(std::find(move_path.begin(), move_path.end(), faces_iterator->neighbor(j)->info().agent_id) != move_path.end()) &&
                                faces_iterator->neighbor(j)->info().agent_id != faces_iterator->info().agent_id)
                            return faces_iterator->neighbor(j)->info().agent_id;
                } else if ( !(std::find(dead_end.begin(), dead_end.end(), faces_iterator->neighbor(j)->info().agent_id) != dead_end.end()) &&
                            !(std::find(move_path.begin(), move_path.end(), faces_iterator->neighbor(j)->info().agent_id) != move_path.end()) &&
                             faces_iterator->neighbor(j)->is_in_domain()) {
    //                        &&
    //                        !(faces_iterator->neighbor(j)->info().agent_id != faces_iterator->info().agent_id) ){
                        return faces_iterator->neighbor(j)->info().agent_id;
                    }
                }
            }
        }
        dead_end.push_back(move_path[move_path.size()-1]);
        move_path.erase(std::remove(move_path.begin(), move_path.end(), move_path[move_path.size()-1]), move_path.end());
        return -1;
    }

    void Tnp_update::move_cells(qtnp::Uas_model &toUAS, std::pair<int,int> &from_unassigned){//, std::vector<int> path){

        std::vector<int> path = find_path(toUAS.get_id(), -1);
        // why reversed?
        std::reverse(path.begin(), path.end());

        try {
            //std::cout << "Move cells: UAS " << toUAS.get_id() << " assigned cells BEFORE: " << toUAS.get_assigned_cells() << std::endl;
            moveCOV(toUAS, toUAS.get_remaining_cells(), path);
            //std::cout << "Move cells: UAS " << toUAS.get_id() << "assigned cells AFTER: " << toUAS.get_assigned_cells() << std::endl;
        } catch (const std::runtime_error& e) {
             std::cout << e.what();
        }
    }

    // sensors version: introducing cdt var for clearing aux
    void Tnp_update::clear_aux(CDT &l_cdt){
        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
          faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            faces_iterator->info().aux = false;
        }
    }

    // this is for the initial CDT partition, using member cdt
    // TODO V2 should count cells respecting area too, returning both
    int Tnp_update::count_adjacent_cells(int from_agent, int to_agent){

        int cells(0);
        clear_aux(m_cdt);
        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
                      faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
            for (int i=0; i<3; i++){
                if ( (faces_iterator->info().agent_id == from_agent) &&
                     (faces_iterator->neighbor(i)->info().agent_id == to_agent) &&
                     (!faces_iterator->neighbor(i)->info().aux) ) {
                    faces_iterator->neighbor(i)->info().aux = true;
                    cells++;
                }
            }
        }
        clear_aux(m_cdt);
        return cells;
    }

    // this is for the initial CDT partition, using member cdt
    // NOTE cdt should have coverage depth first
    int Tnp_update::get_max_coverage_depth_against_other(int from_agent, int to_agent){

        int coverage_depth(0);
        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
                      faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
            if ( (faces_iterator->info().agent_id == from_agent) &&
                 (faces_iterator->info().coverage_depth >= coverage_depth) ) {
                for (int i=0; i<3; i++){
                    if( faces_iterator->neighbor(i)->info().agent_id == to_agent){
                        coverage_depth = faces_iterator->info().coverage_depth;
                    }
                }
            }
        }
        return coverage_depth;
    }

    // this is for the initial CDT partition, using member cdt
    // NOTE cdt should have coverage depth first
    int Tnp_update::get_lowest_coverage_depth_against_other(int from_agent, int to_agent){

        int current_coverage_depth = get_max_coverage_depth_against_other(from_agent, to_agent);

        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
                      faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
            if (faces_iterator->info().agent_id == from_agent) {
                for (int z=0; z<3; z++){
                    if ( (faces_iterator->neighbor(z)->info().agent_id == to_agent) &&
                         (faces_iterator->info().coverage_depth <= current_coverage_depth) ){
                        current_coverage_depth = faces_iterator->info().coverage_depth;
                    }
                }
            }
        }
        return current_coverage_depth;
    }

    // this is for the initial CDT partition, using member cdt
    // TODO V2 introduce exchange based on area restriction, adding area var after cells
    // (or replacing cells with area)
    void Tnp_update::exchange_agent_on_border_cells(int from_agent, int to_agent, int cells){

        int current_coverage_depth = get_lowest_coverage_depth_against_other(from_agent, to_agent);
        bool not_inside(false);

        for (int i=0; i< cells; i++){
            not_inside = false;
            for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
              faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){

                if ( (faces_iterator->info().agent_id == from_agent) &&
                     (faces_iterator->info().coverage_depth == current_coverage_depth)){
                    for (int j=0; j<3; j++){
                        if ( (faces_iterator->neighbor(j)->info().agent_id == to_agent) && (i < cells) ){
                            faces_iterator->neighbor(j)->info().agent_id = from_agent;
                            faces_iterator->neighbor(j)->info().depth = faces_iterator->info().depth + 1;
                            faces_iterator->neighbor(j)->info().coverage_depth = current_coverage_depth + 10;
                            i++;
                            not_inside = true;
                        }
                    }
                }
            }
            if (!not_inside) {
                current_coverage_depth = get_lowest_coverage_depth_against_other(from_agent, to_agent);
                i--;
            }
        }
    }

    void Tnp_update::moveCOV(qtnp::Uas_model &uas, int cells, std::vector<int> path){

        path = find_path(path[0], path[path.size()-1]);

        //std::cout << "----- MoveCOV ----- " << std::endl;
        //std::cout << "Moving " << cells << " cells through path: [ ";
        //for (int i=0; i<path.size(); i++){
        //  std::cout << path[i] << " ";
        //}
        //std::cout << "]" << std::endl;

        for (int i = 0; i < path.size() - 1; i++){

            path = find_path(path[0], path[path.size()-1]);

            int adjacent_cells = count_adjacent_cells(path[i], path[i+1]);
            //std::cout << "adjacent cells counted: " << adjacent_cells << " between UAS " << path[i] << " and " << path[i+1] << std::endl;
            if (adjacent_cells >= cells){
                exchange_agent_on_border_cells(path[i+1], path[i], cells);
                if(path[i+1] == uas.get_id()) {
                    uas.set_assigned_cells(uas.get_assigned_cells() + cells);
                }
                //std::cout << "COV: Moved " << cells << " cells from agent " << path[i] << " to agent " << path[i+1] << std::endl;
            } else {
                std::vector<int> rest_of_the_path;
                for (int j = i; j < path.size(); j++) {
                    rest_of_the_path.push_back(path[j]);
                }

                //std::cout << "Recursion " << std::endl;
                moveCOV(uas, adjacent_cells, rest_of_the_path);
                cells = cells - adjacent_cells;
                //std::cout << "COV: tried to move " << adjacent_cells << " ADJACENT CELLS from agent " << path[i] << " to agent " << path[i+1] << std::endl;
                //std::cout << "COV: Those: " << cells << " cells remained, going out to: " << std::endl;
                i--;
            }
        }
    }

    // this is for the initial CDT partition, using member cdt
    // TODO V2 Remove (+++) or refactor
    int Tnp_update::moveAWP(int cells, std::vector<int> path){

        int cells_remaining = cells;
        //std::cout << "the path: [";
        for (int i=0; i<path.size(); i++){
            //std::cout << path[i] << " ";
        }
        //std::cout << "]" << std::endl;

        for (int i=0; i<path.size() -1; i++){

            cells_remaining = cells;
            bool found = false;
            int depth(-1); // FIXME magic number, chooses the closest to the agent. should find a better way. if the furthest is
            // chosen also creates some problems, but probably less. Possible solution in V2 is to remove AWP completely

            int that_depth_id(0);

            for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
              faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
              if (faces_iterator->info().agent_id == path[i]) {
                for (int z=0; z<3; z++){
                  if (faces_iterator->neighbor(z)->info().agent_id == path[i+1]){
                   if (faces_iterator->neighbor(z)->info().depth > depth){
                        that_depth_id = faces_iterator->neighbor(z)->info().id;
                        depth = faces_iterator->neighbor(z)->info().depth;
                        found = true;
                   }
                  }
                }
              }
            }

            if (found){
                for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
                  faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
                    if (faces_iterator->info().id == that_depth_id){
                        faces_iterator->info().agent_id = path[i];
                        faces_iterator->info().aux = true;
                        cells_remaining--;
                        break;
                    }
                }
            } else {
                path.erase(std::remove(path.begin(), path.end(), path[i+1]), path.end());
                i--;
                continue;
            }

            for (int j=1; j<cells; j++){
                for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
                  faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
                    if ( (faces_iterator->info().agent_id == path[i]) && (faces_iterator->info().aux == true) ){
                        for (int z=0; z<3; z++){
                            if (faces_iterator->neighbor(z)->info().agent_id == path[i+1] && cells_remaining > 0){
                                faces_iterator->neighbor(z)->info().agent_id = path[i];
                                faces_iterator->neighbor(z)->info().aux = true;
                                faces_iterator->info().aux = false;
                                j++;
                                cells_remaining--;
                            }
                        }
                    }
                }
            }

            clear_aux(m_cdt);

            //std::cout << "tried to move " << cells << " cells from agent " << path[i+1] << " to agent " << path[i] << std::endl;
            //std::cout << cells_remaining << " cells remained somewhere.." << std::endl;
            if (cells_remaining > 0) {
                std::vector<int> remaining_vector;
                remaining_vector.push_back(path[i]);
                if (are_neighbors(path[i],path[i+1])){
                    remaining_vector.push_back(path[i+1]);
                    cells_remaining = moveAWP(cells_remaining, remaining_vector);
                }
//                else {
//                    path.erase(std::remove(path.begin(), path.end(), path[i+1]), path.end());
//                    i--;
//                    continue;
//                }

                if (cells_remaining > 0){
                    //std::cout << "these cells remain:" << cells_remaining << std::endl;

                      std::vector<int> new_path = find_path(path[i], path[i+1]);
                      cells_remaining = moveAWP(cells_remaining, new_path);
                }
            }
        }
        return cells_remaining;
    }

    void Tnp_update::clear_rviz_objects(){
        rviz_objects_ref.clear_edges();
        rviz_objects_ref.clear_center_points();
        rviz_objects_ref.clear_center_points_with_cell_id();
    }

    // clearing member cdt as also as visualizations
    void Tnp_update::init(){

        m_cdt.clear();
        cdt_polygon_edges.clear();
        clear_rviz_objects();

        area_extremes.max_lat = -constants::max_lat;
        area_extremes.min_lat = -constants::min_lat;
        area_extremes.max_lon = -constants::max_lon;
        area_extremes.min_lon = -constants::min_lon;
    }


    // angle constrain is static in this version
    void Tnp_update::perform_cdt(CDT &l_cdt, double angle_cons, double edge_cons){

        std::cout << currentDateTime() << " Started CDT perform" << std::endl;

        // INFO: edge constrain is converted before function to a CGAL/RVIZ metric. meters->cgal/rviz points
        double crAngle = angle_cons;// 0.125; -- the default angle criteria
        double crEdge = edge_cons;
        std::cout << "Number of vertices before meshing and refining: " << l_cdt.number_of_vertices() << " angle:" << crAngle << " edge: " << crEdge << " " << std::endl;
        Mesher mesher(l_cdt);
        //mesher.refine_mesh();
        //std::cout << "Number of vertices after creating mesher: " << l_cdt.number_of_vertices() << std::endl;
        //std::cout << "Meshing again with new criteria..." << std::endl;

        mesher.set_criteria(Criteria(crAngle, crEdge));
        mesher.refine_mesh();
        std::cout << "Number of vertices after meshing and refining with new criteria: " << l_cdt.number_of_vertices() << std::endl;

        CGAL::lloyd_optimize_mesh_2(l_cdt,
                                    CGAL::parameters::max_iteration_number = get_lloyd_iter());

        //std::cout << "Number of vertices AFTER LLOYD (" << get_lloyd_iter() << " iterations): " << l_cdt.number_of_vertices() << std::endl;
        std::cout << currentDateTime() << " Ended CDT perform" << std::endl;

    }

    void Tnp_update::initialize_cdt_struct(int agent_id, CDT &l_cdt, int initialize_base){

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

          if (faces_iterator->is_in_domain()){

            faces_iterator->info().initialize(agent_id, initialize_base);

            CDT::Point point1 = l_cdt.triangle(faces_iterator)[0];
            CDT::Point point2 = l_cdt.triangle(faces_iterator)[1];
            CDT::Point point3 = l_cdt.triangle(faces_iterator)[2];
            geometry_msgs::Point center = utilities::face_points_to_center(point1, point2, point3);
            faces_iterator->info().center_lat = utilities::convert_range(constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lat_max,
                                                                         area_extremes.min_lat,area_extremes.max_lat,center.x);
            faces_iterator->info().center_lon = utilities::convert_range(constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lon_max,
                                                                         area_extremes.min_lon,area_extremes.max_lon,center.y);
            rviz_objects_ref.push_center_point(center);
            rviz_objects_ref.push_center_point_with_cell_id(initialize_base,center);

            initialize_base++;
          }
        }
        // this is great
        geometry_msgs::Point grid_point1; grid_point1.x = 15; grid_point1.y = 15; grid_point1.z = 0;
        rviz_objects_ref.push_grid_point(grid_point1);

        for (int i= 0; i<17; i++){
            for (int j= 0; j<17; j++){
                grid_point1.x = grid_point1.x + 30;
                rviz_objects_ref.push_grid_point(grid_point1);
            }
            grid_point1.y = grid_point1.y + 30;
            grid_point1.x = -15;
        }
    }

    void Tnp_update::initialize_starting_positions(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas){

        // the jumps agent for path tracking
        int jumps_ad = 1;

        // TODO maybe add CDT cell id to either Position or UAS model.
        // Probably position to each position to have a respective cell.
        for (int i=0; i<uas.size(); i++){

            int starter_cell_id = coordinates_to_cdt_cell_id(uas[i].get_initial_position().get_latitude(),
                                                       uas[i].get_initial_position().get_longitude());
            if (uas.size() == 1){
                int total_cells(0);
                for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                    faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
                    if (faces_iterator->is_in_domain()){
                        total_cells++;
                    }
                }
                uas[i].set_capability_cells(total_cells);
                uas[i].set_assigned_cells(0);
            } else {
                uas[i].set_capability_cells( ( (uas[i].get_autonomy() *
                                                rviz_objects_ref.count_cells()) /
                                                100.0) +
                                                0.3 );
                uas[i].set_assigned_cells(0);
            }
            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
              if ( faces_iterator->info().id == starter_cell_id) {
                  faces_iterator->info().numbered = true;
                  faces_iterator->info().depth = 1;
                  faces_iterator->info().agent_id = uas[i].get_id();
                  uas[i].increase_assigned_cells();

                  for (int j=0; j<3; j++){
                      faces_iterator->neighbor(j)->info().jumps_agent_id = jumps_ad;
                      jumps_ad++;
                  }
              }
              if ( !(faces_iterator->is_in_domain()) ) {
                  faces_iterator->info().agent_id = -99;
              }
            }
        }
    }

    // THIS IS THE INITIAL polygon definition has to do with kml and rviz so using member cdt
    void Tnp_update::perform_polygon_definition(std::vector<Coordinates> placemarks_array, double angle_cons, double edge_cons, int lloyd_iterations){

        ROS_INFO_STREAM("Got a new polygon definition");

        init();
        set_lloyd_iter(lloyd_iterations);

        std::cout << std::setprecision(7);

        for (std::vector<Coordinates>::iterator it = placemarks_array.begin(); it<placemarks_array.end(); it++){

            int size = it->latitude.size();
            std::vector<double> latitude_array(size);
            std::vector<double> longitude_array(size);

            latitude_array  = it->latitude;
            longitude_array = it->longitude;

            if (it->placemark_type == "constrain"){
                for (int i=0; i<size; i++){
                    area_extremes.max_lat = latitude_array[i] > area_extremes.max_lat ? latitude_array[i] : area_extremes.max_lat;
                    area_extremes.max_lon = longitude_array[i] > area_extremes.max_lon ? longitude_array[i] : area_extremes.max_lon;

                    area_extremes.min_lat = latitude_array[i] < area_extremes.min_lat ? latitude_array[i] : area_extremes.min_lat;
                    area_extremes.min_lon = longitude_array[i] < area_extremes.min_lon ? longitude_array[i] : area_extremes.min_lon;
                }
            }
        }

         // -------------- TODO DELETE AFTER NORMALIZE --------------------------------//
        double max_lat_rad = (area_extremes.max_lat * constants::PI) / 180.0;
        double max_lon_rad = (area_extremes.max_lon * constants::PI) / 180.0;
        double min_lat_rad = (area_extremes.min_lat * constants::PI) / 180.0;
        double min_lon_rad = (area_extremes.min_lon * constants::PI) / 180.0;

        // points: 1:max_lat/max_lon, 2:min_lat/min_lon, 3:max_lat/min_lon
        // distance between points 2-3 and 1-3
        double distance_x_lat_23 = max_lat_rad - min_lat_rad;
        double distance_y_lon_23 = 0.0;

        double distance_x_lat_13 = 0.0;
        double distance_y_lon_13 = min_lon_rad - max_lon_rad;

        double angular_a_23 = (std::pow(std::sin(distance_x_lat_23/2),2)) + std::cos(min_lat_rad) * std::cos(max_lat_rad) * std::pow(std::sin(distance_y_lon_23/2),2);
        double angular_a_13 = (std::pow(std::sin(distance_x_lat_13/2),2)) + std::cos(max_lat_rad) * std::cos(max_lat_rad) * std::pow(std::sin(distance_y_lon_13/2),2);

        double angular_c_23 = 2*std::atan2(std::sqrt(angular_a_23), std::sqrt(1-angular_a_23));
        double angular_c_13 = 2*std::atan2(std::sqrt(angular_a_13), std::sqrt(1-angular_a_13));

        double distance_23 = constants::r_earth_m * angular_c_23;
        double distance_13 = constants::r_earth_m * angular_c_13;

        // TODO LOGOS CHECK IF MAKES SENSE
        double logos = distance_23 > distance_13 ? distance_13/distance_23 : distance_23/distance_13;
        // multiply FoV with meter conversion to find CDT constrain
        double meter_conversion = distance_23 > distance_13 ? constants::rviz_range_max * logos : constants::rviz_range_max * logos;

//        if (distance_23 > distance_13){
//            rviz_objects_ref.set_rviz_range(constants::rviz_range_max,constants::rviz_range_max * logos, meter_conversion);
//        }
//        else {
//            rviz_objects_ref.set_rviz_range(constants::rviz_range_max * logos,constants::rviz_range_max, meter_conversion);
//        }

            rviz_objects_ref.set_rviz_range(constants::rviz_range_max,constants::rviz_range_max, meter_conversion);

            //        if (std::abs( distance_23 ) > std::abs(distance_13) ){
//            double top_lon_range = (constants::rviz_range_max * distance_13) / distance_23;
//            rviz_objects_ref.set_rviz_range(constants::rviz_range_max, top_lon_range, meter_conversion);
//        }
//        else {
//            double top_lat_range = (constants::rviz_range_max * distance_23) / distance_13;
//            rviz_objects_ref.set_rviz_range(top_lat_range,constants::rviz_range_max, meter_conversion);
//        }
        // -----------------------------------------------------------------------------------//

        // TODO PROBABLY IN NORMALIZATION
//            // normalizing area extremes to -1 1
//            double normalized_lat = utilities::normalize_latitude(area_extremes.max_lat, area_extremes.max_lon);
//            double normalized_lon = utilities::normalize_longitude(area_extremes.max_lat, area_extremes.max_lon);
//            area_extremes.max_lat = normalized_lat;
//            area_extremes.max_lon = normalized_lon;

//            normalized_lat = utilities::normalize_latitude(area_extremes.min_lat, area_extremes.min_lon);
//            normalized_lon = utilities::normalize_longitude(area_extremes.min_lat, area_extremes.min_lon);
//            area_extremes.min_lat = normalized_lat;
//            area_extremes.min_lon = normalized_lon;


        // TODO NOW: add list of seeds in global class or somewhere in order for the sub cdts to inherit the holes
        std::list<CDT::Point> list_of_seeds;
        for (std::vector<qtnp::Coordinates>::iterator it = placemarks_array.begin(); it<placemarks_array.end(); it++){

            int size = it->longitude.size();
            std::vector<double> longitude_array(size);
            std::vector<double> latitude_array(size);
            bool is_an_obstacle = (it->placemark_type == "hole") ? true :false;
            //
            if (is_an_obstacle) list_of_seeds.push_back(CDT::Point(
                        utilities::convert_range(area_extremes.min_lat,area_extremes.max_lat,
                                    constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lat_max,it->seed_latitude),
                        utilities::convert_range(area_extremes.min_lon,area_extremes.max_lon,
                                    constants::rviz_range_min,rviz_objects_ref.get_rviz_view().lon_max,it->seed_longitude)));

            longitude_array = it->longitude;
            latitude_array  = it->latitude;

            for (int i=1; i<size; i++){

                double previous_latitude = utilities::convert_range(area_extremes.min_lat,
                                                                    area_extremes.max_lat,
                                                                    constants::rviz_range_min,
                                                                    rviz_objects_ref.get_rviz_view().lat_max,latitude_array[i-1]);
                double previous_longitude = utilities::convert_range(area_extremes.min_lon,
                                                                     area_extremes.max_lon,
                                                                     constants::rviz_range_min,
                                                                     rviz_objects_ref.get_rviz_view().lon_max,longitude_array[i-1]);
                double current_latitude = utilities::convert_range(area_extremes.min_lat,
                                                                   area_extremes.max_lat,
                                                                   constants::rviz_range_min,
                                                                   rviz_objects_ref.get_rviz_view().lat_max,latitude_array[i]);
                double current_longitude = utilities::convert_range(area_extremes.min_lon,
                                                                    area_extremes.max_lon,
                                                                    constants::rviz_range_min,
                                                                    rviz_objects_ref.get_rviz_view().lon_max,longitude_array[i]);

                CDT::Vertex_handle va = m_cdt.insert(CDT::Point(previous_latitude,previous_longitude));
                CDT::Vertex_handle vb = m_cdt.insert(CDT::Point(current_latitude,current_longitude));
                m_cdt.insert_constraint(va,vb);

                if (!is_an_obstacle){
                    cdt_polygon_edges.push_back
                            (kernel_Point_2(previous_latitude,previous_longitude));
                    rviz_objects_ref.push_edge_point
                            (utilities::cgal_point_to_ros_geometry_point(kernel_Point_2(previous_latitude,previous_longitude)));
                    cdt_polygon_edges.push_back
                            (kernel_Point_2(current_latitude,current_longitude));
                    rviz_objects_ref.push_polygon_point
                            (utilities::point_to_point_32(utilities::cgal_point_to_ros_geometry_point
                                               (kernel_Point_2(current_latitude,current_longitude))));
                }
            }
        }
        std::cout << "The edge input was: " << edge_cons << " meters";
        edge_cons = edge_cons;// TODO: correct! * rviz_objects_ref.get_meter_conversion();
        std::cout << " and has been converted to " << edge_cons << " CGAL/RVIZ units (maximum 500)" << std::endl;

        // NOTE: gets the greatest FoV out of the collection of UASs in the UI table
        perform_cdt(m_cdt, angle_cons, edge_cons);

        //  Adding the seeds which define the holes.
        if (!list_of_seeds.empty()){
            //std::cout << "Refining and meshing the domain including seeds defining holes" << std::endl;
            CGAL::refine_Delaunay_mesh_2(m_cdt, list_of_seeds.begin(), list_of_seeds.end(), Criteria(angle_cons, edge_cons));
            //std::cout << "Number of vertices after meshing CDT refining and seeding holes: " << m_cdt.number_of_vertices() << std::endl;
        }

        int init_base = 0;
        initialize_cdt_struct(-1, m_cdt, init_base);
        rviz_objects_ref.set_polygon_ready(true);
    }

    // TODO qtnp_uav put the final contrainTs list to a global or not vector
    // which is converted to a ROS type message along with the UAVid.
    // After the partition, each UAV will CDT its own list (not on the initial
    // communication/mission start). If the list (global constraints list/CDT)
    // is updated by some change or if one UAV is down, someone (the gcs maybe?)
    // is responsible for recalculating the constrainTs list vector. If the change is
    // in the local plan, the UAV should also re-CDT the area.
    CDT Tnp_update::find_new_cdt_constrains(CDT &l_cdt, int agent_id){


        // qtnp_uav::GlobalConstraints global_constraints <-- this is where you push all agents;
        qtnp_uav::CDTConstraints current_cdt;
        current_cdt.uav_id = agent_id;
        qtnp_uav::Coordinates that_constraint;

        std::cout << currentDateTime() << " Started Finding new CDT for UAV: " << agent_id << std::endl;

        std::set< std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > > outer_triangle_vertices;
        std::set< std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > > inner_triangle_vertices;
        std::vector< std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > > constrains_list;

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

            if (faces_iterator->info().agent_id == agent_id){

                CGAL::Point_2<K> vertex1 = l_cdt.triangle(faces_iterator)[0];
                CGAL::Point_2<K> vertex2 = l_cdt.triangle(faces_iterator)[1];
                CGAL::Point_2<K> vertex3 = l_cdt.triangle(faces_iterator)[2];
                // TODO V3 -> replace these pairs with CGAL::Vector_2 which is used to represent segments
                std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > cw_segment_1(vertex1, vertex2);
                std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > cw_segment_2(vertex2, vertex3);
                std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > cw_segment_3(vertex3, vertex1);

                if (faces_iterator->info().coverage_depth == constants::coverage_depth_max)
                {
                    outer_triangle_vertices.insert(cw_segment_1);
                    outer_triangle_vertices.insert(cw_segment_2);
                    outer_triangle_vertices.insert(cw_segment_3);
                } else
                {
                    std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > ccw_segment_1(vertex1, vertex2);
                    std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > ccw_segment_2(vertex2, vertex3);
                    std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > ccw_segment_3(vertex3, vertex1);

                    inner_triangle_vertices.insert(cw_segment_1);
                    inner_triangle_vertices.insert(cw_segment_2);
                    inner_triangle_vertices.insert(cw_segment_3);

                    inner_triangle_vertices.insert(ccw_segment_1);
                    inner_triangle_vertices.insert(ccw_segment_2);
                    inner_triangle_vertices.insert(ccw_segment_3);
                }
            }
        }

        bool found_it(false);

        // eliminating "d" edges of two outer adjacent triangles
        //
        //                  /|\             /
        //                 / | \            /
        //       outer->  / d|  \ <-outer   /
        //               /___|___\          /
        //
        for(std::set<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator
            it = outer_triangle_vertices.begin(); it!= outer_triangle_vertices.end();){
            found_it = false;
            for(std::set<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator
                it2 = it; ++it2 != outer_triangle_vertices.end();){

                if( ( (it->first.x() == it2->first.x()) && (it->first.y() == it2->first.y()) &&
                      (it->second.x() == it2->second.x()) && (it->second.y() == it2->second.y()) ) ||
                    ( (it->first.x() == it2->second.x()) && (it->first.y() == it2->second.y()) &&
                      (it->second.x() == it2->first.x()) && (it->second.y() == it2->first.y()) ) ) {
                    it = outer_triangle_vertices.erase(it);
                    outer_triangle_vertices.erase(it2);
                    found_it = true;
                    break;
                }
            }
            if (!found_it) ++it;
        }

        // eliminating "a" and "b" edges of an outer and inner triangles
        //
        //                  /|\             /
        //                 / | \            /
        //       outer->  / a|  \ <-inner   /
        //               /___|___\          /
        //               \ b |              /
        //                \  |              /
        //       inner->   \ |              /
        //                  \|              /
        //
        for(std::set<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator
            it = outer_triangle_vertices.begin(); it!= outer_triangle_vertices.end();){
            found_it = false;
            for(std::set<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator
                it2 = inner_triangle_vertices.begin(); it2 != inner_triangle_vertices.end(); ++it2){

                if( ( (it->first.x() == it2->first.x()) && (it->first.y() == it2->first.y()) &&
                      (it->second.x() == it2->second.x()) && (it->second.y() == it2->second.y()) ) ||
                    ( (it->first.x() == it2->second.x()) && (it->first.y() == it2->second.y()) &&
                      (it->second.x() == it2->first.x()) && (it->second.y() == it2->first.y()) ) ){
                    it = outer_triangle_vertices.erase(it);
                    found_it = true;
                    break;
                }
            }
            if (!found_it) ++it;
        }

        std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > new_item(outer_triangle_vertices.begin()->first,
                                                                outer_triangle_vertices.begin()->second);

        // TODO THIS MIGHT BE UPSIDE DOWN
        that_constraint.placemark_type = "constrain";
        current_cdt.constraints.push_back(that_constraint);

        global_constraints.CDTS.push_back(current_cdt);

        // the constraints message must have pairs of vertex handles not lat lon.
        // it should also have a way to transform again the cdt metric to lat lon..

        //that_constraint.latitude.push_back(outer_triangle_vertices.begin()->first);
        //that_constraint.latitude.push_back(outer_triangle_vertices.begin()->second);

        constrains_list.push_back(new_item);

        do {
            std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > &current_item = constrains_list.back();

            for(std::set<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator
                it = outer_triangle_vertices.begin(); it!= outer_triangle_vertices.end(); it++){
                if( (it->first.x() == current_item.second.x()) && (it->first.y() == current_item.second.y()) ) {
                    std::pair<CGAL::Point_2<K> ,CGAL::Point_2<K> > item(it->first, it->second);
                    constrains_list.push_back(item);
                }
            }
        } while (outer_triangle_vertices.size() > constrains_list.size());

        constrains_list.push_back(new_item);

        int counter(0);
        CDT sub_cdt;

        for(std::vector<std::pair<CGAL::Point_2<K>,CGAL::Point_2<K> > >::iterator it = constrains_list.begin(); it!= constrains_list.end(); ++it){
            //std::cout << "unique segment: Ax:" << it->first.x() << " Ay: " << it->first.y() << " Bx: " << it->second.x() << " By: " << it->second.y() << std::endl;
            counter++;
            CDT::Vertex_handle va = sub_cdt.insert(it->first);
            CDT::Vertex_handle vb = sub_cdt.insert(it->second);
            sub_cdt.insert_constraint(va,vb);
            cdt_polygon_edges.push_back
                    (utilities::point_2_to_kernel(it->first));
            rviz_objects_ref.push_edge_point
                    (utilities::cgal_point_to_ros_geometry_point(utilities::point_2_to_kernel(it->first)));
            cdt_polygon_edges.push_back
                    (utilities::point_2_to_kernel(it->second));
            // TODO V2: create polygon publishers for each sub-cdt
            //rviz_objects_ref.push_polygon_point(utilities::point_to_point_32(utilities::cgal_point_to_ros_geometry_point(utilities::point_2_to_kernel(it->second))));
        }

        //std::cout << "Total segments: " << counter << std::endl;
        std::cout << currentDateTime() << " Ended Finding new CDT for UAV: " << agent_id << std::endl;

        return sub_cdt;

    }

    void Tnp_update::replenish(std::vector<qtnp::Uas_model> &uas){

        std::cout << "---- Replenishing ----" << std::endl;

        bool finished(false);

        do {
            for (int i=0; i < uas.size(); i++){
                int not_allocated_cells(0);
                for (int j=0; j < uas.size(); j++){
                    not_allocated_cells += uas[j].get_remaining_cells();
                }
                if (not_allocated_cells > 0){
                    if (uas[i].get_remaining_cells() > 0) {
                        std::pair<int,int> from_unassigned(-1, not_allocated_cells);
                        move_cells(uas[i], from_unassigned);
                    }
                } else {
                    finished = true;
                }
            }
        } while (!finished);
    }

    // TODO V2 incorporate that bug into code
    void Tnp_update::replenish_revisited(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas){
        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            if(faces_iterator->info().agent_id == -1){
                for(int i=0; i<3; i++){
                    if ( (faces_iterator->neighbor(i)->is_in_domain()) &&
                         (faces_iterator->neighbor(i)->info().agent_id != -1) ) {
                        faces_iterator->info().agent_id = faces_iterator->neighbor(i)->info().agent_id;
                        uas[faces_iterator->neighbor(i)->info().agent_id-1].increase_assigned_cells();
                        break;
                    }
                }
            }
        }
    }

    void Tnp_update::partition(std::vector<qtnp::Uas_model> &uas){

        std::cout << currentDateTime() << " Partitioning started " << std::endl;
        rviz_objects_ref.clear_triangulation_mesh();
        m_sub_cdt_vector.clear();

        initialize_starting_positions(m_cdt, uas);
        isotropic_initial_partition(m_cdt, uas); // or initial partitioning..

        //TODO remove:
        report_initial_partitioning(m_cdt, uas);
        coverage_cost_attribution(m_cdt);

        replenish(uas);
        replenish_revisited(m_cdt, uas);

        std::cout << "After replenish AND revisited" << std::endl;
        int agent_minus_one(0);
        // initializing again depth and number var to perform isotropic cost attribution
        for(CDT::Finite_faces_iterator faces_iterator = m_cdt.finite_faces_begin();
            faces_iterator != m_cdt.finite_faces_end(); ++faces_iterator){
                if (faces_iterator->is_in_domain()) {
                    faces_iterator->info().visited = false;
                        if (faces_iterator->info().depth != 1){
                            faces_iterator->info().depth = 0;
                            faces_iterator->info().numbered = false;
                        }
                    if (faces_iterator->info().agent_id == -1) agent_minus_one++;
                }
        }

        isotropic_cost_attribution(m_cdt);
        coverage_cost_attribution(m_cdt);

        report_initial_partitioning(m_cdt, uas);
        report_distances_from_center(m_cdt, uas);

        //TODO Remove
                //        for (int i=0; i< uas.size(); i++){
        //            std::cout << "UAS " << i+1 << " has " << uas[i].get_assigned_cells() << " cells. (" <<
        //                         uas[i].get_capability_cells() << ")" << std::endl;
        //        }
                std::cout << "Agent -1 has " << agent_minus_one << " cells" << std::endl;

        std::cout << currentDateTime() << " Beginning CDT separation for " << uas.size() << " UAS." <<std::endl;
        if (uas.size() > 1){
            seperate_cdts(m_cdt, uas);
        } else {
            m_sub_cdt_vector.push_back(m_cdt);
        }

        // Here the m_sub_cdt_vector has all CDTs
        is_broadcast_ready = true;

        // TODO V2 remove that, make either connected UAS class or member vector through code.
        set_instance_uas_vector(uas);

        std::cout << currentDateTime() << " Partitioning ended " << std::endl;

        mesh_coloring();
        rviz_objects_ref.set_polygon_ready(true);

    }

    bool Tnp_update::has_global_constraints(){
        return is_broadcast_ready;
    }

    qtnp_uav::GlobalConstraints Tnp_update::get_global_constraints(){
        return global_constraints;
    }

    void Tnp_update::set_instance_uas_vector(std::vector<qtnp::Uas_model> &uas){

        for (int i=0; i < uas.size(); i++){
            m_uas_vector.push_back(uas[i]);
        }
    }

    void Tnp_update::isotropic_cost_attribution(CDT &l_cdt){

        bool finished(false);
        int hopIterator(1);

        do {
            hopIterator++; // including non domain triangles
            finished = true;

            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
                if ((faces_iterator->is_in_domain()) && (faces_iterator->info().has_number())
                        && !(faces_iterator->info().is_visited()) && !(faces_iterator->info().depth == hopIterator)) {
                    finished = false;
                    faces_iterator->info().visited = true;
                    for (int i=0; i<3; i++){
                        if ((faces_iterator->neighbor(i)->is_in_domain()) &&
                                (faces_iterator->neighbor(i)->info().agent_id == faces_iterator->info().agent_id) &&
                                !(faces_iterator->neighbor(i)->info().has_number())) {
                            if (faces_iterator->info().depth != 1){
                                faces_iterator->neighbor(i)->info().jumps_agent_id = faces_iterator->info().jumps_agent_id;
                            }
                            faces_iterator->neighbor(i)->info().depth = hopIterator;
                            faces_iterator->neighbor(i)->info().numbered = true;
                        }
                    }
                }
            }
        } while (!finished);
    }

    void Tnp_update::isotropic_initial_partition(CDT &l_cdt, std::vector<qtnp::Uas_model > &uas){

        bool neverInside(false);
        int jumpsIterator(1);

        do {
            jumpsIterator++; // including non domain triangles

            neverInside = true;

            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
              faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

                if ((faces_iterator->is_in_domain()) &&
                    (faces_iterator->info().has_number()) &&
                    !(faces_iterator->info().is_visited()) &&
                    !(faces_iterator->info().depth == jumpsIterator)) {

                    int that_agent = faces_iterator->info().agent_id;
                    neverInside = false;
                    faces_iterator->info().visited = true;

                    for (int i=0; i<3; i++){
                        if ( (faces_iterator->neighbor(i)->is_in_domain()) &&
                            !(faces_iterator->neighbor(i)->info().has_number())) {
                            if (uas[that_agent-1].get_capability_cells() > uas[that_agent-1].get_assigned_cells()){
                                if (faces_iterator->info().depth != 1){
                                    // branching agents propagation
                                    faces_iterator->neighbor(i)->info().jumps_agent_id = faces_iterator->info().jumps_agent_id;
                                }
                                faces_iterator->neighbor(i)->info().depth = jumpsIterator;
                                faces_iterator->neighbor(i)->info().numbered = true;
                                // agent id propagation
                                faces_iterator->neighbor(i)->info().agent_id = that_agent;
                                // increasing the cells appointed
                                uas[that_agent-1].increase_assigned_cells();
                            }
                        }
                    }
                }
            }
        } while (neverInside == false);
    }

    void Tnp_update::report_distances_from_center(CDT& l_cdt, std::vector<qtnp::Uas_model> &uas){

        geometry_msgs::Point center_point_initial;
        double distance;
        double total_distance{0};

        for(int i=0; i < uas.size(); i++){

            distance = 0;
            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
                if( (faces_iterator->info().agent_id == i+1) && (faces_iterator->info().depth == 1) ){
                    center_point_initial = utilities::face_to_center(l_cdt, faces_iterator);
                    break;
                }
            }

            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

                if( (faces_iterator->info().agent_id == i+1) && (faces_iterator->info().depth != 1) ){

                geometry_msgs::Point center_point_next = utilities::face_to_center(l_cdt, faces_iterator);
                distance += utilities::calculate_distance(center_point_initial, center_point_next);
                }
            }
            total_distance += distance;

            std::cout << "---- Total distance from initial point for UAV " << i+1 << " is: " << distance << "  rviz units----" << std::endl;
        }


    }

    void Tnp_update::report_initial_partitioning(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas){

        std::vector<std::pair<int,int> > number_of_assigned_cells(uas.size());
        int total_cells(0);
        int assigned_cells(0);
        int total_uas_cells(0);
        int assigned_uas_cells(0);

        int free_cells(0);

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
        faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            if (faces_iterator->is_in_domain() ) {
                total_cells++;
                if (!(faces_iterator->info().agent_id == -1)) {
                    assigned_cells++;
                    number_of_assigned_cells[faces_iterator->info().agent_id-1].first = faces_iterator->info().agent_id;
                    number_of_assigned_cells[faces_iterator->info().agent_id-1].second += 1;
                } else {
                    free_cells++;
                }
            }
        }

        for(int i=0; i < uas.size(); i++){
            total_uas_cells += uas[i].get_capability_cells();
            assigned_uas_cells += uas[i].get_assigned_cells();
        }

        std::cout << "---- CDT Count ----" << std::endl;
        std::cout << "Total cells: " << total_cells << std::endl;
        std::cout << "Remaining cells: " << total_cells - assigned_cells << std::endl;

        std::cout << "Assigned cells: " << std::endl;
        for (int i=0; i < number_of_assigned_cells.size(); i++){
            std::cout << "agent " << i+1 << ": " << number_of_assigned_cells[i].second << " = " <<  (number_of_assigned_cells[i].second * 100.0)/total_cells << "% " << std::endl;
        }
        std::cout << "Free cells: " << free_cells << std::endl;

        std::cout << "---- UAS Model Count ----" << std::endl;
        std::cout << "Total UAS capability: " << total_uas_cells << std::endl;
            std::cout << "Total UAS assignment: " << assigned_uas_cells << std::endl;
        for(int i=0; i< uas.size(); i++){
            std::cout << "Agent " << i+1 << " Capability: " << uas[i].get_capability_cells() <<
                         " Assigned: " << uas[i].get_assigned_cells() << " = " <<  (uas[i].get_assigned_cells() * 100.0)/total_uas_cells << "% " << std::endl;
        }

        std::cout << "---- CDT - UAS Difference ----" << std::endl;
        std::cout << "CDT remaining: " << total_cells - assigned_cells << " UAS Model remaining: " <<
                     total_uas_cells - assigned_uas_cells << std::endl;

    }

    void Tnp_update::seperate_cdts(CDT &l_cdt, std::vector<qtnp::Uas_model> &uas){


        std::cout << currentDateTime() << " CDT seperation started " << std::endl;
        clear_rviz_objects();
        for (int i=0; i < uas.size(); i++){

            CDT sub_cdt = find_new_cdt_constrains(l_cdt, i+1);
            // INFO: static version of angle constrain, edge_cons is the fov_size
            double angle_cons(constants::angle_criterion_default);
            // TODO ALSO HERE EDGE!
            double edge_cons = uas[i].get_fov();// * rviz_objects_ref.get_meter_conversion();
            perform_cdt(sub_cdt, angle_cons, edge_cons);
            initialize_cdt_struct(i+1, sub_cdt, ((i+1)*5000) );
            std::vector<Uas_model> single_uas;
            single_uas.push_back(uas[i]);
            initialize_starting_positions(sub_cdt, single_uas);
            isotropic_cost_attribution(sub_cdt);
            coverage_cost_attribution(sub_cdt);
            m_sub_cdt_vector.push_back(sub_cdt);
        }

        std::cout << currentDateTime() << " CDT seperation ended " << std::endl;

    }

    void Tnp_update::mesh_coloring(){

        for (std::vector<CDT>::iterator that_cdt = m_sub_cdt_vector.begin();
             that_cdt != m_sub_cdt_vector.end(); ++that_cdt) {


            int color_iterator = 0;

            for(CDT::Finite_faces_iterator faces_iterator = that_cdt->finite_faces_begin();
                faces_iterator != that_cdt->finite_faces_end(); ++faces_iterator){

              color_iterator += 1.0;
              // for every face, we need a face handle to perform the various operations.
              CDT::Face_handle face = faces_iterator;

              // if this face is in the domain, meaning inside the contrained borders but outside the defined holes
              if (face->is_in_domain()){

                // create a point for each of the edges of the face.
                CDT::Point point1 = that_cdt->triangle(face)[0];
                CDT::Point point2 = that_cdt->triangle(face)[1];
                CDT::Point point3 = that_cdt->triangle(face)[2];

                double face_depth = rviz_objects_ref.get_settings().task_cost ? face->info().depth : face->info().coverage_depth;
                float z = -face_depth;

                // each triangle in rviz mesh need three points..
                rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point1, z));
                rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point2, z));
                rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point3, z));

                std_msgs::ColorRGBA triangle_color;
                triangle_color.a = 1.0f;// + (face_depth/900.0);

                // agent coloring for partition viz
                if (rviz_objects_ref.get_settings().partition){
                    double agent_color = face->info().agent_id * 5;
                    triangle_color.r = 50 + agent_color;
                    triangle_color.b = 50 + agent_color;
                    triangle_color.g = 50 + agent_color;
                }

                // isotropic cost depth coloring
                if (rviz_objects_ref.get_settings().task_cost){
                    triangle_color.r = 1.0f - (face_depth/100.0) - (face->info().agent_id*0.05);
                    triangle_color.b = 1.0f - (face_depth/100.0) - (face->info().agent_id*0.05);
                    triangle_color.g = 1.0f - (face_depth/100.0) - (face->info().agent_id*0.05);
                    if (triangle_color.r < 0.5f) triangle_color.r -= 0.5f;
                    if (triangle_color.b < 0.5f) triangle_color.b -= 0.5f;
                    if (triangle_color.g < 0.5f) triangle_color.g -= 0.5f;
                }

                // coverage depth coloring.. it's rbg not rgb..
                if (rviz_objects_ref.get_settings().coverage_cost){
                    triangle_color.r = 1.0f;// - (face_depth/500.0) +0.02f + (face->info().agent_id*2);// + (the_agent/5.0);
                    triangle_color.b = 0.1f - (face_depth/500.0)+0.02f ; + (face->info().agent_id*2);// + (the_agent/5.0);// + (face->info().depth/45.0);//color_iterator*2.50/100;
                    triangle_color.g = 0.4f + (face_depth/250.0)+0.05f+ (face->info().agent_id*2);// + (the_agent/5.0);// + (face_depth/75.0);//color_iterator*8.0/100;
                }

                // borders coloring
                if (rviz_objects_ref.get_settings().borders){
                    if (face->info().coverage_depth == constants::coverage_depth_max){
                        triangle_color.g = 0.7f;
                    }
                }

                // initial positions are white
                if (face->info().depth == 1){ // also include target coloring?
                  triangle_color.r = 1.0f;
                  triangle_color.g = 1.0f;
                  triangle_color.b = 1.0f;
                }
                rviz_objects_ref.push_mesh_cell_color(triangle_color);
              }
            }
        }
    }

    void Tnp_update::path_planning_coverage(int uas, int mountain_sensitivity){


        std::cout << currentDateTime() << " Complete coverage started " << std::endl;
        complete_path_coverage(uas, mountain_sensitivity);
        std::cout << currentDateTime() << " Complete coverage finished " << std::endl;
        create_cdt_log(uas, get_lloyd_iter(), mountain_sensitivity);
        create_path_log(uas, get_lloyd_iter(), mountain_sensitivity);
        // TODO after mesh coloring, and planning ready, could add function to form to begin the flight, upload the new plan and monitor
        mesh_coloring();
        rviz_objects_ref.set_planning_ready(true) ;
    }

    // TODO V2 seperate log classes:
    void Tnp_update::create_cdt_log(int uas_id, int lloyd_iterations, int mountain_sensitivity){

        CDT &l_cdt = m_sub_cdt_vector[uas_id - 1];

        std::stringstream log_filename;
        std::string data_path = "/home/fotis/Dev/Data/logs/";
        log_filename << data_path << currentDateTime() << "_BF_CDT_" << "UAV_" << uas_id << "_LLOYD_" << lloyd_iterations << " _MNTSENS_" << mountain_sensitivity << ".txt";
        const std::string& tmp = log_filename.str();
        const char* cstr = tmp.c_str();
        std::ofstream log_file(cstr);
        log_file << "LLOYD MTN_SENS CELL_ID ANGLE_1 ANGLE_2 ANGLE_3 SIDE_1 SIDE_2 SIDE_3 NEIGHB_1_DIST NEIGHB_2_DIST NEIGHB_3_DIST" << std::endl;

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

            if (faces_iterator->info().agent_id == uas_id){

                int cell_id = faces_iterator->info().id;

                CGAL::Point_2<K> vertex1 = l_cdt.triangle(faces_iterator)[0];
                CGAL::Point_2<K> vertex2 = l_cdt.triangle(faces_iterator)[1];
                CGAL::Point_2<K> vertex3 = l_cdt.triangle(faces_iterator)[2];

                double a = CGAL::sqrt((vertex2.x() - vertex3.x())*(vertex2.x() - vertex3.x()) + (vertex2.y() - vertex3.y()) * (vertex2.y() - vertex3.y()));
                double b = CGAL::sqrt((vertex1.x() - vertex3.x())*(vertex1.x() - vertex3.x()) + (vertex1.y() - vertex3.y()) * (vertex1.y() - vertex3.y()));
                double c = CGAL::sqrt((vertex2.x() - vertex1.x())*(vertex2.x() - vertex1.x()) + (vertex2.y() - vertex1.y()) * (vertex2.y() - vertex1.y()));

                double angle1 = ( (std::acos((b*b+c*c-a*a)/(2*b*c))) * 180 )/constants::PI;
                double angle2 = ( (std::acos((a*a+c*c-b*b)/(2*a*c))) * 180 )/constants::PI;
                double angle3 = ( (std::acos((a*a+b*b-c*c)/(2*b*a))) * 180 )/constants::PI;

                CGAL::Vector_2<K> v1(vertex1,vertex2);
                CGAL::Vector_2<K> v2(vertex2,vertex3);
                CGAL::Vector_2<K> v3(vertex3,vertex1);

                double side1 = CGAL::sqrt(v1.squared_length());
                double side2 = CGAL::sqrt(v2.squared_length());
                double side3 = CGAL::sqrt(v3.squared_length());

                log_file << lloyd_iterations << " " << mountain_sensitivity << " " << cell_id << " " << angle1 << " " << angle2 << " " << angle3 << " " << side1 << " " << side2 << " " << side3 << " ";

                double center_x = ( vertex1.x() + vertex2.x() + vertex3.x() ) / 3;
                double center_y = ( vertex1.y() + vertex2.y() + vertex3.y() ) / 3;
                CGAL::Point_2<K> center(center_x, center_y);

                for (int i=0; i<3; i++){
                    if ( faces_iterator->neighbor(i)->info().agent_id == uas_id ){
                        CGAL::Point_2<K> neighb_vertex1 = l_cdt.triangle(faces_iterator->neighbor(i))[0];
                        CGAL::Point_2<K> neighb_vertex2 = l_cdt.triangle(faces_iterator->neighbor(i))[1];
                        CGAL::Point_2<K> neighb_vertex3 = l_cdt.triangle(faces_iterator->neighbor(i))[2];

                        double new_neighb_x = (neighb_vertex1.x() + neighb_vertex2.x() + neighb_vertex3.x() ) / 3;
                        double new_neighb_y = (neighb_vertex1.y() + neighb_vertex2.y() + neighb_vertex3.y() ) / 3;

                        CGAL::Point_2<K> neighb_center(new_neighb_x, new_neighb_y);
                        CGAL::Vector_2<K> vector_between_centers(center,neighb_center);

                        double distance = CGAL::sqrt(vector_between_centers.squared_length());
                        log_file << distance << " ";

                    }
                }
                log_file << " " << std::endl;
            }
        }

        log_file.close();

    }

    // TODO V2 unify angle calculation in utilities class
    void Tnp_update::create_path_log(int uas_id, int lloyd_iterations, int mountain_sensitivity){

        std::stringstream log_path_filename;
        std::string data_path = "/home/fotis/Dev/Data/logs/";
        log_path_filename << data_path << currentDateTime() << "_BF_PATH_" << "UAV_" << uas_id << "_LLOYD_" << lloyd_iterations << " _MNTSENS_" << mountain_sensitivity << ".txt";
        const std::string& tmp = log_path_filename.str();
        const char* cstr = tmp.c_str();
        std::ofstream path_log_file(cstr);
        path_log_file << "LLOYD MTN_SENS WAYPOINT_NO X Y DISTANCE_FROM_PREVIOUS ANGLE_OF_PREVIOUS" << std::endl;

        std::vector<geometry_msgs::PoseStamped> path_list = rviz_objects_ref.get_path().poses;

        int i = 0;
        double previous_x{0};
        double previous_y{0};
        double antepenultimate_x{0}; // heh http://english.stackexchange.com/questions/319003/word-to-describe-the-one-before-the-last-one
        double antepenultimate_y{0}; // heh http://www.dictionary.com/browse/antepenultimate

        for (std::vector<geometry_msgs::PoseStamped>::iterator it = path_list.begin();
             it != path_list.end(); ++it){

            geometry_msgs::PoseStamped& waypoint = *it;
            double distance = std::sqrt(std::pow((previous_x - waypoint.pose.position.x), 2) + std::pow( (previous_y - waypoint.pose.position.y), 2));

            if ( i < 2 ){
                if (i == 0) distance = 0;
                path_log_file << lloyd_iterations << " " << mountain_sensitivity << " " << i << " " << waypoint.pose.position.x << " " << waypoint.pose.position.y << " " << distance << std::endl;
            }
            else {

                double Ppa = sqrt(std::pow( (previous_x - antepenultimate_x) ,2) + std::pow( (previous_y - antepenultimate_y) ,2));
                double Ppw = distance;
                double Paw = sqrt(std::pow( (antepenultimate_x - waypoint.pose.position.x) ,2) + std::pow( (antepenultimate_y - waypoint.pose.position.y) ,2));
                double previous_angle = ((std::acos((Ppa*Ppa + Ppw*Ppw - Paw*Paw) / (2*Ppa*Ppw))) * 180)/constants::PI;

                path_log_file << lloyd_iterations << " " << mountain_sensitivity << " " << i << " " << waypoint.pose.position.x << " " << waypoint.pose.position.y << " " << distance << " " << previous_angle << std::endl;
            }

            antepenultimate_x = previous_x;
            antepenultimate_y = previous_y;
            previous_x = waypoint.pose.position.x;
            previous_y = waypoint.pose.position.y;
            i++;
        }

        path_log_file.close();
    }

    void Tnp_update::path_planning_to_goal(int uas, double lat, double lon){

        rviz_objects_ref.clear_path();
        path_to_goal(uas, coordinates_to_cdt_cell_id(lat,lon) );
        mesh_coloring();
        rviz_objects_ref.set_planning_ready(true) ;

    }

    // TODO V3 path to goal to be implemented in version 3.
    void Tnp_update::path_to_goal(int uas, int goal_cell_id){

        CDT::Face_handle current_face;
        // TODO V3 which is the correct list-uas index?
        CDT &l_cdt = m_sub_cdt_vector[uas];
        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            // TODO V3 make uas_model class. make current_cell_id member var inside and take it in situations like this
            if( (faces_iterator->info().agent_id == uas) && (faces_iterator->info().depth == 1) ){
                current_face = faces_iterator;
                // TODO V3 the face_to_center is not going to work since we haven't constructed the face-center list
                rviz_objects_ref.push_path_point(utilities::build_pose_stamped(utilities::face_to_center(l_cdt, current_face)));
                break;
            }
        }

      CDT::Face_handle target_face;
      geometry_msgs::Point target_face_center;
      int target_face_depth(0);

      // put it in the path
      rviz_objects_ref.push_path_point(utilities::build_pose_stamped(utilities::face_to_center(l_cdt, current_face)));

      Distance_Vector distance_vector;

      // get target face
      for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
          faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
        if (faces_iterator->info().id == goal_cell_id){
          target_face = faces_iterator;
          target_face_center = utilities::face_to_center(l_cdt, target_face);
          target_face_depth = target_face->info().depth;
          // if it happens our target to be at the borders, we temporaly change its depth
          if (target_face_depth == constants::coverage_depth_max){
            int previous = 0;
              for (int i=0; i<3; i++){
                if (target_face->neighbor(i)->is_in_domain()){
                    target_face_depth = (target_face->neighbor(i)->info().depth > previous) ?
                                target_face->neighbor(i)->info().depth : previous;
                    previous = target_face->neighbor(i)->info().depth;
                }
            }
          }
          break;
        }
      }

      float previous_distance = utilities::calculate_distance(
                  (utilities::face_to_center(l_cdt, current_face)) , target_face_center);
      //std::cout << "Initial distance from start: " << previous_distance << std::endl;
      int depth_runs = 1;
      int branch_id = target_face->info().jumps_agent_id;

      do {

        depth_runs+=4;

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin(); faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
          if ( (faces_iterator->info().agent_id == uas) &&
               (faces_iterator->info().depth < depth_runs) &&
               (faces_iterator->info().jumps_agent_id == branch_id) ){

            float distance = utilities::calculate_distance(utilities::face_to_center(l_cdt, faces_iterator), target_face_center);
            Distance_Entry this_entry = std::make_pair(faces_iterator, distance);
            distance_vector.push_back(this_entry);
          }
        }

        std::sort(distance_vector.begin(), distance_vector.end(), utilities::distance_comparison);
        // put the nearer to path
        rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                         (utilities::face_to_center(l_cdt, distance_vector.front().first)));
        distance_vector.clear();


      }while (depth_runs < target_face_depth);

    }

    void Tnp_update::coverage_cost_attribution(CDT &l_cdt){

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            faces_iterator->info().coverage_depth = 0;
            faces_iterator->info().cover_depth = false;
        }

        // go through all triangles to give border depth to the borders between agents
        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            // initialize again the path visited attribute
            if (faces_iterator->is_in_domain()) {
                for (int i=0;i<3;i++){
                    if ( (faces_iterator->neighbor(i)->info().agent_id != faces_iterator->info().agent_id) ||
                         !(faces_iterator->neighbor(i)->is_in_domain()) ){
                        faces_iterator->info().coverage_depth = constants::coverage_depth_max;
                        faces_iterator->info().cover_depth = true;
                    }
                }
            }
        }

        int so_many(0);
        int da_coverage_depth(constants::coverage_depth_max);
        bool never_ever_again(true);

        do {
            da_coverage_depth = da_coverage_depth - 10;
            never_ever_again = true;
            for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
                if (faces_iterator->is_in_domain()) {
                    if((faces_iterator->info().has_coverage_depth()) &&
                            (faces_iterator->info().coverage_depth > da_coverage_depth) ){
                        for (int i=0;i<3;i++){
                            if (!faces_iterator->neighbor(i)->info().has_coverage_depth()){
                                faces_iterator->neighbor(i)->info().coverage_depth = da_coverage_depth;
                                faces_iterator->neighbor(i)->info().cover_depth = true;
                                never_ever_again = false;
                                so_many++;
                            }
                        }
                    }
                }
            }
        } while (!never_ever_again);
    }

    void Tnp_update::complete_path_coverage(int uas, int mountain_sensitivity){

        int uas_id = uas;

        CDT &l_cdt = m_sub_cdt_vector[uas_id - 1];
        rviz_objects_ref.clear_path();
        std::vector< std::pair<double, double> > coord_path;

        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            faces_iterator->info().reset_path_visited();
        }

        CDT::Face_handle initial_cell;
        for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
            faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){
            if ( (faces_iterator->is_in_domain())  && (faces_iterator->info().depth == 1) ) {
                initial_cell = faces_iterator;
                break;
            }
        }

        CDT::Face_handle &starter_cell = initial_cell;
        Face_Handle_Vector borders_vector;
        Distance_Vector borders_distance_vector;

        Face_Handle_Vector mountain_vector;
        Distance_Vector mountain_distance_vector;

        int current_depth = constants::coverage_depth_max;
        int smallest_depth = constants::coverage_depth_max - 1;
        bool not_finished = true;
        bool initial = true;

        bool mountain_found = false;
        bool mountain_cross = false;

        starter_cell->info().path_visited = true;
        rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                         (utilities::face_to_center(l_cdt, starter_cell)));
        // lat, lon
        coord_path.push_back(std::pair<double, double>(starter_cell->info().center_lat, starter_cell->info().center_lon));

        do {

            not_finished = false;
            mountain_found = false;
            mountain_cross = false;

            // a mountain is found
            if (current_depth < smallest_depth){//

                // the closest one to the current, from the list of mountains
                // calculate the distance from all borders to the starter cell in order to choose the first border cell to visit
                for (std::vector<CDT::Face_handle>::iterator it = mountain_vector.begin(); it != mountain_vector.end(); it++){//
                    float this_distance = utilities::calculate_distance(utilities::face_to_center(l_cdt, *it),//
                                             utilities::face_to_center(l_cdt, starter_cell));//
                    Distance_Entry this_entry = std::make_pair(*it, this_distance);//
                    mountain_distance_vector.push_back(this_entry);//
                }//

                not_finished = false;//
                std::sort(mountain_distance_vector.begin(), mountain_distance_vector.end(), utilities::distance_comparison);//
                CDT::Face_handle next_cell = mountain_distance_vector.front().first;//
                // giati tha meiwthei meta
                current_depth = next_cell->info().coverage_depth + 10 ;//

                // removes the cell from the mountain vector
                mountain_vector.erase(std::remove(mountain_vector.begin(), mountain_vector.end(), next_cell), mountain_vector.end());//

                rviz_objects_ref.push_path_point(utilities::build_pose_stamped//
                                             (utilities::face_to_center(l_cdt, next_cell)));//
                next_cell->info().path_visited = true;//
                coord_path.push_back(std::pair<double, double>(next_cell->info().center_lat, next_cell->info().center_lon));//
                starter_cell = next_cell;//

                mountain_distance_vector.clear();//

                mesh_coloring();//
                rviz_objects_ref.set_planning_ready(true) ;//


            } else {//

                // go through all triangles, get the starter cell and the borders vector
                for(CDT::Finite_faces_iterator faces_iterator = l_cdt.finite_faces_begin();
                    faces_iterator != l_cdt.finite_faces_end(); ++faces_iterator){

                    if ( (faces_iterator->info().coverage_depth >= current_depth)
                         && (faces_iterator->info().agent_id == uas_id)
                         && (!faces_iterator->info().is_path_visited())) {
                        //current_depth = faces_iterator->info().coverage_depth;
                        borders_vector.push_back(faces_iterator);
                        not_finished = true;
                    }

                    if (initial){
                        if ((faces_iterator->info().coverage_depth < smallest_depth)
                            && (faces_iterator->info().agent_id == uas_id)){
                            smallest_depth = faces_iterator->info().coverage_depth;
                        }
                    }
                }
            }//

            if (!not_finished){ // or mountain == true
                current_depth = current_depth - 10;
            } else {

                // calculate the distance from all borders to the starter cell in order to choose the first border cell to visit
                for (std::vector<CDT::Face_handle>::iterator it = borders_vector.begin(); it != borders_vector.end(); it++){
                    float this_distance = utilities::calculate_distance(utilities::face_to_center(l_cdt, *it),
                                                             utilities::face_to_center(l_cdt, starter_cell));
                    Distance_Entry this_entry = std::make_pair(*it, this_distance);
                    borders_distance_vector.push_back(this_entry);
                }

                std::sort(borders_distance_vector.begin(), borders_distance_vector.end(), utilities::distance_comparison);
                CDT::Face_handle first_of_the_border = borders_distance_vector.front().first;

                float next_waypoint_distance = borders_distance_vector.front().second;
                // panw apo 3 fores megaliteri apostasi apo oti apo ton neighbor tou
// REMOVE NEXT COMMENT FOR MOUNTAIN
                                for (int i=0; i<3; i++){//
                    if (!initial && (starter_cell->neighbor(i)->is_in_domain()) ){//
                        if ( (utilities::calculate_distance(//
                                utilities::face_to_center(l_cdt, starter_cell),//
                                utilities::face_to_center(l_cdt, starter_cell->neighbor(i))) * mountain_sensitivity) < next_waypoint_distance){//

                            // TODO V2 not optimized solution ( O(N^2) ). Look at http://stackoverflow.com/questions/10376065/pushing-unique-data-into-vector=
                            if (std::find(mountain_vector.begin(), mountain_vector.end(), borders_distance_vector.front().first) == mountain_vector.end()) {//
                                mountain_vector.push_back(borders_distance_vector.front().first);//
                            }//
                            current_depth = current_depth - 10;//
                            mountain_found = true;//
                            break;//
                        }//
                    }//
                }//
//00000000000000000000000000000000000000000000000000000000000

                // an o geitonas tou starter_cell, diladi toy proigoymenoy vimatos, pou einai pio konta
                // ston first of the border, den exei ton firstOfTHeBor ws geitona,
                // tote vale ayton ton geitona sto path, kanton visited an den einai,
                // valton ws starter cell kai epanelave

                // REMOVE COMMENT FOR MOUNTAIN, last line too
                if (!mountain_found){//

                    current_depth = first_of_the_border->info().coverage_depth;
                    mountain_vector.erase(std::remove(mountain_vector.begin(), mountain_vector.end(), first_of_the_border), mountain_vector.end());//
                    rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                                 (utilities::face_to_center(l_cdt, first_of_the_border)));
                    first_of_the_border->info().path_visited = true;
                    coord_path.push_back(std::pair<double, double>(first_of_the_border->info().center_lat,
                                                               first_of_the_border->info().center_lon));
                    starter_cell = first_of_the_border;
                }//
            }

            initial = false;
            borders_vector.clear();
            borders_distance_vector.clear();
        } while (current_depth >= smallest_depth || !mountain_vector.empty());//

        make_mavros_waypoint_list(uas, coord_path);
    }


    void Tnp_update::make_mavros_waypoint_list(int uas, std::vector<std::pair<double, double> > path){ // also put uas_id

        mavros_msgs::Waypoint initialWaypoint;
        mavros_msgs::WaypointList &waypoint_list = m_waypoint_list;

        waypoint_list.waypoints.clear();

        double initialLatitude = m_uas_vector[uas-1].get_initial_position().get_latitude(); // path.poses[0].position.y;
        double initialLongitude = m_uas_vector[uas-1].get_initial_position().get_longitude(); // of the uas agent according to initial position by ui (or later, current)

//        std::cout << "Center list: " << std::endl;
//        std::cout << std::fixed << std::setprecision(8) << "lat: " << initialLatitude << " lon: " << initialLongitude << std::endl;
        // this is for first initial position // maybe need to change frame, put it global (0)
        initialWaypoint.frame = 3;
        initialWaypoint.command = 16;
        initialWaypoint.is_current = true;
        initialWaypoint.autocontinue = true;
        initialWaypoint.param1 = 0;
        initialWaypoint.param2 = 0;
        initialWaypoint.param3 = 0;
        initialWaypoint.param4 = 0;
        initialWaypoint.x_lat = round(initialLatitude*100000000.0)/100000000.0;
        initialWaypoint.y_long = round(initialLongitude*100000000.0)/100000000.0;
        initialWaypoint.z_alt = 285; // 0? for initial relevant altitude
        waypoint_list.waypoints.push_back(initialWaypoint);

        // -------------------------------------------------//
        // file generation
        int sequence = 1;

        std::stringstream mavlink_filename;
        std::string data_path = "/home/fotis/Dev/Data/Missions/";
        mavlink_filename << data_path << "mavlink_plan_" << currentDateTime() << ".txt";
        const std::string& tmp = mavlink_filename.str();
        const char* cstr = tmp.c_str();
        std::ofstream mavlink_fWPPlan(cstr);
        mavlink_fWPPlan << "QGC WPL 110" << std::endl;

        mavlink_fWPPlan << "0\t1\t0\t16\t0\t0\t0\t0\t" << std::fixed << std::setprecision(7) << initialWaypoint.x_lat << "\t"
                    << std::fixed <<  std::setprecision(7) << initialWaypoint.y_long << "\t585\t1" << std::endl;
        // -------------------------------------------------//

        // TODO integrate fixed and precision once for all the file
        bool initial = true;

        // begin() +1 ?
        for (std::vector<std::pair<double, double> >::iterator it = path.begin(); it != path.end(); it++){

            mavros_msgs::Waypoint waypoint;

            if (initial){

                // this is for take off
                waypoint.frame = 3;
                waypoint.command = 22;
                waypoint.is_current = false;
                waypoint.autocontinue = true;
                waypoint.param1 = 15;
                waypoint.param2 = 0;
                waypoint.param3 = 0;
                waypoint.param4 = 0;
                waypoint.x_lat = round( (it->second) *100000000.0)/100000000.0;
                waypoint.y_long = round( (it->first)*100000000.0)/100000000.0;
                waypoint.z_alt = 50; // 100? for takeoff
                waypoint_list.waypoints.push_back(waypoint);
                initial = false;
//                std::cout << std::fixed << std::setprecision(8) << " lat: " << it->second << " lon: " << it->first << std::endl;

                //--------------------------------//
                // file generation //
                mavlink_fWPPlan << "1\t0\t3\t22\t15\t0\t0\t0\t" << std::fixed << std::setprecision(7) << waypoint.x_lat << "\t"
                        << std::fixed << std::setprecision(7) << waypoint.y_long << "\t50\t1" << std::endl;
                //--------------------------------//

            } else {

                // this is for path:
                waypoint.frame = 3;
                waypoint.command = 16;
                waypoint.is_current = false;
                waypoint.autocontinue = true;
                waypoint.param1 = 0;
                waypoint.param2 = 0;
                waypoint.param3 = 0;
                waypoint.param4 = 0;
                waypoint.x_lat = round( (it->second) *100000000.0)/100000000.0;
                waypoint.y_long = round( (it->first)*100000000.0)/100000000.0;
                waypoint.z_alt = 50; // 100? for takeoff
                waypoint_list.waypoints.push_back(waypoint);
//                std::cout << std::fixed << std::setprecision(8) << " lat: " << it->second << " lon: " << it->first << std::endl;

                //-----------------------------------//
                // file generation //
                mavlink_fWPPlan << sequence << "\t0\t3\t16\t0\t0\t0\t0\t" << std::fixed << std::setprecision(7) << waypoint.x_lat << "\t"
                        << std::fixed << std::setprecision(7) << waypoint.y_long << "\t50\t1" << std::endl;
                sequence++;
                //-----------------------------------//

            }
        }

        mavros_msgs::Waypoint waypoint;
        // this is for landing
        waypoint.frame = 3;
        waypoint.command = 21;
        waypoint.is_current = false;
        waypoint.autocontinue = true;
        waypoint.param1 = 480;
        waypoint.param2 = 0;
        waypoint.param3 = 0;
        waypoint.param4 = 25;
        waypoint.x_lat = round(initialLatitude*100000000.0)/100000000.0;
        waypoint.y_long = round(initialLongitude*100000000.0)/100000000.0;
        waypoint.z_alt = 580; // 100? for takeoff
        waypoint_list.waypoints.push_back(waypoint);
//        std::cout << std::fixed << std::setprecision(8) << initialLatitude << " " << initialLongitude << std::endl;


        //--------------------------------//
        // file generation //
        mavlink_fWPPlan << sequence << "\t0\t3\t21\t480\t0\t0\t25\t" << std::fixed << std::setprecision(7) << waypoint.x_lat << "\t"
                << std::fixed << std::setprecision(7) << waypoint.y_long << "\t580\t1"; // << std::endl;
        mavlink_fWPPlan.close();
        //--------------------------------//

    }

}
