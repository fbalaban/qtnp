/**
 * @file /src/log_settings.cpp
 *
 * @brief Log settings dialog.
 *
 * @date February 2017
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <std_msgs/Float64.h>
#include <QString>
#include <QSettings>
#include <boost/algorithm/string/trim.hpp>
#include <iostream>
#include "../include/qtnp/log_settings.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace Ui {

    using namespace Qt;

    /*****************************************************************************
    ** Helpers
    *****************************************************************************/


    /*****************************************************************************
    ** Implementation
    *****************************************************************************/

    LogSettings::LogSettings(QWidget *parent):
        QDialog(parent)
    {
        ui_log_settings.setupUi(this);
        settings = new QSettings(parent);
        ReadSettings();

    }

    LogSettings::~LogSettings() {
    }

    void LogSettings::ReadSettings() {

        ui_log_settings.checkbox_cdt_angles->setChecked(settings->value("log_cdt_angle",false).toBool());
        ui_log_settings.checkbox_cdt_sides->setChecked(settings->value("log_cdt_sides",false).toBool());
        ui_log_settings.checkbox_centroid_distance->setChecked(settings->value("log_centroid_distance",false).toBool());
        ui_log_settings.checkbox_path_angles->setChecked(settings->value("log_path_angles",false).toBool());
        ui_log_settings.checkbox_path_lenght_expected->setChecked(settings->value("log_path_lenght_expected",false).toBool());
        ui_log_settings.checkbox_computational_time->setChecked(settings->value("log_computational_time",false).toBool());
        ui_log_settings.checkbox_pitch->setChecked(settings->value("log_pitch",false).toBool());
        ui_log_settings.checkbox_roll->setChecked(settings->value("log_roll",false).toBool());
        ui_log_settings.checkbox_altitude->setChecked(settings->value("log_altitude",false).toBool());
        ui_log_settings.checkbox_coordinates->setChecked(settings->value("log_coordinates",false).toBool());
        ui_log_settings.checkbox_speed->setChecked(settings->value("log_speed",false).toBool());
        ui_log_settings.checkbox_heading->setChecked(settings->value("log_heading",false).toBool());
        ui_log_settings.checkbox_path_lenght_real->setChecked(settings->value("log_path_lenght_real",false).toBool());
        ui_log_settings.checkbox_time_to_finish->setChecked(settings->value("log_time_to_finish",false).toBool());

    }

    /*****************************************************************************
    ** Implementation [Slots]
    *****************************************************************************/
    void LogSettings::on_checkbox_cdt_angles_stateChanged(int state) {
        settings->setValue("log_cdt_angle", state);
    }
    void LogSettings::on_checkbox_cdt_sides_stateChanged(int state) {
        settings->setValue("log_cdt_sides", state);
    }
    void LogSettings::on_checkbox_centroid_distance_stateChanged(int state){
            settings->setValue("log_centroid_distance", state);
    }
    void LogSettings::on_checkbox_path_angles_stateChanged(int state){
            settings->setValue("log_path_angles",state);
    }
    void LogSettings::on_checkbox_path_lenght_expected_stateChanged(int state){
            settings->setValue("log_path_lenght_expected",state);
    }
    void LogSettings::on_checkbox_computational_time_stateChanged(int state){
            settings->setValue("log_computational_time",state);
    }
    void LogSettings::on_checkbox_pitch_stateChanged(int state){
            settings->setValue("log_pitch",state);
    }
    void LogSettings::on_checkbox_roll_stateChanged(int state){
            settings->setValue("log_roll",state);
    }
    void LogSettings::on_checkbox_altitude_stateChanged(int state){
            settings->setValue("log_altitude",state);
    }
    void LogSettings::on_checkbox_coordinates_stateChanged(int state){
            settings->setValue("log_coordinates",state);
    }
    void LogSettings::on_checkbox_speed_stateChanged(int state){
            settings->setValue("log_speed",state);
    }
    void LogSettings::on_checkbox_heading_stateChanged(int state){
            settings->setValue("log_heading",state);
    }
    void LogSettings::on_checkbox_path_lenght_real_stateChanged(int state){
            settings->setValue("log_path_lenght_real",state);
    }
    void LogSettings::on_checkbox_time_to_finish_stateChanged(int state){
            settings->setValue("log_time_to_finish",state);
    }

    void LogSettings::on_button_check_all_clicked(bool check){

        QRegExp rx("log_*");
        rx.setPatternSyntax(QRegExp::Wildcard);
        foreach (const QString &key, settings->allKeys()) {
            if (rx.exactMatch(key)){
                settings->setValue(key,true);
            }
        }
        foreach (QCheckBox *box, boxes){
            box->setChecked(true);
        }
    }

    void LogSettings::on_button_uncheck_all_clicked(bool check){

        QRegExp rx("log_*");
        rx.setPatternSyntax(QRegExp::Wildcard);
        foreach (const QString &key, settings->allKeys()) {
            if (rx.exactMatch(key)){
                settings->setValue(key,false);
            }
        }
        foreach (QCheckBox *box, ui_log_settings.groupBox_3->findChildren<QCheckBox *>()){
            box->setChecked(false);
        }
    }

    /*****************************************************************************
    ** Implementation [Configuration]
    *****************************************************************************/

}  // namespace qtnp


