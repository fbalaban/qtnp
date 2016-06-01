/**
 * @file /src/tnp_update.cpp
 *
 * @brief Triangulation and planning functions
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>

#include "../include/qtnp/tnp_update.hpp"
#include "../include/qtnp/utilities.hpp"

#include "qtnp/InitialCoordinates.h"
#include "qtnp/Coordinates.h"
#include "qtnp/Placemarks.h"


struct comp
{
    comp(int const& i) : _i(i) { }

    bool operator () (std::pair<int, int> const& p)
    {
        return (p.first == _i);
    }

    int _i;
};

namespace qtnp {

/*****************************************************************************
** Implementation
*****************************************************************************/

// reference constructor
//Tnp_update::Tnp_update(Rviz_objects& rvizReference) : rviz_objects_ref(rvizReference){}

void Tnp_update::init(){

    cdt.clear();
    cdt_polygon_edges.clear();
    rviz_objects_ref.clear_edges();
    rviz_objects_ref.clear_center_points();
    rviz_objects_ref.clear_center_points_with_cell_id();

    area_extremes.max_lat = -constants::max_lat;
    area_extremes.min_lat = -constants::min_lat;
    area_extremes.max_lon = -constants::max_lon;
    area_extremes.min_lon = -constants::min_lon;
}

// custom callback function of the ROS listener for polygpn definition
void Tnp_update::polygon_def_callback(const Placemarks::ConstPtr &msg){

    std::vector<Coordinates> placemarks_array = msg->placemarks;

    // for service calls, performs cdt with default angle, edge constrains
    perform_polygon_definition(placemarks_array, constants::angle_criterion_default, constants::edge_criterion_default);
}

