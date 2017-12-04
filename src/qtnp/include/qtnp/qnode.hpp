/**
 * @file /include/qtnp/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date May 2016
 *
 * @author Fotis Balampanis fbalaban@cs.teiath.gr
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtnp_QNODE_HPP_
#define qtnp_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QString>

#include "rviz_objects.hpp"
#include "tnp_update.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv);
    ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

    void init_publishers(ros::NodeHandle n);

    Tnp_update *get_tnp_update_pointer(){ return &tnp_update; }
    Rviz_objects *get_rviz_objects_pointer(){ return &rviz_objects; }

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

    void enable_broadcasting(){broadcasting_constraints = true;}

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;

    Rviz_objects rviz_objects;
    Tnp_update tnp_update;

    ros::Publisher chatter_publisher, edges_pub, polygon_pub, triangulation_mesh_pub, center_pub, path_pub, grid_marker_pub, global_constraints_pub;
    ros::ServiceClient waypoints_s_client;

    QStringListModel logging_model;
    bool broadcasting_constraints{false};
};

}  // namespace qtnp

#endif /* qtnp_QNODE_HPP_ */
