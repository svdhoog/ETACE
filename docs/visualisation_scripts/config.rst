Configuration files
====

There are three configuration files, through which the necessary conditions can be input. The configuration files have a
hierarchial format, not just for clarity but also for functionality. Hence, it is very important to abide by the
indentation for the input to be interpreted correctly.

*Note:* Any error in the yaml file might be caught by the exception handler, but indentation errors go unnoticed
sometimes, therefore resulting in undesired output. Hence, extra care is advised when formulating a configuration file.

config.yaml
~~~~~~~~~

``i/o``: Specify the name of the repository root folder ``repo_name`` and input, output path in the subhierarchies ``input_path`` and ``output_path``. You can choose between an absolute path (/path/to/your/files) which always starts with a '/' or a relative path (path/relative/to/project/folder). It is necessary to set the name of the repository root folder to make use of relative paths.

::

  i/o:
    # set up the name of the root folder from repository
    repo_name: 'FLAViz'

    # for absolute input paths use:
    input_path: '/path/to/FLAViz/data'

    # for relative input paths use:
    input_path: 'data/visualisation'


    # for absolute output paths use:
    output_path: '/path/to/FLAViz/results'

    # for relative output paths use:
    output_path: 'results'

    input_files:
        CentralBank: CentralBank.h5
        Eurostat: Eurostat.h5
        Firm: Firm.h5

*Note:* The key name to the input files should correspond to the Agent-type (i.e. Bank, Eurostat, Firm etc.)

**Plot-key (i.e.** ``plot1`` **) :** Specify a key for the plot (mainly to keep track of the plot-number for other configuration files). Can be any string.


**Plot-type (i.e.** ``timeseries`` **) :** Nested under **Plot-key (** ``plot1`` **)**, "Plot-type" specifies the type of plot desired. *Possible types:* ``timeseries``, ``boxplot``, ``histogram``, ``scatterplot``


*Note [Exception]*: For the case of transform, simply specify ``transform`` in the Plot-type, and it will perform the transform (no plots will be produced).


* ``agent``: Name of the agent-type, nested under **Plot-type**.

* ``analysis``: Type of analysis. *Possible types:*  ``agent``, ``multiple_run``, ``multiple_batch``, ``multiple_set``.

The type of analysis determines how the data set is being grouped using the ``groupby`` function:

``agent``: ``data.groupby(level=['set', 'run', 'major', 'minor'])``, the full data set

``multiple_run``: ``data.groupby(level=['set', 'run', 'major'])``, sets, runs, and iterations

``multiple_batch``: ``data.groupby(level=['set', 'major'])``, sets and iterations

``multiple_set``: ``data.groupby(level=['major'])``, only iterations

As an example, the relevant code for taking the mean is (see ``summarystats.py``):

        agent_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major', 'minor']).mean()

        multiple_run_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major']).mean()

        multiple_batch_analysis = lambda: self.__data.groupby(level=['set', 'major']).mean()

        multiple_set_analysis = lambda: self.__data.groupby(level=['major']).mean()

*NOTE:* the major axis are the iterations, the minor axis are the agent instances.


* ``variables``: Variables from the particular agent-type that is to be processed/ visualized. The sub-hierarchy ``var1``, ``var2`` etc. allows the input of multiple variables for any agent type. The variable names can be inside a set of square braces *[]* or simply inside a set of single-quotation marks *''*. Example 2 shows that it is also allowed to pass a list of variable names inside the entry ``var1``.


Example 1::

    plot1:
        timeseries:
            agent: Bank
            analysis: multiple_set
            variables:
              var1: [total_credit]
              var2: [equity]

Example 2::

    plot1:
        timeseries:
            agent: Bank
            analysis: multiple_set
            variables:
              var1: [total_credit,equity]


Example (*only for Transform*)::

    plot1:
        transform:
            agent: Bank
            analysis: multiple_set
            variables:
              var1: [total_credit]
              var2: [equity]



``conditional_filtering`` : There is an option of filtering the variables that meet certain criteria i.e.
get only those values of the variables that satisfy a certain upper/lower limit or fall within a certain range.

For conditional filtering, specify the variables as above, but with the filter conditions in place. *Possible operator types:* ``<``, ``>``, ``<=``, ``>=``, ``==``.

