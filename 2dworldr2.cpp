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
struct vect {float x; float y;};
char text1[30];
char text2[20];
char text3[20];
char text4[20];
char text5[20];
char text6[10];
char text7[10];
char text8[10];
char text9[10];

float xtrans=0.0f, ytrans=0.0f,jump=0.0f;
float lastx, lasty;

const float piover180 = 0.0174532925f;
float heading;

int mouse_x;
int mouse_y;

GLfloat lookupdown = 0.0f;

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
    time_t start1,end1;
    time_t start2,end2;
    double delta_time[2];
    int stopwatch;
    vect velocity;
    vect momentum;
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
    action 8: moving left/right
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
        if(current.y<=resting.y+0.01 && current.y>resting.y)
        {
            action[1]=true;
            velocity.y=0.0f;

        }
        else
        time(&start2);


        if(action[1]==true)
        {

            resting.y=current.y;
            time(&end2);
            //delta_time[2]=difftime(end2,start2);


        }

        if(action[2]==true || action[3]==true)
        {
            resting.x=current.x;
            time(&start1);
        }
        else
        {
            time(&end1);
            //delta_time[1]=difftime(end1,start1);

        }
    }
    void calc_velocity()
    {   delta_time[1]=(current.x-resting.x)/velocity.x;
        //velocity.x=(current.x-resting.x)/delta_time[1];

        delta_time[2]=(current.y-resting.y)/velocity.y;
        //velocity.y=(current.y-resting.y)/delta_time[2];
    }

    void calc_momentum()
    {
        momentum.x=mass*velocity.x;
        current.x +=momentum.x;
        if(momentum.x==0)
        action[8]=false;
        momentum.y=mass*velocity.y;
        current.y +=momentum.y;
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
        mass=0.005;
        solidity=5;
        energy=100;
        momentum.x=0.0f;
        momentum.y=0.0f;
        velocity.x=0.0f;
        velocity.y=0.0f;



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
        velocity.y-=world_gravity;
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
        velocity.y=velocity.y * (solidity-B.solidity);
    }
    if(current.x<B.xmax && current.x>B.xmin && ymax>=B.ymin && current.y<B.current.y)
    {
        touching[2]=true;
        velocity.y=velocity.y * (solidity-B.solidity);
    }
    if(xmax>=B.xmin && current.x<B.current.x && ymax<=B.ymax && ymin>=B.ymin)
    {
        touching[3]=true;
        velocity.x=velocity.x * (solidity-B.solidity);

    }
    if(xmin<=B.xmax && current.x>B.current.x && ymax<=B.ymax && ymin>=B.ymin)
    {
        touching[4]=true;
        velocity.x=velocity.x * (solidity-B.solidity);
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
/*
void ViewOrtho(int x, int y)							// Set Up An Ortho View
{
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho( 0, x , y , 0, -1, 1 );				// Select Ortho Mode
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
}
*/
/*
void ViewPerspective(void)							// Set Up A Perspective View
{
	glMatrixMode( GL_PROJECTION );					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode( GL_MODELVIEW );					// Select Modelview
	glPopMatrix();							// Pop The Matrix
}
*/

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
        player.velocity.y+=0.01;
        player.action[4]=true;
    }

if (keyStates['s'])
    {
        player.current.y-=0.01;
        player.velocity.y-=0.01;
        player.action[5]=true;

    }

if (keyStates['a'])
    {
        player.current.x-=0.01;
        player.velocity.x-=0.01;
        player.action[2]=true;

    }
    else
    player.action[2]=false;

if (keyStates['d'])
    {
        player.current.x+=0.01;
        player.velocity.x+=0.01;
        player.action[3]=true;
    }



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

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position

    if(x>=window_width||x<=-window_width || y>=window_height||y<=-window_height)
    glutWarpPointer(window_width / 2, window_height / 2);
}

void text ()
{

    sprintf(text1,"player coordinates=%.3f,%.3f",player.current.x,player.current.y);
    glutPrint (window_width/-80,window_height/90.5, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"player velocity %.4f,%.4f",player.velocity.x,player.velocity.y);
    glutPrint (window_width/-80,3, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"player action %d",player.get_action());
    glutPrint (window_width/-80,2, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"player resting: %.3f, %.3f",player.resting.x,player.resting.y);
    glutPrint (window_width/-80,1, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time: %.3f %.3f",player.delta_time[1],player.delta_time[2]);
    glutPrint (window_width/-80,0, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.3f %.3f",player.momentum.x,player.momentum.y);
    glutPrint (window_width/-80,-1, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);
    gametime=time(NULL);
    sprintf(text7,"Time: %ld",gametime);
    glutPrint (window_width/-80,-2, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"time change x: %d %d",player.start1,player.end1);
    glutPrint (window_width/-80,-3, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"time change y: %d %d",player.start2,player.end2);
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

    player.gravity();
    player.set_resting();
    //player.calc_velocity();
    player.calc_momentum();
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
