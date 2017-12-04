/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <std_msgs/Float64.h>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QDomDocument>
#include <QTableView>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include "../include/qtnp/main_window.hpp"
#include "../include/qtnp/log_settings.hpp"
#include "../include/qtnp/uas_model.hpp"
#include "../include/qtnp/position.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtnp {

using namespace Qt;

/*****************************************************************************
** Helpers
*****************************************************************************/

qtnp::Placemarks kml_parsing(const QString &filename) {

    QDomDocument doc;
    QFile file(filename);
    qtnp::Placemarks placemarks_msg;

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return placemarks_msg; // return nothing

    QDomNodeList placemarks = doc.elementsByTagName("Placemark");
    for (int i = 0; i < placemarks.size(); i++) {

        QDomNode placemark = placemarks.item(i);
        char split_char = ',';

        // setting the placemark type (constrain or hole)
        qtnp::Coordinates placemark_coordinates;
        placemark_coordinates.placemark_type = placemark.firstChildElement("name").text().toStdString();

        // if the placemark is a hole, we need to also add the coordinates of the seed inside the hole
        if (placemark_coordinates.placemark_type == "hole"){

            std::istringstream split_seed(placemark.firstChildElement("seed").text().toStdString());
            std::vector<std::string> seed_tokens;
            for (std::string each; std::getline(split_seed, each, split_char); seed_tokens.push_back(each));

            placemark_coordinates.seed_latitude = std::atof(seed_tokens[0].c_str());
            placemark_coordinates.seed_longitude = std::atof(seed_tokens[1].c_str());
        }

        // pushing all coordinates to form the shape
        std::string all_coordinates = placemark.namedItem("Polygon").namedItem("LinearRing")
                .firstChildElement("coordinates").text().toStdString();
        split_char = '\n';
        boost::algorithm::trim(all_coordinates);
        std::istringstream split(all_coordinates);
        std::vector<std::string> tokens;
        for (std::string each; std::getline(split, each, split_char); tokens.push_back(each));
        split_char = ',';
        for (int i=0; i<tokens.size(); i++){
            std::istringstream split2(tokens[i]);
            std::vector<std::string> tokens2;
            // TODO: it takes lat and lon incorrectly. in kml file, lon is first
            for (std::string each; std::getline(split2, each, split_char); tokens2.push_back(each));
            placemark_coordinates.latitude.push_back(std::atof(tokens2[0].data()));
            placemark_coordinates.longitude.push_back(std::atof(tokens2[1].data()));
        }

        placemarks_msg.placemarks.push_back(placemark_coordinates);
    }
    return placemarks_msg;
}


/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    /*********************
    ** a simple uas table view
    **********************/
    model = new QStandardItemModel(2,4,this); //2 Rows and 4 Columns

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Sensor type")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("FoV size (m)")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Autonomy %")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Task")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Latitude")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Longitude")));

    ui.table_view_uas->setModel(model);

    /*******************************************/

    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    ReadSettings();
    ui.tab_manager->setCurrentIndex(1); // ensure the second tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    /*********************
    ** Logging
	**********************/

	ui.view_logging->setModel(qnode.loggingModel());
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));

    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/


bool MainWindow::validate_connection(){

    bool result(false);

    if ( ui.checkbox_use_environment->isChecked() ) {
        if ( !qnode.init() ) {
            showNoMasterMessage();
        } else {
            ui.button_connect->setEnabled(false);
            result = true;
        }
    } else {
        if ( ! qnode.init(ui.line_edit_master->text().toStdString(),
                   ui.line_edit_host->text().toStdString()) ) {
            showNoMasterMessage();
        } else {
            ui.button_connect->setEnabled(false);
            ui.line_edit_master->setReadOnly(true);
            ui.line_edit_host->setReadOnly(true);
            ui.line_edit_topic->setReadOnly(true);
            result = true;
        }
    }
    return result;
}

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    // close(); // closes the app
}

