#Set all parameters here
#Parameters should have 3 set()'s: set(X_ARG arg_literal), set(X_CDEF DEF), set(X_VAL, value)

#Namespace params
set(R_NS aero)
set(O_NS occupancy)
set(L_NS local)
set(G_NS global)
set(T_NS tentacles)
set(S_NS speed_set)
set(SP_NS supervisor)
set(LD_NS lidar)

#Parameter for the topic for exchanging OccupancyGrids between the global and local planner
set(OCCUPANCY_TOPIC_ARG ${R_NS}/occupancy_topic)
set(OCCUPANCY_TOPIC_CDF OCCUPANCY_TOPIC)
set(OCCUPANCY_TOPIC_VAL "\"${R_NS}/occupancy_topic\"")

#Parameter defining the velocity command topic
set(VELOCITY_CMD_TOPIC_ARG ${R_NS}/velocity_command_topic)
set(VELOCITY_CMD_TOPIC_CDF VEL_CMD_TOPIC)
set(VELOCITY_CMD_TOPIC_VAL "\"${R_NS}/velocity_command_topic\"")

#Paramter defining the odometry topic
set(ODOMETRY_TOPIC_ARG ${R_NS}/odometry)
set(ODOMETRY_TOPIC_CDF ODOMETRY_TOPIC)
set(ODOMETRY_TOPIC_VAL "\"${R_NS}/odometry\"")

#Paramter defining the manual contorl twist topic
set(MAN_TOPIC_ARG ${R_NS}/manual_twist_topic)
set(MAN_TOPIC_CDF MAN_TOPIC)
set(MAN_TOPIC_VAL "\"/manual_twist_topic\"")

#Paramter defining the state topic
set(STATE_TOPIC_ARG ${R_NS}/${SP_NS}/state)
set(STATE_TOPIC_CDF STATE_TOPIC)
set(STATE_TOPIC_VAL "\"${R_NS}/${SP_NS}/state\"")

#Parameter defining what platform we're on
set(PLATFORM_ARG ${R_NS}/platform)
set(PLATFORM_CDF PLATFORM)
set(PLATFORM_VAL "\"0\"")

#Parameters for defining tentacle selection huristics
set(GOAL_WEIGHT_ARG ${R_NS}/goal_weight)
set(GOAL_WEIGHT_CDF GOAL_WEIGHT)
set(GOAL_WEIGHT_VAL "\"3.0\"")

set(TRAV_WEIGHT_ARG ${R_NS}/traversed_weight)
set(TRAV_WEIGHT_CDF TRAV_WEIGHT)
set(TRAV_WEIGHT_VAL "\"0.1\"")

set(DIFF_WEIGHT_ARG ${R_NS}/difficult_weight)
set(DIFF_WEIGHT_CDF DIFF_WEIGHT)
set(DIFF_WEIGHT_VAL "\"0.25\"")

set(UNKN_WEIGHT_ARG ${R_NS}/unknown_weight)
set(UNKN_WEIGHT_CDF UNKN_WEIGHT)
set(UNKN_WEIGHT_VAL "\"0.1\"")

#Parameters for speed_sets on param server
set(S_MIN_SPEED_ARG ${S_NS}/min_speed)
set(S_MIN_SPEED_CDF S_MIN_SPEED)
set(S_MIN_SPEED_VAL "\"0.2\"")

set(S_MAX_SPEED_ARG ${S_NS}/max_speed)
set(S_MAX_SPEED_CDF S_MAX_SPEED)
set(S_MAX_SPEED_VAL "\"1.5\"")

set(S_NUMBER_ARG ${S_NS}/number)
set(S_NUMBER_CDF S_NUMBER)
set(S_NUMBER_VAL "\"15\"")

#Parameters for local occupancy grid information
set(L_OCC_UPDTRT_ARG "${R_NS}/${O_NS}/${L_NS}/update_rate")
set(L_OCC_UPDTRT_CDF L_OCC_UPDTRT)
set(L_OCC_UPDTRT_VAL "\"0.10\"")

set(L_OCC_XDIM_ARG "${R_NS}/${O_NS}/${L_NS}/x_dim")
set(L_OCC_XDIM_CDF L_OCC_XDIM)
set(L_OCC_XDIM_VAL "\"200\"")

set(L_OCC_YDIM_ARG "${R_NS}/${O_NS}/${L_NS}/y_dim")
set(L_OCC_YDIM_CDF L_OCC_YDIM)
set(L_OCC_YDIM_VAL "\"200\"")

set(L_OCC_ZDIM_ARG "${R_NS}/${O_NS}/${L_NS}/z_dim")
set(L_OCC_ZDIM_CDF L_OCC_ZDIM)
set(L_OCC_ZDIM_VAL "\"0\"")

