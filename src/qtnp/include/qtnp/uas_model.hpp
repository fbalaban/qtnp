/**
 * @file /include/qtnp/uas_model.hpp
 *
 * @brief UAS Model
 *
 * @date October 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef UAS_MODEL_HPP
#define UAS_MODEL_HPP

/*****************************************************************************
** Includes
*****************************************************************************/

#include <string>
#include "position.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

/*****************************************************************************
** Class
*****************************************************************************/

class Uas_model{

  public:

    Uas_model(int id, qtnp::Position initial_position, double fov, int autonomy) : m_capability_cells {0}, m_assigned_cells {0} {

      m_id = id;
      m_position_initial = initial_position;
      m_fov = fov;
      m_autonomy = autonomy;

    }

    void set_capability_cells (int cells) { this->m_capability_cells = cells; }

    void increase_assigned_cells(){ this->m_assigned_cells += 1; }
    void set_assigned_cells (int cells) { this->m_assigned_cells = cells; }

    int get_id() { return this->m_id; }
    qtnp::Position get_initial_position() { return this->m_position_initial; }
    int get_autonomy() { return this->m_autonomy; }

    double get_fov() { return this->m_fov; }
    int get_capability_cells() { return this->m_capability_cells; }
    int get_assigned_cells() { return this->m_assigned_cells; }
    int get_remaining_cells() { return this->m_capability_cells - this->m_assigned_cells; }

  private:

    int m_id;
    std::string m_label; // an AKA name
    std::string m_type; // platform type e.g. fixed wing or MAV, UAV, ROV etc
    std::string m_sensor_type;
    std::string m_task_label; // task to accomplish, e.g. coverage. TODO V2 class Task: includes position or other relative information
    qtnp::Position m_position_initial; // latitude and longitude, if needed, also includes frame, altitude, attitude
    qtnp::Position m_position_current;
    qtnp::Position m_position_next;
    double m_fov; // in meters or units. TODO V2, should have sensor metrics like lenght & width, focal lenght etc
    int m_autonomy; // % of total area
    int m_capability_cells; // Zi
    double m_capability_area;
    int m_assigned_cells; // Yi
    double m_assigned_area;

};

} // namespace qtnp

#endif // UAS_MODEL_HPP

