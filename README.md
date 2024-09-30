This is a template for M1 Macs to run raylib with a basic window.

I created this after the bulk majority of sources on the internet
were terrible in getting raylib to compile on M1 Macs. 

While I should clean this project up because it is a mess, this
should easily run raylib on any M1/M2/M3/M(WhateverTheFuck) Mac

I have decided to publish this for the sake of making people's 
lives easier, as a working build of raylib just doesn't exist from
scratch.

In order to run this:
1. cd into the src folder in terminal.
2. regret your life decisions to use raylib over Godot/Unity/Unreal
3. run the command "make" (remove the quotes)
    this should compile all the files neccessary to run raylib. You
    can choose to go back to the original .c file and implement the
    standard template if you choose to. I'm not your mother, do
    what yout want.
4. run "./raylib_game"