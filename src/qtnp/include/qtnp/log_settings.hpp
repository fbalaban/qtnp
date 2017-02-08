 
/**
 * @file /include/qtnp/log_settings.hpp
 *
 * @brief Log settings dialog.
 *
 * @date February 2017
 **/
#ifndef qtnp_LOG_SETTINGS_HPP
#define qtnp_LOG_SETTINGS_HPP

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QDialog>
#include <QSettings>
#include <QStandardItemModel>
#include "ui_log_settings.h"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace Ui {

/*****************************************************************************
** Interface [LogSettings]
*****************************************************************************/

class LogSettings : public QDialog {

    Q_OBJECT

public:
    LogSettings(QWidget *parent);
    ~LogSettings();

    void ReadSettings();

public Q_SLOTS:

    void on_checkbox_cdt_angles_stateChanged(int state);
    void on_checkbox_cdt_sides_stateChanged(int state);
    void on_checkbox_centroid_distance_stateChanged(int state);
    void on_checkbox_path_angles_stateChanged(int state);
    void on_checkbox_path_lenght_expected_stateChanged(int state);
    void on_checkbox_computational_time_stateChanged(int state);
    void on_checkbox_pitch_stateChanged(int state);
    void on_checkbox_roll_stateChanged(int state);
    void on_checkbox_altitude_stateChanged(int state);
    void on_checkbox_coordinates_stateChanged(int state);
    void on_checkbox_speed_stateChanged(int state);
    void on_checkbox_heading_stateChanged(int state);
    void on_checkbox_path_lenght_real_stateChanged(int state);
    void on_checkbox_time_to_finish_stateChanged(int state);

    void on_button_check_all_clicked(bool check);
    void on_button_uncheck_all_clicked(bool check);

private:
    Ui::Dialog_log_settings ui_log_settings;
    QSettings* settings;
};

}  // namespace qtnp

#endif // qtnp_LOG_SETTINGS_HPP
