#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\complex_object.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\vect.h>


class movable_object: public complex_object
{
    public:
    point2i rally;
    bool rally_set;
    vect step[4];//unit by which an object moves in x and y directions.
    int steps_taken[4];
    double degrees_rotated;
    double step_size;

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
        if(steps_taken[1]<100)
        {
            current.x+=step[1].x;
            current.y+=step[1].y;
            steps_taken[1]++;
            return true;
        }
        else
        return false;

    }

    bool move_left(int steps_left)
    {
        if(steps_taken[1]<steps_left*100)
        {
            current.x+=step[1].x;
            current.y+=step[1].y;
            steps_taken[1]++;
            return true;
        }
        else
        return false;

    }

    bool move_right()
    {
        if(steps_taken[2]<100)
        {
            current.x+=step[2].x;
            current.y+=step[2].y;
            steps_taken[2]++;
            return true;
        }
        else
        return false;

    }

    bool move_right(int steps_right)
    {
        if(steps_taken[2]<steps_right*100)
        {
            current.x+=step[2].x;
            current.y+=step[2].y;
            steps_taken[2]++;
            return true;
        }
        else
        return false;

    }

    bool move_forward()
    {
        if(steps_taken[3]<100)
        {
            current.x+=step[3].x;
            current.y+=step[3].y;
            steps_taken[3]++;
            return true;
        }
        else
        return false;

    }

    bool move_forward(int steps_forward)
    {
        if(steps_taken[3]<steps_forward*100)
        {
            current.x+=step[3].x;
            current.y+=step[3].y;
            steps_taken[3]++;
            return true;
        }
        else
        return false;

    }

    bool move_back()
    {
        if(steps_taken[4]<100)
        {
            current.x+=step[4].x;
            current.y+=step[4].y;
            steps_taken[4]++;
            return true;
        }
        else
        return false;
    }

    bool move_back(int steps_back)
    {
        if(steps_taken[4]<steps_back*100)
        {
            current.x+=step[4].x;
            current.y+=step[4].y;
            steps_taken[4]++;
            return true;
        }
        else
        return false;
    }

    bool move(int direction,int steps)//moves object steps in direction
    {
        if(steps_taken[direction]<steps*100)
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
    void move_to_point(float destination_x, float destination_y, float rate)
    {
        if(destination_x>current.x && destination_y>current.y)//destination lies in quadrant 1
        rotation=atan((destination_y-current.y)/(destination_x-current.x))*180/PI;

        if(destination_x<current.x && destination_y>current.y)//destination lies in quadrant 2
        rotation=atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

        if(destination_x<current.x && destination_y<current.y)//destination lies in quadrant 3
        rotation=atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 180;

        if(destination_x>current.x && destination_y<current.y)//destination lies in quadrant 4
        rotation=atan((destination_y-current.y)/(destination_x-current.x))*180/PI + 360;

        if(destination_x==current.x && destination_y>current.y)//destination lies at 12 O'clock
        rotation=90;

        if(destination_x==current.x && destination_y<current.y)//destination lies at 6'O'clock
        rotation=270;

        if(destination_x<current.x && destination_y==current.y)//destination lies at 9 O'clock
        rotation=180;

        if(destination_x>current.x && destination_y==current.y)//destination lies at 3 O'clock
        rotation=360;

        if(distance(current.x,current.y,destination_x,destination_y)>0)
        {
            current.x+=step[4].x*rate;
            current.y+=step[4].y*rate;
        }

    }
    movable_object()
    {
        name="movable object";
        rally.x=resting.x;
        rally.y=resting.y;
        step_size=0.01;
        steps_taken[1]=0;
        steps_taken[2]=0;
        steps_taken[3]=0;
        steps_taken[4]=0;
        printf("object %d: %s created\n", number, name);

    }

    ~movable_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
