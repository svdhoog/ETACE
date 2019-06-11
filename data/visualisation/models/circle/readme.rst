Test data
=========

Files: .. _circle_model: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle

.. _Dataset_1: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_1_agents_2/h5_agentwise

.. _Dataset_2: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_2_agents_6/h5_agentwise


Purpose
--
This model creates test data for the visualization library FLAViz.
To this end, the data is very simple and predictable, and not random.
To test the library properly, it should be clear in both time series x(t) and scatter plots (x(t),y(t))

Settings
--
Time series create a circle with its centre at x,y-coordinates: (a,b) and radius r.

In parametric equation form:

x(s) = a + r*cos(s)
y(s) = b + r*sin(s), s in [0,2*PI]

with
 
s = (t.dx)mod(2*PI)
dx = 1e-2
t = 1...628+ (such that the interval [0,2*PI] is traversed at least once.)

Code
--

The FLAME C code for this model:

	A = ID;

	X = A + CONST_RADIUS*cos(s);

	B = CONST_B;

	Y = B + CONST_RADIUS*sin(s);

with

CONST_RADIUS = set_no
CONST_B = set_no

Output
--------------
This model test data produces the following:

- (x,y) scatter plots: circles with radius equal to set_no
- centre point of the circle is at (a,b)
- Agent ID yields a
- Set no. yields b

Data sets
--
Data set 1:

	Sets: 2
	Runs: 1
	Agents: 2


|set|run|agent|radius|centre point (a,b)|
|---|---|---|---|---|
| 1 | 1 | 1 | 1 | (1,1) |
|   |   | 2 | 1 | (2,1) |
| 2 | 1 | 1 | 2 | (1,2) |
|   |   | 2 | 2 | (2,2) |


**Data set 2:**

	Sets: 4
	Runs: 2
	Agents: 6

|set|run|agent|radius|centre point (a,b)|
|---|---|---|---|---|
| 1 | 1 | 1 | 1 | (1,1) |
|   |   | 2 | 1 | (2,1) |
|   |   | 3 | 1 | (3,1) |
|   |   | 4 | 1 | (4,1) |
|   |   | 5 | 1 | (5,1) |
|   |   | 6 | 1 | (6,1) |
| 2 | 1 | 1 | 2 | (1,2) |
|   |   | 2 | 2 | (2,2) |
|   |   | 3 | 2 | (3,2) |
|   |   | 4 | 2 | (4,2) |
|   |   | 5 | 2 | (5,2) |
|   |   | 6 | 2 | (6,2) |
| 3 | 1 | 1 | 3 | (1,3) |
|   |   | ... | ... |... |
| 4 | 1 | 1 | 4 | (1,4) |
|   |   | ... | ... |... |
| 5 | 1 | 1 | 5 | (1,5) |
|   |   | ... | ... |... |
| 6 | 1 | 1 | 6 | (1,6) |
|   |   | ... | ... |... |


Example plots
--