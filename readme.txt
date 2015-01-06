G2 Editor
=======
by James Nakano A.K.A. "confuzedskull"

I. Troubleshooting
A. Windows
1. If the program doesn't run, then you must right click it and select "Run as Administrator"

B. Mac
1. If the message "2D Editor was blocked from opening because it is not from an identified developer" pops up, do the following:
a. Go to System Preferences and click on Security & Privacy.
b. Somewhere near the bottom you'll see a message and then a button "Open Anyway". Click it.
c. A prompt will come up saying ""2dworld is a Unix applicaiton downloaded from the internet. Are you sure you want to open it?" Click open.

C. Linux
1. If the program doesn't run when you double click it, try these solutions:
a. Run the program via terminal.
b. Run the program as super user.
c. Make sure the program is being opened as an executable.

II. Controls
A. Mouse
1. In-Game
a. left click an object to select it
b. left click empty space to deselect
c. left drag empty space to create a selection box
2.
a. right click empty space to set the rally point and make the selected object move to it
c. right drag to have the selected object follow the cursor
3. Draggable Objects
a. left click and drag an object to move it around

B. Keyboard
1. Global
a. hold down or right arrow key to select next item in menu
b. hold up or left arrow key to select previous item in menu
c. press "enter" or "return" key to choose selected item in menu
2. In-Game
a. press 'esc' to pause game
3. Key-enabled objects
a. hold 'W','A','S','D' to move up,left,down,right, respectively
b. hold 'Q' and 'E' to rotate

III. Known Bugs:
A. Global
2. When navigating menus with the arrow keys, the selector sometimes gets stuck.
3. Some objects appear to twitch when moving.
B. Drag-enabled Objects
1. While dragging, an object may get stuck on top of another object when they collide.
C. Physics Objects
1. Some of the object's physics values do not zero out when object is at rest.

Disclaimer:
 This program uses the OpenGL Utility Toolkit(A.K.A."GLUT") created by Mark Kilgard.
Thanks to his work, creating cross-platform OpenGL applications is much easier.
Since GLUT is not open source, I have not touched any of the source files.
Instead, I have linked the library to the executable and included glut32.dll in the project directory.
For more information on GLUT, visit https://www.opengl.org/resources/libraries/glut/