// TODO transform edge size to rviz size
void Tnp_update::perform_polygon_definition(std::vector<Coordinates> placemarks_array, double angle_cons, double edge_cons){

    ROS_INFO_STREAM("Got a new polygon definition");

    init();

    std::cout << std::setprecision(7);

    // define minimum and maximum values of the constrained area so to convert lat,lon to visualization ranges
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

    std::list<CDT::Point> list_of_seeds;
    // convert ranges, draw CDT and visualization objects
    for (std::vector<qtnp::Coordinates>::iterator it = placemarks_array.begin(); it<placemarks_array.end(); it++){

        int size = it->longitude.size();
        std::vector<double> longitude_array(size);
        std::vector<double> latitude_array(size);
        bool is_an_obstacle = (it->placemark_type == "hole") ? true :false;

        if (is_an_obstacle) list_of_seeds.push_back(CDT::Point(
                    utilities::convert_range(area_extremes.min_lat,area_extremes.max_lat,
                                constants::rviz_range_min,constants::rviz_range_max,it->seed_latitude),
                    utilities::convert_range(area_extremes.min_lon,area_extremes.max_lon,
                                constants::rviz_range_min,constants::rviz_range_max,it->seed_longitude)));

        longitude_array = it->longitude;
        latitude_array  = it->latitude;

        // TODO: Warning. this info (min,max,range) should be propagated to the path planning callback,
        // or else the visualization information will be wrong

        for (int i=1; i<size; i++){

            double previous_latitude = utilities::convert_range(area_extremes.min_lat,area_extremes.max_lat,constants::rviz_range_min,constants::rviz_range_max,latitude_array[i-1]);
            double previous_longitude = utilities::convert_range(area_extremes.min_lon,area_extremes.max_lon,constants::rviz_range_min,constants::rviz_range_max,longitude_array[i-1]);

            double current_latitude = utilities::convert_range(area_extremes.min_lat,area_extremes.max_lat,constants::rviz_range_min,constants::rviz_range_max,latitude_array[i]);
            double current_longitude = utilities::convert_range(area_extremes.min_lon,area_extremes.max_lon,constants::rviz_range_min,constants::rviz_range_max,longitude_array[i]);

            // inserting the area definition vertexes by drawing points and connecting them
            CDT::Vertex_handle va = cdt.insert(CDT::Point(previous_latitude,previous_longitude));
            CDT::Vertex_handle vb = cdt.insert(CDT::Point(current_latitude,current_longitude));
            cdt.insert_constraint(va,vb);

            // draw only a polygon for contrained area, not for obstacles.
            if (!is_an_obstacle){
                // adding the previous point
                cdt_polygon_edges.push_back
                        (kernel_Point_2(previous_latitude,previous_longitude));
                // also adding it to the referenced rviz edge visualization
                rviz_objects_ref.push_edge_point
                        (utilities::cgal_point_to_ros_geometry_point(kernel_Point_2(previous_latitude,previous_longitude)));

//                rviz_objects_ref.edges.points.push_back
//                        (cgal_point_to_ros_geometry_point(kernel_Point_2(previous_latitude,previous_longitude)));
                // adding the current point
                cdt_polygon_edges.push_back
                        (kernel_Point_2(current_latitude,current_longitude));
                // and this also to the rviz objects
                rviz_objects_ref.push_polygon_point
                        (utilities::point_to_point_32(utilities::cgal_point_to_ros_geometry_point
                                           (kernel_Point_2(current_latitude,current_longitude))));
            }

        }
    }

    // TODO: seperate rest of function

    double crAngle = angle_cons;// 0.125; -- the default angle criteria
    double crEdge = edge_cons; // 25.0; -- the default edge criteria(50m footprint)
    std::cout << "Number of vertices before meshing and refining: " << cdt.number_of_vertices() << std::endl;
    std::cout << "Meshing the triangulation with default criteria..." << std::endl;
    Mesher mesher(cdt);
    mesher.refine_mesh();
    std::cout << "Number of vertices after meshing: " << cdt.number_of_vertices() << std::endl;
    std::cout << "Meshing again with new criteria..." << std::endl;

    mesher.set_criteria(Criteria(crAngle, crEdge));
    mesher.refine_mesh();
    std::cout << "Number of vertices after meshing and refining with new criteria: "
            << cdt.number_of_vertices() << std::endl;

    //  Adding the seeds which define the holes.
    if (!list_of_seeds.empty()){
        std::cout << "Refining and meshing the domain including seeds defining holes" << std::endl;
        CGAL::refine_Delaunay_mesh_2(cdt, list_of_seeds.begin(), list_of_seeds.end(), Criteria());
        std::cout << "Number of vertices after meshing CDT refining and seeding holes: " << cdt.number_of_vertices() << std::endl;
    }
    // dataFile << cdt.number_of_vertices() << " ";
    ROS_INFO_STREAM("# of vertices after meshing and refining with CDT: " + cdt.number_of_vertices());

    // ------------- rviz coloring schema ----------------//
    // also counting the biggest and smalest side //
    double smallest_side = 999.999;
    double biggest_side = 0.0;
    double smallest_angle = 190.0;
    double biggest_angle = 0.0;

    int initialize_iterator = 0;

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

      // for every face, we need a face handle to perform the various operations.
      CDT::Face_handle face = faces_iterator;


      // if this face is in the domain, meaning inside the contrained borders but outside the defined holes
      if (face->is_in_domain()){

        // initialize face, along with it's id. TODO remove it from partition (initialize_mesh function)
        faces_iterator->info().initialize(initialize_iterator);

        // create a point for each of the edges of the face.
        CDT::Point point1 = cdt.triangle(face)[0];
        CDT::Point point2 = cdt.triangle(face)[1];
        CDT::Point point3 = cdt.triangle(face)[2];

        // here gathering the smallest and biggest distances:
        smallest_side =  ( utilities::smallest_distance(point1, point2, point3) < smallest_side) ?
                    utilities::smallest_distance(point1, point2, point3) : smallest_side;
        biggest_side = ( utilities::biggest_distance(point1, point2, point3) > biggest_side) ?
                    utilities::biggest_distance(point1, point2, point3) : biggest_side;

        // calulating an angle (only one...)
        double angle = atan2((point2.y() - point1.y()), (point2.x() - point1.x()) ) -
                atan2( (point3.y() - point1.y()) , (point3.x() - point1.x()) );
        angle = abs(angle*180.0/3.14159265);

        angle = (angle > 180) ? (360.0 - angle) : angle;

        if (angle < smallest_angle) smallest_angle = angle;
        if (angle > biggest_angle) biggest_angle = angle;
        // adding the center of every triangle
        rviz_objects_ref.push_center_point(utilities::face_points_to_center(point1, point2, point3));
        // adding it also to the center-id vector
        rviz_objects_ref.push_center_point_with_cell_id(initialize_iterator, utilities::face_points_to_center(point1, point2, point3));
        initialize_iterator++;

      }
    }

    rviz_objects_ref.set_polygon_ready(true);
}

