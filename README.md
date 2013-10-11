Music Box (work in progress)
============================

Animation of a music box. Made by [Anirudh Vemula](vvanirudh@gmail.com) and [Rohan Prinja](rohan.prinja@gmail.com) for the second assignment of our [Computer Graphics](http://www.cse.iitb.ac.in/~paragc/teaching/2013/cs475) course. The exact problem statement can be found in the `problem-statement.pdf` file in the root directory of this repo.

Directories
-----------

1. `src` source code
2. `bin` (created after compilation, deleted on cleanup) - `musicbox`, the final program
3. `obj` (created after compilation, deleted on cleanup) - `.o` files
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

Quick Walkthrough
-----------------

Keybindings:

1. Exit the program: `Esc`
2. Toggle which object to move: `t` (when you start the program, the dancer is selected)
3. Toggle which side to move: `l` (when you start the program, the left side is selected)
4. Select joint: `0` to `9`
5. Rotate about x-axis: `w` and `s`
6. Rotate about x-axis: `a` and `d`
7. Rotate about x-axis: `q` and `e`
8. Rotate the entire dancer: `,` and `.`

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