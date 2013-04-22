#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265

//2D World
//by James Nakano

//This is a basic 2D game engine created from the ground up using openGL and glut
//Disclaimer: The glut and opengl libraries are obviously not mine, but everything else is an original creation.
//
//NOTE: in general, position related arrays use index 2 as left, 3 as right, 4 as forward, 5 as backward

//changelog
//going all out with class inheritance. broke object class down into subclasses.
//can now shoot one projectile at a time with spacebar.
//created array of projectiles.
//created projectile bullet.
//modified collision_detection. now it first detects whether the objects are close before calculating anything else
//the HUD isn't showing that the player is colliding with other objects
//created enum shape. no particular use yet.
//got rid of some old commented out code.

//global definitions
//direction definitions - I used this to make directions less confusing when reading code
const int left=2;
const int right=3;
const int up=4;
const int down=5;
GLfloat size=3.0;
int current_object = 1;
const int max_objects = 6;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number
const int max_projectiles =2;
bool* key_states = new bool[256]; // Create an array of boolean values of letters
//width and height of program window
int window_width=640;
int window_height=320;

int random1 = rand() % 4 + 1;//random number between 1 and 4
int random2 = rand() % 4 + 1;//another random number between 1 and 4

int object_no=0;//initial object number. This gets incremented and assigned to object.number after each object is created.

int player_action;

int frames=0;//to be used for frame count

time_t gametime;//to be used for game clock

enum shape
{
    circle,
    line,
    triangle,
    rectangle,
    polygon
};

class color
    {
        public:
        float r;
        float g;
        float b;

        void set(float red, float green, float blue)
        {
            r=red;
            g=green;
            b=blue;

        }

        void set(color c)
        {
            r=c.r;
            g=c.g;
            b=c.b;
        }

        color()
        {

        }

        color(float red, float green, float blue)
        {
            r=red;
            g=green;
            b=blue;
        }

    };//color with red, green, blue
const color RED(1.0,0.0,0.0);
const color GREEN(0.0,1.0,0.0);
const color BLUE(0.0,0.0,1.0);
const color BLACK(0.0,0.0,0.0);
const color WHITE(1.0,1.0,1.0);

struct point {float x; float y;};
struct vect {float x; float y;};// named vect instead of vector because vector is already declared as part of the c++ lib...I think
struct limits {float xmin; float xmax; float ymin; float ymax;};
//text
char text0[30];
char text1[30];
char text2[20];
char text3[20];
char text4[20];
char text5[20];
char text6[10];
char text7[10];
char text8[10];
char text9[10];
char text10[20];
char text11[10];
char text12[10];

int temp_toggle[2];
int toggle_text=1;

