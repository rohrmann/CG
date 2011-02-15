Author: Till Rohrmann
Matric number: A0079376

Primitives and transformations:
Besides the standard primitives which were introduced in the class, I'm using textures for the planets,
convex triangles which I draw with my own written function and solid as well as non-solid circles.

What am I drawing?
I'm drawing a solar system with several planets. It is more like a physical simulation since the flight paths
of the planets are calculated out of the differential equation of the gravitational force. In fact, it is
a solution to the one-body problem. The differential equation x''= G*m/|x|^2 is solved by the means of 
the Runge Kutta method of the forth order. Besides that, I'm using textures of several planets of our
solar system. Furthermore, there are some bicycles cycling around some planets. And last but not least
there are some planets which have some moons. Since all the planets are rotating around the sun, they are
all affected by the sun light and the side which is not facing the sun is dark (=night) whereby the other
side is bright (=day). The animated stars in the background are being created randomly according to a uniform 
distribution and the glowing duration of a star is distributed exponentially. Moreover, the sun has a corona
which one can see if one zooms in. One can switch between the clock mode and the simulation mode by pressing
"T". 

Methods modified?
I didn't use any of the provided code and developed the application instead from scratch on my own.

Coolest thing?
The flight paths of the planets, which behave like Kepler's rules postulate, is the most interesting aspect
of my work. Moreover, the corona of the sun is cool which one can see if one zooms in.