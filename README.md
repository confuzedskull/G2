# G2 Editor
by James Nakano A.K.A. "confuzedskull"

# Troubleshooting
## Windows
If the program doesn't run, then you must right click it and select "Run as Administrator"

## Mac
If the message "2D Editor was blocked from opening because it is not from an identified developer" pops up, do the following:

1. Go to System Preferences and click on Security & Privacy.
2. Somewhere near the bottom you'll see a message and then a button "Open Anyway". Click it.
3. A prompt will come up saying "2dworld is a Unix applicaiton downloaded from the internet. Are you sure you want to open it?" Click open.

## Linux
If the program doesn't run when you double click it, try these solutions:

1. Run the program via terminal.
2. Run the program as super user.
3. Make sure the program is being opened as an executable.

# Controls
## Mouse
### In-Game
- left click an object to select it
- left click empty space to deselect

### RTS Objects (colored squares)

- left drag down and right to create a selection box
- right click empty space to set the rally point and make the selected object move to it
- right click an object to make the selected object follow it
- right drag to have the selected object follow the cursor

### Draggable Objects
- left click and drag an object to move it around

## Keyboard
### Global
- hold down or right arrow key to select next item in menu
- hold up or left arrow key to select previous item in menu
- press "enter" or "return" key to choose selected item in menu

### In-Game
- press 'i' to toggle information overlay
- press 'esc' to pause game
- press "delete" to delete selected object
- press "insert" to create object of previous selection

### Physics Objects (gray squares)
- hold 'W','A','S','D' to move up,left,down,right, respectively
- hold 'Q' and 'E' to rotate

# Known Bugs
## Global
- The "insert" key doesn't work on Macs.
- When navigating menus with the arrow keys, the selector sometimes gets stuck.
- Some objects appear to twitch when moving.

## Drag-enabled Objects
- While dragging, an object may get stuck on top of another object when they collide.

## Physics Objects
- Some of the object's physics values do not zero out when object is at rest.

# Disclaimer
 This program uses the OpenGL Utility Toolkit(A.K.A."GLUT") created by Mark Kilgard.
Thanks to his work, creating cross-platform OpenGL applications is much easier.
Since GLUT is not open source, I have not touched any of the source files.
Instead, I have linked the library to the executable and included glut32.dll in the project directory.
For more information on GLUT, visit https://www.opengl.org/resources/libraries/glut/