float distance(float x1, float y1, float x2, float y2)//calculates distance given x,y values
{
    return (int)(sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

float distance(point A, point B)//calculates distance from A to B
{
    return (int)(sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

class cursor
{

    public:
    char* name;
    int number;
    point left_down;
    point left_up;
    point left_drag;
    point right_down;
    point right_up;
    point right_drag;
    point rally;
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

class world
{
    public:
    char* name;
    int type;
    int state;
    float timer;
    limits boundaries;
    float gravity;
    float wind;
    int no_of_objects;
    bool settings[10];


};
world current_world;

double world_gravity=-0.01;

class object
{

    public:
    char* name;
    int number;
    int category;
    point current;
    point resting;//resting point
    float xmin,xmax,ymin,ymax;//boundaries used for collision detection and rendering

    double rotation;
    float width, height;
    float radius;//used for round objects or object's perimeter
    color current_color;//RGB values
    color prev_color;

    void set_coordinates(float a,float b)//sets coordinates of current object position
    {
        current.x=a;
        current.y=b;
    }

    void undo_color()
    {
        current_color.r=prev_color.r;
        current_color.g=prev_color.g;
        current_color.b=prev_color.b;
    }

    int within_radius;

    void turn(double angle)
    {
        rotation+=angle;
    }

    void render()
    {

        glPushMatrix();//need push and pop so that entire scene isn't rotated

        glTranslatef(current.x,current.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-current.x,-current.y,0.0);//translate object according to coordinates
        glColor3f(current_color.r,current_color.g,current_color.b);//color the square with object.current_color

        glBegin(GL_POLYGON);//draws a filled in rectangle

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner


        glEnd();//finish drawing

        glPopMatrix();//reset transformation matrix

    }
    object()//constructs an object
    {
        name="generic object";
        object_no++;
        number=object_no;
        current.x=320;
        current.y=160;
        resting.x=320;
        resting.y=160;
        width=50.0;
        height=50.0;
        radius = (width + height)/4;
        toggle_text=1;
        current_color.set(0.0,0.0,0.0);
        prev_color.set(current_color.r,current_color.g,current_color.b);
        rotation=90;

        xmin= current.x-(width/2);
        xmax= current.x+(width/2);
        ymin= current.y-(height/2);
        ymax= current.y+(height/2);

        printf("object: %s no.%d initialized\n", name, number);
    }

    object(float x, float y, float w, float h, color c)
    {
        current.x=x;
        current.y=y;
        width=w;
        height=h;
        current_color=c;
        rotation=90;
    }

};

class movable_object: public object
{
    public:
    point rally;
    bool rally_set;
    vect step[5];//unit by which an object moves in x and y directions.
    int steps_taken[5];
    double step_size;


    void set_boundaries()
    {
        xmin= current.x-(width/2);
        xmax= current.x+(width/2);
        ymin= current.y-(height/2);
        ymax= current.y+(height/2);

    }


    void calc_step()
    {
        //left step
        step[2].x=-(sin(rotation*PI/180))*step_size;
        step[2].y=cos(rotation*PI/180)*step_size;
        //right step
        step[3].x=sin(rotation*PI/180)*step_size;
        step[3].y=-(cos(rotation*PI/180))*step_size;
        //forward step
        step[4].x=cos(rotation*PI/180)*step_size;
        step[4].y=sin(rotation*PI/180)*step_size;
        //backward step
        step[5].x=-(cos(rotation*PI/180))*step_size;
        step[5].y=-(sin(rotation*PI/180))*step_size;
    }

    bool move_left(int steps_left)
    {
        if(steps_taken[2]<steps_left*100)
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
        if(steps_taken[3]<steps_right*100)
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
        if(steps_taken[4]<steps_forward*100)
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
        if(steps_taken[5]<steps_back*100)
        {
            current.x+=step[5].x;
            current.y+=step[5].y;
            steps_taken[5]++;
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
        steps_taken[2]=0;
        steps_taken[3]=0;
        steps_taken[4]=0;
        steps_taken[5]=0;

    }
};

class tangible_object: public movable_object
{
    public:

    int touching[5];//the number of the touching object is stored in each index. "0" is no object.
    /* touching 1: on top of
    touching 2: left
    touching 3: right
    touching 4: top
    touching 5: bottom*/

    point front_side;
    point back_side;
    point left_side;
    point right_side;

    void calc_sides()
    {
        front_side.x=current.x+((step[up].x/step_size)*(height/2));
        front_side.y=current.y+((step[up].y/step_size)*(height/2));
        back_side.x=current.x+((step[down].x/step_size)*(height/2));
        back_side.y=current.y+((step[down].y/step_size)*(height/2));
        left_side.x=current.x+((step[left].x/step_size)*(width/2));
        left_side.y=current.y+((step[left].y/step_size)*(width/2));
        right_side.x=current.x+((step[right].x/step_size)*(width/2));
        right_side.y=current.y+((step[right].y/step_size)*(width/2));
    }

    tangible_object()
    {
        name="tangible object";

    }
};


class physics_object: public tangible_object
{
    public:
    float mass;
    float delta_time[4];//each element of array represents how much time a change in a direction or velocity took
    //1:change in x, 2:change in velocity, 3:change in velocity x, 4:change in velocity y
    vect velocity[2];// 1:initial velocity, 2: final velocity
    vect acceleration;
    vect momentum;
    vect force;
    int solidity;//a value from 1 to 5 that indicates the density of the object

    void collision()//does stuff depending on whether the object is being touched in a certain place
{

    if(touching[left]>0)//touching left
    {
        current_color.set(2,1,0);//yellow
    }

    if(touching[right]>0)//touching right
    {
        current_color.set(0,1,1);//cyan
    }

    if(touching[up]>0)//touching top
    {
        current_color.set(1,0.65,0);//orange
    }

    if(touching[down]>0)//touching bottom
    {
        current_color.set(1,0,1);//pink
    }

    if(touching[down]==0 && touching[up]==0 && touching[right]==0 && touching[left]==0)//touching nothing
    {
        undo_color();
    }
}
    void set_resting()
    {

        if(velocity[2].y>-1 && velocity[2].y<1)
        {
            resting.y=current.y;
        }

        if(velocity[2].x>-1 && velocity[2].x<1)
        {
            resting.x=current.x;
        }
    }

    void calc_delta_time()
    {

        if(current.x==resting.x)
        delta_time[1]=0;
        else
        delta_time[1]+=0.004;

        if(current.y==resting.y)
        delta_time[2]=0;
        else
        delta_time[2]+=0.004;

        if(velocity[2].x==velocity[1].x)
        delta_time[3]=0;
        else
        delta_time[3]+=0.004;

        if(velocity[2].y==velocity[1].y)
        delta_time[4]=0;
        else
        delta_time[4]+=0.004;
    }
    void calc_velocity()
    {
        velocity[1].x=(current.x-resting.x)/delta_time[1];
        velocity[1].y=(current.y-resting.y)/delta_time[2];
    }

    void calc_acceleration()
    {   if(delta_time[3]!=0)
        acceleration.x=0;
        else
        acceleration.x=(velocity[2].x - velocity[1].x)/delta_time[3];

        if(delta_time[4]!=0)
        acceleration.y=0;
        else
        acceleration.y=(velocity[2].y - velocity[1].y)/delta_time[4];

    }

    void calc_force()
    {
        force.x=mass*acceleration.x;
        force.y=mass*acceleration.y;
    }

    void calc_momentum()
    {
        momentum.x=mass*velocity[1].x;
        //player.x+=momentum.x; //only increase player.x when momentum is not null
        velocity[2].x = velocity[1].x + momentum.x;

        momentum.y=mass*velocity[1].y;
        //player.y+=momentum.y; //only increase player.y when momentum is not null
        velocity[2].y = velocity[1].y + momentum.y;
    }

    void friction()
    {
        if(force.x>0)
        force.x-=0.0001;
        if(force.x<0)
        force.x+=0.0001;
    }

    void physics()
    {
        set_resting();
        calc_delta_time();
        calc_velocity();
        //friction();
        calc_acceleration();
        calc_momentum();
        calc_force();
        calc_step();
        set_boundaries();
        calc_sides();
        //collision();
    }

    physics_object()
    {
        name="physics object";
        mass=0.01;//note: changing this seems to have an effect on set_resting
        touching[1]=0;
        touching[2]=0;
        touching[3]=0;
        touching[4]=0;
        touching[5]=0;
    }
};

class clickable_object:movable_object
{
    public:
    bool selected;

    bool left_clicked()
    {
        if(cursor1.left_down.x<xmax && cursor1.left_down.x>xmin && cursor1.left_down.y<ymax && cursor1.left_down.y>ymin )
        return true;
        else
        return false;
    }

    bool right_clicked()
    {
        if(cursor1.right_up.x<xmax && cursor1.right_up.x>xmin && cursor1.right_up.y<ymax && cursor1.right_up.y>ymin)
        return true;
        else
        return false;
    }

    bool highlighted()
    {//if object lies within selection box boundaries, return true
        if(current.x<cursor1.xmax && current.x>cursor1.xmin && current.y>cursor1.ymax && current.y<cursor1.ymin)
        return true;
        else
        return false;
    }

    void mouse_function()
    {
        if(left_clicked()==true && cursor1.left_click==true)//clicked this object
        {
            cursor1.objects_selected=1;
            cursor1.selected_object=number;
            cursor1.highlighted_objects[number]=true;

            }

        if(cursor1.left_click==true && cursor1.objects_selected>0 && cursor1.highlighted_objects[number]==false)//clicked another object
        {
            cursor1.highlighted_objects[number]=false;
        }

        if(cursor1.left_click==true && left_clicked()==false )
        {
            cursor1.highlighted_objects[number]=false;
            cursor1.objects_selected=0;
        }

        if(highlighted()==true)
        {

            cursor1.highlighted_objects[number]=true;
        }

        if(highlighted()==false && cursor1.highlighted_objects[number]==true)
        {
            if(left_clicked()==false && selected==false)
            cursor1.objects_selected++;

            cursor1.highlighted_objects[number]=true;
        }

        if(right_clicked()==true)
        {
            cursor1.rally.x=current.x;
            cursor1.rally.y=current.y;
        }

        selected=cursor1.highlighted_objects[number];

        if(selected==true)
        {
            if(cursor1.right_click==true && right_clicked()==false)
            {
                rally.x=cursor1.right_down.x;
                rally.y=cursor1.right_down.y;
            }
            if(cursor1.right_dragging==true && right_clicked()==false)
            {
                rally.x=cursor1.right_drag.x;
                rally.y=cursor1.right_drag.y;
            }
            current_color.set(GREEN);
        }
        else
        undo_color();
    }

    clickable_object()
    {
        name="clickable object";
        selected=false;

    }
};

class player: public physics_object
{

    public:
    int health;
    int energy;
    int defense;
    int attack;
    int shield;
    bool action[10];
    /* action 1:resting
    action 2: left
    action 3: right
    action 4: up/forward
    action 5: down/backward
    action 6: jumping
    action 7: falling
    action 8: primary
    action 9: secondary
    */

    player()
    {


    }
};

player* objects = new player[max_objects];

class projectile: public physics_object
{
    public:

    int range;//how far the projectile can go until it resets
    int power;
    bool fired;

    void reset()
    {
        current.x=resting.x;
        current.y=resting.y;
        steps_taken[up]=0;
        fired=false;
    }

    void fire(object source)//an object fires a projectile
    {
        if(!fired)
        {
        current.x=source.current.x;
        resting.x=source.current.x;
        current.y=source.current.y;
        resting.y=source.current.y;
        rotation=source.rotation;
        calc_step();//orient it to the direction aiming
        fired=true;
        }
    }

    void update()
    {
        set_boundaries();

        if(fired)
        move_forward(range);
        else
        {//set projectile position to somewhere outside of scene
            current.x=0;
            current.y=0;
        }

        if(steps_taken[up]==range)
        {
            reset();
        }

    }

    projectile()
    {

        width=10;
        height=10;
        radius=5;
        range=1000;
        fired=false;
        step_size=0.5;
        set_boundaries();
        steps_taken[4]=0;
        current_color=RED;
    }
};

projectile bullet;

object* projectiles = new projectile[max_projectiles];

void collision_detection()
{
    for(int a=0; a<max_objects; a++)
    {
        for(int b=0; b<max_objects; b++)
        {
            if(distance(objects[a].current.x,objects[a].current.y, objects[b].current.x, objects[b].current.y) < (objects[a].radius + objects[b].radius))
                {
                objects[a].within_radius=objects[b].number;
                //objects[a].current_color=objects[b].current_color;
                }
                else
                objects[a].within_radius=0;

            if(a!=b && objects[a].within_radius>0)
            {

                if(distance(objects[a].back_side.x,objects[a].back_side.y,objects[b].current.x,objects[b].current.y)<objects[b].radius)
                {
                    objects[a].touching[down]=objects[b].number;
                }

                if(distance(objects[a].front_side.x, objects[a].front_side.y,objects[b].current.x,objects[b].current.y)<objects[b].radius)
                {
                    objects[a].touching[up]=objects[b].number;
                }

                if(distance(objects[a].left_side.x,objects[a].left_side.y,objects[b].current.x,objects[b].current.y)<objects[b].radius)
                {
                    objects[a].touching[left]=objects[b].number;
                }

                if(distance(objects[a].right_side.x,objects[a].right_side.y,objects[b].current.x,objects[b].current.y) < objects[b].radius)
                {
                    objects[a].touching[right]=objects[b].number;
                }


            }
            else
            {
                objects[a].touching[2]=0;
                objects[a].touching[3]=0;
                objects[a].touching[4]=0;
                objects[a].touching[5]=0;

            }

        }
        for(int p=0; p<max_projectiles; p++)//projectile collision detection
            {
                if(distance(projectiles[p].current.x,projectiles[p].current.y, objects[a].current.x, objects[a].current.y) < (objects[p].radius + objects[a].radius))
                {
                objects[p].within_radius=projectiles[a].number;
                }
                else
                {
                objects[a].within_radius=0;
                }
            }

    }
};
object B;



void change_size(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h, -1.0,1.0);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	// Set the correct perspective.
	//gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    window_width=w;
    window_height=h;
}


void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);


    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}

void mouse_click( int button, int state, int x, int y )
{
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
	{
	    cursor1.left_down.x=x;
	    cursor1.left_down.y=window_height-y;
	    cursor1.left_click=true;
	}

    if ( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
	{
        cursor1.left_up.x=x;
        cursor1.left_up.y=window_height-y;
        cursor1.highlighting=false;
        cursor1.left_click=false;

	}

	if ( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )
	{
	    cursor1.highlighting=false;
	    cursor1.right_click=true;
        cursor1.right_down.x=x;
        cursor1.right_down.y=window_height-y;
        cursor1.right_dragging=false;

    }

    if ( button==GLUT_RIGHT_BUTTON && state==GLUT_UP )
	{
	    cursor1.highlighting=false;
	    cursor1.right_click=false;
        cursor1.right_up.x=x;
        cursor1.right_up.y=window_height-y;

    }

}

//This is called when user clicks and drags
void mouse_drag(int x, int y)
{
    if(x>cursor1.left_down.x+10 && (window_height - y)<cursor1.left_down.y+10 && cursor1.left_click==true)
    {
        cursor1.highlighting=true;
        cursor1.left_drag.x=x;
        cursor1.left_drag.y=window_height-y;
        cursor1.right_dragging=false;

    }
    else
    {
        cursor1.highlighting=false;
        cursor1.right_drag.x=x;
        cursor1.right_drag.y=window_height-y;
        cursor1.right_dragging=true;

    }


}

void key_pressed (unsigned char key, int x, int y)
{
key_states[key] = true; // Set the state of the current key to pressed
}

void key_up (unsigned char key, int x, int y)
{
key_states[key] = false; // Set the state of the current key to not pressed
}

void key_operations (void)
{

if (key_states['w'])
    {
        objects[current_object].current.y+=objects[current_object].step[up].y;
        objects[current_object].current.x+=objects[current_object].step[up].x;
        //objects[current_object].move_forward(1);
        objects[current_object].action[up]=true;
    }

if (key_states['s'])
    {
        objects[current_object].current.x+=objects[current_object].step[down].x;
        objects[current_object].current.y+=objects[current_object].step[down].y;
        //objects[current_object].move_back(1);
        objects[current_object].action[down]=true;
    }

if (key_states['a'])
    {
        objects[current_object].current.x+=objects[current_object].step[left].x;
        objects[current_object].current.y+=objects[current_object].step[left].y;
        //objects[current_object].move_left(1);
        objects[current_object].action[left]=true;
    }

if (key_states['d'])
    {
        objects[current_object].current.x+=objects[current_object].step[right].x;
        objects[current_object].current.y+=objects[current_object].step[right].y;
        //objects[current_object].move_right(1);
        objects[current_object].action[right]=true;
    }

if (key_states['q'])
    {
        objects[current_object].rotation+=0.1;
    }

if (key_states['e'])
    {
        objects[current_object].rotation-=0.1;
    }



if (key_states['i'])
    {
        if(toggle_text==1)
        temp_toggle[1]=0;

        if(toggle_text==0)
        temp_toggle[1]=1;

    }
else
toggle_text=temp_toggle[1];

// spacebar
if (key_states[32])
    {
        objects[current_object].action[8]=true;
        bullet.fire(objects[current_object]);
    }
    else
    {
        objects[current_object].action[8]=false;

    }

//escape
if (key_states[27])
		exit(0);
}


void text ()
{

    sprintf(text0,"object no.%i", objects[current_object].number);
    glutPrint (window_width/40,window_height -20, GLUT_BITMAP_HELVETICA_12, text0, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text1,"coordinates=%.3f,%.3f", objects[current_object].current.x,objects[current_object].current.y);
    glutPrint (window_width/40,window_height-40, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"velocity %.4f,%.4f",objects[current_object].velocity[1].x,objects[current_object].velocity[1].y);
    glutPrint (window_width/40,window_height -60, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"velocity2 %.4f,%.4f",objects[current_object].velocity[2].x,objects[current_object].velocity[2].y);
    glutPrint (window_width/40,window_height -80, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"resting: %.3f, %.3f",objects[current_object].resting.x,objects[current_object].resting.y);
    glutPrint (window_width/40,window_height -100, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time distance: %.3f %.3f",objects[current_object].delta_time[1],objects[current_object].delta_time[2]);
    glutPrint (window_width/40,window_height -120, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.3f %.3f",objects[current_object].momentum.x,objects[current_object].momentum.y);
    glutPrint (window_width/40,window_height -140, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);
    gametime=time(NULL);
    sprintf(text7,"Force: %.3f %.3f",objects[current_object].force.x,objects[current_object].force.y);
    glutPrint (window_width/40,window_height -160, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.3f %.3f",objects[current_object].acceleration.x,objects[current_object].acceleration.y);
    glutPrint (window_width/40,window_height-180, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.3f %.3f",objects[current_object].delta_time[3],objects[current_object].delta_time[4]);
    glutPrint (window_width/40,window_height-200, GLUT_BITMAP_HELVETICA_12, text9, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text10,"touching object no. L:%d R:%d T:%d B:%d",objects[current_object].touching[left], objects[current_object].touching[right], objects[current_object].touching[up],objects[current_object].touching[down]);
    glutPrint (window_width/40,window_height-220, GLUT_BITMAP_HELVETICA_12, text10, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text11,"rotation:%.2f",objects[current_object].rotation);
    glutPrint (window_width/40,window_height-240, GLUT_BITMAP_HELVETICA_12, text11, 1.0f,0.0f,0.0f, 0.5f);

    /*sprintf(text12,"front:%.2f,%.2f",objects[current_object].front.x,objects[current_object].front.y);
    glutPrint (window_width/40,window_height-260, GLUT_BITMAP_HELVETICA_12, text12, 1.0f,0.0f,0.0f, 0.5f);*/


}


void init_objects()
{
    //initialize the objects

    // object B -the control group
    B.current_color.set(GREEN);
    B.set_coordinates(200.0,160.0);


    //first object from objects array (player)

    objects[1].current_color.set(BLUE);
    objects[1].step_size=0.05;


    //objects[1].rotation=90;

    //second object from objects array
    objects[2].current_color.set(RED);
    objects[2].set_coordinates(400.0,160.0);
    objects[2].rally.x=objects[2].current.x;
    objects[2].rally.y=objects[2].current.y;

    //third object from objects array
    objects[3].current_color.set(0.5,0.5,0.5);
    objects[3].set_coordinates(320.0,60);
    objects[3].rally.x=objects[3].current.x;
    objects[3].rally.y=objects[3].current.y;

    //fourth object from objects array
    objects[4].current_color.set(BLACK);
    objects[4].set_coordinates(320,260);
    objects[4].rally.x=objects[4].current.x;
    objects[4].rally.y=objects[4].current.y;


    //fifth object from objects array
    objects[5].current_color.set(0.0,1.0,1.0);
    objects[5].set_coordinates(200,260);
    objects[5].width=75;
    objects[5].height=75;
    objects[5].step_size=0.001;
    objects[5].rally.x=objects[5].current.x;
    objects[5].rally.y=objects[5].current.y;
}

void render_scene(void) {
    key_operations();


	// Clear Color Buffers
	glClear(GL_COLOR_BUFFER_BIT);

    //glTranslatef(320,160,1.0);

    cursor1.set_boundaries();
    cursor1.selection_box();

//calculate the physics for all objects
    objects[1].physics();
    objects[2].physics();
    objects[3].physics();
    objects[4].physics();
    objects[5].physics();
    bullet.update();
    //bullet.physics();

    collision_detection();//calculate object collision
//move objects

    /*objects[1].move_to_point(objects[1].rally.x,objects[1].rally.y, 9);
    objects[2].move_to_point(objects[2].rally.x,objects[2].rally.y, 8);
    objects[3].move_to_point(objects[3].rally.x,objects[3].rally.y, 7);
    objects[4].move_to_point(objects[4].rally.x,objects[4].rally.y, 6);
    objects[5].move_to_point(objects[5].rally.x,objects[5].rally.y, 5);*/
//mouse interactivity
/*    objects[1].mouse_function();
    objects[2].mouse_function();
    objects[3].mouse_function();
    objects[4].mouse_function();
    objects[5].mouse_function();*/
//render the objects
//NOTE: objects are rendered ontop of eachother according to order rendered below (bottom first)
    objects[5].render();
    objects[4].render();
    objects[3].render();
    objects[2].render();
    B.render();
    bullet.render();
    objects[1].render();
    if(toggle_text==1)
	text();

	glFlush();
}

void initializeWindow()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glViewport(0,0,window_width,window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) window_width , 0.0, (GLdouble) window_height , -1.0, 1.0);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv) {
    /* initialize random seed: */
    srand ( time(NULL) );
    init_objects();
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(window_width,window_height);
	printf("window size: %dX%d\n", window_width, window_height);
	glutCreateWindow("2D World");
	initializeWindow();
	glutReshapeFunc(change_size);
	glutIdleFunc(render_scene); //use this for animations
	glutKeyboardFunc(key_pressed); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(key_up); // Tell GLUT to use the method "keyUp" for key releases
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_drag);
  //  glutPassiveMotionFunc(mouseMovement);
	// enter GLUT event processing cycle
    glutDisplayFunc(render_scene);
	printf("rendering...\n");
	glutMainLoop();
}
