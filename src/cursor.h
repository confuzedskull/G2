const int max_objects = 6;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number

class cursor
{

    public:
    char* name;
    int number;
    point2f passive;
    point2f left_down;
    point2f left_up;
    point2f left_drag;
    point2f right_down;
    point2f right_up;
    point2f right_drag;
    point2f rally;
    bool left_click;
    bool right_click;
    bool right_dragging;
    int solidity;
    float xmin,xmax,ymin,ymax;
    color box_color;//RGB values
    bool highlighting;
    bool highlighted_objects[max_objects];
    int selected_object;
    int objects_selected;

    void set_color(float R,float G,float B)
    {
        box_color.r=R;
        box_color.g=G;
        box_color.b=B;
    }

    void set_boundaries()//boundaries of the selection box
    {
        xmin= left_down.x;
        xmax= left_drag.x;
        ymin= left_down.y;
        ymax= left_drag.y;
    }

    void selection_box()//this is the box that is created when user clicks and drags
    {
        if(highlighting==true)
        {

        glColor3f(box_color.r,box_color.g,box_color.b);
        glBegin(GL_QUADS);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();

        }
    }
    cursor()//constructor
    {
        set_color(0.0,0.9,0.0);
        objects_selected=0;
    }
};
cursor cursor1;
