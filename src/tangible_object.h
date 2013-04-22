#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\movable_object.h>
class tangible_object: public movable_object
{
    public:

    int touching[4];//the number of the touching object is stored in each index. "0" is no object.
    /*
    touching 1: left
    touching 2: right
    touching 3: front
    touching 4: back*/
    void repel(object B)
    {
        if(near_front(B))
        move_back(1);
        if(near_back(B))
        move_forward(1);
        if(near_left(B))
        move_right(1);
        if(near_right(B))
        move_left(1);

    }

    void attract(object B)
    {
        if(near_front(B))
        move_forward(1);
        if(near_back(B))
        move_back(1);
        if(near_left(B))
        move_left(1);
        if(near_right(B))
        move_right(1);

    }

    void simon_says(object B)
    {
        if(near_front(B))
        current_color.set(RED);
        if(near_back(B))
        current_color.set(GREEN);
        if(near_left(B))
        current_color.set(BLUE);
        if(near_right(B))
        current_color.set(YELLOW);

    }

    bool is_close(object B)
    {
        if(compare(distance(current,B.current),(getRadius()+B.getRadius()))==-1)
        return true;
        else
        return false;
    }
    bool near_front(object B)
    {
        if(compare(distance(front,B.current),B.getRadius())==-1)
                    {
                    return true;
                    }
                    else
                    return false;
    }
    bool near_back(object B)
    {
        if(compare(distance(back,B.current),B.getRadius())==-1)
                    {
                    return true;
                    }
                    else
                    return false;
    }

    bool near_left(object B)
    {
        if(compare(distance(left,B.current),B.getRadius())==-1)
                    {
                    return true;
                    }
                    else
                    return false;
    }

    bool near_right(object B)
    {
        if(compare(distance(right,B.current),B.getRadius())==-1)
                    {
                    return true;
                    }
                    else
                    return false;
    }

    tangible_object()
    {
        name="tangible object";
        printf("object %d: %s created\n", number, name);
    }

    ~tangible_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
