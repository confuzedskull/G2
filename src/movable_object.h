#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\complex_object.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\vect.h>


class movable_object: public complex_object
{
public:
    point2i rally;
    bool rally_set;
    vect step[4];//unit by which an object moves in x and y directions.
    int steps_taken[4];
    int units_moved[4];
    float degrees_rotated;
    float step_size;
    bool moving_vertical;
    bool moving_horizontal;

    void calc_step()
    {
        //left step
        step[1].x=leftward.x*step_size;
        step[1].y=leftward.y*step_size;
        //right step
        step[2].x=rightward.x*step_size;
        step[2].y=rightward.y*step_size;
        //forward step
        step[3].x=forward.x*step_size;
        step[3].y=forward.y*step_size;
        //backward step
        step[4].x=backward.x*step_size;
        step[4].y=backward.y*step_size;
    }

    void reset_steps()
    {
        steps_taken[1]=0;
        steps_taken[2]=0;
        steps_taken[3]=0;
        steps_taken[4]=0;
    }

    bool turn_right()
    {
        if(degrees_rotated>-90)
        {
            rotate(-1);
            degrees_rotated--;
            return true;
        }
        else
            return false;

    }

    bool turn_left()
    {
        if(degrees_rotated<90)
        {
            rotate(1);
            degrees_rotated++;
            return true;
        }
        else
            return false;

    }

    bool move_left()
    {
        moving_horizontal=true;
        if(units_moved[1]<1)
        {
            current.x+=left.x;
            current.y+=left.y;
            units_moved[1]++;
            return true;
        }
        else
            return false;

    }

    bool move_left(int units_left)
    {
        moving_horizontal=true;
        if(units_moved[1]<units_left)
        {
            current.x+=left.x;
            current.y+=left.y;
            units_moved[1]++;
            return true;
        }
        else
            return false;

    }

    bool move_right()
    {
        moving_horizontal=true;
        if(units_moved[2]<1)
        {
            current.x+=right.x;
            current.y+=right.y;
            units_moved[2]++;
            return true;
        }
        else
            return false;

    }

    bool move_right(int units_right)
    {
        if(units_moved[2]<units_right)
        {
            current.x+=right.x;
            current.y+=right.y;
            units_moved[2]++;
            return true;
        }
        else
            return false;

    }

    bool move_forward()
    {
        moving_vertical=true;
        if(units_moved[3]<1)
        {
            current.x+=forward.x;
            current.y+=forward.y;
            units_moved[3]++;
            return true;
        }
        else
            return false;

    }

    bool move_forward(int units_forward)
    {
        moving_vertical=true;
        if(units_moved[3]<units_forward)
        {
            current.x+=forward.x;
            current.y+=forward.y;
            units_moved[3]++;
            return true;
        }
        else
            return false;
    }

    bool move_back()
    {
        moving_vertical=true;
        if(units_moved[4]<1)
        {
            current.x+=back.x;
            current.y+=back.y;
            units_moved[4]++;
            return true;
        }
        else
            return false;
    }

    bool move_back(int units_back)
    {
        moving_vertical=true;
        if(units_moved[4]<units_back)
        {
            current.x+=back.x;
            current.y+=back.y;
            units_moved[4]++;
            return true;
        }
        else
            return false;
    }

    bool walk_left()
    {
        moving_horizontal=true;
        if(steps_taken[1]<1)
        {
            current.x+=step[1].x;
            current.y+=step[1].y;
            steps_taken[1]++;
            return true;
        }
        else
            return false;

    }

    bool walk_left(int steps_left)
    {
        moving_horizontal=true;
        if(steps_taken[1]<steps_left)
        {
            current.x+=step[1].x;
            current.y+=step[1].y;
            steps_taken[1]++;
            return true;
        }
        else
            return false;

    }

    bool walk_right()
    {
        moving_horizontal=true;
        if(steps_taken[2]<1)
        {
            current.x+=step[2].x;
            current.y+=step[2].y;
            steps_taken[2]++;
            return true;
        }
        else
            return false;

    }

    bool walk_right(int steps_right)
    {
        if(steps_taken[2]<steps_right)
        {
            current.x+=step[2].x;
            current.y+=step[2].y;
            steps_taken[2]++;
            return true;
        }
        else
            return false;

    }

    bool walk_forward()
    {
        moving_vertical=true;
        if(steps_taken[3]<1)
        {
            current.x+=step[3].x;
            current.y+=step[3].y;
            steps_taken[3]++;
            return true;
        }
        else
            return false;

    }

    bool walk_forward(int steps_forward)
    {
        moving_vertical=true;
        if(steps_taken[3]<steps_forward)
        {
            current.x+=step[3].x;
            current.y+=step[3].y;
            steps_taken[3]++;
            return true;
        }
        else
            return false;
    }

    bool walk_back()
    {
        moving_vertical=true;
        if(steps_taken[4]<1)
        {
            current.x+=step[4].x;
            current.y+=step[4].y;
            steps_taken[4]++;
            return true;
        }
        else
            return false;
    }

    bool walk_back(int steps_back)
    {
        moving_vertical=true;
        if(steps_taken[4]<steps_back)
        {
            current.x+=step[4].x;
            current.y+=step[4].y;
            steps_taken[4]++;
            return true;
        }
        else
            return false;
    }

    bool move(int direction,int steps)//moves object steps in direction[1,2,3,or 4]
    {
        if(steps_taken[direction]<steps)
        {
            current.x+=step[direction].x;
            current.y+=step[direction].y;
            steps_taken[direction]++;
            return true;
        }
        else
            return false;
    }
    //moves object to destination over time at specified rate
    void walk_to_point(float destination_x, float destination_y, float rate)
    {
        if(rally_set)
        {
            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==1)//destination lies in quadrant 1
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==1)//destination lies in quadrant 2
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 3
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 4
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 360;

            if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==1)//destination lies at 12 O'clock
                rotation = 90;

            if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==-1)//destination lies at 6'O'clock
                rotation = 270;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==0)//destination lies at 9 O'clock
                rotation = 180;

            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==0)//destination lies at 3 O'clock
                rotation = 0;

            if(compare(distance(current.x,current.y,destination_x,destination_y),1.5)==-1)
                rally_set=false;

            current.x+=step[3].x*rate;
            current.y+=step[3].y*rate;
        }

    }

    //moves object to destination over time at specified rate
    void move_to_point(float destination_x, float destination_y, float rate)
    {
        if(rally_set)
        {
            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==1)//destination lies in quadrant 1
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==1)//destination lies in quadrant 2
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 3
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 4
                rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 360;

            if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==1)//destination lies at 12 O'clock
                rotation = 90;

            if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==-1)//destination lies at 6'O'clock
                rotation = 270;

            if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==0)//destination lies at 9 O'clock
                rotation = 180;

            if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==0)//destination lies at 3 O'clock
                rotation = 0;

            if(compare(distance(current.x,current.y,destination_x,destination_y),1.5)==-1)
                rally_set=false;

            current.x+=forward.x*rate;
            current.y+=forward.y*rate;
        }

    }

    movable_object()
    {
        name="movable object";
        rally.x=resting.x;
        rally.y=resting.y;
        rally_set=false;
        step_size=0.001;
        reset_steps();
        printf("object %d: %s created\n", number, name);

    }

    ~movable_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
