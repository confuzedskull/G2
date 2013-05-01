
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\color.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\point.h>

int object_no=0;//initial object number. This gets incremented and assigned to object.number after each object is created.

class object
{
    public:
    char* name;
    int number;
    point2f current;
    point2f resting;//resting point
    float rotation;
    float width, height;
    color current_color;//RGB values
    color prev_color;
    bool visible;
    float xmax,xmin,ymax,ymin;

    void set_boundaries()//calculates the max's and mins
    {
        xmin= current.x-(width/2);
        xmax= current.x+(width/2);
        ymin= current.y-(height/2);
        ymax= current.y+(height/2);

    }

            void render()//draws the object
    {

        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(current.x,current.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-current.x,-current.y,0.0);//translate object according to coordinates
        glColor3f(current_color.r,current_color.g,current_color.b);//color the square with object.current_color

        if(!visible)
        {
            printf("object %d: %s rendered\n", number, name);
            visible=true;
        }
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();//finish drawing

        glPopMatrix();//reset transformation matrix

    }

    void undo_color()//sets the current color to the previous
    {
        current_color.r=prev_color.r;
        current_color.g=prev_color.g;
        current_color.b=prev_color.b;
    }

    void rotate(float angle)
    {
        rotation+=angle;
    }

    int get_radius()//calculates a radius from the width and height
    {
        return ((width/2)+(height/2))/2;
    }


    object()//constructs an object
    {
        name="generic object";
        object_no++;
        number=object_no;
        current.x=320.0;
        current.y=160.0;
        resting.x=320.0;
        resting.y=160.0;
        width=64;
        height=64;
        current_color.set(0.0,0.0,0.0);
        prev_color.set(current_color.r,current_color.g,current_color.b);
        rotation=90;
        visible=false;
        printf("object %d: %s created\n", number, name);
    }

    object(float x, float y, float w, float h, color c)
    {
        current.x=x;
        current.y=y;
        width=w;
        height=h;
        current_color=c;
        rotation=90;
        visible=false;
    }

    ~object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }

};
