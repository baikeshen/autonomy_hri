#ifndef GRID_INTERFACE_H
#define GRID_INTERFACE_H
#include <ros/ros.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud.h>
#include <autonomy_human/human.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/ChannelFloat32.h>
#include "grid.h"


class GridInterface
{
private:
    ros::NodeHandle n;
    tf::TransformListener* tf_listener;
    // Leg
    ros::Publisher legs_grid_pub;
    std::string leg_frame_id;
    Grid* leg_grid;
    ros::Time last_leg_time;
    ros::Duration diff_leg_time;
    // Face
    ros::Publisher face_grid_pub;
    std::string face_frame_id;
    Grid* face_grid;
    ros::Time last_face_time;
    ros::Duration diff_face_time;
    // Human
    ros::Publisher human_grid_pub;
    std::string human_frame_id;
    Grid* human_grid;
    double update_rate;
    double update_time_ratio;
    CellProbability_t cell_probability;
    GridFOV_t global_fov;
    PointRAP_t* world_base;
    PointRAP_t* world_odom;
    void initWorldGrids();
    geometry_msgs::PointStamped transformToBase(geometry_msgs::PointStamped& tmp_point);
    geometry_msgs::PointStamped transformToOdom(geometry_msgs::PointStamped& tmp_point);
    sensor_msgs::PointCloud pointCloudGrid(Grid *polar_grid);
public:
    GridInterface();
    GridInterface(ros::NodeHandle _n,
                            tf::TransformListener* _tf_listener,
                            GridFOV_t _global_fov,
                            double _update_rate,
                            double _update_time_ratio,
                            CellProbability_t _cell_probability);   // TO BE MODIFIED FOR EVERY HUMAN FEATURE
    void initLegs(GridFOV_t sensor_fov);              //NEEDED FOR EVERY HUMAN FEATURE
    void legCallBack(const geometry_msgs::PoseArray& msg);      //NEEDED FOR EVERY HUMAN FEATURE
    void initFaces(GridFOV_t sensor_fov);
    void faceCallBack(const autonomy_human::human& msg);
    void initHuman();
    void spin();                            // TO BE MODIFIED FOR EVERY HUMAN FEATURE
    void publish();                                         // TO BE MODIFIED FOR EVERY HUMAN FEATURE
    ~GridInterface();                             // TO BE MODIFIED FOR EVERY HUMAN FEATURE
};


#endif
