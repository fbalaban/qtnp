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

    const double angle_criterion(0.125);
    const double edge_criterion(25.0);
}

#endif /* qtnp_CONSTANTS_HPP_ */
