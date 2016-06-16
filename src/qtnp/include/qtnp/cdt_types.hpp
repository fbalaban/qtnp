/**
 * @file /include/qtnp/cdt_types.hpp
 *
 * @brief Constrained delaunay triangulation types
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtnp_CDT_TYPES_HPP_
#define qtnp_CDT_TYPES_HPP_

#define CGAL_MESH_2_OPTIMIZER_VERBOSE
//#define CGAL_MESH_2_OPTIMIZERS_DEBUG
//#define CGAL_MESH_2_SIZING_FIELD_USE_BARYCENTRIC_COORDINATES

/*****************************************************************************
** Includes
*****************************************************************************/

#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_mesh_vertex_base_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

#include <CGAL/lloyd_optimize_mesh_2.h>

#include "constants.hpp"

/*****************************************************************************
** CDT cell struct, defining extra info for each cell
*****************************************************************************/

struct FaceInfo2
{
  FaceInfo2(){}

  bool visited, numbered, path_visited, cover_depth, aux, occupied;
  int id, depth, agent_id, jumps_agent_id, coverage_depth;

  void initialize(int face_id){
    visited = numbered = path_visited = cover_depth = aux = occupied = false;
    depth = 0;
    coverage_depth = constants::coverage_depth_max;
    id = face_id;
    agent_id = 0;
  }

  void reset_path_visited(){
      path_visited = false;
  }

  bool is_visited(){
    return visited;
  }
  bool is_path_visited(){
    return path_visited;
  }
  bool has_number(){
    return numbered;
  }
  bool has_coverage_depth(){
    return cover_depth;
  }
};

/*****************************************************************************
** Types
*****************************************************************************/

// the cartesian Kernel
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 kernel_Point_2;
// the constructions Kernel
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Delaunay_mesh_vertex_base_2<K> Vb;
typedef CGAL::Delaunay_mesh_face_base_2<K> Fb;
//typedef CGAL::Constrained_triangulation_face_base_2<K,Fb>        CTFb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2,K,Fb>    InfoFbb;
typedef CGAL::Triangulation_data_structure_2<Vb, InfoFbb> Tds;
typedef CGAL::Exact_predicates_tag Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, Tds, Itag> CDT;
typedef CGAL::Delaunay_mesh_size_criteria_2<CDT> Criteria;
typedef CGAL::Delaunay_mesher_2<CDT, Criteria> Mesher;

typedef std::vector<kernel_Point_2> CDT_Point_2_vector;


#endif /* qtnp_CDT_TYPES_HPP_ */
