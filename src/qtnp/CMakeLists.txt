##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.11)
project(qtnp)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
# set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

##############################################################################
# CGAL
##############################################################################

set(CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE CACHE BOOL "Don't override flags")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I/usr/include/eigen3 -lgmp -lCGAL -lCGAL_Core -frounding-math ${CMAKE_CXX_FLAGS}")

find_package(CGAL REQUIRED COMPONENTS Core)

##############################################################################
# Catkin & ROS
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS 
  qt_build
  roscpp
  rospy
  std_msgs
  message_generation
  visualization_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   InitialCoordinates.msg
   Coordinates.msg
   Placemarks.msg
 )

 generate_messages(
   DEPENDENCIES
   std_msgs
   visualization_msgs
 )

# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime visualization_msgs
  #  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  include/${PROJECT_NAME}/
)

##############################################################################
# Qt Environment
##############################################################################

# this comes from qt_build's qt-ros.cmake which is automatically
# included via the dependency call in package.xml
#rosbuild_prepare_qt5(QtCore QtGui QtXml) # Add the appropriate components to the component list here

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)

##############################################################################
# Sections
##############################################################################

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/qtnp/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################

add_executable(qtnp ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
add_dependencies(qtnp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(qtnp ${catkin_LIBRARIES} CGAL gmp)
install(TARGETS qtnp RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

qt5_use_modules(qtnp Core)
qt5_use_modules(qtnp Widgets)
qt5_use_modules(qtnp Xml)
