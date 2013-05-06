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
    std::queue< std::vector<int> > actions;

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

    void reset_moved()
    {
        units_moved[1]=0;
        units_moved[2]=0;
        units_moved[3]=0;
        units_moved[4]=0;
    }

    void turn_right()
    {
        rotation++;
    }

    void turn_left()
    {
        rotation--;
    }

    void move_left()
    {
            current.x+=leftward.x;
            current.y+=leftward.y;
    }

    void move_left(int units_left)
    {
        moving_horizontal=true;
        if(units_moved[1]<units_left)
        {
            move_left();
            units_moved[1]++;
        }
    }

    void move_right()
    {
            current.x+=rightward.x;
            current.y+=rightward.y;
    }

    void move_right(int units_right)
    {
        if(units_moved[2]<units_right)
        {
            move_right();
            units_moved[2]++;
        }
    }

    void move_forward()
    {
            current.x+=forward.x;
            current.y+=forward.y;
    }

    void move_forward(int units_forward)
    {
        moving_vertical=true;
        if(units_moved[3]<units_forward)
        {
            move_forward();
            units_moved[3]++;
        }
    }

    void move_back()
    {
            current.x+=backward.x;
            current.y+=backward.y;
    }

    void move_back(int units_back)
    {
        moving_vertical=true;
        if(units_moved[4]<units_back)
        {
            move_back();
            units_moved[4]++;
        }
    }

    void walk_left()
    {
            current.x+=step[1].x;
            current.y+=step[1].y;
    }

    void walk_left(int steps_left)
    {
        moving_horizontal=true;
        if(steps_taken[1]<steps_left)
        {
            walk_left();
            steps_taken[1]++;
        }
    }

    void walk_right()
    {
            current.x+=step[2].x;
            current.y+=step[2].y;
    }

    void walk_right(int steps_right)
    {
        if(steps_taken[2]<steps_right)
        {
            walk_right();
            steps_taken[2]++;
        }
    }

    void walk_forward()
    {
            current.x+=step[3].x;
            current.y+=step[3].y;
    }

    void walk_forward(int steps_forward)
    {
        moving_vertical=true;
        if(steps_taken[3]<steps_forward)
        {
            walk_forward();
            steps_taken[3]++;
        }
    }

    void walk_back()
    {
            current.x+=step[4].x;
            current.y+=step[4].y;
    }

    void walk_back(int steps_back)
    {
        moving_vertical=true;
        if(steps_taken[4]<steps_back)
        {
            walk_back();
            steps_taken[4]++;
        }
    }

    void move(int direction,int steps)//moves object steps in direction[1,2,3,or 4]
    {
        if(steps_taken[direction]<steps)
        {
            current.x+=step[direction].x;
            current.y+=step[direction].y;
            steps_taken[direction]++;
        }
    }

    void turn_to_point(float destination_x, float destination_y)//rotates object to face the given coordinates
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
    }

    void turn_to_point(point2f destination)
    {
        turn_to_point(destination.x,destination.y);
    }
    //moves object to destination over time at specified rate
    void walk_to_point(float destination_x, float destination_y, float rate)
    {
        if(rally_set)
        {
            turn_to_point(destination_x,destination_y);
            if(compare(distance(current.x,current.y,destination_x,destination_y),1.5)==-1)
                rally_set=false;
            current.x+=step[3].x*rate;
            current.y+=step[3].y*rate;
        }

    }

     void walk_to_point(point2f destination, float rate)
     {
         walk_to_point(destination.x,destination.y,rate);
     }

    //moves object to destination over time at specified rate
    void move_to_point(float destination_x, float destination_y, float rate)
    {
        if(rally_set)
        {
            turn_to_point(destination_x,destination_y);
            if(compare(distance(current.x,current.y,destination_x,destination_y),1.5)==-1)
                rally_set=false;
            current.x+=forward.x*rate;
            current.y+=forward.y*rate;
        }

    }

    void move_to_point(point2f destination,float rate)
    {
        move_to_point(destination.x,destination.y,rate);
    }

    void add_action(int action_no, int times)
    {
        std::vector<int> action;
        action.push_back(action_no);//number of the action to do
        action.push_back(times);//number of times to do the action
        action.push_back(0);//how many times its already been done
        actions.push(action);
    }

    void perform_actions()
    {
        if(!actions.empty())
        {
            if(actions.front().at(2)<actions.front().at(1))//times done is less than times to do
        {
            switch(actions.front().at(0))
            {
            case 1://move left
                move_left();
                break;
            case 2://move right
                move_right();
                break;
            case 3://move up
                move_forward();
                break;
            case 4://move down
                move_back();
                break;
            case 5://turn left
                turn_left();
                break;
            case 6://turn right
                turn_right();
                break;
            }
            actions.front().at(2)++;
        }
        else
            actions.pop();
        }
    }

    movable_object()
    {
        name="movable object";
        rally.x=resting.x;
        rally.y=resting.y;
        rally_set=false;
        step_size=0.001;
        reset_moved();
        reset_steps();
        printf("object %d: %s created\n", number, name);

    }

    ~movable_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
