        FLAViz: Flexible Large-scale Agent Visualization Library

-------------------------------------------------------------------------------

      Copyright (c) 2018 Sander van der Hoog
      If you have any problems or enquiries, you can contact the
      library maintainer at <svdhoog@gmail.com>

-------------------------------------------------------------------------------

The Flexible Large-scale Agent Visualization Library (FLAViz) is a data analysis and agent visualization library developed for agent-based simulation models created using the FLAME simulation environment.

Agent-based simulations typically generate data spanning multiple dimensions, e.g. parameter sets, Monte Carlo replication runs, different agent types, many agent instances per type, many variables per agent, and the time dimension.

To deal with such a large heterogeneity and variety of data, it should be stored as an organized, high-dimensional data set, to allow for proper data aggregation, filtering, selection, slicing etc.

FLAViz builds on Python pandas and matplotlib, and can be used to filter, transform, and visualize time series data that is stored using hierarchical levels in the HDF5 file format. Various plotting styles can be specified, e.g., time series, box plots, scatter plots, histograms, and delay- or phase plots.

-------------------------------------------------------------------------------
Features
--
v1.0 - First release

 * data conversion from XML to SQLite DB and HDF5
 * data module using Python pandas
 * visualization module based on matplotlib


Getting started
--

For more information on how to use the library, view the [manual](https://github.com/svdhoog/FLAViz/blob/master/docs/manual/tex/FLAViz_Manual.pdf). 

Many example plots are [here](https://github.com/svdhoog/FLAViz/tree/master/docs/visualisation_scripts/readme.rst).
 
To get started immediately, you can run the library out-of-the-box using the [test data](https://github.com/svdhoog/FLAViz/tree/master/data/visualisation). Instructions on how to do this can be found in the section on Testing in the [tutorial](https://github.com/svdhoog/FLAViz/tree/master/docs/visualisation_scripts/readme.rst).

Test data
--

A simple model with test data is provided in the folder [circles model](https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle). A description is in the [readme file](https://github.com/svdhoog/FLAViz/tree/master/data/visualisation/models/circle/readme.rst).


Requirements:
--

You will need to satisfy the following dependencies.

For the FLAViz visualization scripts:

* python3 (>= 3.4) Python3 core libraries
* python3-h5py (>= 2.2.1) -- needed for HDF5 files to be re-writable, appendable
* python3-matplotlib (>= 2.2.2)
* python3-numexp (>= 2.6)
* python3-numpy (>= 1.14.3)
* python3-pandas (0.22.0 or >= 0.19.0)
* python3-pyTables (>= 3.4) -- currently used for HDF5 files, using the 'tables' format (slower than 'fixed' format, but allows for appendable HDFStores)
* python3-scipy (1.1.0)
* python3-tk (>= 3.4.3)
* python3-yaml (>= 3.12)
* python3-lxml (4.2.1 or >= 3.3.3)

For the data conversion scripts:

* sqlite3 (>= 3.8.2)
* python3-pandas (0.22.0 or >= 0.19.0)
* python3-lxml (4.2.1 or >= 3.3.3)

Installation:
--

To see which versions of the Python3 packages you have installed, run:

```
$ ls /usr/local/lib/python3.4/dist-packages -lh
```

Notes:
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

Running the main module
--

The main Python script has a single argument, which is the path to the folder containing configuration files:
To start the library, you should run it from the root FLAViz folder:

```
$ python3 /src/visualisation_scripts/main.py -p /src/visualisation_scripts/config
```
where `config` is the path to the config folder containing the configuration files:

* config.yaml
* plot_config.yaml
* config_transform.yaml [optional]

For more information please see the `docs/` folder.


Contributors
------------
  - [Sander van der Hoog](https://github.com/svdhoog)
  - [Krishna Raj Devkota](https://github.com/krdevkota)
  - [Fabian Herrmann](https://github.com/0xfabi)

Contributing
------------

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

Copyright
---------

Copyright (c) 2018 Sander van der Hoog. See LICENSE for further details.
