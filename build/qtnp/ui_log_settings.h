/********************************************************************************
** Form generated from reading UI file 'log_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_SETTINGS_H
#define UI_LOG_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_log_settings
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_3;
    QCheckBox *checkbox_pitch;
    QCheckBox *checkbox_roll;
    QCheckBox *checkbox_altitude;
    QCheckBox *checkbox_coordinates;
    QCheckBox *checkbox_speed;
    QCheckBox *checkbox_heading;
    QCheckBox *checkbox_path_lenght_real;
    QCheckBox *checkbox_time_to_finish;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QCheckBox *checkbox_cdt_angles;
    QCheckBox *checkbox_cdt_sides;
    QCheckBox *checkbox_centroid_distance;
    QCheckBox *checkbox_path_angles;
    QCheckBox *checkbox_path_lenght_expected;
    QCheckBox *checkbox_computational_time;
    QPushButton *button_check_all;
    QPushButton *button_uncheck_all;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog_log_settings)
    {
        if (Dialog_log_settings->objectName().isEmpty())
            Dialog_log_settings->setObjectName(QStringLiteral("Dialog_log_settings"));
        Dialog_log_settings->setWindowModality(Qt::ApplicationModal);
        Dialog_log_settings->resize(446, 367);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog_log_settings->sizePolicy().hasHeightForWidth());
        Dialog_log_settings->setSizePolicy(sizePolicy);
        Dialog_log_settings->setModal(true);
        gridLayout = new QGridLayout(Dialog_log_settings);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_3 = new QGroupBox(Dialog_log_settings);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        formLayout_3 = new QFormLayout(groupBox_2);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        checkbox_pitch = new QCheckBox(groupBox_2);
        checkbox_pitch->setObjectName(QStringLiteral("checkbox_pitch"));
        sizePolicy1.setHeightForWidth(checkbox_pitch->sizePolicy().hasHeightForWidth());
        checkbox_pitch->setSizePolicy(sizePolicy1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, checkbox_pitch);

        checkbox_roll = new QCheckBox(groupBox_2);
        checkbox_roll->setObjectName(QStringLiteral("checkbox_roll"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, checkbox_roll);

        checkbox_altitude = new QCheckBox(groupBox_2);
        checkbox_altitude->setObjectName(QStringLiteral("checkbox_altitude"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, checkbox_altitude);

        checkbox_coordinates = new QCheckBox(groupBox_2);
        checkbox_coordinates->setObjectName(QStringLiteral("checkbox_coordinates"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, checkbox_coordinates);

        checkbox_speed = new QCheckBox(groupBox_2);
        checkbox_speed->setObjectName(QStringLiteral("checkbox_speed"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, checkbox_speed);

        checkbox_heading = new QCheckBox(groupBox_2);
        checkbox_heading->setObjectName(QStringLiteral("checkbox_heading"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, checkbox_heading);

        checkbox_path_lenght_real = new QCheckBox(groupBox_2);
        checkbox_path_lenght_real->setObjectName(QStringLiteral("checkbox_path_lenght_real"));

        formLayout_3->setWidget(6, QFormLayout::LabelRole, checkbox_path_lenght_real);

        checkbox_time_to_finish = new QCheckBox(groupBox_2);
        checkbox_time_to_finish->setObjectName(QStringLiteral("checkbox_time_to_finish"));

        formLayout_3->setWidget(7, QFormLayout::LabelRole, checkbox_time_to_finish);


        horizontalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        checkbox_cdt_angles = new QCheckBox(groupBox);
        checkbox_cdt_angles->setObjectName(QStringLiteral("checkbox_cdt_angles"));
        sizePolicy1.setHeightForWidth(checkbox_cdt_angles->sizePolicy().hasHeightForWidth());
        checkbox_cdt_angles->setSizePolicy(sizePolicy1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, checkbox_cdt_angles);

        checkbox_cdt_sides = new QCheckBox(groupBox);
        checkbox_cdt_sides->setObjectName(QStringLiteral("checkbox_cdt_sides"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, checkbox_cdt_sides);

        checkbox_centroid_distance = new QCheckBox(groupBox);
        checkbox_centroid_distance->setObjectName(QStringLiteral("checkbox_centroid_distance"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, checkbox_centroid_distance);

        checkbox_path_angles = new QCheckBox(groupBox);
        checkbox_path_angles->setObjectName(QStringLiteral("checkbox_path_angles"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, checkbox_path_angles);

        checkbox_path_lenght_expected = new QCheckBox(groupBox);
        checkbox_path_lenght_expected->setObjectName(QStringLiteral("checkbox_path_lenght_expected"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, checkbox_path_lenght_expected);

        checkbox_computational_time = new QCheckBox(groupBox);
        checkbox_computational_time->setObjectName(QStringLiteral("checkbox_computational_time"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, checkbox_computational_time);


        horizontalLayout->addWidget(groupBox);


        gridLayout->addWidget(groupBox_3, 0, 0, 1, 2);

        button_check_all = new QPushButton(Dialog_log_settings);
        button_check_all->setObjectName(QStringLiteral("button_check_all"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(button_check_all->sizePolicy().hasHeightForWidth());
        button_check_all->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(button_check_all, 2, 0, 1, 1);

        button_uncheck_all = new QPushButton(Dialog_log_settings);
        button_uncheck_all->setObjectName(QStringLiteral("button_uncheck_all"));
        sizePolicy3.setHeightForWidth(button_uncheck_all->sizePolicy().hasHeightForWidth());
        button_uncheck_all->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(button_uncheck_all, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog_log_settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        sizePolicy3.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy3);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(Dialog_log_settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_log_settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_log_settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_log_settings);
    } // setupUi

    void retranslateUi(QDialog *Dialog_log_settings)
    {
        Dialog_log_settings->setWindowTitle(QApplication::translate("Dialog_log_settings", "Log settings", 0));
        groupBox_3->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("Dialog_log_settings", "During / After flight", 0));
        checkbox_pitch->setText(QApplication::translate("Dialog_log_settings", "Pitch min/max", 0));
        checkbox_roll->setText(QApplication::translate("Dialog_log_settings", "Roll min/max", 0));
        checkbox_altitude->setText(QApplication::translate("Dialog_log_settings", "Altitude min/max", 0));
        checkbox_coordinates->setText(QApplication::translate("Dialog_log_settings", "Coordinates (lat, lon)", 0));
        checkbox_speed->setText(QApplication::translate("Dialog_log_settings", "Speed", 0));
        checkbox_heading->setText(QApplication::translate("Dialog_log_settings", "Heading", 0));
        checkbox_path_lenght_real->setText(QApplication::translate("Dialog_log_settings", "Total path lenght", 0));
        checkbox_time_to_finish->setText(QApplication::translate("Dialog_log_settings", "Time to finish", 0));
        groupBox->setTitle(QApplication::translate("Dialog_log_settings", "Before flight", 0));
        checkbox_cdt_angles->setText(QApplication::translate("Dialog_log_settings", "CDT min/max angles", 0));
        checkbox_cdt_sides->setText(QApplication::translate("Dialog_log_settings", "CDT min/max sides", 0));
        checkbox_centroid_distance->setText(QApplication::translate("Dialog_log_settings", "Min/max centroid distances", 0));
        checkbox_path_angles->setText(QApplication::translate("Dialog_log_settings", "Path min/max angles", 0));
        checkbox_path_lenght_expected->setText(QApplication::translate("Dialog_log_settings", "Total path lenght", 0));
        checkbox_computational_time->setText(QApplication::translate("Dialog_log_settings", "Total computational time", 0));
        button_check_all->setText(QApplication::translate("Dialog_log_settings", "Check All", 0));
        button_uncheck_all->setText(QApplication::translate("Dialog_log_settings", "Uncheck All", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_log_settings: public Ui_Dialog_log_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_SETTINGS_H