// custom callback function of the ROS listener for path planning
void Tnp_update::path_planning_callback(const InitialCoordinates::ConstPtr &msg){

    std::cout << std::setprecision(7);
    int uav_id = (int) msg->uav_id;
    double longitude = (double) msg->longitude;
    double latitude = (double) msg->latitude;
    // coverage or target
    // if target, cell of target

    ROS_INFO("I heard UAV id: [%i]", uav_id);
    ROS_INFO("I heard the longitude: [%3.7f]", longitude);
    ROS_INFO("I heard the latitude: [%3.7f]", latitude);

    // TODO: in that way you make use of the referenced visualization objects in main ROS node
    // rviz_objects_ref.set_polygon_ready(false);

    // TODO: initializing with hard coded cell numbers...
    // initialize_mesh(cdt);
    // hop_cost_attribution(cdt);
    // coverage_cost_attribution(cdt);

    // 695 is a good target triangle for use with agent 1
    int target_face_number = 595;

    // applying either shortest path to target or coverage algorithms for path production
    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

      CDT::Face_handle face = faces_iterator;

      if ((face->is_in_domain()) && (face->info().agent_id == uav_id) && (face->info().depth == 1)){
        //TODO: introduce also not over holes in complete coverage-shortest distance
        complete_path_coverage(cdt, face, uav_id);
        //shortest_path_coverage(cdt, face, uav_id, target_face_number);
        break;
      }
    }
}

// void Tnp_update::partition(std::vector<std::pair<double,double> > uas_coords){
void Tnp_update::partition(std::vector<std::pair< std::pair<double,double> , int > >  uas_coords_with_percentage){

    rviz_objects_ref.clear_triangulation_mesh();
    int uas_count = uas_coords_with_percentage.size();
    int total_cdt_cells = rviz_objects_ref.count_cells();

    std::vector< std::pair<int,int> > id_cell_count_vector;
    std::vector<std::pair<int, geometry_msgs::Point> > id_center_list(rviz_objects_ref.get_center_points_with_cell_id());

    std::vector<int> initial_positions_cell_ids;

    int agent_id = 1;
    int jumps_ad = 1;

    for (int i=0; i<uas_count; i++){

        // TODO: they are upside down. if file is correct, change lat, lon
        double cdt_lat = utilities::convert_range(this->area_extremes.min_lat,this->area_extremes.max_lat,
                                    constants::rviz_range_min,constants::rviz_range_max,uas_coords_with_percentage[i].first.second);//here
        double ctd_lon = utilities::convert_range(this->area_extremes.min_lon,this->area_extremes.max_lon,
                                    constants::rviz_range_min,constants::rviz_range_max,uas_coords_with_percentage[i].first.first); // and here

        kernel_Point_2 initial_position(cdt_lat, ctd_lon);

        int result_id(0);
        int comparison_id(0);

        // refactor conversion below, its a spaggeti shit
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
        initial_positions_cell_ids.push_back(result_id);

        int cells_for_agent = ( (uas_coords_with_percentage[i].second * total_cdt_cells) / 100) + 0.5;
        id_cell_count_vector.push_back(std::pair<int,int>(i+1,cells_for_agent));

    }

    std::cout << initial_positions_cell_ids[0] << std::endl;
    std::cout << initial_positions_cell_ids[1] << std::endl;
    std::cout << initial_positions_cell_ids.size() << std::endl;

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

      if (faces_iterator->is_in_domain()){

        // this is for the complicated shape
        if (std::find(initial_positions_cell_ids.begin(),
                      initial_positions_cell_ids.end(),
                      faces_iterator->info().id) != initial_positions_cell_ids.end()){
          faces_iterator->info().numbered = true;
          faces_iterator->info().depth = 1;
          faces_iterator->info().agent_id = agent_id;
          agent_id++;
          for (int j=0; j<3; j++){
              faces_iterator->neighbor(j)->info().jumps_agent_id = jumps_ad;
              jumps_ad++;
          }
        }
      }else {
        faces_iterator->info().agent_id = -1;
      }
    }

    // id_cell_count_vector

    // hop cost/partitioning, passing autonomy percentage table
    hop_cost_attribution(cdt, id_cell_count_vector);
    coverage_cost_attribution(cdt);
    // rviz coloring
    mesh_coloring();
}


