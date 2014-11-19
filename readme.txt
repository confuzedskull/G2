2DWorld
=======
by James Nakano A.K.A. "confuzedskull"

I. Troubleshooting
A. Windows
1. If the program doesn't run, then you must right click it and select "Run as Administrator"

B. Mac
1. If the message " "2dworld" was blocked from opening because it is not from an identified developer" pops up, do the following:
a. Go to System Preferences and click on Security & Privacy.
b. Somewhere near the bottom you'll see a message and then a button "Open Anyway". Click it.
c. A prompt will come up saying ""2dworld is a Unix applicaiton downloaded from the internet. Are you sure you want to open it?" Click open.

C. Linux
1. If you're using Linux, you can probably figure out how to get it running on your own.

II. Controls
A. Mouse
1. In-Game
a. left click an object to select it
b. left click empty space to deselect
2. RTS Objects (colored squares)
a. left drag down and right to create a selection box
b. right click empty space to set the rally point and make the selected object move to it
c. right click an object to make the selected object follow it
d. right drag to have the selected object follow the cursor
3. Draggable Objects (black squares)
a. left click and drag an object to move it around

B. Keyboard
1. Global
a. hold down or right arrow key to select next item in menu
b. hold up or left arrow key to select previous item in menu
c. press "enter" or "return" key to choose selected item in menu
2. In-Game
a. press 'i' to toggle information overlay
b. press 'esc' to pause/resume game
c. press "delete" to delete selected object
d. press "insert" to create object of previous selection
3. Physics Objects (gray squares)
a. hold 'W','A','S','D' to move up,left,down,right, respectively
b. hold 'Q' and 'E' to rotate

III. Known Bugs:
A. Global
1. The "insert" key doesn't work on Macs.
2. When navigating menus with the arrow keys, the selector sometimes gets stuck.
3. Some objects appear to twitch when moving.
B. Draggable Objects
1. While dragging, an object may get stuck on top of another object when they collide.
C. Physics Objects
1. An object's resting point gets set even when it's moving.
2. Some of the object's physics values do not zero out when object is at rest.
D. RTS Objects
1. An object's resting point doesn't get set at all.

Disclaimer:
This program uses the OpenGL Utility Toolkit(A.K.A."GLUT") created by Mark Kilgard.
Thanks to his work, creating cross-platform OpenGL applications is much easier.
Since GLUT is not open source, I have not touched any of the source files.
Instead, I have linked the library to the executable and included glut32.dll in the project directory.
For more information on GLUT, visit https://www.opengl.org/resources/libraries/glut/