There are three parameter files, through which the necessary conditions can be input. The parameter files have a 
hierarchial format, not just for clarity but also for functionality. Hence, it is very important to abide by the 
indentation for the input to be interpreted correctly. 

*Note:* Any error in the yaml file might be caught by the exception handler, but indentation errors go unnoticed
sometimes, therefore resulting in undesired output. Hence, extra care is advised when formulating a parameter file.

main.yaml
~~~~~~~~~

``i/o``: Specify the input and output path, in the subhierarchies ``input_path`` and ``output_path``::
  
  i/o:
    input_path: '/home/etace/Desktop/GitHub/HDFDataFiles'

    input_files: 
        CentralBank: CentralBank.h5
        Eurostat: Eurostat.h5
        Firm: Firm.h5
        
*Note:* The key name to the input files should correspond to the Agent-type (i.e. Bank, Eurostat, Firm etc.)

Similarly, the output path::

    output_path: '/home/etace/Spaces/ETACE-Conquaire Project/Data/data_reproduction_task/timeseries_classify_LS_output'
    
    
**Plot-key (i.e.** ``plot1`` **) :** Specify a key for the plot (mainly to keep track of the plot-number for other configuration files). Can be any string.


**Plot-type (i.e.** ``timeseries`` **) :** Nested under **Plot-key (** ``plot1`` **)**, "Plot-type" specifies the type of plot desired. *Possible types:* ``timeseries``, ``boxplot``, ``histogram``, ``scatterplot``


*Note [Exception]*: For the case of transform, simply specify ``transform`` in the Plot-type, and it will perform the transform (no plots will be produced). 



``agent``: Name of the agent-type, nested under **Plot-type**.

``analysis``: Type of analysis. *Possible types:*  ``agent``, ``multiple_run``, ``multiple_batch``, ``multiple_set``.

``variables``: Variables from the particular agent-type that is to be processed/ visualized. The sub-hierarchy ``var1``, ``var2`` etc. allows
the input of multiple variables for any agent type. The variable names can be inside a set of square braces *[]* or simply inside a set of single-quotation marks *''*. 


Example::

    plot1:
        timeseries:
            agent: Bank
            analysis: multiple_set
            variables: 
              var1: [total_credit]  
              var2: [equity]
    

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

Possible types : ``mean``, ``median``, ``custom_quantile``, ``upper_quartile``, ``lower_quartile``, ``maximum``, ``minimum``.


Example::

    plot1:
        timeseries:
            summary: mean


Hence, a typical main configuration file may look like::

    i/o:
        input_path: 
            Bank: '/home/etace/Desktop/GitHub/Bank/Bank.h5' # please name the key as the agent name
            Eurostat: '/home/etace/Desktop/GitHub/Bank/Eurostat.h5'
        output_path: '/home/etace/Spaces/ETACE-Conquaire Project/Data/data_reproduction_task/timeseries_classify_LS_output'
        
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
            summary: mean
            
    plot2:
        boxplot:
            agent: Eurostat
            analysis: multiple_run
            variables: 
                var1: [total_credit]       
            set: [1]
            run: [1]
            major: [range,[6020,6900,20]]
            minor: [1,8] 
            summary: custom_quantile
            


plot.yaml
~~~~~~~~~

The *plot.yaml* file contains all the necessary configurations for a plot that is output. Whenever a plot is specified on the *main.yaml* file, the plot.yaml file is read for the necessary 
specifications of the plot.
As such, some of the parameters from the *plot.yaml* file is explained below:

**Plot-key( i.e.** ``plot1`` **):** This string should be the same as the Plot-key in the main.yaml file, to make sure
the correct parameters are mapped to the respective plot.

``number_plots``: Specifies how many plots will be output per variable for a particular agent type. 
*Possible values:* ``one``, ``many``.

``plot_name``: Specify filename for the plot.

*Note:* In case of multiple plots, a numerical suffix (*in increasing order*) is added after the specified file name.

``plot_legend``: Specify legend for the plot.

``legend_loc``: Specify location of the legend, either inside the box or outside of it. *Possible values:* ``in``, ``out``.

``legend_label``: Specify name for the lines in the plot. Can be any string value.

``x-axis label``: Specify label for the x-axis. Can be any combination of string values.

``y-axis label``: Specify label for the y-axis. Can be any combination of string values.

``linestyle``: Specify line characteristic. *Possible values:* ``solid``, ``dashed``, ``dashdot``, ``dotted`` etc.


Therefore, a particular *plot.yaml* file might look like::

    plot1:
        number_plots: one
        plot_name: timeseries_equity.png
        l_lim: no
        u_lim: no
        tmin: no
        tmax: no
        plot_legend: yes
        legend_loc: out
        legend_label: equity
        x-axis label: months
        y-axis label: equity value
        linestyle: solid
        
    
    plot2:
        number_plots: many
        plot_name: boxplot_monthly_output.png
        l_lim: no
        u_lim: no
        tmin: no
        tmax: no
        plot_legend: no
        legend_loc: in
        legend_label: monthly_output
        x-axis label: months
        y-axis label: monthly_output
        linestyle: dashed


transform.yaml
~~~~~~~~~~~~~~

The *transform.yaml* file contains all the necessary configurations for any transformation specified on the *main.yaml* file. Whenever a transformation is specified on the *main.yaml* file, the *transform.yaml* file is read for the necessary
specifications of the plot.

As such, some of the parameters from the *transform.yaml* file is explained below:

**Plot-key( i.e.** ``plot1`` **):** This string should be the same as the Plot-key in the main.yaml file, to make sure
the correct parameters are mapped to the respective plot.

*Note:* Although it is called Plot-key, the transform case is an exception and no plots are produced in transform case.

``variables``: Variables from the particular agent-type that is to be transformed. The sub-hierarchy ``var1``, ``var2`` etc. allows
the input of multiple variables for any agent type. 

``transform_function``: The transformation function to apply for the given variables to produce the necessary transforms.

*Possible functions:*

- Quarterly growth rate (quarter on quarter freq quaterly) ``q_o_q_q``
- Quarterly growth rate (quarter on quarter freq annual) ``q_o_q_a``
- Monthly growth rate (month on month freq annual) ``m_o_m_a``
- Monthly growth rate (month on month freq monthly) ``m_o_m_m``
- Annual growth (year on year freq annual) ``y_o_y_a``
- Other custom functions

*Note:* Other elementary functions such as **sum**, **difference**, **product**, and **division** can also be performed, which has been left for the user (will be added as custom functions).

``aggregate``: If the transformation is to be performed after calculating the summary stats, then a necessary aggregation method can be specified.
*Possible values:* ``mean``, ``median``, ``maximum``, ``minimum``, ``custom_quantile``, ``upper_quartile``, ``lower_quartile``.

``write_file``: Specify whether to write the transformation as a file. *Possible values:* ``yes``, ``no``.

``output_path``: If the ``write_file`` option above is set to ``yes``, then a output path for the file needs to be specified.
Can be any valid filepath, as a string, including upto the filename.

``hdf_groupname``: Specify the rootname for the HDF5 group name (internal hierarchy) for the transformed variable. Can be any valid string.

A particular *transform.yaml* file may, therefore, look as follows::

    plot2:
        variables: 
            var1: total_credit
            var2: equity       
        transform_function: m_o_m_ONE_CYCLE
        aggregate: mean    
     
        write_file: yes
        output_path: '/home/etaceguest/transform_test/transform_out/transformed.h5'
        hdf_groupname: 'total_credit_equity_ratio'



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**References:**

 Matplotlib: https://matplotlib.org/

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
