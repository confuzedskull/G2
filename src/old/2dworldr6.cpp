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
//2D World
//by James Nakano

//This is an original game engine created from the ground up using openGL and glut
//Disclaimer: The glut and opengl libraries are obviously not mine, but everything else is.
//

//changelog
//objects[1] is now objects[2]
//changed object player to objects[1] and made necessary changes to any methods called by "player"
//changed max_objects to 3. apparently the number of max objects is crucial to the program compiling
//added condition to object_collision so that objects aren't compared to themselves
//renamed object_collision  to collision_detection
//added object.prev_color and object.undo_color
//modified object.collision() for testing collision_detections
//fixed collision detection. y boundary conditions were wrong.
//added else statements to collision detection. The touching boolean values did not have false conditions
//removed else statements from object.collision()
//changed colors for better contrast

//global definitions

const int max_objects = 3;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number
bool* keyStates = new bool[256]; // Create an array of boolean values of letters
//width and height of program window
int window_width=640;
int window_height=320;

int random1 = rand() % 4 + 1;//random number between 1 and 4
int random2 = rand() % 4 + 1;//another random number between 1 and 4

int object_no=0;//initial object number. This gets incremented and assigned to object.number after each object is created.

int player_action;

int frames=0;//to be used for frame count

time_t gametime;//to be used for game clock

struct color {float r; float g; float b;};//color with red, green, blue

struct point {float x; float y;};
struct vect {float x; float y;};// used vect instead of vector because vector is already declared....I think
char text1[30];
char text2[20];
char text3[20];
char text4[20];
char text5[20];
char text6[10];
char text7[10];
char text8[10];
char text9[10];

const float piover180 = 0.0174532925f;
float heading;

int mouse_x;//global variable for mouse x
int mouse_y;//global variable for mouse y

int temp_toggle[2];
int toggle_text;

class world
{
    public:
    char name;
    int gravity;
    int wind;
    void physics();
};
world current_world;

double world_gravity=-0.01;

class object
{

    public:
    char* name;
    int number;
    char catagory[10];//not yet used
    char status[10];//not yet used
    point current;
    point resting;
    double width, height;
    int radius;//used for round objects or object's perimeter
    float mass;
    float delta_time[4];//each element of array represents how much time a change in a direction or velocity took
    //1:change in x, 2:change in velocity, 3:change in velocity x, 4:change in velocity y
    vect velocity[2];// 1:initial velocity, 2: final velocity
    vect acceleration;
    vect momentum;
    vect force;
    float energy;
    int solidity;//a value from 1 to 5 that indicates the density of the object
    float xmin,xmax,ymin,ymax;//boundaries used for collision detection and rendering
    color current_color;//RGB values
    color prev_color;
    void set_coordinates(float a,float b)//sets coordinates of current object position
    {
        current.x=a;
        current.y=b;
    }
    void set_boundaries()
    {
        xmin= current.x-(width/2);
        xmax= current.x+(width/2);
        ymin= current.y-(height/2);
        ymax= current.y+(height/2);
    }
    void set_color(float R,float G,float B)
    {
        prev_color.r=current_color.r;
        prev_color.g=current_color.g;
        prev_color.b=current_color.b;
        current_color.r=R;
        current_color.g=G;
        current_color.b=B;
    }

    void undo_color()
    {
        current_color.r=prev_color.r;
        current_color.g=prev_color.g;
        current_color.b=prev_color.b;
    }

    bool on_screen()
    {
        if(xmax>-4 && xmin<4 &&
           ymin>-2 && ymax<2)
           return true;
        else
            return false;
    }

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

    int get_action()
    {

        for(int a=1;a<10;a++)
        {
            if(action[a]==true)
            return a;
            else
            return 0;

        }

    }

    bool touching[5];
    /* touching 1: on top of
    touching 2: left
    touching 3: right
    touching 4: top
    touching 5: bottom*/

    void set_resting()

