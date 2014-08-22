#ifndef COMPLEX_H
#define COMPLEX_H
#include "object.h"
#include "point2f.h"
#include "line2f.h"

class complex_object: public object
{
    public:
    point2f front;
    point2f back;
    point2f left;
    point2f right;

    point2f leftward;
    point2f rightward;
    point2f forward;
    point2f backward;

    point2f front_right;
    point2f front_left;
    point2f back_right;
    point2f back_left;

    line2f front_side;
    line2f back_side;
    line2f left_side;
    line2f right_side;
    void calc_sides();
    void calc_direction();
    void rotate(float angle);
    void calc_points();
    void render();
    complex_object();
};

#endif // COMPLEX_H
