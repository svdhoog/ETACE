.. _tutorial:

Possible Uses
=============

The module can be used to filter, transform, and visualize time series data, in multiple hierarchial levels.

The different kinds of plots that are possible are: time series, box plot, scatter plot, histogram, and delay plot.

Structure
=========

There are several scripts, located in folder ``/src`` that deal with different steps during the data visualisation/transformation processes:

- ``main.py`` : Contains code to read in the input data and primary parameter files, filter the data based on necessary conditions, and link the different Summary, Plot, and Transformation modules.
- ``summarystats.py`` : Takes in a Pandas dataframe, and computes the necessary summary as needed, and outputs the result as a Pandas dataframe.
- ``plots.py``: Takes in a Pandas dataframe, and returns the necessary plots as specified.
- ``transform.py`` : Takes in a Pandas dataframe, and returns/ writes to a file the necessary transformations.

The parameter files are contained in the folder named ``/config``. It contains three configuration files:

- ``main.yaml`` : define i/o path, plot-types, agents and appropriate variables, filter options, desired summary
- ``plot.yaml`` : define plot properties i.e. name, legends, line style, fill etc.
- ``transform.yaml``: define variables to transform, type of data transformations, i/o info to store data in a file after transformations


Note: Further details on how to use the parameter (yaml) files can be found on the ``/parameters.rst`` file of the documentation.

Testing
=======

To run the module, simply use:

   $ python main.py parameter-path

where, parameter path is the path to the folder containing the yaml files

Note: The module has only been tested under Unix/ Unix-like systems. It has not been tested for Windows and therefore 
there is no guarentee of proper execution for such systems.

Examples
========

Once the necessary parameters are set, by following the instructions specified in *parameters.rst* file, the module can be run to get the desired results. To demonstrate some of the functionalities, 
the parameters of the configuration files are shown below, along with the plots they yield.


Using the dataset <insert dataset url>, and the following parameter settings, the following plots can be produced.

**Example 1** (*For agent Firm, one set, ten runs, eighty instances, plotted in a single plot* ):

main.yaml::

    plot1:
        timeseries:
            agent: Firm
            analysis: multiple_run
            variables:
                var1: [price]
            set: [13]
            run: [range,[1,10]]
            major: [range,[6020,12500,20]]
            minor: [range,[1,80]] 
            summary: mean

plot.yaml::

    plot1:
        number_plots: one
        plot_name: one_set_multiple_runs_timeseries.png
        plot_legend: yes
        legend_location: best
        xaxis_label: Time
        yaxis_label: price
        linestyle: solid
        marker: None


.. image:: ./plots/one_set_multiple_runs_timeseries_price.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right


**Example 2** (*For agent Firm, one set, one run, quantile values of of distribution over eighty instances, plotted in a single plot* ):

main.yaml::

    plot2:
        timeseries:
            agent: Firm
            analysis: multiple_run
            variables:
                var1: [price]
            set: [10]
            run: [1]
            major: [range,[6020,12500,20]]
            minor: [range,[1,80]] 
            summary: custom_quantile
            quantile_values:          
               lower_quantile : 0.20
               upper_quantile : 0.80

plot.yaml::

    plot2:
        number_plots: one
        plot_name: one_set_multiple_runs_ts_quantile.png
        plot_legend: yes
        legend_location: best
        xaxis_label: Time
        yaxis_label: price
        linestyle: solid
        marker: None
        fill_between_quartiles: yes
        fillcolor: red


.. image:: ./plots/one_set_multiple_runs_ts_quantile_0.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right


**Example 3** (*For agent Firm, four sets, twenty runs each, eighty instances, plotted in a single plot* ):

main.yaml::

    plot3:
        timeseries:
            agent: Firm
            analysis: multiple_batch
            variables:
                var1: [output]
            set: [10,13,16,17]
            run: [range,[1,20]]
            major: [range,[6020,12500,20]]
            minor: [range,[1,80]] 
            summary: mean

plot.yaml::

    plot3:
        number_plots: one
        plot_name: timeseries_agentanalysis.png
        plot_legend: yes
        legend_location: best
        x-axis label: Time
        y-axis label: output
        linestyle: dashed
        marker: None


.. image:: ./images/P3_ts_output.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right
   

**Example 4** (*For agent Firm, four sets, twenty runs each, eighty instances, plotted in a single plot* ):

main.yaml::

    plot4:
        timeseries:
            agent: Firm
            analysis: multiple_batch
            variables:
                var1: [price]
            set: [10,13,16,17]
            run: [range,[1,20]]
            major: [range,[6020,12500,20]]
            minor: [range,[1,80]] 
            summary: mean

plot.yaml::

    plot3:
        number_plots: one
        plot_name: timeseries_agentanalysis.png
        plot_legend: yes
        legend_location: best
        x-axis label: Time
        y-axis label: price
        linestyle: dashed
        marker: None


.. image:: ./images/P4_ts_price.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right



**Example 5** (*For agent Eurostat, four sets, twenty runs each, one instance each, plotted in a single plot* ):

main.yaml::

    plot5:
        timeseries:
            agent: Eurostat
            analysis: multiple_batch
            variables:
                var1: [unemployment_rate]
            set: [10,13,16,17]
            run: [range,[1,20]]
            major: [range,[6020,12500,20]]
            minor: [0] 
            summary: mean

plot.yaml::

    plot5:
        number_plots: one
        plot_name: timeseries_multibatchanalysis.png
        plot_legend: no
        x-axis label: Time
        y-axis label: unemployment_rate
        linestyle: solid
        marker: None


.. image:: ./images/P5_ts_unemployment_rate.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right



**Example 6** (*For agent Eurostat, four sets, twenty runs each, one instance each, plotted in a single plot* ):

main.yaml::

    plot6:
        timeseries:
            agent: Eurostat
            analysis: multiple_batch
            variables:
                var1: [monthly_output]
            set: [10,13,16,17]
            run: [range,[1,20]]
            major: [range,[6020,12500,20]]
            minor: [0] 
            summary: mean

plot.yaml::

    plot6:
        number_plots: one
        plot_name: timeseries_multibatchanalysis.png
        plot_legend: no
        x-axis label: Time
        y-axis label: monthly_output
        linestyle: solid
        marker: None


.. image:: ./images/P6_ts_monthly_output.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right


**Example 7** (*For agent Firm, four sets, twenty runs each, eighty instances, quantile values plotted in a single plot* ):

main.yaml::

    plot7:
        timeseries:
            agent: Firm
            analysis: multiple_batch
            variables:
                var1: [price]
            set: [10,13,16,17]
            run: [range,[1,20]]
            major: [range,[6020,12500,20]]
            minor: [range,[1,80]] 
            summary: custom_quantile
            quantile_values:          
                lower_quantile : 0.20
                upper_quantile : 0.80


plot.yaml::

    plot7:
        number_plots: one
        plot_name: ts_multibatch_analysis.png
        plot_legend: yes
        legend_location: best
        x-axis label: Time
        y-axis label: price
        linestyle: solid
        marker: None
        fill_between_quartiles: yes


.. image:: ./images/P7_ts_price.png
   :height: 100px
   :width: 200 px
   :scale: 50 %
   :alt: alternate text
   :align: right
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