    {

        if(velocity[2].y>-1 && velocity[2].y<1)
        {

            resting.y=current.y;

            action[4]=false;
            action[5]=false;

        }

        if(velocity[2].x>-1 && velocity[2].x<1)
        {
            resting.x=current.x;
            action[2]=false;
            action[3]=false;
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
    {   //delta_time[1]=(current.x-resting.x)/velocity[2].x;

        /*if(delta_time[1]==0)
        velocity[1].x=0;
        else*/
        velocity[1].x=(current.x-resting.x)/delta_time[1];

        //delta_time[2]=(current.y-resting.y)/velocity[2].y;
        /*if(delta_time[2]==0)
        velocity[1].y=0;
        else*/
        velocity[1].y=(current.y-resting.y)/delta_time[2];


    }

    void calc_acceleration()
    {   if(delta_time[3]!=0)
        acceleration.x=0;
        else
        acceleration.x=(velocity[2].x - velocity[1].x)/delta_time[3];



        //delta_time[3]=(velocity[1].x - velocity[2].x)/acceleration.x;
        //velocity[2].x=-1*((delta_time[3]*acceleration.x)-velocity[1].x);
        //velocity[1].x=(delta_time[3]*acceleration.x)+velocity[2].x;

        if(delta_time[4]!=0)
        acceleration.y=0;
        else
        acceleration.y=(velocity[2].y - velocity[1].y)/delta_time[4];


        //delta_time[4]=(velocity[1].y - velocity[2].y)/acceleration.y;
        //velocity[2].y=-1*((delta_time[4]*acceleration.y)-velocity[1].y);
        //velocity[1].y=(delta_time[4]*acceleration.y)+velocity[2].y;
    }

    void calc_force()
    {
        force.x=mass*acceleration.x;
        //acceleration.x=force.x/mass;
        force.y=mass*acceleration.y;
        //acceleration.y=force.y/mass;
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
    void gravity();
    void collision();
    void physics();

    void render()
    {
        glScaled(width,height,0.0);
        glBegin(GL_QUADS);
        glColor3f(current_color.r,current_color.g,current_color.b);
        glVertex3f(xmin, ymin, 0.0f); // The bottom left corner
        glVertex3f(xmin, ymax, 0.0f); // The top left corner
        glVertex3f(xmax, ymax, 0.0f); // The top right corner
        glVertex3f(xmax, ymin, 0.0f); // The bottom right corner
        glEnd();
    }
    object()
    {
        name="generic object";
        object_no++;
        number=object_no;
        current.x=0;
        current.y=0;
        resting.x=0;
        resting.y=0;
        width=1.0;
        height=1.0;
        mass=0.01;//note: changing this seems to have an effect on set_resting
        solidity=5;
        energy=100;
        toggle_text=1;
        current_color.r=1;
        current_color.g=1;
        current_color.b=1;







        printf("object: %s no.%d initialized\n", name, number);
    }

};
object B;


void object::gravity()
{


    if(momentum.y==0)
    {
        action[7]==true;
    }

    if(action[7]==true)
    {
        velocity[2].y-=world_gravity;
        action[1]==false;
    }

}





float distance(float x1, float y1, float x2, float y2)
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

//does stuff depending on whether the object is being touched in a certain place
void object::collision()
{

    if(touching[2]==true)//touching left
    {
        set_color(2,1,0);//yellow
    }


    if(touching[3]==true)//touching right
    {
        set_color(0,1,1);//cyan
    }



    if(touching[4]==true)//touching top
    {
        set_color(1,0.65,0);//orange
    }


    if(touching[5]==true)//touching bottom
    {
        set_color(1,0,1);//pink
    }



}


object* objects = new object[max_objects];

void collision_detection()
{
    for(int a=0; a<max_objects; a++)
    {
        for(int b=0; b<max_objects; b++)
        {
            if(b!=a)
            {
            if(objects[a].xmin<objects[b].xmax && objects[a].current.x>objects[b].xmax
               && objects[a].ymin<objects[b].ymax && objects[a].ymax>objects[b].ymin)
                {
                    objects[a].touching[2]=true;
                    //objects[a].velocity[2].y=objects[a].velocity[2].y * (objects[a].solidity-objects[b].solidity);
                }
                else
                objects[a].touching[2]=false;

            if(objects[a].xmax>objects[b].xmin && objects[a].current.x<objects[b].xmin
               && objects[a].ymax>objects[b].ymin && objects[a].ymin<objects[b].ymax)
                {
                    objects[a].touching[3]=true;
                    //objects[a].velocity[2].y=objects[a].velocity[2].y * (objects[a].solidity-B.solidity);
                }
                else
                objects[a].touching[3]=false;

            if(objects[a].xmax>objects[b].xmin && objects[a].xmin<objects[b].xmax
               && objects[a].current.y<objects[b].ymin && objects[a].ymax>objects[b].ymin)
                {
                    objects[a].touching[4]=true;
                    //objects[a].velocity[2].x=objects[a].velocity[2].x * (objects[a].solidity-objects[b].solidity);

                }
                else
                objects[a].touching[4]=false;

            if(objects[a].xmin<objects[b].xmax && objects[a].xmax>objects[b].xmin
               && objects[a].current.y>objects[b].ymax && objects[a].ymin<objects[b].ymax)
                {
                    objects[a].touching[5]=true;
                    //objects[a].velocity[2].x=objects[a].velocity[2].x * (objects[a].solidity-objects[b].solidity);
                }
                else
                objects[a].touching[5]=false;
            }
        }
    }
}

void object::physics()
{
    set_resting();
    calc_delta_time();
    calc_velocity();
    //friction();
    calc_acceleration();
    calc_momentum();
    calc_force();
    set_boundaries();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
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

void keyPressed (unsigned char key, int x, int y)
{
keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp (unsigned char key, int x, int y)
{
keyStates[key] = false; // Set the state of the current key to not pressed
}

void keyOperations (void)
{

if (keyStates['w'])
    {
        objects[1].current.y+=0.01;
        objects[1].action[4]=true;
    }

if (keyStates['s'])
    {
        objects[1].current.y-=0.01;
        objects[1].action[5]=true;
    }

if (keyStates['a'])
    {
        objects[1].current.x-=0.01;
        objects[1].action[2]=true;
    }

if (keyStates['d'])
    {
        objects[1].current.x+=0.01;
        objects[1].action[3]=true;
    }

if (keyStates['i'])
    {
        if(toggle_text==1)
        temp_toggle[1]=0;

        if(toggle_text==0)
        temp_toggle[1]=1;

    }
else
toggle_text=temp_toggle[1];

// spacebar
if (keyStates[32])
    {
        objects[1].action[6]=true;

    }
    else
    objects[1].energy=100;
//escape
if (keyStates[27])
		exit(0);
}


void mouse_enter(int state)
{
    if (state==GLUT_ENTERED)
    glutWarpPointer(window_width / 2, window_height / 2);
}

void mouse_func( int button, int state, int x, int y )
{
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
	{
	    mouse_x=x;
	    mouse_y=y;
		//glutPostRedisplay();
	}

	if ( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
	{

	}
}


void text ()
{

    sprintf(text1,"player coordinates=%.3f,%.3f",objects[1].current.x,objects[1].current.y);
    glutPrint (window_width/-80,window_height/90.5, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"player velocity %.4f,%.4f",objects[1].velocity[1].x,objects[1].velocity[1].y);
    glutPrint (window_width/-80,3, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"player velocity2 %.4f,%.4f",objects[1].velocity[2].x,objects[1].velocity[2].y);
    glutPrint (window_width/-80,2, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"player resting: %.3f, %.3f",objects[1].resting.x,objects[1].resting.y);
    glutPrint (window_width/-80,1, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time distance: %.3f %.3f",objects[1].delta_time[1],objects[1].delta_time[2]);
    glutPrint (window_width/-80,0, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.3f %.3f",objects[1].momentum.x,objects[1].momentum.y);
    glutPrint (window_width/-80,-1, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);
    gametime=time(NULL);
    sprintf(text7,"Force: %.3f %.3f",objects[1].force.x,objects[1].force.y);
    glutPrint (window_width/-80,-2, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.3f %.3f",objects[1].acceleration.x,objects[1].acceleration.y);
    glutPrint (window_width/-80,-3, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.3f %.3f",objects[1].delta_time[3],objects[1].delta_time[4]);
    glutPrint (window_width/-80,-3.5, GLUT_BITMAP_HELVETICA_12, text9, 1.0f,0.0f,0.0f, 0.5f);


}

void updateScene(void)
{


}

void renderScene(void) {

    keyOperations();


	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

    gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);
//initialize the objects

//first object from objects array (player)
    objects[1].set_color(0.0,0.0,1.0);
    objects[1].physics();
    objects[1].collision();


//second object from objects array
    objects[2].set_coordinates(5.0,0.0);
    objects[2].physics();
    objects[2].set_color(1.0,0.0,0.0);
    objects[2].collision();

// object B -the control group
    B.set_color(0.0,1.0,0.0);
    B.set_coordinates(-5.0,0.0);
    B.physics();
    B.collision();

//render the objects
//NOTE: objects are rendered ontop of eachother according to order rendered below (bottom first)

    glTranslatef(0.0,0.0,0.0f);

    objects[2].render();
    B.render();
    objects[1].render();
    text();


    collision_detection();//calculate object collision

	glutSwapBuffers();
}

int main(int argc, char **argv) {
    /* initialize random seed: */
    srand ( time(NULL) );
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(window_width,window_height);
	printf("window size: %dX%d\n", window_width, window_height);
	glutCreateWindow("2D World");
	glClearColor(1.0f,1.0f,1.0f,0.0f);

	glutDisplayFunc(renderScene);
	printf("rendering...\n");

	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene); //use this for animations

	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key releases
//    glutEntryFunc(mouse_enter);
   // glutMouseFunc(mouse_func);
  //  glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	// enter GLUT event processing cycle
	glutMainLoop();


}
