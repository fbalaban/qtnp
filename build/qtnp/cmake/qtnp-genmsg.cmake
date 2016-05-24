# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "qtnp: 3 messages, 0 services")

set(MSG_I_FLAGS "-Iqtnp:/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Ivisualization_msgs:/opt/ros/indigo/share/visualization_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(qtnp_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_custom_target(_qtnp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "qtnp" "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" ""
)

get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_custom_target(_qtnp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "qtnp" "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" ""
)

get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_custom_target(_qtnp_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "qtnp" "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" "qtnp/Coordinates"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp
)
_generate_msg_cpp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp
)
_generate_msg_cpp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg"
  "${MSG_I_FLAGS}"
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp
)

### Generating Services

### Generating Module File
_generate_module_cpp(qtnp
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(qtnp_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(qtnp_generate_messages qtnp_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_cpp _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_cpp _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_cpp _qtnp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(qtnp_gencpp)
add_dependencies(qtnp_gencpp qtnp_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS qtnp_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
)
_generate_msg_lisp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
)
_generate_msg_lisp(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg"
  "${MSG_I_FLAGS}"
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
)

### Generating Services

### Generating Module File
_generate_module_lisp(qtnp
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(qtnp_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(qtnp_generate_messages qtnp_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_lisp _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_lisp _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_lisp _qtnp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(qtnp_genlisp)
add_dependencies(qtnp_genlisp qtnp_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS qtnp_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
)
_generate_msg_py(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
)
_generate_msg_py(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg"
  "${MSG_I_FLAGS}"
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
)

### Generating Services

### Generating Module File
_generate_module_py(qtnp
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(qtnp_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(qtnp_generate_messages qtnp_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_py _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_py _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_py _qtnp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(qtnp_genpy)
add_dependencies(qtnp_genpy qtnp_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS qtnp_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/qtnp
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(qtnp_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(qtnp_generate_messages_cpp visualization_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(qtnp_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(qtnp_generate_messages_lisp visualization_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(qtnp_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(qtnp_generate_messages_py visualization_msgs_generate_messages_py)
