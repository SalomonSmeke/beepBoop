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

####Input Handling

There are two main challenges with input handling and one extension that I can think of. The data we get from a potentiometer is unstructured and raw. It does not account for inaccuracies in current and therefore measurement, inaccuracies in the potentiometer and innacuracies in the user.

The first two can be somewhat addressed with a dead zone. adding a straight percentage dead zone, however, creates a strange square dead zone, not round. This is very easy to implement, but creates a bias against diagonals.

With this in mind, it is not necessary to check if a vertical direction was a "part" of a diagonal. Since diagonals wont occur unless severely sought, direct comparisons ( == ) are preferred to includes ( & ) for single direction queries.

Additionally, we can introduce buffered inputs.

So far, an input request can be:

Direct - Not Recommended.
Dead-zoned - Better.
Buffered - Preferred.

As such, lets not implement a facade for direct information, just Dead-zoned and Buffered. Thankfully this is basically what is implemented now:

BufferedInput <- Buffer
ReadDir <- Direction

However, it would be helpful to have a third helper we can provide with "directions we are looking for". these would ideally be ==.

Furthermore, once an input has been selected once, the Buffer is less necessary.

UserInput <- facade. (byte[] matches, sensitivity)

Our previous scheme was: 00[UNUSED]00[UNUSED]00[X]00[Y]

lets use the unused bits for intensity in V2. The scheme will work for now.

####Modules

Modules cannot be added to a list and run, C is not functional. However, Modules CAN be a one line add.

ModuleLoader ->
Loads modules.
lets make a screen for each module. some visual element that makes it obvious.
Modules Interface ->
menu screen. Animated? (V2, maybe)
loop.
creepage color.

#####Loading Modules

Selection creepage.

#####Module Structure

Loop()
SentinelCheck()

Example multi level module:

Module A Loop {
	Module B Loop {
		Sentinel() <- Block button until un ticked.
	}
	Sentinel()
}

#####Dead Man switch

Arduino feature we should use because im bad at memory allocation.
We can also use it to reset if no input is ever detected.
