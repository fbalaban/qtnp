/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
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
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *checkBox_3;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QMenuBar *menubar;
    QMenu *menu_File;
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
    QLineEdit *line_edit_kml_file;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *line_edit_edge_constr;
    QLineEdit *line_edit_angle_constr;
    QPushButton *button_validate_kml;
    QPushButton *button_browse;
    QPushButton *button_perform_cdt;
    QGroupBox *groupBox_5;
    QLabel *label_7;
    QLabel *label_11;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit;
    QPushButton *button_partition;
    QSpinBox *spinBox_coverage;
    QPushButton *button_coverage;
    QPushButton *quit_button;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(944, 704);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tab_manager = new QTabWidget(centralwidget);
        tab_manager->setObjectName(QString::fromUtf8("tab_manager"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tab_manager->sizePolicy().hasHeightForWidth());
        tab_manager->setSizePolicy(sizePolicy);
        tab_manager->setMinimumSize(QSize(100, 0));
        tab_manager->setLocale(QLocale(QLocale::English, QLocale::Australia));
        tab_status = new QWidget();
        tab_status->setObjectName(QString::fromUtf8("tab_status"));
        verticalLayout_2 = new QVBoxLayout(tab_status);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_12 = new QGroupBox(tab_status);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_12->sizePolicy().hasHeightForWidth());
        groupBox_12->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(groupBox_12);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        view_logging = new QListView(groupBox_12);
        view_logging->setObjectName(QString::fromUtf8("view_logging"));

        verticalLayout_4->addWidget(view_logging);


        verticalLayout_2->addWidget(groupBox_12);

        tab_manager->addTab(tab_status, QString());
        tab_uas_manager = new QWidget();
        tab_uas_manager->setObjectName(QString::fromUtf8("tab_uas_manager"));
        tab_uas_manager->setEnabled(true);
        verticalLayout_8 = new QVBoxLayout(tab_uas_manager);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox_3 = new QGroupBox(tab_uas_manager);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        groupBox_3->setAlignment(Qt::AlignCenter);
        verticalLayout_7 = new QVBoxLayout(groupBox_3);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_7->addWidget(label_8);

        table_view_uas = new QTableView(groupBox_3);
        table_view_uas->setObjectName(QString::fromUtf8("table_view_uas"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(table_view_uas->sizePolicy().hasHeightForWidth());
        table_view_uas->setSizePolicy(sizePolicy3);

        verticalLayout_7->addWidget(table_view_uas);

        groupBox_4 = new QGroupBox(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        button_add = new QPushButton(groupBox_4);
        button_add->setObjectName(QString::fromUtf8("button_add"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(button_add->sizePolicy().hasHeightForWidth());
        button_add->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(button_add, 0, 0, 1, 1);

        button_remove = new QPushButton(groupBox_4);
        button_remove->setObjectName(QString::fromUtf8("button_remove"));
        sizePolicy4.setHeightForWidth(button_remove->sizePolicy().hasHeightForWidth());
        button_remove->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(button_remove, 0, 1, 1, 1);

        button_save_uas_config = new QPushButton(groupBox_4);
        button_save_uas_config->setObjectName(QString::fromUtf8("button_save_uas_config"));

        gridLayout_3->addWidget(button_save_uas_config, 1, 0, 1, 1);

        button_load_last_uas_conf = new QPushButton(groupBox_4);
        button_load_last_uas_conf->setObjectName(QString::fromUtf8("button_load_last_uas_conf"));
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
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy6);
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy7);
        verticalLayout_5 = new QVBoxLayout(groupBox_7);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBox = new QCheckBox(groupBox_7);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_5->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox_7);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        verticalLayout_5->addWidget(checkBox_2);


        gridLayout_2->addWidget(groupBox_7, 0, 1, 1, 1);

        groupBox_8 = new QGroupBox(groupBox_6);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy8);
        verticalLayout_6 = new QVBoxLayout(groupBox_8);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        checkBox_3 = new QCheckBox(groupBox_8);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        verticalLayout_6->addWidget(checkBox_3);


        gridLayout_2->addWidget(groupBox_8, 0, 2, 1, 1);

        groupBox_9 = new QGroupBox(groupBox_6);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy9);
        verticalLayout_9 = new QVBoxLayout(groupBox_9);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        radioButton = new QRadioButton(groupBox_9);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        sizePolicy5.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy5);

        verticalLayout_9->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_9);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_9->addWidget(radioButton_2);


        gridLayout_2->addWidget(groupBox_9, 0, 0, 1, 1);


        verticalLayout_8->addWidget(groupBox_6);

        tab_manager->addTab(tab_uas_manager, QString());

        gridLayout_4->addWidget(tab_manager, 0, 0, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 944, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        dock_status = new QDockWidget(MainWindowDesign);
        dock_status->setObjectName(QString::fromUtf8("dock_status"));
        dock_status->setEnabled(true);
        QSizePolicy sizePolicy10(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(dock_status->sizePolicy().hasHeightForWidth());
        dock_status->setSizePolicy(sizePolicy10);
        dock_status->setFloating(false);
        dock_status->setFeatures(QDockWidget::NoDockWidgetFeatures);
        dock_status->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        sizePolicy2.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(dockWidgetContents_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy5.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy5);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy6.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy6);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        line_edit_topic = new QLineEdit(groupBox);
        line_edit_topic->setObjectName(QString::fromUtf8("line_edit_topic"));
        line_edit_topic->setEnabled(false);
        sizePolicy5.setHeightForWidth(line_edit_topic->sizePolicy().hasHeightForWidth());
        line_edit_topic->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(line_edit_topic, 5, 1, 1, 1);

        checkbox_use_environment = new QCheckBox(groupBox);
        checkbox_use_environment->setObjectName(QString::fromUtf8("checkbox_use_environment"));
        sizePolicy5.setHeightForWidth(checkbox_use_environment->sizePolicy().hasHeightForWidth());
        checkbox_use_environment->setSizePolicy(sizePolicy5);
        checkbox_use_environment->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_use_environment, 8, 1, 1, 1);

        line_edit_host = new QLineEdit(groupBox);
        line_edit_host->setObjectName(QString::fromUtf8("line_edit_host"));
        sizePolicy5.setHeightForWidth(line_edit_host->sizePolicy().hasHeightForWidth());
        line_edit_host->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(line_edit_host, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy5.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy5);
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy5.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy5);
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        line_edit_master = new QLineEdit(groupBox);
        line_edit_master->setObjectName(QString::fromUtf8("line_edit_master"));
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(line_edit_master->sizePolicy().hasHeightForWidth());
        line_edit_master->setSizePolicy(sizePolicy11);

        gridLayout->addWidget(line_edit_master, 0, 1, 1, 1);

        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QString::fromUtf8("checkbox_remember_settings"));
        sizePolicy7.setHeightForWidth(checkbox_remember_settings->sizePolicy().hasHeightForWidth());
        checkbox_remember_settings->setSizePolicy(sizePolicy7);
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 8, 0, 1, 1);

        button_connect = new QPushButton(groupBox);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));
        button_connect->setEnabled(true);
        sizePolicy11.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy11);

        gridLayout->addWidget(button_connect, 9, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy12);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        line_edit_kml_file = new QLineEdit(groupBox_2);
        line_edit_kml_file->setObjectName(QString::fromUtf8("line_edit_kml_file"));
        sizePolicy5.setHeightForWidth(line_edit_kml_file->sizePolicy().hasHeightForWidth());
        line_edit_kml_file->setSizePolicy(sizePolicy5);
        line_edit_kml_file->setReadOnly(false);

        gridLayout_5->addWidget(line_edit_kml_file, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy5.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy5.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy5.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);

        line_edit_edge_constr = new QLineEdit(groupBox_2);
        line_edit_edge_constr->setObjectName(QString::fromUtf8("line_edit_edge_constr"));
        sizePolicy5.setHeightForWidth(line_edit_edge_constr->sizePolicy().hasHeightForWidth());
        line_edit_edge_constr->setSizePolicy(sizePolicy5);
        line_edit_edge_constr->setMaxLength(10);

        gridLayout_5->addWidget(line_edit_edge_constr, 1, 1, 1, 2);

        line_edit_angle_constr = new QLineEdit(groupBox_2);
        line_edit_angle_constr->setObjectName(QString::fromUtf8("line_edit_angle_constr"));
        sizePolicy5.setHeightForWidth(line_edit_angle_constr->sizePolicy().hasHeightForWidth());
        line_edit_angle_constr->setSizePolicy(sizePolicy5);
        line_edit_angle_constr->setMaxLength(10);

        gridLayout_5->addWidget(line_edit_angle_constr, 0, 1, 1, 2);

        button_validate_kml = new QPushButton(groupBox_2);
        button_validate_kml->setObjectName(QString::fromUtf8("button_validate_kml"));
        button_validate_kml->setEnabled(false);
        sizePolicy5.setHeightForWidth(button_validate_kml->sizePolicy().hasHeightForWidth());
        button_validate_kml->setSizePolicy(sizePolicy5);
        button_validate_kml->setFlat(false);

        gridLayout_5->addWidget(button_validate_kml, 5, 1, 1, 1);

        button_browse = new QPushButton(groupBox_2);
        button_browse->setObjectName(QString::fromUtf8("button_browse"));
        sizePolicy5.setHeightForWidth(button_browse->sizePolicy().hasHeightForWidth());
        button_browse->setSizePolicy(sizePolicy5);

        gridLayout_5->addWidget(button_browse, 2, 2, 1, 1);

        button_perform_cdt = new QPushButton(groupBox_2);
        button_perform_cdt->setObjectName(QString::fromUtf8("button_perform_cdt"));
        sizePolicy12.setHeightForWidth(button_perform_cdt->sizePolicy().hasHeightForWidth());
        button_perform_cdt->setSizePolicy(sizePolicy12);

        gridLayout_5->addWidget(button_perform_cdt, 5, 2, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy5.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy5);
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(44, 40, 260, 16));
        QSizePolicy sizePolicy13(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy13);
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(120, 140, 47, 16));
        sizePolicy7.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy7);
        lineEdit_2 = new QLineEdit(groupBox_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 140, 125, 24));
        QSizePolicy sizePolicy14(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy14);
        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 140, 80, 24));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 80, 203, 16));
        sizePolicy7.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy7);
        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(61, 110, 107, 16));
        sizePolicy7.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy7);
        lineEdit = new QLineEdit(groupBox_5);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 110, 125, 24));
        sizePolicy11.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy11);
        button_partition = new QPushButton(groupBox_5);
        button_partition->setObjectName(QString::fromUtf8("button_partition"));
        button_partition->setGeometry(QRect(320, 40, 80, 24));
        sizePolicy13.setHeightForWidth(button_partition->sizePolicy().hasHeightForWidth());
        button_partition->setSizePolicy(sizePolicy13);
        spinBox_coverage = new QSpinBox(groupBox_5);
        spinBox_coverage->setObjectName(QString::fromUtf8("spinBox_coverage"));
        spinBox_coverage->setGeometry(QRect(260, 74, 46, 25));
        sizePolicy7.setHeightForWidth(spinBox_coverage->sizePolicy().hasHeightForWidth());
        spinBox_coverage->setSizePolicy(sizePolicy7);
        spinBox_coverage->setMaximum(10);
        button_coverage = new QPushButton(groupBox_5);
        button_coverage->setObjectName(QString::fromUtf8("button_coverage"));
        button_coverage->setGeometry(QRect(320, 74, 80, 24));
        sizePolicy14.setHeightForWidth(button_coverage->sizePolicy().hasHeightForWidth());
        button_coverage->setSizePolicy(sizePolicy14);

        verticalLayout_3->addWidget(groupBox_5);


        verticalLayout->addWidget(frame);

        quit_button = new QPushButton(dockWidgetContents_2);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        sizePolicy14.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy14);

        verticalLayout->addWidget(quit_button);

        dock_status->setWidget(dockWidgetContents_2);
        MainWindowDesign->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_status);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));
        QObject::connect(quit_button, SIGNAL(clicked()), MainWindowDesign, SLOT(close()));

        tab_manager->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", 0, QApplication::UnicodeUTF8));
        groupBox_12->setTitle(QApplication::translate("MainWindowDesign", "Logging", 0, QApplication::UnicodeUTF8));
        tab_manager->setTabText(tab_manager->indexOf(tab_status), QApplication::translate("MainWindowDesign", "Ros Communications", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        label_8->setText(QApplication::translate("MainWindowDesign", "UAS Table", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindowDesign", "Rows", 0, QApplication::UnicodeUTF8));
        button_add->setText(QApplication::translate("MainWindowDesign", "add row", 0, QApplication::UnicodeUTF8));
        button_remove->setText(QApplication::translate("MainWindowDesign", "remove row", 0, QApplication::UnicodeUTF8));
        button_save_uas_config->setText(QApplication::translate("MainWindowDesign", "save configuration", 0, QApplication::UnicodeUTF8));
        button_load_last_uas_conf->setText(QApplication::translate("MainWindowDesign", "load last configuration", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MainWindowDesign", "Visualizations", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("MainWindowDesign", "Rviz", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindowDesign", "Borders", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("MainWindowDesign", "Waypoints", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("MainWindowDesign", "Gazebo", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("MainWindowDesign", "Whatever", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("MainWindowDesign", "General", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("MainWindowDesign", "Task cost", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("MainWindowDesign", "Coverage cost", 0, QApplication::UnicodeUTF8));
        tab_manager->setTabText(tab_manager->indexOf(tab_uas_manager), QApplication::translate("MainWindowDesign", "UAS Manager", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", 0, QApplication::UnicodeUTF8));
        dock_status->setWindowTitle(QApplication::translate("MainWindowDesign", "Command Panel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindowDesign", "1. Ros Master", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowDesign", "Ros IP", 0, QApplication::UnicodeUTF8));
        line_edit_topic->setText(QApplication::translate("MainWindowDesign", "unused", 0, QApplication::UnicodeUTF8));
        checkbox_use_environment->setText(QApplication::translate("MainWindowDesign", "Use environment variables", 0, QApplication::UnicodeUTF8));
        line_edit_host->setText(QApplication::translate("MainWindowDesign", "192.168.1.67", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowDesign", "Ros Master Url", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowDesign", "Ros Hostname", 0, QApplication::UnicodeUTF8));
        line_edit_master->setText(QApplication::translate("MainWindowDesign", "http://192.168.1.2:11311/", 0, QApplication::UnicodeUTF8));
        checkbox_remember_settings->setText(QApplication::translate("MainWindowDesign", "Remember settings on startup", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        button_connect->setToolTip(QApplication::translate("MainWindowDesign", "Set the target to the current joint trajectory state.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        button_connect->setStatusTip(QApplication::translate("MainWindowDesign", "Clear all waypoints and set the target to the current joint trajectory state.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        button_connect->setText(QApplication::translate("MainWindowDesign", "Connect", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindowDesign", "2. CGAL CDT", 0, QApplication::UnicodeUTF8));
        line_edit_kml_file->setPlaceholderText(QApplication::translate("MainWindowDesign", "(empty)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowDesign", "Angle constrain", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindowDesign", "Kml file:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowDesign", "Edge constrain (m)", 0, QApplication::UnicodeUTF8));
        line_edit_angle_constr->setPlaceholderText(QApplication::translate("MainWindowDesign", "max 0.320 recommended 0.125", 0, QApplication::UnicodeUTF8));
        button_validate_kml->setText(QApplication::translate("MainWindowDesign", "Validate", 0, QApplication::UnicodeUTF8));
        button_browse->setText(QApplication::translate("MainWindowDesign", "Browse", 0, QApplication::UnicodeUTF8));
        button_perform_cdt->setText(QApplication::translate("MainWindowDesign", "Perform CDT", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindowDesign", "3. Path planning", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindowDesign", "Perform partitioning for agents in UAS table", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindowDesign", "and lon:", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindowDesign", "Go to goal", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindowDesign", "Perform coverage task for UAS no ", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindowDesign", "Go to cell with lat:", 0, QApplication::UnicodeUTF8));
        button_partition->setText(QApplication::translate("MainWindowDesign", "Partitioning", 0, QApplication::UnicodeUTF8));
        button_coverage->setText(QApplication::translate("MainWindowDesign", "Coverage", 0, QApplication::UnicodeUTF8));
        quit_button->setText(QApplication::translate("MainWindowDesign", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
