#ifndef CURSOR_H
#define CURSOR_H
#include "point2f.h"
#include "color.h"
#include "object.h"
#include "game.h"

class cursor
{
public:

char* name;
int number;
static point2f passive;
static point2f left_down;
static point2f left_up;
static point2f left_drag;
static point2f right_down;
static point2f right_up;
static point2f right_drag;
static point2f rally;
static bool left_click;
static bool left_dragging;
static bool right_click;
static bool right_dragging;
static float xmin,xmax,ymin,ymax;
static color box_color;//RGB values
static bool highlighting;
static bool highlighted_objects[game::max_objects];
static int selected_object;
static object * left_clicked_object;
static object * right_clicked_object;
static bool set_rally;
static bool left_clicked_an_object;
static bool right_clicked_an_object;
static int objects_selected();
static void set_boundaries();
static void selection_box();
};

#endif // CURSOR_H
