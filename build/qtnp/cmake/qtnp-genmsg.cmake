# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "qtnp: 3 messages, 0 services")

set(MSG_I_FLAGS "-Iqtnp:/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg;-Ivisualization_msgs:/opt/ros/kinetic/share/visualization_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/kinetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
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
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
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

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp
)
_generate_msg_eus(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp
)
_generate_msg_eus(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg"
  "${MSG_I_FLAGS}"
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp
)

### Generating Services

### Generating Module File
_generate_module_eus(qtnp
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(qtnp_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(qtnp_generate_messages qtnp_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_eus _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_eus _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_eus _qtnp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(qtnp_geneus)
add_dependencies(qtnp_geneus qtnp_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS qtnp_generate_messages_eus)

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

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp
)
_generate_msg_nodejs(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp
)
_generate_msg_nodejs(qtnp
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg"
  "${MSG_I_FLAGS}"
  "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp
)

### Generating Services

### Generating Module File
_generate_module_nodejs(qtnp
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(qtnp_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(qtnp_generate_messages qtnp_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/InitialCoordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_nodejs _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Coordinates.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_nodejs _qtnp_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/fotis/Dev/Workspaces/ROS/qTnP/src/qtnp/msg/Placemarks.msg" NAME_WE)
add_dependencies(qtnp_generate_messages_nodejs _qtnp_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(qtnp_gennodejs)
add_dependencies(qtnp_gennodejs qtnp_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS qtnp_generate_messages_nodejs)

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
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(qtnp_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET visualization_msgs_generate_messages_cpp)
  add_dependencies(qtnp_generate_messages_cpp visualization_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/qtnp
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(qtnp_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET visualization_msgs_generate_messages_eus)
  add_dependencies(qtnp_generate_messages_eus visualization_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/qtnp
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(qtnp_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET visualization_msgs_generate_messages_lisp)
  add_dependencies(qtnp_generate_messages_lisp visualization_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/qtnp
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(qtnp_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET visualization_msgs_generate_messages_nodejs)
  add_dependencies(qtnp_generate_messages_nodejs visualization_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/qtnp
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(qtnp_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET visualization_msgs_generate_messages_py)
  add_dependencies(qtnp_generate_messages_py visualization_msgs_generate_messages_py)
endif()
