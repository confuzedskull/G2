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
//started implementing object collision (object_collision as apposed to object.collision())
//added array of objects called "objects[max_objects]"
//added const int max_object to global variables
//removed gltranslate from render method
//added comments
//rendered object B and first object from the array "objects"
//fixed text to display on top of everything else
//more comments here and there
//created new struct "color"
//changed object.color from float color[3] to color current_color and applied changes to render method


//global definitions
const int max_objects = 2;//maximum number of objects to be created for collision testing
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
        current_color.r=R;
        current_color.g=G;
        current_color.b=B;
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

    bool touching[4];
    /* touching 1: top
    touching 2: bottom
    touching 3: left
    touching 4: right*/

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





        printf("object: %s no.%d initialized\n", name, number);
    }

};
object B;
object player;


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

//Collision Detection
void object::collision()
{if(number!=B.number && B.solidity>0)
{
    if(current.x<B.xmax && current.x>B.xmin && ymin<=B.ymax && current.y>B.current.y)
    {
        touching[1]=true;
        velocity[2].y=velocity[2].y * (solidity-B.solidity);
    }
    if(current.x<B.xmax && current.x>B.xmin && ymax>=B.ymin && current.y<B.current.y)
    {
        touching[2]=true;
        velocity[2].y=velocity[2].y * (solidity-B.solidity);
    }
    if(xmax>=B.xmin && current.x<B.current.x && ymax<=B.ymax && ymin>=B.ymin)
    {
        touching[3]=true;
        velocity[2].x=velocity[2].x * (solidity-B.solidity);

    }
    if(xmin<=B.xmax && current.x>B.current.x && ymax<=B.ymax && ymin>=B.ymin)
    {
        touching[4]=true;
        velocity[2].x=velocity[2].x * (solidity-B.solidity);
    }
}
}

object* objects = new object[max_objects];

void object_collision()
{
    for(int a; a<max_objects; a++)
    {
        for(int b; b<max_objects; b++)
        {
            if(objects[a].current.x<objects[b].xmax && objects[a].current.x>objects[b].xmin && objects[a].ymin<=objects[b].ymax && objects[a].current.y>objects[b].current.y)
                {
                    objects[a].touching[1]=true;
                    objects[a].velocity[2].y=objects[a].velocity[2].y * (objects[a].solidity-objects[b].solidity);
                }
            if(objects[a].current.x<objects[b].xmax && objects[a].current.x>objects[b].xmin && objects[a].ymax>=objects[b].ymin && objects[a].current.y<objects[b].current.y)
                {
                    objects[a].touching[2]=true;
                    objects[a].velocity[2].y=objects[a].velocity[2].y * (objects[a].solidity-B.solidity);
                }
            if(objects[a].xmax>=objects[b].xmin && objects[a].current.x<objects[b].current.x && objects[a].ymax<=objects[b].ymax && objects[a].ymin>=objects[b].ymin)
                {
                    objects[a].touching[3]=true;
                    objects[a].velocity[2].x=objects[a].velocity[2].x * (objects[a].solidity-objects[b].solidity);

                }
            if(objects[a].xmin<=objects[b].xmax && objects[a].current.x>objects[b].current.x && objects[a].ymax<=objects[b].ymax && objects[a].ymin>=objects[b].ymin)
                {
                    objects[a].touching[4]=true;
                    objects[a].velocity[2].x=objects[a].velocity[2].x * (objects[a].solidity-objects[b].solidity);
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
        player.current.y+=0.01;
        player.action[4]=true;
    }

if (keyStates['s'])
    {
        player.current.y-=0.01;
        player.action[5]=true;
    }

if (keyStates['a'])
    {
        player.current.x-=0.01;
        player.action[2]=true;
    }

if (keyStates['d'])
    {
        player.current.x+=0.01;
        player.action[3]=true;
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
        player.action[6]=true;

    }
    else
    player.energy=100;
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

    sprintf(text1,"player coordinates=%.3f,%.3f",player.current.x,player.current.y);
    glutPrint (window_width/-80,window_height/90.5, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"player velocity %.4f,%.4f",player.velocity[1].x,player.velocity[1].y);
    glutPrint (window_width/-80,3, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"player velocity2 %.4f,%.4f",player.velocity[2].x,player.velocity[2].y);
    glutPrint (window_width/-80,2, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"player resting: %.3f, %.3f",player.resting.x,player.resting.y);
    glutPrint (window_width/-80,1, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time distance: %.3f %.3f",player.delta_time[1],player.delta_time[2]);
    glutPrint (window_width/-80,0, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.3f %.3f",player.momentum.x,player.momentum.y);
    glutPrint (window_width/-80,-1, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);
    gametime=time(NULL);
    sprintf(text7,"Force: %.3f %.3f",player.force.x,player.force.y);
    glutPrint (window_width/-80,-2, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.3f %.3f",player.acceleration.x,player.acceleration.y);
    glutPrint (window_width/-80,-3, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.3f %.3f",player.delta_time[3],player.delta_time[4]);
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
    player.set_color(0.0,0.0,1.0);
    B.set_color(0.0,1.0,0.0);
    player.physics();
    B.physics();

//initialize first object from objects array
    objects[1].set_coordinates(5.0,0.0);
    objects[1].physics();
    objects[1].set_color(1.0,0.0,0.0);

//render the objects
//NOTE: objects are rendered ontop of eachother according to order rendered below (bottom first)

    glTranslatef(0.0,0.0,0.0f);

    objects[1].render();
    B.render();
    player.render();
    text();


    object_collision();

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
