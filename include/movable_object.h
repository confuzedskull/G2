#ifndef MOVABLE_H
#define MOVABLE_H
#include "complex_object.h"
#include "vector2f.h"
#include "point2f.h"
#include <queue>

//A movable object uses the sides of a complex object to calculate steps in each direction relative to the object's rotation
class movable_object: public complex_object
{
public:
    point2f * rally;
    bool rally_set;//whether or not the object has a point to move to
    vector2f step[4];//unit by which an object moves in x and y directions.
    float degrees_rotated;//keeps track of the progress of a rotation animation
    float step_size;//unit for modifying the magnitude of a step
    bool moving_forward;
    bool moving_backward;
    bool moving_left;
    bool moving_right;
    std::queue< std::vector<int> > actions;//a cue of actions for the object to perform
    void calc_step();//calculates the appropriate x and y values for a step in each direction relative to rotation
    void reset_motion();
    bool moving_vertical();
    bool moving_horizontal();
    bool resting();
    bool moving();
    //turn functions make the object rotate over time
    void turn_right();
    void turn_right(float degrees);
    void turn_left();
    void turn_left(float degrees);
    //move functions make the object move immediately in given direction
    void move_left();
    void move_left(float units_left);
    void move_right();
    void move_right(float units_right);
    void move_forward();
    void move_forward(float units_forward);
    void move_back();
    void move_back(float units_back);
    //walking functions make the object move over time in a given direction
    void walk_left();
    void walk_left(int steps_left);
    void walk_right();
    void walk_right(int steps_right);
    void walk_forward();
    void walk_forward(int steps_forward);
    void walk_back();
    void walk_back(int steps_back);
    void walk(int direction,int steps);//moves object n steps in direction[1,2,3,or 4]
    //rotates object to face the given coordinates
    void turn_to_point(float destination_x, float destination_y);
    void turn_to_point(point2f destination);
    //moves object to destination over time at specified rate
    void walk_to_point(float destination_x, float destination_y, float rate);
    void walk_to_point(point2f destination, float rate);
    //moves object to destination over time at specified rate
    void move_to_point(float destination_x, float destination_y, float rate);
    void move_to_point(point2f destination,float rate);
    void add_action(int action_no, int times);//adds an action to be performed n times to the action cue
    void perform_actions();//makes the object perform the cued actions
    movable_object();
};
#endif // MOVABLE_H
