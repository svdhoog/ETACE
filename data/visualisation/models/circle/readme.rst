Test data
=========

Files:

circle_model_

.. _circle_model: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle

Dataset_1_

.. _Dataset_1: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_1_agents_2/h5_agentwise

Dataset_2_

.. _Dataset_2: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_2_agents_6/h5_agentwise


Purpose
=======

To test the proper functionality of the library, this model creates test data.

The output plots should be clear in both time series x(t) and scatter plots ``(x(t),y(t))`` dimensions.

To this end, the data is very simple and predictable, and not random.

Setup
=====

This model produces test data with the following specifications:

- Scatter plots in ``(x,y)``-space show circles with a radius equal to the set number.
- The centre point of the circle is at ``(a,b)``.
- The x-axis horizontal shift ``a`` is equal to the agent ID.
- The y-axis vertical shift ``b`` is equal to the set number.

The parametric equations for a circle with centre point ``(a,b)`` and radius ``r`` are given by:

	x(s) = a + r*cos(s)

	y(s) = b + r*sin(s), with s in [0,2*PI]

For the time index ``s`` we use a transformation of the iteration counter ``t``, such that ``s`` remains in the interval ``[0,2 \PI]``:
 
	s = (t.dx)mod(2*PI)
	dx = 1e-2

We let iterations ``t = 1...628`` such that ``100t=6.28`` which equals ``2 \PI``, approximately.

Code
====

The C code for this model is:

	A = ID;

	X = A + CONST_RADIUS*cos(s);

	B = CONST_B;

	Y = B + CONST_RADIUS*sin(s);

with

	CONST_RADIUS = set_no

	CONST_B = set_no

Output Data Sets
=========

**Data set 1:**

	Sets: 2

	Runs: 1
	
	Agents: 2


| set | run | agent | radius | centre point (a,b) |
| --- | --- | --- | --- | --- |
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
=========

