/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionLog_options;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QTabWidget *tab_manager;
    QWidget *tab_status;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_4;
    QListView *view_logging;
    QWidget *tab_uas_manager;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_8;
    QTableView *table_view_uas;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QPushButton *button_add;
    QPushButton *button_remove;
    QPushButton *button_save_uas_config;
    QPushButton *button_load_last_uas_conf;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBox_3;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *radio_button_hop;
    QRadioButton *radio_button_coverage;
    QRadioButton *radio_button_partitions;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *check_box_borders;
    QCheckBox *check_box_waypoints;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Preferences;
    QStatusBar *statusbar;
    QDockWidget *dock_status;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *line_edit_topic;
    QCheckBox *checkbox_use_environment;
    QLineEdit *line_edit_host;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *line_edit_master;
    QCheckBox *checkbox_remember_settings;
    QPushButton *button_connect;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLabel *label_6;
    QSpinBox *spinBox_lloyd;
    QLineEdit *line_edit_edge_constr;
    QLabel *label_12;
    QLabel *label_5;
    QLineEdit *line_edit_angle_constr;
    QLineEdit *line_edit_kml_file;
    QPushButton *button_partition;
    QPushButton *button_perform_cdt;
    QPushButton *button_validate_kml;
    QPushButton *button_browse;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QLabel *label_9;
    QLineEdit *line_edit_task_lon;
    QLineEdit *line_edit_task_lat;
    QSpinBox *spinBox_coverage;
    QLabel *label_13;
    QLabel *label_10;
    QPushButton *button_coverage;
    QSpinBox *spinBox_mountain;
    QPushButton *button_go_to_goal;
    QPushButton *quit_button;
    QButtonGroup *button_group_color_coding;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QStringLiteral("MainWindowDesign"));
        MainWindowDesign->resize(1026, 551);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowDesign->sizePolicy().hasHeightForWidth());
        MainWindowDesign->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(9);
        MainWindowDesign->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/earth.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        actionLog_options = new QAction(MainWindowDesign);
        actionLog_options->setObjectName(QStringLiteral("actionLog_options"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tab_manager = new QTabWidget(centralwidget);
        tab_manager->setObjectName(QStringLiteral("tab_manager"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tab_manager->sizePolicy().hasHeightForWidth());
        tab_manager->setSizePolicy(sizePolicy1);
        tab_manager->setMinimumSize(QSize(100, 0));
        tab_manager->setFont(font);
        tab_manager->setLocale(QLocale(QLocale::English, QLocale::Australia));
        tab_status = new QWidget();
        tab_status->setObjectName(QStringLiteral("tab_status"));
        verticalLayout_2 = new QVBoxLayout(tab_status);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_12 = new QGroupBox(tab_status);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(groupBox_12);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        view_logging = new QListView(groupBox_12);
        view_logging->setObjectName(QStringLiteral("view_logging"));

        verticalLayout_4->addWidget(view_logging);


        verticalLayout_2->addWidget(groupBox_12);

        tab_manager->addTab(tab_status, QString());
        tab_uas_manager = new QWidget();
        tab_uas_manager->setObjectName(QStringLiteral("tab_uas_manager"));
        tab_uas_manager->setEnabled(true);
        verticalLayout_8 = new QVBoxLayout(tab_uas_manager);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        groupBox_3 = new QGroupBox(tab_uas_manager);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(label_8);

        table_view_uas = new QTableView(groupBox_3);
        table_view_uas->setObjectName(QStringLiteral("table_view_uas"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(table_view_uas->sizePolicy().hasHeightForWidth());
        table_view_uas->setSizePolicy(sizePolicy3);

        verticalLayout_7->addWidget(table_view_uas);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        button_add = new QPushButton(groupBox_4);
        button_add->setObjectName(QStringLiteral("button_add"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(button_add->sizePolicy().hasHeightForWidth());
        button_add->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(button_add, 0, 0, 1, 1);

        button_remove = new QPushButton(groupBox_4);
        button_remove->setObjectName(QStringLiteral("button_remove"));
        sizePolicy4.setHeightForWidth(button_remove->sizePolicy().hasHeightForWidth());
        button_remove->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(button_remove, 0, 1, 1, 1);

        button_save_uas_config = new QPushButton(groupBox_4);
        button_save_uas_config->setObjectName(QStringLiteral("button_save_uas_config"));

        gridLayout_3->addWidget(button_save_uas_config, 1, 0, 1, 1);

        button_load_last_uas_conf = new QPushButton(groupBox_4);
        button_load_last_uas_conf->setObjectName(QStringLiteral("button_load_last_uas_conf"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(button_load_last_uas_conf->sizePolicy().hasHeightForWidth());
        button_load_last_uas_conf->setSizePolicy(sizePolicy5);
        button_load_last_uas_conf->setIconSize(QSize(17, 17));

        gridLayout_3->addWidget(button_load_last_uas_conf, 1, 1, 1, 1);


        verticalLayout_7->addWidget(groupBox_4);


        verticalLayout_8->addWidget(groupBox_3);

        groupBox_6 = new QGroupBox(tab_uas_manager);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy6);
        groupBox_6->setAlignment(Qt::AlignJustify|Qt::AlignTop);
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_8 = new QGroupBox(groupBox_6);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy7);
        verticalLayout_6 = new QVBoxLayout(groupBox_8);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        checkBox_3 = new QCheckBox(groupBox_8);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_6->addWidget(checkBox_3);


        gridLayout_2->addWidget(groupBox_8, 0, 2, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_6);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy8);
        groupBox_9->setCheckable(false);
        verticalLayout_9 = new QVBoxLayout(groupBox_9);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        radio_button_hop = new QRadioButton(groupBox_9);
        button_group_color_coding = new QButtonGroup(MainWindowDesign);
        button_group_color_coding->setObjectName(QStringLiteral("button_group_color_coding"));
        button_group_color_coding->addButton(radio_button_hop);
        radio_button_hop->setObjectName(QStringLiteral("radio_button_hop"));
        sizePolicy5.setHeightForWidth(radio_button_hop->sizePolicy().hasHeightForWidth());
        radio_button_hop->setSizePolicy(sizePolicy5);
        radio_button_hop->setChecked(true);

        verticalLayout_9->addWidget(radio_button_hop);

        radio_button_coverage = new QRadioButton(groupBox_9);
        button_group_color_coding->addButton(radio_button_coverage);
        radio_button_coverage->setObjectName(QStringLiteral("radio_button_coverage"));

        verticalLayout_9->addWidget(radio_button_coverage);

        radio_button_partitions = new QRadioButton(groupBox_9);
        button_group_color_coding->addButton(radio_button_partitions);
        radio_button_partitions->setObjectName(QStringLiteral("radio_button_partitions"));

        verticalLayout_9->addWidget(radio_button_partitions);


        gridLayout_2->addWidget(groupBox_9, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        QSizePolicy sizePolicy9(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy9);
        verticalLayout_5 = new QVBoxLayout(groupBox_7);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        check_box_borders = new QCheckBox(groupBox_7);
        check_box_borders->setObjectName(QStringLiteral("check_box_borders"));

        verticalLayout_5->addWidget(check_box_borders);

        check_box_waypoints = new QCheckBox(groupBox_7);
        check_box_waypoints->setObjectName(QStringLiteral("check_box_waypoints"));
        check_box_waypoints->setEnabled(false);

        verticalLayout_5->addWidget(check_box_waypoints);


        gridLayout_2->addWidget(groupBox_7, 0, 1, 1, 1);


        verticalLayout_8->addWidget(groupBox_6);

        tab_manager->addTab(tab_uas_manager, QString());

        gridLayout_4->addWidget(tab_manager, 0, 0, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1026, 19));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Preferences = new QMenu(menu_File);
        menu_Preferences->setObjectName(QStringLiteral("menu_Preferences"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        dock_status = new QDockWidget(MainWindowDesign);
        dock_status->setObjectName(QStringLiteral("dock_status"));
        dock_status->setEnabled(true);
        sizePolicy1.setHeightForWidth(dock_status->sizePolicy().hasHeightForWidth());
        dock_status->setSizePolicy(sizePolicy1);
        dock_status->setFloating(false);
        dock_status->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dock_status->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy10);
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy11);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy6.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy6);
        groupBox->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        line_edit_topic = new QLineEdit(groupBox);
        line_edit_topic->setObjectName(QStringLiteral("line_edit_topic"));
        line_edit_topic->setEnabled(false);
        sizePolicy5.setHeightForWidth(line_edit_topic->sizePolicy().hasHeightForWidth());
        line_edit_topic->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(line_edit_topic, 5, 1, 1, 1);

        checkbox_use_environment = new QCheckBox(groupBox);
        checkbox_use_environment->setObjectName(QStringLiteral("checkbox_use_environment"));
        sizePolicy5.setHeightForWidth(checkbox_use_environment->sizePolicy().hasHeightForWidth());
        checkbox_use_environment->setSizePolicy(sizePolicy5);
        checkbox_use_environment->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_use_environment, 8, 1, 1, 1);

        line_edit_host = new QLineEdit(groupBox);
        line_edit_host->setObjectName(QStringLiteral("line_edit_host"));
        sizePolicy5.setHeightForWidth(line_edit_host->sizePolicy().hasHeightForWidth());
        line_edit_host->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(line_edit_host, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy5.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy5);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        line_edit_master = new QLineEdit(groupBox);
        line_edit_master->setObjectName(QStringLiteral("line_edit_master"));
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(line_edit_master->sizePolicy().hasHeightForWidth());
        line_edit_master->setSizePolicy(sizePolicy12);

        gridLayout->addWidget(line_edit_master, 0, 1, 1, 1);

        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QStringLiteral("checkbox_remember_settings"));
        sizePolicy9.setHeightForWidth(checkbox_remember_settings->sizePolicy().hasHeightForWidth());
        checkbox_remember_settings->setSizePolicy(sizePolicy9);
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 8, 0, 1, 1);

        button_connect = new QPushButton(groupBox);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);
        sizePolicy12.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy12);

        gridLayout->addWidget(button_connect, 9, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy6.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy6);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_6, 2, 0, 1, 1);

        spinBox_lloyd = new QSpinBox(groupBox_2);
        spinBox_lloyd->setObjectName(QStringLiteral("spinBox_lloyd"));
        sizePolicy1.setHeightForWidth(spinBox_lloyd->sizePolicy().hasHeightForWidth());
        spinBox_lloyd->setSizePolicy(sizePolicy1);
        spinBox_lloyd->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_lloyd->setMinimum(1);
        spinBox_lloyd->setMaximum(50);
        spinBox_lloyd->setValue(10);

        gridLayout_5->addWidget(spinBox_lloyd, 4, 2, 1, 1);

        line_edit_edge_constr = new QLineEdit(groupBox_2);
        line_edit_edge_constr->setObjectName(QStringLiteral("line_edit_edge_constr"));
        sizePolicy9.setHeightForWidth(line_edit_edge_constr->sizePolicy().hasHeightForWidth());
        line_edit_edge_constr->setSizePolicy(sizePolicy9);
        line_edit_edge_constr->setMaxLength(10);

        gridLayout_5->addWidget(line_edit_edge_constr, 0, 5, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_5->addWidget(label_12, 4, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy5.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_5, 0, 4, 1, 1);

        line_edit_angle_constr = new QLineEdit(groupBox_2);
        line_edit_angle_constr->setObjectName(QStringLiteral("line_edit_angle_constr"));
        sizePolicy9.setHeightForWidth(line_edit_angle_constr->sizePolicy().hasHeightForWidth());
        line_edit_angle_constr->setSizePolicy(sizePolicy9);
        line_edit_angle_constr->setMaxLength(10);

        gridLayout_5->addWidget(line_edit_angle_constr, 0, 2, 1, 1);

        line_edit_kml_file = new QLineEdit(groupBox_2);
        line_edit_kml_file->setObjectName(QStringLiteral("line_edit_kml_file"));
        sizePolicy9.setHeightForWidth(line_edit_kml_file->sizePolicy().hasHeightForWidth());
        line_edit_kml_file->setSizePolicy(sizePolicy9);
        line_edit_kml_file->setReadOnly(false);

        gridLayout_5->addWidget(line_edit_kml_file, 2, 2, 1, 1);

        button_partition = new QPushButton(groupBox_2);
        button_partition->setObjectName(QStringLiteral("button_partition"));
        sizePolicy10.setHeightForWidth(button_partition->sizePolicy().hasHeightForWidth());
        button_partition->setSizePolicy(sizePolicy10);

        gridLayout_5->addWidget(button_partition, 4, 5, 1, 1);

        button_perform_cdt = new QPushButton(groupBox_2);
        button_perform_cdt->setObjectName(QStringLiteral("button_perform_cdt"));
        sizePolicy1.setHeightForWidth(button_perform_cdt->sizePolicy().hasHeightForWidth());
        button_perform_cdt->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(button_perform_cdt, 4, 4, 1, 1);

        button_validate_kml = new QPushButton(groupBox_2);
        button_validate_kml->setObjectName(QStringLiteral("button_validate_kml"));
        button_validate_kml->setEnabled(false);
        sizePolicy5.setHeightForWidth(button_validate_kml->sizePolicy().hasHeightForWidth());
        button_validate_kml->setSizePolicy(sizePolicy5);
        button_validate_kml->setFlat(false);

        gridLayout_5->addWidget(button_validate_kml, 2, 5, 1, 1);

        button_browse = new QPushButton(groupBox_2);
        button_browse->setObjectName(QStringLiteral("button_browse"));
        sizePolicy5.setHeightForWidth(button_browse->sizePolicy().hasHeightForWidth());
        button_browse->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(button_browse, 2, 4, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy6.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy6);

        gridLayout_6->addWidget(label_9, 0, 0, 1, 1);

        line_edit_task_lon = new QLineEdit(groupBox_5);
        line_edit_task_lon->setObjectName(QStringLiteral("line_edit_task_lon"));
        sizePolicy12.setHeightForWidth(line_edit_task_lon->sizePolicy().hasHeightForWidth());
        line_edit_task_lon->setSizePolicy(sizePolicy12);

        gridLayout_6->addWidget(line_edit_task_lon, 2, 1, 1, 1);

        line_edit_task_lat = new QLineEdit(groupBox_5);
        line_edit_task_lat->setObjectName(QStringLiteral("line_edit_task_lat"));
        sizePolicy12.setHeightForWidth(line_edit_task_lat->sizePolicy().hasHeightForWidth());
        line_edit_task_lat->setSizePolicy(sizePolicy12);

        gridLayout_6->addWidget(line_edit_task_lat, 2, 2, 1, 1);

        spinBox_coverage = new QSpinBox(groupBox_5);
        spinBox_coverage->setObjectName(QStringLiteral("spinBox_coverage"));
        sizePolicy6.setHeightForWidth(spinBox_coverage->sizePolicy().hasHeightForWidth());
        spinBox_coverage->setSizePolicy(sizePolicy6);
        spinBox_coverage->setMaximum(10);

        gridLayout_6->addWidget(spinBox_coverage, 0, 1, 1, 1);

        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));
        QSizePolicy sizePolicy13(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy13);

        gridLayout_6->addWidget(label_13, 0, 2, 1, 1);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy9.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy9);

        gridLayout_6->addWidget(label_10, 2, 0, 1, 1);

        button_coverage = new QPushButton(groupBox_5);
        button_coverage->setObjectName(QStringLiteral("button_coverage"));
        QSizePolicy sizePolicy14(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(button_coverage->sizePolicy().hasHeightForWidth());
        button_coverage->setSizePolicy(sizePolicy14);

        gridLayout_6->addWidget(button_coverage, 1, 3, 1, 1);

        spinBox_mountain = new QSpinBox(groupBox_5);
        spinBox_mountain->setObjectName(QStringLiteral("spinBox_mountain"));
        sizePolicy14.setHeightForWidth(spinBox_mountain->sizePolicy().hasHeightForWidth());
        spinBox_mountain->setSizePolicy(sizePolicy14);
        spinBox_mountain->setMinimum(2);
        spinBox_mountain->setMaximum(6);

        gridLayout_6->addWidget(spinBox_mountain, 0, 3, 1, 1);

        button_go_to_goal = new QPushButton(groupBox_5);
        button_go_to_goal->setObjectName(QStringLiteral("button_go_to_goal"));
        sizePolicy14.setHeightForWidth(button_go_to_goal->sizePolicy().hasHeightForWidth());
        button_go_to_goal->setSizePolicy(sizePolicy14);

        gridLayout_6->addWidget(button_go_to_goal, 2, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox_5);

        quit_button = new QPushButton(frame);
        quit_button->setObjectName(QStringLiteral("quit_button"));
        sizePolicy12.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy12);

        verticalLayout_3->addWidget(quit_button);


        verticalLayout->addWidget(frame);

        dock_status->setWidget(dockWidgetContents_2);
        MainWindowDesign->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_status);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(menu_Preferences->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menu_Preferences->addAction(actionLog_options);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));
        QObject::connect(quit_button, SIGNAL(clicked()), MainWindowDesign, SLOT(close()));

        tab_manager->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "qTnP Application", 0));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", 0));
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", 0));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", 0));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", 0));
        actionLog_options->setText(QApplication::translate("MainWindowDesign", "Log options", 0));
        groupBox_12->setTitle(QApplication::translate("MainWindowDesign", "Logging", 0));
        tab_manager->setTabText(tab_manager->indexOf(tab_status), QApplication::translate("MainWindowDesign", "Ros Communications", 0));
        groupBox_3->setTitle(QString());
        label_8->setText(QApplication::translate("MainWindowDesign", "UAV Table", 0));
        groupBox_4->setTitle(QString());
        button_add->setText(QApplication::translate("MainWindowDesign", "add row", 0));
        button_remove->setText(QApplication::translate("MainWindowDesign", "remove row", 0));
        button_save_uas_config->setText(QApplication::translate("MainWindowDesign", "save configuration", 0));
        button_load_last_uas_conf->setText(QApplication::translate("MainWindowDesign", "load last configuration", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindowDesign", "Visualization", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindowDesign", "Gazebo", 0));
        checkBox_3->setText(QApplication::translate("MainWindowDesign", "Enable", 0));
        groupBox_9->setTitle(QApplication::translate("MainWindowDesign", "Color coding", 0));
        radio_button_hop->setText(QApplication::translate("MainWindowDesign", "Isotropic cost", 0));
        radio_button_coverage->setText(QApplication::translate("MainWindowDesign", "Watershed cost", 0));
        radio_button_partitions->setText(QApplication::translate("MainWindowDesign", "Partitions", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindowDesign", "Rviz", 0));
        check_box_borders->setText(QApplication::translate("MainWindowDesign", "Show Borders", 0));
        check_box_waypoints->setText(QApplication::translate("MainWindowDesign", "Show Waypoints", 0));
        tab_manager->setTabText(tab_manager->indexOf(tab_uas_manager), QApplication::translate("MainWindowDesign", "UAV Manager", 0));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", 0));
        menu_Preferences->setTitle(QApplication::translate("MainWindowDesign", "&Preferences", 0));
        dock_status->setWindowTitle(QApplication::translate("MainWindowDesign", "Command Panel", 0));
        groupBox->setTitle(QApplication::translate("MainWindowDesign", "1. Ros Master", 0));
        label_2->setText(QApplication::translate("MainWindowDesign", "Ros IP", 0));
        line_edit_topic->setText(QApplication::translate("MainWindowDesign", "unused", 0));
        checkbox_use_environment->setText(QApplication::translate("MainWindowDesign", "Use environment variables", 0));
        line_edit_host->setText(QApplication::translate("MainWindowDesign", "192.168.1.67", 0));
        label->setText(QApplication::translate("MainWindowDesign", "Ros Master Url", 0));
        label_3->setText(QApplication::translate("MainWindowDesign", "Ros Hostname", 0));
        line_edit_master->setText(QApplication::translate("MainWindowDesign", "http://192.168.1.2:11311/", 0));
        checkbox_remember_settings->setText(QApplication::translate("MainWindowDesign", "Remember settings on startup", 0));
#ifndef QT_NO_TOOLTIP
        button_connect->setToolTip(QApplication::translate("MainWindowDesign", "Set the target to the current joint trajectory state.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        button_connect->setStatusTip(QApplication::translate("MainWindowDesign", "Clear all waypoints and set the target to the current joint trajectory state.", 0));
#endif // QT_NO_STATUSTIP
        button_connect->setText(QApplication::translate("MainWindowDesign", "Connect", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindowDesign", "2. CDT And Partition", 0));
        label_4->setText(QApplication::translate("MainWindowDesign", "Angle", 0));
        label_6->setText(QApplication::translate("MainWindowDesign", "Kml file:", 0));
        label_12->setText(QApplication::translate("MainWindowDesign", "Lloyd Iterations", 0));
        label_5->setText(QApplication::translate("MainWindowDesign", "Edge", 0));
        line_edit_angle_constr->setPlaceholderText(QApplication::translate("MainWindowDesign", "max 0.320 recommended 0.125", 0));
        line_edit_kml_file->setPlaceholderText(QApplication::translate("MainWindowDesign", "(empty)", 0));
        button_partition->setText(QApplication::translate("MainWindowDesign", "Partitioning", 0));
        button_perform_cdt->setText(QApplication::translate("MainWindowDesign", "Perform CDT", 0));
        button_validate_kml->setText(QApplication::translate("MainWindowDesign", "Validate", 0));
        button_browse->setText(QApplication::translate("MainWindowDesign", "Browse", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindowDesign", "3. Path planning", 0));
        label_9->setText(QApplication::translate("MainWindowDesign", "For UAV", 0));
        line_edit_task_lon->setInputMask(QApplication::translate("MainWindowDesign", "#009.999999", 0));
        line_edit_task_lat->setInputMask(QApplication::translate("MainWindowDesign", "#009.999999", 0));
        label_13->setText(QApplication::translate("MainWindowDesign", "Mountain sensitivity", 0));
        label_10->setText(QApplication::translate("MainWindowDesign", "Lat, Lon", 0));
        button_coverage->setText(QApplication::translate("MainWindowDesign", "Coverage", 0));
#ifndef QT_NO_TOOLTIP
        spinBox_mountain->setToolTip(QApplication::translate("MainWindowDesign", "Smaller: will always detect unreachable mountain regions. Bigger, less sensitivity -> might miss some mountains", 0));
#endif // QT_NO_TOOLTIP
        button_go_to_goal->setText(QApplication::translate("MainWindowDesign", "Go!", 0));
        quit_button->setText(QApplication::translate("MainWindowDesign", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
