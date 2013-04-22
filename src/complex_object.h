
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\object.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\distance.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\line.h>
#define PI 3.14159265
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



    void calc_sides()
    {
        calc_points();
        front_side.set(front_left,front_right);
        back_side.set(back_left,back_right);
        left_side.set(front_left,back_left);
        right_side.set(front_right,back_right);
    }

    void calc_direction()
    {
        leftward.set(-(sin(rotation*PI/180)),cos(rotation*PI/180));
        rightward.set(sin(rotation*PI/180),-(cos(rotation*PI/180)));
        forward.set(cos(rotation*PI/180),sin(rotation*PI/180));
        backward.set(-(cos(rotation*PI/180)),-(sin(rotation*PI/180)));
    }

    void rotate(double angle)
    {
        rotation+=angle;
        calc_direction();
        calc_points();
    }


    void calc_points()
    {

        front.set(current.x+(forward.x*(height/2)),current.y+(forward.y*(height/2)));
        back.set(current.x+(backward.x*(height/2)),current.y+(backward.y*(height/2)));
        left.set(current.x+(leftward.x*(width/2)),current.y+(leftward.y*(width/2)));
        right.set(current.x+(rightward.x*(width/2)),current.y+(rightward.y*(width/2)));
        front_left.set((front.x+left.x),front.y+left.y);
        front_right.set(front.x+right.x,front.y+right.y);
        back_left.set(back.x+left.x,back.y+left.y);
        back_right.set(back.x+right.x,back.y+right.y);

    }

        void render()
    {
        glColor3f(current_color.r,current_color.g,current_color.b);//color the square with object.current_color

        if(!visible)
        {
            printf("object %d: %s rendered\n", number, name);
            visible=true;
        }
        glBegin(GL_POLYGON);//draws a filled in rectangle
            glVertex2f(back_left.x, back_left.y); // The bottom left corner
            glVertex2f(front_left.x, front_left.y); // The top left corner
            glVertex2f(front_right.x, front_right.y); // The top right corner
            glVertex2f(back_right.x, back_right.y); // The bottom right corner
        glEnd();//finish drawing

    }
    complex_object()
    {
        name="complex object";
        set_boundaries();
        printf("object %d: %s created\n", number, name);
    }

    ~complex_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
