/**
 * @file /include/qtnp/position.hpp
 *
 * @brief Position class
 *
 * @date October 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/

/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef POSITION_HPP
#define POSITION_HPP


/*****************************************************************************
** Includes
*****************************************************************************/

#include <string>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

/*****************************************************************************
** Class
*****************************************************************************/

class Position {

public:

  Position(){}

  Position (double latitude, double longitude){

    m_latitude = latitude;
    m_longitude = longitude;

  }

  double get_latitude() const{ return m_latitude; }
  double get_longitude() const{ return m_longitude; }

private:

  std::string m_frame;
  double m_latitude;
  double m_longitude;
  double m_altitude;
  double m_attitude;

};

} // namespace qtnp
#endif // POSITION_HPP

