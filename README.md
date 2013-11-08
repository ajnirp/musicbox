Music Box (work in progress)
============================

Animation of a music box. Made by [Anirudh Vemula](vvanirudh@gmail.com) and [Rohan Prinja](rohan.prinja@gmail.com) for the second assignment of our [Computer Graphics](http://www.cse.iitb.ac.in/~paragc/teaching/2013/cs475) course. The exact problem statement can be found in the `problem-statement.pdf` file in the root directory of this repo.

Directories
-----------

1. `src` source code
2. `bin` (created after compilation, gets deleted when you run `make clean`) - `musicbox`, the final program
3. `obj` (created after compilation, gets deleted when you run `make clean`) - `.o` files
4. `tex` textures

Link to Report for Part 1
-------------------------

The report can be found [here](http://www.cse.iitb.ac.in/~rohanp/musicbox.html). It contains screenshots of our code in action, and a diagram of the hierarchical model we used to make the dancing doll.

Link to Report for Part 2
-------------------------

The report can be found [here](http://www.cse.iitb.ac.in/~rohanp/musicbox2.html)

Link to Report for Part 3
-------------------------

The report can be found [here](http://www.cse.iitb.ac.in/~rohanp/musicbox3.html).
The YouTube video of our animation is [here](http://www.youtube.com/watch?v=AV051Oyuoa0)

Installation
------------

OpenGL and `g++` are required. We used g++ v4.7.3. Once you have those two:

1. Download this repo
2. Unzip
3. `cd musicbox`

Running
-------

1. `make`
2. `./bin/musicbox`

Cleaning Up
-----------

1. `make clean`

Clearing out the Keyframes File
-------------------------------

1. `make clear`

Keybindings/Mouse actions
-------------------------

These keybindings apply to parts 1 and 2 of the assignment.

1. Exit the program: `Esc`
2. Get help on keybindings: `F1`
3. Toggle which object to move: `t` (when you start the program, the dancer is selected)
4. Toggle which side to move: `r` (when you start the program, the left side is selected)
5. Select joint: `0` to `9`
6. Rotate about x-axis: `w` and `s`
7. Rotate about x-axis: `a` and `d`
8. Rotate about x-axis: `q` and `e`
9. Rotate the entire dancer about the y-axis: `,` and `.`
10. Display information: `i`
11. Switch on/switch off the lamp: `k`
12. Switch on/switch off the wall light: `l`
13. Reset everything: `F5`
14. Enter the room: `Enter`
15. Move the control point selection plane along the z-axis: `↑` and `↓`
16. Select a point to use as a control point: mouse click
17. Start the animation: `Space`
18. Delete the last created control points: right mouse click

These keybindings apply to part 3 of the assignment

1. Exit the program: `Esc`
2. Get help on keybindings: `F1`
3. Open and close the box lid: `z` and `x`
4. Move the dancer up and down: `c` and `v`
5. Select joint: `0` to `9`
6. Rotate about x-axis: `w` and `s`
7. Rotate about x-axis: `a` and `d`
8. Rotate about x-axis: `q` and `e`
9. Save a keyframe: `F3`
10. Clear the keyframes file: `F11`

Walkthrough
-----------

For part 1
----------

This section applies to part 1 of the assignment. Please skip ahead to "For part 2" for a description of how the program behaves and what to do when the program starts.

When you run the program using `./bin/musicbox` you should see a wooden box and a wooden doll standing next to each other. You can move the box lid and various parts of the doll by pressing the keys `w`, `s`, `a`, `d`, `q` and `e`. The first two are for rotating about the x-axis, the next two are for rotating about the y-axis, and the last two are for rotating about the z-axis.

First, you need to select the object that you want to move. By default the dancer is selected. To toggle between objects press `t`. So if you start the program and press `t` the box will be selected.

When the box is selected, use `w` and `s` to open and close the lid, respectively.

When the dancer is selected, you need to select which of the joints to move. For a list of which joints are movable and with how many degrees of freedom, refer to page 2 of the `problem-statement.pdf` file in the root of this project repo. The joint mappings are as follows:

| Key | Joint |
| --- |:-----:|
| `0` | head-neck |
| `1` | shoulder |
| `2` | neck-torso1 |
| `3` | torso1-torso2 |
| `4` | torso2-torso3 |
| `5` | hip |
| `6` | ankle |
| `7` | wrist |
| `8` | knee |
| `9` | elbow |

Pressing any number key from `0` to `9` will select that joint. By default, the selected joint is the head-neck joint.

Once you've selected a joint, you have to select a side to move (in case the joint is for a body part for which there are two parts. For example, the dancer has two knees. To toggle the side that you want to move, press `r`. By default, the selected side is the left side. So if you run the program and then press `8`, and press `w`, the *left* knee will bend backward.

Once you've selected a joint and a side, the keybindings are simple. Use `w` and `s` to rotate about the x-axis. For the y-axis, `a` and `d`. For the z-axis, `q` and `e`. Note that each joint is restricted to a certain range of movement so that the whole doll looks realistic. Also note that pressing `a`, `d`, `q` or `e` will have no effect if you have selected a joint that has only 1 degree of freedom, like the doll's knees or its elbows.

To rotate the entire dancer about the y-axis, use `,` and `.`. As you'd expect, these keys do nothing if the dancer is not selected.

For part 2
----------

In part 2, the dancer has been placed inside the box, which in turn has been placed in a room with some furniture and two lights.

When you start the program, you will see the front wall of the room, and a door. To open and close the door use `+` and `-`. When you're done, press `g` and you will now be inside the room. You can now see the room and the furniture inside it. In the far left, at the back of the room, you can see a table on which there is a box. This is the same box as in part 1 of the assignment. Inside the box (not visible yet) is a dancer, the same dancer as in part 1.

The room also contains a lamp and a wall light. The lamp is to the left of the room and the wall light is on the back wall of the room and to the right. To turn on the lamp, press `k`, and to turn on the wall light, press `l`. To move the selector plane, use the up and down arrow keys, and click on the selector plane when you want to select a bezier control point. A small blue sphere will appear where you clicked. This allows you to see which control points you have selected so far. If you mistakenly click somewhere you didn't want to, you can always delete the last clicked control point by right clicking.

If at any point you lose track of which object and which joint is selected or which light is turned on, simply press `F1` and the required information will be printed to the terminal. In any case, whenever you change the selected side or change the selected object a message will be logged to the terminal, so you can look at the terminal logs to see what transpired.

Once you've selected the control points, press `Space` and watch the animation. The camera will pan through the room along a Bezier curve that is formed from the control points you clicked on. Then the box will open and the dancer will rise up.

For part 3
----------

**Note** The code for part 3 is contained completely within the `navigate` branch of this repo. This means that the `master` branch contains the code for parts 2 and 1 together.

Compilation is as usual, but to execute you must now supply an option. If you don't, the program complains about a lack of arguments and quits.

+ `./bin/musicbox --help` prints help and exits.
+ `./bin/musicbox --record` opens the program in record mode. In this mode you can save keyframes by pressing `F3`
+ `./bin/musicbox --playblack` plays the animation with interpolation between the keyframes. To dump frames while the program is running, press `p`. Press `p` again to turn off dumping. Image dumping is an expensive operation, so doing so will slow the program noticeably. The end result is that a number of `.ppm` files will be written to the `frm` directory.

Standard workflow is to first open the program in record mode (with the `--record` flag), save a few keyframes by moving the dancer around, then close the program and reopen it in playback mode (with the `--playback` flag).

The `keyframes.txt` file contains the following space-separated values:

+ The `dancer_angles` vector which stores information about the dancer
+ The extent to which the box lid is open, namely `lid_angle`

Credits
-------

All of the code was written entirely by the two of us, except for the following parts:

1. `Makefile` is a modified version of the Makefile given to us in the Software Systems Lab course at IIT Bombay
2. The code for getting the 3D point from the mouse click is a modified version of the `GetOGLPos` function written [here](http://nehe.gamedev.net/article/using_gluunproject/16013/).
3. The code for checking whether a file is empty or not (that is, the `file_is_empty()` function in `src/file.cpp`) was taken from [here](http://www.cplusplus.com/forum/windows/10853/)
4. The frame capture code was supplied to us by our course instructor. It can be found [here]()
5. The music we used for our video was taken from [Open Game Art](http://opengameart.org/content/sage-of-corinth-music).
6. Swamp painting (not used) taken also from [Open Game Art](from http://opengameart.org/content/rhythos-modified-lpc-assets)

References
----------

1. http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
2. http://www.glprogramming.com/red/chapter09.html#name2
3. http://nehe.gamedev.net/article/using_gluunproject/16013/ (Unprojecting points)

License
-------

This code is licensed under the [WTFPL](http://www.wtfpl.net/about/), which means that you can take it and do whatever the fudge you wish to with it. Enjoy!