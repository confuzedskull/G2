#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "physics_object.h"

//A clickable object interfaces with the cursor
class clickable_object: public physics_object
{
    public:
    bool selected;//marks this object as selected or not
    bool left_clicked();//checks if the cursor left clicked inside this object
    bool right_clicked();//checks if the cursor right clicked inside this object
    bool highlighted();//checks if this object lies within the highlighting box
    bool grabbed();//checks if this object was grabbed by the cursor
    void mouse_function();//performs a variety of actions dependent on cursor interaction
    void render();//makes the object visible
    clickable_object();
};
#endif // CLICKABLE_H