Example::

    var1: [variable name, 'operator[value]']
    e.g.
    var1: [total_credit, '>[700]']  # selects those values of total credit variable that are greater than 700


    var2: [variable name, 'operator1[value]','operator2[value]']
    e.g.
    var2: [equity, '>[700]', '<[1500]'] # selects those values of total credit variable that are between 700 and 1500


Usage Example::

    plot1:
        timeseries:
            agent: Bank
            analysis: multiple_set
            variables:
                  var1: [total_credit, '>[700]']
                  var2: [equity, '>[700]', '<[800]']




Similarly, for desired **sets**, **runs**, **major** and **minor** axes, filter conditions can be specified as necessary.

``set`` : Specify the set numbers to be processed. Input can be a list ( *Case I* ), or ( *esp. for long lists*) a custom way
to specify the range of values ( *Case II* ).

Example::

    Case I:
    set: [val(1),val(2),...,val(N)]
    e.g.
    set: [1,2]  # list with values 1 and 2

    Case II:
    set: [range,[val(1),val(N),step-size]]
    e.g.
    set: [range, [1,10,2]]  # list with values from 1 to 10 with a step-size of 2


``run`` : Specify the runs to process. Syntax similar to ``set`` above.

``major`` : Specify the values from the major axis (time periods) to process. Syntax similar to ``set`` above.

``minor`` : Specify the values from the minor axis (agent instances) to process. Syntax similar to ``set`` above.

*Note:* The ``set``, ``run``, ``major``, and ``minor`` values are nested under "Plot-type"

Example::

    plot1:
        timeseries:
            agent: Bank
            analysis: multiple_set
            variables:
                  var1: [total_credit]
                  var2: [equity]
            set: [1]
            run: [1,2]
            major: [range,[6020,26000,20]]
            minor: [1,5,7]

``summary``: Specify the type of statistical summary. This is also nested under Plot-type.

**Possible values**

* ``mean``: returns the mean

* ``median``: returns the median

* ``custom_quantile``: this allows to select an upper and a lower quantile, see below.

* ``third_quartile``: returns the 75th percentile of the data set

* ``first_quartile``: returns the 25th percentile of the data set

* ``maximum``: returns maximum value of the data set

* ``minimum``: returns minimum value of the data set

* ``full``: returns the full data set as an ensemble distribution.


.. * ``no``, ``none``: any non-existent keyword can be used if no summary of the data set is needed; these will be ignored by the code.

Example::

    plot1:
        timeseries:
            summary: mean

For the value ``custom_quantile`` the lower and upper quantiles should be specified as floats in [0,1].

Example::

    plot2:
        timeseries:
            summary: custom_quantile
            quantile_values:
               lower_percentile : 0.20
               upper_percentile : 0.80

A typical main configuration file may look as follows::

    i/o:
        # set up the name of the root folder from repository
        repo_name: 'FLAViz'

        # set up your input_path for the resulting plots, it's relative unless it starts with a '/'
        input_path: 'data/visualisation'

        # set up your output_path for the resulting plots, it's relative unless it starts with a '/'
        output_path: 'results'

        input_files:
            CentralBank: CentralBank.h5 # please name the key as the agent name
            Eurostat: Eurostat.h5
            Firm: Firm.h5

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
               lower_percentile : 0.20
               upper_percentile : 0.80

plot_config.yaml
~~~~~~~~~

The *plot_config.yaml* file contains all the necessary configuration options for a plot. Whenever a plot is specified on the *config.yaml* file, the *plot_config.yaml* file is read for the necessary specifications of the plot. As such, some of the parameters from the *plot_config.yaml* file is explained below.
All options can also be found on the matplotlib website
https://matplotlib.org/api/_as_gen/matplotlib.pyplot.plot.html

**Plot-key( i.e.** ``plot1`` **):** This string should be the same as the Plot-key in the *config.yaml* file, to make sure
the correct parameters are mapped to the respective plot.

``number_plots``: Specifies how many plots will be output per variable for a particular agent type.
*Possible values:* ``one``, ``many``.

``plot_format``: Specify filetype for the plot [png|pdf].

``plot_name``: Specify a filename manually. If you leave it out the filename will be autogenerated (plot_name='Agent_Variable')

*Note:* In case of multiple plots, a numerical suffix (*in increasing order*) is added after the specified file name.

``plot_legend``: Specify legend for the plot.

