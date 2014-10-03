2DWorld
=======
by James Nakano AKA confuzedskull

Troubleshooting:
<Windows>
If the program doesn't run, then you must right click it and select "Run as Administrator"

<Mac>
If the message ""2dworld" was blocked from opening because it is not from an identified developer" do this:
1. Go to System Preferences and click on Security & Privacy
2. Somewhere near the bottom you'll see a message and then a button "Open Anyway". Click it.
3. A prompt will come up saying ""2dworld is a Unix applicaiton downloaded from the internet. Are you sure you want to open it?" Click open.

<Linux>
If you're using Linux, you can probably figure out how to get it running on your own.

Controls:
<Mouse>
-left click object to select
-left drag box around objects to select multiples
-left click empty space to deselect
-left click and drag an object to move it around
-right click empty space to set rally point and make selected object move to it
-right click an object to make selected object follow it
-right drag to have selected object follow cursor
<Keyboard>
-W,A,S,D to move up,left,down,right
-Q and E to rotate
-spacebar to shoot
-i for information overlay
-esc to quit

Known Bugs:
-sometimes objects stop shooting for no reason
-information overlay sometimes crashes
-an object's resting point gets set even when it's moving
-some of the object's physics values do not zero out when object is at rest
-information overlay displays information of wrong object
-having the information overlay up after clicking an object sometimes makes the program crash

Disclaimer:
This program was made using the OpenGL Utility Toolkit(GLUT) created by Mark Kilgard.
I do not own the rights to this API nor do I claim them as my own.