void Tnp_update::mesh_coloring(){

    int color_iterator = 0;

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

      color_iterator += 1.0;
      // for every face, we need a face handle to perform the various operations.
      CDT::Face_handle face = faces_iterator;

      // if this face is in the domain, meaning inside the contrained borders but outside the defined holes
      if (face->is_in_domain()){

        // create a point for each of the edges of the face.
        CDT::Point point1 = cdt.triangle(face)[0];
        CDT::Point point2 = cdt.triangle(face)[1];
        CDT::Point point3 = cdt.triangle(face)[2];

        int face_depth = face->info().depth;
        //int face_depth = face->info().coverage_depth;
        float z = -face_depth;

        // each triangle in rviz mesh need three points..
        rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point1, z));
        rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point2, z));
        rviz_objects_ref.push_mesh_point(utilities::cgal_triangulation_point_to_ros_geometry_point(point3, z));

        std_msgs::ColorRGBA triangle_color;
        triangle_color.r = 0.0f + (face_depth/85.0) +0.02f + (face->info().agent_id*2);// + (the_agent/5.0);
        triangle_color.b = 0.0f + (face_depth/85.0)+0.02f + (face->info().agent_id*2);// + (the_agent/5.0);// + (face->info().depth/45.0);//color_iterator*2.50/100;
        triangle_color.g = 0.0f + (face_depth/85.0)+0.05f+ (face->info().agent_id*2);// + (the_agent/5.0);// + (face_depth/75.0);//color_iterator*8.0/100;
        triangle_color.a = 1.0f;// + (face_depth/900.0);

        // also: if (face->info().jumps_agent_id == target_jumps_agent_id)
        if (face->info().depth == 1){ // also include target coloring
            std::cout << "cell id:" << face->info().id << std::endl;
          triangle_color.r = 1.0f;// + (face->info().depth/30.0);
          triangle_color.g = 1.0f;// + (face->info().depth/50.0);//color_iterator*2.50/100;
          triangle_color.b = 1.0f;// + (face->info().depth/60.0);//color_iterator*8.0/100;
          triangle_color.a = 1.0f;
        }
        rviz_objects_ref.push_mesh_cell_color(triangle_color);
      }
    }
    rviz_objects_ref.set_planning_ready(true) ;
}

void Tnp_update::path_planning_coverage(){}
void Tnp_update::path_planning_to_goal(){}


