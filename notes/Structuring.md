##What now?

After the spaghetti code implementation now archived under v0, I have a more concrete idea of what I want to do. Lets talk (at least about the first iteration) of the interplay of software and hardware.

###Hardware.

The segmented displays I picked for this project were a mistake. 16 segments allow for nicer looking digits, but require a controller of their own. This is something I can add later on, but for now lets not talk about those.

Generally, the makeup is this:

8 * 8 display.
2 axis potentiometer.

The rest is hookup and enabling these two to function.

Arduino & misc carp.

Now all this is fine and good, and the spaghetti v0 focused only on performance assumes these constraints. Which leads to many many non-modular sections.

Adding this constraint makes things more interesting: N Displays. Such that n is a square integer.

Assuming the hardware can handle the neopixels (which, up to 4, it can without much change). Then the spagnetti code needs to take some generalized shape here.

###Software.

Initially, the software had one goal:
Create a 4-way gradient, where you can edit the origins.

This was a neat enough idea, but the implementation was trivial and the result is unappealing to play with. Lets make modules.

A module has an icon, defined in 8*8 pixels which is equivalent to a screen. You can return to module selection with another button, equivalent to a soft reset.

Examples of modules:
4 origin gradient, 2 origin gradient, 1 origin pallete, 1 origin shades, 2 origin shades, clock, etc.

Given that many of these modules are similar, the idea of submodules is not unappealing. In this case, we can implement the button as a "back" instead of a soft reset.

This is a single threaded application, so there are some intricacies with input. And this button creates some additional difficulties.

####Modules

Modules cannot be added to a list and run, C is not functional. However, Modules CAN be a one line add.

ModuleLoader -> 
Loads modules.
lets make a screen for each module. some visual element that makes it obvious.
Modules Interface ->
menu screen. Animated? (V2, maybe)
loop.