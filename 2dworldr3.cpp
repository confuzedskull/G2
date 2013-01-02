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


//fixed set_resting
//removed difftime function and start/end time_t variables
//fixed calc_velocity
//delta_time now works
//working on acceleration,force, momentum.


bool* keyStates = new bool[256]; // Create an array of boolean values of letters
//width and height of program window
int window_width=640;
int window_height=320;

int random1 = rand() % 4 + 1;
int random2 = rand() % 4 + 1;

int object_no=0;

int player_action;

int frames=0;

time_t gametime;

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
    char catagory[10];
    char status[10];
    point current;
    point resting;
    double width, height;
    int radius;
    float mass;
    float delta_time[4];//each element of array represents a change in time for a change in a direction or velocity
    vect velocity[2];
    vect acceleration;
    vect momentum;
    vect force;
    float energy;
    int solidity;
    float xmin,xmax,ymin,ymax;
    float color[3];//RGB values
    void set_coordinates(float a,float b)
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
        color[1]=R;
        color[2]=G;
        color[3]=B;
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
        if(velocity[2].y<0.001 && velocity[2].y>-0.001)
        {
            action[1]=true;
            resting.y=current.y;
            action[4]=false;
            action[5]=false;

        }

        if(velocity[2].x<0.001 && velocity[2].x>-0.001)
        {
            resting.x=current.x;
            action[2]=false;
            action[3]=false;
        }
    }

    void calc_delta_time()
    {

        if(current.x==resting.x || action[2]==false && action[3]==false)
        delta_time[1]=0.0;
        else
        delta_time[1]+=0.01;

        if(current.y==resting.y ||action[4]==false && action[5]==false)
        delta_time[2]=0.0;
        else
        delta_time[2]+=0.01;

        if(velocity[2].x==velocity[1].x)
        delta_time[3]=0.0;
        else
        delta_time[3]+=0.01;

        if(velocity[2].y==velocity[1].y)
        delta_time[4]=0.0;
        else
        delta_time[4]+=0.01;
    }
    void calc_velocity()
    {   //delta_time[1]=(current.x-resting.x)/velocity[2].x;

        if(delta_time[1]==0 || current.x==resting.x)
        velocity[2].x=0;
        else
        velocity[2].x=(current.x-resting.x)/delta_time[1];

        //delta_time[2]=(current.y-resting.y)/velocity[2].y;
        if(delta_time[2]==0 || current.y==resting.y)
        velocity[2].y=0;
        else
        velocity[2].y=(current.y-resting.y)/delta_time[2];
    }

    void calc_acceleration()
    {   /*if(velocity[1].x==velocity[2].x || delta_time[3]==0)
        acceleration.x=0.0f;
        else*/
        acceleration.x=(velocity[2].x - velocity[1].x)/delta_time[3];


        //delta_time[3]=(velocity[1].x - velocity[2].x)/acceleration.x;
        //velocity[2].x=-1*((delta_time[3]*acceleration.x)-velocity[1].x);
        //velocity[1].x=(delta_time[3]*acceleration.x)+velocity[2].x;

        /*if(velocity[1].y==velocity[2].y || delta_time[4]==0)
        acceleration.y=0.0f;
        else*/
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
        momentum.x=mass*velocity[2].x;
        //current.x +=momentum.x;
        momentum.y=mass*velocity[2].y;
        //current.y +=momentum.y;
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
        glTranslatef(current.x,current.y,0.0f);
        glBegin(GL_QUADS);
        glColor3f(color[1],color[2],color[3]);
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
        current.x=0.0;
        current.y=0.0;
        resting.x=0.0;
        resting.y=-1.8;
        width=1.0;
        height=1.0;
        mass=5;
        solidity=5;
        energy=100;
        momentum.x=0.0f;
        momentum.y=0.0f;
        force.x=0;
        force.y=0;
        velocity[1].x=0.0f;
        velocity[1].y=0.0f;
        velocity[2].x=0.0f;
        velocity[2].y=0.0f;



        printf("object: %s no.%d initialized\n", name, number);
    }

};

object player;

object enemy;

void object::gravity()
{


    if(momentum.y==0 && action[1]==false)
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
object B;
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

void object::physics()
{
    calc_velocity();
    calc_momentum();
    gravity();
    collision();
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
        //player.velocity[2].y+=0.01;
        player.action[4]=true;
        //player.force.y=0.001;
    }

if (keyStates['s'])
    {
        player.current.y-=0.01;
        //player.velocity[2].y-=0.01;
        player.action[5]=true;
        //player.force.y=-0.001;

    }

if (keyStates['a'])
    {
        player.current.x-=0.01;
        //player.velocity[2].x-=0.01;
        player.action[2]=true;
        //player.force.x=-0.001;
        //player.delta_time[3]=player.delta_time[1];

    }
    /*else
    {
        player.velocity[1].x=player.velocity[2].x;

    }*/


if (keyStates['d'])
    {
        player.current.x+=0.01;
        //player.velocity[2].x+=0.01;
        player.action[3]=true;
        //player.force.x=0.001;
        //player.delta_time[3]=player.delta_time[1];
    }
    /*else
    {
        player.velocity[1].x=player.velocity[2].x;
    }*/




// spacebar
if (keyStates[32])
    {
        player.action[6]=true;

    }
    else
    player.energy=100;

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

    sprintf(text2,"player velocity %.4f,%.4f",player.velocity[2].x,player.velocity[2].y);
    glutPrint (window_width/-80,3, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"player action %d",player.get_action());
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
    keyOperations();
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

    //player.gravity();

    player.set_resting();
    player.calc_delta_time();
    player.calc_velocity();
    //player.friction();
    player.calc_acceleration();
    player.calc_momentum();
    player.calc_force();
    player.set_boundaries();
    player.set_color(0.0,0.0,1.0);
//render the objects

    glTranslatef(0.0,0.0,0.0f);
    text();
    player.render();

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
	glutSetCursor(GLUT_CURSOR_NONE);
//    glutEntryFunc(mouse_enter);
   // glutMouseFunc(mouse_func);
  //  glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	// enter GLUT event processing cycle
	glutMainLoop();


}
