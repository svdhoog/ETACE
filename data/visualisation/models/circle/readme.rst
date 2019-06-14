Test data: Circles model
=======

Purpose
-------

To test the proper functionality of the library, this model creates test data that is both simple to understand, and predictable.

The output plots should be clear in both the time series ``x(t)`` and scatter plot ``(x(t),y(t))`` dimensions.


Files:

circle_model_

.. _circle_model: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle

Dataset_1_

.. _Dataset_1: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_1_agents_2/h5_agentwise

Dataset_2_

.. _Dataset_2: https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/dataset_2_agents_6/h5_agentwise


Setup
-------

This model produces test data with the following specifications:

- Scatter plots in ``(x,y)``-space showing circles with a radius equal to the set number.
- The centre point of the circle is at ``(a,b)``.
- The x-axis horizontal shift ``a`` is equal to the agent ID.
- The y-axis vertical shift ``b`` is equal to the set number.

The parametric equations for a circle with centre point ``(a,b)`` and radius ``r`` are given by:

	x(s) = a + r*cos(s)

	y(s) = b + r*sin(s), with s in [0,2*PI]

For the time index ``s`` we use a transformation of the iteration counter ``t``, such that ``s`` remains in the interval ``[0,2 PI]``:
 
	s = (t.dx)mod(2*PI)

	dx = 1e-2

We let iterations ``t = 1...628`` such that ``100t=6.28`` which equals ``2 \PI``, approximately.

Code
-------

The C code for this model is:

	A = ID;

	X = A + CONST_RADIUS*cos(s);

	B = CONST_B;

	Y = B + CONST_RADIUS*sin(s);

with

	CONST_RADIUS = set_no

	CONST_B = run_no

Output Data Sets
-------

**Data set 1:**

	Sets: 2

	Runs: 1
	
	Agents: 2

**Data set 2:**

	Sets: 4

	Runs: 2
	
	Agents: 6

Example plots
-------

**Scatter plots**

p60_scatter_mean_agent_Agent_x_y.png:

.. image:: ./dataset_2_agents_6/Plots/scatterplot/p60_scatter_mean_agent_Agent_x_y.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

p61_scatter_mean_multi_run_Agent_x_y.png:

.. image:: ./dataset_2_agents_6/Plots/scatterplot/p61_scatter_mean_multi_run_Agent_x_y.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

p62_scatter_mean_multi_batch_Agent_x_y.png:

.. image:: ./dataset_2_agents_6/Plots/scatterplot/p62_scatter_mean_multi_batch_Agent_x_y.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

**Time series**

p12_ts_quantile_multi_batch_x.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p12_ts_quantile_multi_batch_x.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

p12_ts_quantile_multi_batch_y.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p12_ts_quantile_multi_batch_y.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

p20_ts_mean_agent_x.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p20_ts_mean_agent_x.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right

p24_ts_mean_agent_many_x_run_0_1.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p24_ts_mean_agent_many_x_run_0_1.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right


p25_ts_mean_multi_run_many_x_0.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p25_ts_mean_multi_run_many_x_0.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right


p26_ts_mean_multi_batch_many_x_0.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p26_ts_mean_multi_batch_many_x_0.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right


p27_ts_mean_multi_set_many_x_0.png:

.. image:: ./dataset_2_agents_6/Plots/timeseries/p27_ts_mean_multi_set_many_x_0.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: 
   :align: right
