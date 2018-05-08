        FLAViz: Flexible Large-scale Agent Visualization Library (Release 0.1.0 beta)

-------------------------------------------------------------------------------

      Copyright (c) 2018 Sander van der Hoog
      If you have any problems or enquiries, you can contact the
      library maintainer at <svdhoog@gmail.com>
      
-------------------------------------------------------------------------------
        
The Flexible Large-scale Agent Visualization Library (FLAViz) is a data
analysis and visualization library developed for multi-agent/agent-based
simulations generated using the FLAME framework.

Agent-based simulation models typically generate data that spans multiple dimensions, e.g. parameter sets, Monte Carlo replication runs, different agent types, multiple agent instances per type, many variables per agent, and time periods (iterations).

To deal with such a large heterogeneity in the data dimensions, the data has to be stored as organized data sets, to allow for proper data aggregation, data filtering, selection, slicing etc. The software package FLAViz can be used to filter, transform, and visualize time series data that has been stored using multiple hierarchical levels in the HDF5 file format. Various kinds of plots can be specified, e.g., time series, box plots, scatter plots, histograms, and delay plots. 

===============================================================================

##### Requirements: #####

You will need to satisfy the following dependencies.

1. FLAViz visualization scripts:
("recommended version", "minimal version")
 
* python3 core libraries
* python3-h5py (>= 2.2.1) -- needed for HDF5 files to be re-writable, appendable
* python3-matplotlib (>= 2.0.2)
* python3-numexp (>= 2.6)
* python3-numpy (>= )
* python3-pandas (0.22, >= 0.19)
* python3-pyTables (>= 3.4) -- currently used for HDF5 files, write-once, non-appendable
* python3-scipy (>= 0.19)
* python3-tk (>= 3.4.3)
* python3-yaml (>= 3.12)
* python3-lxml (4.2.1, >= 3.3.3)

2. Data conversion scripts:
("recommended version", "minimal version")

* sqlite3 (>= 3.8.2)
* python3-pandas (0.22.0, >= 0.19)
* python3-lxml (4.2.1, >= 3.3.3)

##### Installation: #####


##### Using the library: #####

For information on how to use the library, view the README.md file in the root folder.

You can also browse the User Manual online at:

https://github.com/svdhoog/ETACE/blob/master/doc/tutorial.rst


##### Runing the main module #####

The main Python script has a single argument, which is the path to the folder with configuration files:

main.yaml
plot.yaml
transform.yaml [optional]

To start the library, you should run it from the root FLAViz folder:

$ python3 main.py config

where `config` is the path to the config folder containing the configuration files:

* config.yaml
* plot_config.yaml
* transformations.yaml

------------------------------------
2018-05-08 11:00 svdh
