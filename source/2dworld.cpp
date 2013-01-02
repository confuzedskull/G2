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

struct limit{float xmin; float xmax; float ymin; float ymax;};

char* text1;

class object
{

    public:
    char* name;
    int number;
    char catagory[10];
    char status[10];
    double speed;
    float x,y;
    int width, length,height;
    int radius;
    int weight;
    float xmin,xmax,ymin,ymax;
    float color[3];//RGB values
    void set_coordinates(int a,int b)
    {
        x=x+a;
        y=y+b;
    }
    void set_boundaries()
    {
        xmin= x-(width/2);
        xmax= x+(width/2);
        ymin= y-(height/2);
        ymax= y+(height/2);
    }
    void set_color(float R,float G,float B)
    {
        color[1]=R;
        color[2]=G;
        color[3]=B;
    }
    void set_speed(double s)
    {
        speed=s;
    }

    bool on_screen()
    {
        if(x>0 || x<window_width ||
           y>0 || y<window_height)
           return true;
        else
            return false;
    }

    void render()
    {
        glTranslatef(x,y,0.0f);
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
        set_coordinates(random1,random2);
        set_color(1.0,1.0,1.0);
        width=2;
        length=2;
        height=2;
        set_boundaries();

        printf("object: %s no.%d initialized\n", name, number);
    }

};

object player;
object enemy;

float xtrans=0.0f, ytrans=0.0f,jump=0.0f;
float lastx, lasty;

const float piover180 = 0.0174532925f;
float heading;

int mouse_x;
int mouse_y;

GLfloat lookupdown = 0.0f;

float distance(float x1, float y1, float x2, float y2)
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}
/*
bool object::touching(object object1, object object2)
{

    if (distance(object1.x,object1.y,object2.x,object2.y) <= object1.radius+object2.radius)
    return true;
    else
    return false;
}
*/

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
        player.y+=0.01f*player.speed;
    }

if (keyStates['s'])
    {
        player.y-=0.01f*player.speed;
    }

if (keyStates['a'])
    {
        player.x-=0.01f*player.speed;
    }

if (keyStates['d'])
    {
        player.x+=0.01*player.speed;
    }

/* spacebar
if (keyStates[32])
    {

    }


if (keyStates[32]==false && temp!=0 && player.action!=jumping && player.action!=falling)
{
    mod.action=jumping;
    temp=0;
}
*/
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

void text (void)
{
    int scaled_xpos=window_width*0.75;

    sprintf(text1,"x=%f",player.x);

    glutPrint (5.0f,5.0f, GLUT_BITMAP_HELVETICA_12, text1, 0.0f,0.0f,0.0f, 0.5f);

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

    player.set_speed(0.5);
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
