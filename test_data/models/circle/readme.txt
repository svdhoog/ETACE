Test data:
/models/basic_agent_circle

Purpose: This model creates test data for visualization library FLAViz.
To this end, the data is very simple and predictable, and not random.
To test the library properly, it should be clear in both time series x(t) and scatter plots (x(t),y(t))

Settings:

Time series create a circle with its centre at x,y-coordinates: (a,b) and radius r.

In parametric equation form:

x(s) = a + r*cos(s)
y(s) = b + r*sin(s), s in [0,2*PI]

with
 
s = (t.dx)mod(2*PI)
dx = 1e-2
t = 1...628+ (such that the interval [0,2*PI] is traversed at least once.)

CODE
----
	A = ID;

	X = A + CONST_RADIUS*cos(s);

	B = CONST_B;

	Y = B + CONST_RADIUS*sin(s);
with

CONST_RADIUS = set_no
CONST_B = set_no

This produces:
--------------

- (x,y) scatter plots: circles with radius equal to set_no
- centre point of the circle is at (a,b)
- Agent ID yields a
- Set no. yields b

