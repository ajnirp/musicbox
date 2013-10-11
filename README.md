Music Box (work in progress)
============================

Animation of a music box. Made by [Anirudh Vemula](vvanirudh@gmail.com) and [Rohan Prinja](rohan.prinja@gmail.com) for the second assignment of our [Computer Graphics](http://www.cse.iitb.ac.in/~paragc/teaching/2013/cs475) course. The exact problem statement can be found in the `problem-statement.pdf` file in the root directory of this repo.

Directories
-----------

1. `src` source code
2. `bin` (created after compilation, gets deleted when you run `make clean`) - `musicbox`, the final program
3. `obj` (created after compilation, gets deleted when you run `make clean`) - `.o` files
4. `tex` textures

Link to Report
--------------

The report can be found [here](http://www.cse.iitb.ac.in/~rohanp/musicbox.html).

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

Keybindings
-----------

1. Exit the program: `Esc`
2. Toggle which object to move: `t` (when you start the program, the dancer is selected)
3. Toggle which side to move: `l` (when you start the program, the left side is selected)
4. Select joint: `0` to `9`
5. Rotate about x-axis: `w` and `s`
6. Rotate about x-axis: `a` and `d`
7. Rotate about x-axis: `q` and `e`
8. Rotate the entire dancer: `,` and `.`
9. Display information: `i`

Walkthrough
-----------

When you run the program using `./bin/musicbox` you should see a wooden box and a wooden doll standing next to each other. You can move the box lid and various parts of the doll by pressing the keys `w`, `s`, `a`, `d`, `q` and `e`. The first two are for rotating about the x-axis, the next two are for rotating about the y-axis, and the last two are for rotating about the z-axis.

First, you need to select the object that you want to move. By default the dancer is selected. To toggle between objects press `t`. So if you start the program and press `t` the box will be selected.

When the box is selected, use `w` and `s` to open and close the lid, respectively.

When the dancer is selected, you need to select which of the joints to move. For a list of which joints are movable and with how many degrees of freedom, refer to page 2 of the `problem-statement.pdf` file in the root of this project repo. The joint mappings are as follows:

Once you've selected a joint, the keybindings are simple. Use `w` and `s` to rotate about the x-axis. For the y-axis, `a` and `d`. For the z-axis, `q` and `e`. Note that each joint is restricted to a certain range of movement so that the whole doll looks realistic. Also note that pressing `a`, `d`, `q` or `e` will have no effect if you have selected a joint that has only 1 degree of freedom, like the doll's knees or its elbows.

If at any point you lose track of which object and which joint is selected, simply press `i` and the required information will be printed to the terminal.

Credits
-------

All of the code was written entirely by the two of us, except for the following parts:

1. `Makefile` is a modified version of the Makefile given to us in the Software Systems Lab course at IIT Bombay

References
----------

1. http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
2. http://www.glprogramming.com/red/chapter09.html#name2

Roadmap
-------

License
-------

This code is licensed under the [WTFPL](http://www.wtfpl.net/about/), which means that you can take it and do whatever the fudge you wish to with it. Enjoy!