/**
 * @file /include/qtnp/constants.hpp
 *
 * @brief Constants
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtnp_CONSTANTS_HPP_
#define qtnp_CONSTANTS_HPP_

namespace constants
{
    const int coverage_depth_max(999);
    const double max_lat(90.1);
    const double min_lat(-90.1);
    const double max_lon(180.1);
    const double min_lon(-180.1);

    const double rviz_range_min(0.0);
    const double rviz_range_max(500.0);

    const double angle_criterion_default(0.125);
    const double edge_criterion_default(50.0);

    const double PI = 3.1415926;
    const static double r_earth = 6378.137; // in kilometers
}

#endif /* qtnp_CONSTANTS_HPP_ */