void MainWindow::showNoKmlMessage() {

    QMessageBox msgBox;
    msgBox.setText("No kml file is defined.");
    msgBox.exec();
}

void MainWindow::showGenericMessage(QString message) {

    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check ) {
    validate_connection();
}

void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
	bool enabled;
	if ( state == 0 ) {
        enabled = true;
	} else {
        enabled = false;
	}
	ui.line_edit_master->setEnabled(enabled);
	ui.line_edit_host->setEnabled(enabled);
	//ui.line_edit_topic->setEnabled(enabled);
}

void MainWindow::on_button_browse_clicked(bool check ) {

    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open kml file"), "/home/", tr("Kml Files (*.kml)"));

    ui.line_edit_kml_file->setPlaceholderText(filename);
    ui.line_edit_kml_file->setReadOnly(true);

    set_kml_filename(filename);

}

void MainWindow::on_button_broadcast_clicked(bool check ) {

    if ( qnode.get_tnp_update_pointer()->has_global_constraints())
    {
        qnode.enable_broadcasting();
    } else
    {
        showGenericMessage("Area definition and partition must be completed first");
    }

    // TODO: The partitioned and ready CDTs are broadcasted by publishing to topic "global_constraints"

}

void MainWindow::on_button_validate_kml_clicked(bool check ) {

    // TODO
    kml_parsing(kml_filename);

}

void MainWindow::on_button_perform_cdt_clicked(bool check ) {

    // NOTE static kml file name
    // set_kml_filename("/home/fotis/Dev/Data/elefsinaOuterKML.kml");

    double angle_cons(constants::angle_criterion_default);
    double edge_cons(constants::edge_criterion_default);
    int lloyd_iterations(10);

    if ( get_kml_filename() == "" ) {
        showNoKmlMessage();
    } else {
        if (validate_connection()) {
            // TODO validate inputs
            angle_cons = ui.line_edit_angle_constr->text() == "" ?
                        angle_cons : ui.line_edit_angle_constr->text().remove(QRegExp(" .*")).toDouble();
            edge_cons = ui.line_edit_edge_constr->text() == "" ?
                        edge_cons : ui.line_edit_edge_constr->text().remove(QRegExp(" .*")).toDouble();
            lloyd_iterations = ui.spinBox_lloyd->value();

            int uas_count = ui.table_view_uas->model()->rowCount();
            std::vector<double> fov_sizes;
            for (int i=0; i<uas_count; i++){
                fov_sizes.push_back(ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i, 1))).toDouble());
            }
            std::sort(fov_sizes.begin(), fov_sizes.end(), std::greater<int>());

            edge_cons = fov_sizes[0];

            qnode.get_tnp_update_pointer()->perform_polygon_definition
                    (kml_parsing(kml_filename).placemarks, angle_cons, edge_cons, lloyd_iterations);
        }
    }

}

void MainWindow::on_button_add_clicked(bool check ) {
    model->appendRow(new QStandardItem(QString("")));
}

void MainWindow::on_button_remove_clicked(bool check ) {
    model->takeRow((model->rowCount()) -1);
}

void MainWindow::on_button_partition_clicked(bool check ) {

    int auto_check{0};
    int uas_count = ui.table_view_uas->model()->rowCount();

    for (int i=0; i < uas_count; i++){
        auto_check += ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i,2))).toInt();
    }

    if (auto_check !=100){
        showGenericMessage("Autonomy percentages must sum up to 100%");
    } else

    {
        // Visualization options setup
        int button_checked = ui.button_group_color_coding->checkedId();
        std::cout << "button id: " << button_checked << std::endl;
        qnode.get_rviz_objects_pointer()->set_settings(
                      (button_checked == -2 ? true :false ),
                      (button_checked == -3 ? true :false ),
                      (button_checked == -4 ? true :false ),
                      ui.check_box_borders->isChecked(),
                      ui.check_box_waypoints->isChecked());

        // Partitioning setup.
        std::vector<qtnp::Uas_model> uas;

        for (int i=0; i < uas_count; i++){

            double latitude = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i, 4))).toDouble();
            double longitude = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i, 5))).toDouble();
            Position position(latitude, longitude);
            double fov = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i, 1))).toDouble();
            int autonomy_percentage = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(i,2))).toInt();

            qtnp::Uas_model uas_i( (i+1), position, fov, autonomy_percentage);

            uas.push_back(uas_i);

        }

        qnode.get_tnp_update_pointer()->partition(uas);
    }
}

