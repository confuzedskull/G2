#ifndef COMPLEX_H
#define COMPLEX_H
#include "object.h"
#include "point2f.h"
#include "line2f.h"

//A complex object consists of a number of points which are calculated based on the object's position and rotation
class complex_object: public object
{
    public:
    //the mid-point of each side
    point2f front;
    point2f back;
    point2f left;
    point2f right;
    //headings for each direction
    point2f leftward;
    point2f rightward;
    point2f forward;
    point2f backward;
    //each corner of the object
    point2f front_right;
    point2f front_left;
    point2f back_right;
    point2f back_left;
    //each side of the object
    line2f front_side;
    line2f back_side;
    line2f left_side;
    line2f right_side;
    void calc_sides();//calculates the sides
    void calc_direction();//calculates each directional heading
    void rotate(float angle);//performs a rotation transformation based on the given angle
    void calc_points();//calculates the midpoints and corners
    void render();//makes the object visible on screen
    complex_object();
};
#endif // COMPLEX_H
