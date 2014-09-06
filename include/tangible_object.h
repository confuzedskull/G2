#ifndef TANGIBLE_H
#define TANGIBLE_H
#include "movable_object.h"

class tangible_object: public movable_object
{
    public:

    int touching[4];//the number of the touching object is stored in each index. "0" is no object
    /*
    touching 0: left
    touching 1: right
    touching 2: front
    touching 3: back*/
    void repel(object B);//object moves away from object B
    void attract(object B);//object moves toward object B
    void simon_says(object B);//object changes color according to side touched
    void identify(object B);//variable touching[] is updated with number of the touched object
    bool is_close(object B);
    bool near_front(object B);
    bool near_back(object B);
    bool near_left(object B);
    bool near_right(object B);
    tangible_object();
};

#endif // TANGIBLE_H