// TODO: validate with introduced changes (uas_model)
void MainWindow::on_button_coverage_clicked(bool checked){

    int uas = ui.spinBox_coverage->value();
    int mountain_sensitivity = ui.spinBox_mountain->value();

    if ((uas < 1) || (uas > ui.table_view_uas->model()->rowCount()) ) showGenericMessage("Please select a valid UAS");
    else {
        std::pair<double, double> coords;
        //lat
        coords.first = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(uas -1, 4))).toDouble();
        //lon
        coords.second = ui.table_view_uas->model()->data(QModelIndex(ui.table_view_uas->model()->index(uas -1, 5))).toDouble();

        qnode.get_tnp_update_pointer()->path_planning_coverage(uas, mountain_sensitivity);
    }
}

void MainWindow::on_button_go_to_goal_clicked(bool checked){

    int uas = ui.spinBox_coverage->value();
    double lat = ui.line_edit_task_lat->text().toDouble();
    double lon = ui.line_edit_task_lon->text().toDouble();
    std::cout << setiosflags(std::ios::fixed | std::ios::showpoint) <<
                 std::setprecision(6) << "uas: " << uas << " lat: " << lat << " lon: " << lon << std::endl;
    if ((uas < 1) || (uas > ui.table_view_uas->model()->rowCount()) ) showGenericMessage("Please select a valid UAS");
    else qnode.get_tnp_update_pointer()->path_planning_to_goal(uas, lat, lon);

}

void MainWindow::on_button_save_uas_config_clicked(bool check){

    QFile file("/home/fotis/uas_table.conf");
     if (file.open(QIODevice::WriteOnly)) {
         QDataStream stream(&file);
         qint32 n(model->rowCount()), m(model->columnCount());
         stream << n << m;

         for (int i=0; i<n; ++i)
             for (int j=0; j<m; j++)
                 model->item(i,j)->write(stream);
         file.close();
     }
}

void MainWindow::on_button_load_last_uas_conf_clicked(bool check){

    QFile file("/home/fotis/uas_table.conf");
     if (file.open(QIODevice::ReadOnly)) {
         QDataStream stream(&file);
         qint32 n, m;
         stream >> n >> m;

         model->setRowCount(n);
         model->setColumnCount(m);
         for (int i=0; i<n; ++i)
             for (int j=0; j<m; j++){

                 QStandardItem *item = new QStandardItem;
                 item->read(stream);
                 model->setItem(i,j,item);
             }
         file.close();
     }

}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
void MainWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>qTnP 0.10</h2><p>Copyright (C) 2016 Fotis Balampanis under the GNU GPL v3 license</p><p>This program performs a "
                                                "Constrained Delaunay Triangulation on a given area, creating regions of interest "
                                                "for a number of UAVs based on their autonomy capabilities. It also produces coverage"
                                                " and go-to-goal task waypoint lists.</p>"));
}


void MainWindow::on_actionLog_options_triggered() {

    Ui::LogSettings settings_dialog(this);
    settings_dialog.exec();
}


/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "qtnp");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://192.168.1.2:11311/")).toString();
    QString host_url = settings.value("host_url", QString("192.168.1.3")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
    	ui.line_edit_master->setEnabled(false);
    	ui.line_edit_host->setEnabled(false);
    	//ui.line_edit_topic->setEnabled(false);
    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "qtnp");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace qtnp

