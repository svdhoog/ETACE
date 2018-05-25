        FLAViz: Flexible Large-scale Agent Visualization Library

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

-------------------------------------------------------------------------------
Current version
--
v1.0

Requirements:
--

You will need to satisfy the following dependencies.

1. FLAViz visualization scripts:
("recommended version", "minimal version")
 
* python3 (>= 3.4) Python3 core libraries
* python3-h5py (>= 2.2.1) -- needed for HDF5 files to be re-writable, appendable
* python3-matplotlib (>= 2.2.2)
* python3-numexp (>= 2.6)
* python3-numpy (>= 1.14.3)
* python3-pandas (0.22.0 or >= 0.19.0)
* python3-pyTables (>= 3.4) -- currently used for HDF5 files, write-once, non-appendable
* python3-scipy (1.1.0)
* python3-tk (>= 3.4.3)
* python3-yaml (>= 3.12)
* python3-lxml (4.2.1 or >= 3.3.3)

2. Data conversion scripts:
("recommended version", "minimal version")

* sqlite3 (>= 3.8.2)
* python3-pandas (0.22.0 or >= 0.19.0)
* python3-lxml (4.2.1 or >= 3.3.3)

Installation:
--

To see which versions of the Python3 packages you have installed, run:

```
$ ls /usr/local/lib/python3.4/dist-packages -lh
```

NOTE:
--
On some platforms the package manager will install older versions of the above packages.
For example, in Linux Mint 17 (Quiana), the version of matplotlib that is installed using apt-get is 1.19 instead of the newer version 2.2.2 (which is required).

The following packages can be installed via your distribution's package manager:

```
$ sudo apt-get install sqlite3 python3-pip python3-lxml python3-yaml python3-numexp python3-tables python3-tk
```

To install the latest versions of the Python numerical packages, you can use the python3-pip command:

```
$ python3 -mpip install -U matplotlib numpy pandas scipy
```

Alternatively, you can us pip3 directly:

```
$ pip3 install matplotlib numpy pandas scipy
```

Using the library:
--

For information on how to use the library, view the README.md file in the root folder.

You can also browse the User Manual online at:

https://github.com/svdhoog/FLAViz/blob/master/doc/readme.rst


Running the main module
--

The main Python script has a single argument, which is the path to the folder with configuration files:

```
main.yaml
plot.yaml
transform.yaml [optional]
```

To start the library, you should run it from the root FLAViz folder:
```
$ python3 main.py config
```
where `config` is the path to the config folder containing the configuration files:

* config.yaml
* plot_config.yaml
* transformations.yaml

------------------------------------
2018-05-25 11:00 svdh
