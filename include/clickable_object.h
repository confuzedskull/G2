#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "physics_object.h"

class clickable_object: public physics_object
{
    public:
    bool selected;
    bool left_clicked();
    bool right_clicked();
    bool highlighted();
    bool grabbed();
    void mouse_function();
    void render();
    clickable_object();

};
#endif // CLICKABLE_H