set(L_OCC_XORG_ARG "${R_NS}/${O_NS}/${L_NS}/x_org")
set(L_OCC_XORG_CDF L_OCC_XORG)
set(L_OCC_XORG_VAL "\"0\"")

set(L_OCC_YORG_ARG "${R_NS}/${O_NS}/${L_NS}/y_org")
set(L_OCC_YORG_CDF L_OCC_YORG)
set(L_OCC_YORG_VAL "\"100\"")

set(L_OCC_ZORG_ARG "${R_NS}/${O_NS}/${L_NS}/z_org")
set(L_OCC_ZORG_CDF L_OCC_ZORG)
set(L_OCC_ZORG_VAL "\"0\"")

set(L_OCC_RES_ARG "${R_NS}/${O_NS}/${L_NS}/res")
set(L_OCC_RES_CDF L_OCC_RES)
set(L_OCC_RES_VAL "\"0.05\"")

#Parameters for global occupancy grid information
set(G_OCC_UPDTRT_ARG "${R_NS}/${O_NS}/${G_NS}/update_rate")
set(G_OCC_UPDTRT_CDF G_OCC_UPDTRT)
set(G_OCC_UPDTRT_VAL "\"0.2\"")

set(G_OCC_XDIM_ARG "${R_NS}/${O_NS}/${G_NS}/x_dim")
set(G_OCC_XDIM_CDF G_OCC_XDIM)
set(G_OCC_XDIM_VAL "\"2000\"")

set(G_OCC_YDIM_ARG "${R_NS}/${O_NS}/${G_NS}/y_dim")
set(G_OCC_YDIM_CDF G_OCC_YDIM)
set(G_OCC_YDIM_VAL "\"2000\"")

set(G_OCC_ZDIM_ARG "${R_NS}/${O_NS}/${G_NS}/z_dim")
set(G_OCC_ZDIM_CDF G_OCC_ZDIM)
set(G_OCC_ZDIM_VAL "\"0\"")

set(G_OCC_XORG_ARG "${R_NS}/${O_NS}/${G_NS}/x_org")
set(G_OCC_XORG_CDF G_OCC_XORG)
set(G_OCC_XORG_VAL "\"0\"")

set(G_OCC_YORG_ARG "${R_NS}/${O_NS}/${G_NS}/y_org")
set(G_OCC_YORG_CDF G_OCC_YORG)
set(G_OCC_YORG_VAL "\"0\"")

set(G_OCC_ZORG_ARG "${R_NS}/${O_NS}/${G_NS}/z_org")
set(G_OCC_ZORG_CDF G_OCC_ZORG)
set(G_OCC_ZORG_VAL "\"0\"")

set(G_OCC_RES_ARG "${R_NS}/${O_NS}/${G_NS}/res")
set(G_OCC_RES_CDF G_OCC_RES)
set(G_OCC_RES_VAL "\"0.05\"")

#Parameters for tentacle generation
set(T_MINLNTH_ARG "${R_NS}/${T_NS}/min_length")
set(T_MINLNTH_CDF T_MINLNTH)
set(T_MINLNTH_VAL "\"10\"")

set(T_EXPFACT_ARG "${R_NS}/${T_NS}/exp_fact")
set(T_EXPFACT_CDF T_EXPFACT)
set(T_EXPFACT_VAL "\"1.15\"")

set(T_NUMBER_ARG "${R_NS}/${T_NS}/number")
set(T_NUMBER_CDF T_NUMBER)
set(T_NUMBER_VAL "\"81\"")


#Parameters for recciving lidar data
set(LIDAR_LOCAL_TOPIC_ARG ${R_NS}/${LD_NS}/${L_NS})
set(LIDAR_LOCAL_TOPIC_CDF LIDAR_LOCAL_TOPIC)
set(LIDAR_LOCAL_TOPIC_VAL "\"${R_NS}/${LD_NS}/${L_NS}\"")

set(LIDAR_GLOBAL_TOPIC_ARG ${R_NS}/${LD_NS}/${G_NS})
set(LIDAR_GLOBAL_TOPIC_CDF LIDAR_GLOBAL_TOPIC)
set(LIDAR_GLOBAL_TOPIC_VAL "\"${R_NS}/${LD_NS}/${G_NS}\"")

#Build the parameter header
configure_file (
  "AeroPathPlanningParameters.h.in"
  "${PROJECT_BINARY_DIR}/AeroPathPlanningParameters.h"
)

add_subdirectory(planners)
add_subdirectory(planning_strategies)
add_subdirectory(utilities)
add_subdirectory(occupancy_grid)
add_subdirectory(tentacles)
add_subdirectory(nodes)
add_subdirectory(launch)
add_subdirectory(dox)
