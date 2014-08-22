#ifndef MOVABLE_H
#define MOVABLE_H
#include "complex_object.h"
#include "vector2f.h"
#include "point2f.h"
#include <queue>

class movable_object: public complex_object
{
public:
    point2f * rally;
    bool rally_set;
    vector2f step[4];//unit by which an object moves in x and y directions.
    float degrees_rotated;
    float step_size;
    bool moving_forward;
    bool moving_backward;
    bool moving_left;
    bool moving_right;
    std::queue< std::vector<int> > actions;
    void calc_step();
    void reset_motion();
    bool moving_vertical();
    bool moving_horizontal();
    bool resting();
    bool moving();
    void turn_right();
    void turn_right(float degrees);
    void turn_left();
    void turn_left(float degrees);
    void move_left();
    void move_left(float units_left);
    void move_right();
    void move_right(float units_right);
    void move_forward();
    void move_forward(float units_forward);
    void move_back();
    void move_back(float units_back);
    void walk_left();
    void walk_left(int steps_left);
    void walk_right();
    void walk_right(int steps_right);
    void walk_forward();
    void walk_forward(int steps_forward);
    void walk_back();
    void walk_back(int steps_back);
    void walk(int direction,int steps);//moves object steps in direction[1,2,3,or 4]
    void turn_to_point(float destination_x, float destination_y);//rotates object to face the given coordinates
    void turn_to_point(point2f destination);
    //moves object to destination over time at specified rate
    void walk_to_point(float destination_x, float destination_y, float rate);
    void walk_to_point(point2f destination, float rate);
    //moves object to destination over time at specified rate
    void move_to_point(float destination_x, float destination_y, float rate);
    void move_to_point(point2f destination,float rate);
    void add_action(int action_no, int times);
    void perform_actions();
    movable_object();
};
#endif // MOVABLE_H