// TODO: there might be a case where the boundaries of 2 regions doesn't permit one agent to fully
// get his autonomy region. in that case, take agents that are missing and give them cells from
// neighboring agents. if the neighboring have less, it will be performed for them also.
// TODO: also put to log number of total and each agent cells
void Tnp_update::hop_cost_attribution(CDT &cdt, std::vector< std::pair<int,int> > id_cell_count){

    // -------------    HOP COST ALGORITHM ------------------------------------------
    // TODO: seperate hop cost and borders depth from agent attribution. agent attribution is valid
    // for all tasks and its operations don't have to be repeated or missing..
  bool neverInside = false;
  int repeatIterator = 0;
  int jumpsIterator = 1;

  std::cout << "-----Beginning jump cost------" << std::endl;
  do {
    jumpsIterator++; // including non domain triangles

    neverInside = true;

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

      // too many comparisons. we need to refactor the algorithm
      if ((faces_iterator->is_in_domain()) && (faces_iterator->info().has_number())
          && !(faces_iterator->info().is_visited()) && !(faces_iterator->info().depth == jumpsIterator)) {

        neverInside = false;
        faces_iterator->info().visited = true;

        for (int i=0; i<3; i++){

          if ((faces_iterator->neighbor(i)->is_in_domain()) && !(faces_iterator->neighbor(i)->info().has_number())) {

            int that_agent = faces_iterator->info().agent_id;
            int cells_remaining(0);

            std::vector<std::pair <int,int> >::iterator it = std::find_if(id_cell_count.begin(), id_cell_count.end(), comp(that_agent));
            if (it != id_cell_count.end()) cells_remaining = it->second;

            if (cells_remaining != 0){

                  // assign jumpers id in order to see which growing function has managed
                  // to reach the end or target.
                if (faces_iterator->info().depth != 1){
                   faces_iterator->neighbor(i)->info().jumps_agent_id = faces_iterator->info().jumps_agent_id;
                }
                // total cells for agent which is a neighbor
                // and compare it with the vector. or: take the vector, find the agent_id-cells pair,
                // if cells ==0 do nothing else do following and substract 1 from cell count
                faces_iterator->neighbor(i)->info().depth = jumpsIterator;
                faces_iterator->neighbor(i)->info().numbered = true;
                // agent id propagation
                faces_iterator->neighbor(i)->info().agent_id = faces_iterator->info().agent_id;
                it->second = it->second -1;
            }
          }
        }
      }

      repeatIterator++;

    }
   } while (neverInside == false);

  // go through all triangles to give border (or coverage) depth to the borders between agents
  // or domain border cells // actually during cell initialization all cells have 999 coverage depth
  // so make up your mind
  for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
  faces_iterator != cdt.finite_faces_end(); ++faces_iterator){
      // initialize again the path visited attribute
      for (int i=0;i<3;i++){
          if ( !(faces_iterator->neighbor(i)->is_in_domain()) ||
              (faces_iterator->neighbor(i)->info().agent_id != faces_iterator->info().agent_id) ){
            faces_iterator->info().depth = constants::coverage_depth_max;
            faces_iterator->info().cover_depth = true;
          }
      }
  }
  std::cout << "Ended. Maximum Jumps: " << jumpsIterator << " . While loop repetitions: " << repeatIterator << "." << std::endl;
  //dataFile << jumpsIterator << " ";

  // -------- END OF JUMP COST ALGORITHM -------------------//
}

// -------- COMPLETE COVERAGE (BORDER-TO-INNER) COST ALGORITHM -------------------//
void Tnp_update::coverage_cost_attribution(CDT &cdt){

  std::cout << "----Beginning complete coverage algorithm----" << std::endl;

  // go through all triangles to give border depth to the borders between agents
  for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
  faces_iterator != cdt.finite_faces_end(); ++faces_iterator){
      // initialize again the path visited attribute
      for (int i=0;i<3;i++){
          if ( (faces_iterator->neighbor(i)->info().agent_id != faces_iterator->info().agent_id) ){
            faces_iterator->info().coverage_depth = constants::coverage_depth_max;
            faces_iterator->info().cover_depth = true;
          }
      }
  }

  int so_many = 0;
  int da_coverage_depth = constants::coverage_depth_max;
  bool never_ever_again = true;
  do {
      da_coverage_depth = da_coverage_depth - 10;
      never_ever_again = true;
      for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
          faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

          if((faces_iterator->info().has_coverage_depth()) && (faces_iterator->info().coverage_depth > da_coverage_depth) ){
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
  } while (!never_ever_again);
  std::cout << "Total internal cells: " << so_many << std::endl;
}

