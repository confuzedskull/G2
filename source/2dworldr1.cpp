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

int random1 = rand() % 5 + 1;
int random2 = rand() % 5 + 1;

int object_no=0;

struct point {double x; double y;};
struct vect {double x; double y;};
char* text1;

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
world current;

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
    int mass;
    time_t start,end;
    double time_interval[2];
    vect velocity;
    vect momentum;
    int solidity;
    float xmin,xmax,ymin,ymax;
    float color[3];//RGB values
    void set_coordinates(int a,int b)
    {
        current.x=current.x+a;
        current.y=current.y+b;
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
        if(current.x>0 || current.x<window_width ||
           current.y>0 || current.y<window_height)
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

    bool touching[4];
    /* touching 1: top
    touching 2: bottom
    touching 3: left
    touching 4: right*/

    void set_resting()
    {
        if(action[1]==true)
        {
            resting.x=current.x;
            resting.y=current.y;
            time(&end);
            time_interval[1]= difftime(end,start);

        }
        else
        {
            time(&start);
        }
    }
    void calc_velocity()
    {
        velocity.x=(current.x-resting.x)/(time_interval[1]);
        velocity.y=(current.y-resting.y)/(time_interval[1]);
    }

    void calc_momentum()
    {
        momentum.x=mass*velocity.x;
        momentum.y=mass*velocity.y;
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
        set_color(1.0,1.0,1.0);
        width=1.0;
        height=1.0;
        mass=5;
        solidity=5;
        set_boundaries();
        action[7]=true;

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
        current.y=current.y + (velocity.y+world_gravity);
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
        player.current.y+=player.velocity.y;
        player.action[4]=true;
    }

if (keyStates['s'])
    {
        player.current.y-=player.velocity.y;
        player.action[5]=true;
    }

if (keyStates['a'])
    {
        player.current.x-=player.velocity.x;
        player.action[2]=true;
    }

if (keyStates['d'])
    {
        player.current.x+=player.velocity.x;
        player.action[3]=true;
    }

// spacebar
if (keyStates[32])
    {
        player.action[6]=true;
        player.current.y+=0.5;
    }

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
    sprintf(text1,"x=%d",player.current.x);

    glutPrint (0.0f,0.0f, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);
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
    player.velocity.x=0.005;
    player.velocity.y=0.005;

    player.gravity();
    player.set_color(1.0,1.0,1.0);
//render the objects
    glTranslatef(0.0,0.0,0.0f);

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

	return 1;
}