``legend_loc``: Specify location of the legend, either inside the box or outside of it. *Possible values:* ``in``, ``out``.

``legend_label``: Specify name for the lines in the plot. Can be any string value.

``xaxis_label``: Specify label for the x-axis. Can be any combination of string values.

``yaxis_label``: Specify label for the y-axis. Can be any combination of string values.

``linestyle``: Specify line characteristic. *Possible values:* ``solid``, ``dashed``, ``dashdot``, ``dotted`` etc.

``greyscale``: Specify to plot in greyscale. *Possible values:* ``True``, ``False``.

A typical *plot_config.yaml* file might look like this::

    plot1:
        number_plots: one
        plot_name: p1_first_plot
        plot_format: png
        plot_legend: yes
        legend_location: best
        xaxis_label: Time
        yaxis_label: price
        linestyle: solid
        marker: None
        greyscale: True

    plot2:
        number_plots: one
        plot_format: pdf
        plot_legend: yes
        legend_location: best
        xaxis_label: Time
        yaxis_label: price
        linestyle: solid
        marker: None
        fill_between: yes
        fillcolor: red

If an option is not specified, then the default settings are::

    plot_legend = 'no'
    legend_label = None
    legend_location = 'best'
    plot_type = None
    number_plots = 'one'
    plot_name = None
    plot_format = 'png'
    l_lim = None
    u_lim = None
    linestyle = 'solid'
    marker = 4
    markerfacecolor = None
    markersize = None
    facecolors = None
    plot_title = None
    xaxis_label = None
    yaxis_label = None
    number_bins = 50
    histtype = 'bar'
    stacked = False
    normed = 1
    fill_between = False
    fillcolor = 'black'
    greyscale = False
    number_bars = 5




config_transform.yaml
~~~~~~~~~~~~~~

The *config_transform.yaml* file contains all the necessary configurations for any transformation specified on the *config.yaml* file. Whenever a transformation is specified on the *config.yaml* file, the *config_transform.yaml* file is read for the necessary
specifications of the plot.

As such, some of the parameters from the *config_transform.yaml* file is explained below:

**Plot-key( i.e.** ``plot1`` **):** This string should be the same as the Plot-key in the config.yaml file, to make sure
the correct parameters are mapped to the respective plot.

*Note:* Although it is called Plot-key, the transform case is an exception and no plots are produced in transform case.

``variables``: Variables from the particular agent-type that is to be transformed. The sub-hierarchy ``var1``, ``var2`` etc. allows
the input of multiple variables for any agent type.

``transform_function``: The transformation function to apply for the given variables to produce the necessary transforms.

*Possible functions:*

- Quarterly growth rate (quarter on quarter, at quarterly frequency) ``q_o_q_q``
- Quarterly growth rate (quarter on quarter, at annual frequency) ``q_o_q_a``
- Monthly growth rate (month on month, at monthly frequency) ``m_o_m_m``
- Monthly growth rate (month on month, at annual frequency) ``m_o_m_a``
- Annual growth (year on year, at annual frequency) ``y_o_y_a``
- Other custom functions

*Note:* Other elementary functions such as **sum**, **difference**, **product**, and **division** can also be performed, which will be added as custom functions in a future release.

``aggregate``: If the transformation is to be performed after calculating the summary stats, then a necessary aggregation method can be specified.

*Possible values:* ``mean``, ``median``, ``maximum``, ``minimum``, ``custom_quantile``, ``upper_quartile``, ``lower_quartile``.

``write_file``: Specify whether to write the transformation as a file. *Possible values:* ``yes``, ``no``.

``output_path``: If the ``write_file`` option above is set to ``yes``, then a output path for the file needs to be specified.
Can be any valid filepath, as a string, including upto the filename.

``hdf_groupname``: Specify the rootname for the HDF5 group name (internal hierarchy) for the transformed variable. Can be any valid string.

A particular *config_transform.yaml* file may, therefore, look as follows::

    plot2:
        variables:
            var1: total_credit
            var2: equity
        transform_function: q_o_q_q
        aggregate: mean
        new_variables:
            var1: total_credit_q_o_q_q
            var2: equity_q_o_q_q
        write_file: yes
        output_file_name: 'transformed.h5'
        hdf_groupname: 'quarterly_growth_rates'



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**References:**

 Matplotlib: https://matplotlib.org/

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