// TODO: make it go backwards
void Tnp_update::shortest_path_coverage(CDT &cdt, CDT::Face_handle &starter_face, int agent, int target_face_id){

  // TODO: missing initialization function
  CDT::Face_handle target_face;
  // TODO: missing initialization function
  geometry_msgs::Point target_face_center;
  int target_face_depth = 0;

  CDT::Face_handle& current_face = starter_face;
  // put it in the path
  rviz_objects_ref.push_path_point(utilities::build_pose_stamped(utilities::face_to_center(cdt, current_face)));

  Distance_Vector distance_vector;

  // get target face
  for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
      faces_iterator != cdt.finite_faces_end(); ++faces_iterator){
    if (faces_iterator->info().id == target_face_id){
      target_face = faces_iterator;
      target_face_center = utilities::face_to_center(cdt, target_face);
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
              (utilities::face_to_center(cdt, current_face)) , target_face_center);
  std::cout << "Initial distance from start: " << previous_distance << std::endl;
  int depth_runs = 1;
  int branch_id = target_face->info().jumps_agent_id;

  do {

    depth_runs+=4;

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin(); faces_iterator != cdt.finite_faces_end(); ++faces_iterator){
      if ( (faces_iterator->info().agent_id == agent) &&
           (faces_iterator->info().depth < depth_runs) &&
           (faces_iterator->info().jumps_agent_id == branch_id) ){

        float distance = utilities::calculate_distance(utilities::face_to_center(cdt, faces_iterator), target_face_center);
        Distance_Entry this_entry = std::make_pair(faces_iterator, distance);
        distance_vector.push_back(this_entry);
      }
    }

    std::sort(distance_vector.begin(), distance_vector.end(), utilities::distance_comparison);
    // put the nearer to path
    rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                     (utilities::face_to_center(cdt, distance_vector.front().first)));
    distance_vector.clear();


  }while (depth_runs < target_face_depth);

}

// TODO: make starter face a static and remove double reference in body
void Tnp_update::complete_path_coverage(CDT &cdt, CDT::Face_handle &starter_face, int uav_id){

    // clearing the path object in case it had a previous path
    rviz_objects_ref.clear_path();

    for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
        faces_iterator != cdt.finite_faces_end(); ++faces_iterator){
        faces_iterator->info().reset_path_visited();
    };

    CDT::Face_handle &starter_cell = starter_face;
    int agent = uav_id;
    Face_Handle_Vector borders_vector;
    Distance_Vector borders_distance_vector;
    int current_depth = constants::coverage_depth_max;
    int smallest_depth = constants::coverage_depth_max - 1;
    bool not_finished = true;
    bool initial = true;

    starter_cell->info().path_visited = true;
    rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                     (utilities::face_to_center(cdt, starter_cell)));
    do {

        not_finished = false;

        // go through all triangles, get the starter cell and the borders vector
        for(CDT::Finite_faces_iterator faces_iterator = cdt.finite_faces_begin();
            faces_iterator != cdt.finite_faces_end(); ++faces_iterator){

            if ( (faces_iterator->info().coverage_depth >= current_depth)
                 && (faces_iterator->info().agent_id == agent)
                 && (!faces_iterator->info().is_path_visited())) {

                borders_vector.push_back(faces_iterator);
                not_finished = true;
            }

            if (initial){
                if (faces_iterator->info().coverage_depth < smallest_depth){
                    smallest_depth = faces_iterator->info().coverage_depth;
                }
            }
        }

        initial = false;

        if (!not_finished){
            current_depth = current_depth - 10;
        } else {

            // calculate the distance from all borders to the starter cell in order to choose the first border cell to visit
            for (std::vector<CDT::Face_handle>::iterator it = borders_vector.begin(); it != borders_vector.end(); it++){
                float this_distance = utilities::calculate_distance(utilities::face_to_center(cdt, *it),
                                                         utilities::face_to_center(cdt, starter_cell));
                Distance_Entry this_entry = std::make_pair(*it, this_distance);
                borders_distance_vector.push_back(this_entry);
            }

            std::sort(borders_distance_vector.begin(), borders_distance_vector.end(), utilities::distance_comparison);
            // and this is the closest
            CDT::Face_handle &first_of_the_border = borders_distance_vector.front().first;

            // an o geitonas tou starter_cell, diladi toy proigoymenoy vimatos, pou einai pio konta
            // ston first of the border, den exei ton firstOfTHeBor ws geitona,
            // tote vale ayton ton geitona sto path, kanton visited an den einai,
            // valton ws starter cell kai epanelave

            rviz_objects_ref.push_path_point(utilities::build_pose_stamped
                                             (utilities::face_to_center(cdt, first_of_the_border)));
            first_of_the_border->info().path_visited = true;
            starter_cell = first_of_the_border;
        }
        borders_vector.clear();
        borders_distance_vector.clear();
    } while (current_depth >= smallest_depth);
    // TODO: prepei na to kanoyme na min pidaei...
}


}
