2DWorld
=======
by James Nakano AKA confuzedskull

I. Troubleshooting
A. Windows
1. If the program doesn't run, then you must right click it and select "Run as Administrator"

B. Mac
1. If the message " "2dworld" was blocked from opening because it is not from an identified developer" do the following:
a. Go to System Preferences and click on Security & Privacy.
b. Somewhere near the bottom you'll see a message and then a button "Open Anyway". Click it.
c. A prompt will come up saying ""2dworld is a Unix applicaiton downloaded from the internet. Are you sure you want to open it?" Click open.

C. Linux
1. If you're using Linux, you can probably figure out how to get it running on your own.

II. Controls
A. Mouse
1. Global
a. left click an object to select it
b. left click empty space to deselect
2. RTS Objects
a. left drag down and right to create a selection box
b. right click empty space to set the rally point and make the selected object move to it
c. right click an object to make the selected object follow it
d. right drag to have the selected object follow the cursor
3. Draggable Objects
a. left click and drag an object to move it around

B. Keyboard
1. Global
a. 'i' for information overlay
b. esc to quit
2. Physics Objects
a. 'W','A','S','D' to move up,left,down,right, respectively
b. 'Q' and 'E' to rotate
c. spacebar to shoot


III. Known Bugs:
A. Physics Objects
1. Shooting no longer works.
2. An object's resting point gets set even when it's moving.
3. Some of the object's physics values do not zero out when object is at rest.
B. RTS Objects
1. An object's resting point doesn't get set at all.

Disclaimer:
This program uses the OpenGL Utility Toolkit(A.K.A."GLUT") created by Mark Kilgard.
Thanks to his work, creating cross-platform OpenGL applications is much easier.
Since glut is not open source, I have not touched any of the source files.
Instead, I have linked the library to the executable and included glut32.dll in the project directory.
For more information on GLUT, visit https://www.opengl.org/resources/libraries/glut/