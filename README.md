        FLAViz: Flexible Large-scale Agent Visualization Library (Release 0.1.0 beta)
        
        
The Flexible Large-scale Agent Visualization Library (FLAViz) is a data
analysis and visualization library developed for multi-agent/agent-based
simulations generated using the FLAME framework.

Agent-based simulation models typically generate data that spans multiple dimensions, e.g. parameter sets, Monte Carlo replication runs, different agent types, multiple agent instances per type, many variables per agent, and time periods (iterations).

To deal with such a large heterogeneity in the data dimensions, the data has to be stored as organized data sets, to allow for proper data aggregation, data filtering, selection, slicing etc. The software package FLAViz can be used to filter, transform, and visualize time series data that has been stored using multiple hierarchical levels in the HDF5 file format. Various kinds of plots can be specified, e.g., time series, box plots, scatter plots, histograms, and delay plots. 

-------------------------------------------------------------------------------

      Copyright (c) 2018 Sander van der Hoog
      If you have any problems or enquiries, you can contact the
      library maintainer at <svdhoog@gmail.com>
      
===============================================================================

##### Requirements: #####

You will need the following:
* Python core libraries
* pandas
* matplotlib
* h5py
* pyTables
* scipi
* numpy


##### Installation: #####


##### Using the library: #####

For information on how to use the library, view the README.md file in the root folder.

You can also browse the User Manual online at:
https://github.com/krdevkota/ETACE/


##### Runing the main module #####

The main Python script has a single argument, which is the path to the folder with configuration files:

main.yaml
plot.yaml
transform.yaml [optional]

To start the library, run from the /src folder

$ python main.py path-to-config-folder


------------------------------------
2018-02-08 11:00 svdh
 
