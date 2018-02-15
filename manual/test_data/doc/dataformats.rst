FLAViz: Flexible Large-scale Agent Visualization library
--

This is the release of FLAViz 0.1.0 (beta version), a new visualization library developed at the ETACE group at Bielefeld University (Economic Theory and Computational Economics).

FLAViz is a member of the FLAME ecology of tools for the development, simulation and analysis of large-scale agent-based models.

FLAViz targets the analysis and visualization of *time series data* produced from any ABM, but was specifically designed with the output from FLAME models in mind.

FLAViz provides the following features:

- Easy-to-configure yaml files

- Fully written in Python (support for both Python 2.7 and 3.6)

- Based on Python pandas (0.21.0) and matplotlib as standards for data analysis and visualization

- Data conversion from XML files to HDF5 files

- Data transformations of agent variables

- Data selection based on data structure (e.g., select all data at iteration t=x, or select all data for agent ID=i)

- Data filtering based on agent or variable conditions (e.g., filter the selected data on the condition that agent variable X==value)

- Data visualization using various styles: time series, box plots, scatter plots, table output


Dependencies:

- Python (2.7 and 3.6)
- Python pandas (0.21.0)
- matplotlib
- hdf5?
- pytables?


FAQ
--

Q: Why is FLAViz based on Python pandas and matplotlib?

A: Python pandas is open source, has an active user community, and has many developers. It is the current library of choice for time series data analysis.
It provides many in-build statistical functionalities.
There are two main functionalities of pandas that are especially important for us:
- hierarchical indexing: this allows a high dimensional data frame (the ndarray format)
- bygroup

Q: Why the conversion from XML files to HDF5 format?

A: The XML files that FLAME outputs is a fully tagged data format, so it is very verbose. For large scale simulations this is prohibitive, due to the sheer size of the data volumes this generates.
To reduce this storage footprint, but still keep all data together in a structured format, the HDF5 standard was chosen for its hierarchical structure.
The data for each agent type is stored in a single HDF5 file, which can be of any size (we have so far dealt with single files of up to 20 GB without any problems).
Inside of the HDF5 file there is a POSIX-style folder hierarchy, with data groups and data sets. A particular requirement for HDF5 is that the 'data set' has a homogeneous data structure.
For this data structure we have selected the 3D DataFrame from Python pandas (but we should note that the current development of Python pandas goes so quickly, that currently this is shifting to the ndarray, which will replace the 3D Data Panel in a more generic data format).

Q: How do you do the data transformations, data selection and data filtering?

We use the bygroup function of pandas to sort the hierarchical index, and to rotate the data frame.

Q: Can I use FLAViz with other agent-based simulation platforms than FLAME?

Yes, you can! The only requirement is that the final data output is either in XML or in HDF5 format (see the file format specifications).

Q: What file format specifications do you have?

See: file format specifications (ADD LINK).


Data formats
--

# Simulations

We adopted the following ontology to describe how we run simulations:

- "Sets": a set reflects a model parameter setting. Each set differs from another set only in the parameter setting of the model.
- "Runs": a run is a replication, for a fixed parameter setting. Each run differs from other runs by the random seed only. The other initial conditions are kept exactly the same across runs.

Thus, parameter variations are captured in "settings" or "sets". Each set reflects a different parametrization of the simulation model.
If we have any stochasticity in the model, we need to explore the statistical properties using the random seed for the Random Number Generator.
By default we use the RNG from the GNU/GSL library (a Mersenne Twister, mt19937, of period $2^19937 - 1$).

For each set, we then perform multiple runs using different random seeds, producing different simulation output for each run.
These runs can be called Monte Carlo replication runs since the random seeds are themselves varied in a random fashion.
The seed is set randomly based on the system time at launch time, and then stored for later replication of the data if needed.


# Data heterogeneity

The data is heterogeneous across several dimensions:

- agent types: there can be many different agent types (e.g., household agents, firm agents, bank agents, etc.)

- agent instances: there can be a different number of individual agents (called agent instances) per agent type.

- agent memory variables: there can be a different number of memory variables per agent type (but all agents of the same type have the same set of memory variables, specified a priori in the model.xml file that fully specifies the model's structure).

Due to this large data heterogeneity the file sizes may vary across simulations with the same model, even when using exactly the same input file, due to stochasticity.


# Data dimensions in the XML output (listed in the order in which data is being produced by FLAME):

1 Sets
2 Runs
3 Iterations
4 Agent types
5 Agent instances per type
6 Variables

However, due to several conditions we have to impose on the data structure, the order in which data should be stored in the HDF5 file format differs from the order above.
There are two restrictions:

1. For the HDF5 file format it is important that the atomic data set at the lowest hierarchical level is a homgeneous data format.
This means that the choice of the 6 dimensions above requires us to choose those dimensions that remain invariant across all model simulations.
These dimensions are: 5 Agent instances, 3 Iterations, 6 Variables. These dimensions are invariant because we simulate the same model many times, and we do not change the model structure across simulations.
Therefore the number of variables per agent remains the same, the number of agent instances (individual agents) per agent type is constant, and the total number of iterations also remains constant across simulation runs.

2. The 3D DataFrame format in Python pandas is specified as row-major. This means that the 3D data frame requires the largest dimension to be on the major axis (recall it has 3 axis; item, major and minor).
In our case, the largest dimension is the number of iterations, typically 1000 or higher. The other dimensions are the number of agent instances (~100), and the number of variables (~100).

Therefore, we specify the 3D DataFrame with:

- item axis: agent instances
- major axis (table rows): iterations
- minor axis (table columns): variables

# Data dimensions in the HDF5 file (listed in the order in which data is stored in the HDF5 files):

Agent type: HDF5 filename (eg., Bank.h5)
--
Hierarchy inside the HDF5 file:
1 Sets: data group
2 Runs: data set inside data group
--
3 Agent instances
4 Iterations
5 Variables


File format specifications
--

# Step 1: XML output

This is the native format in which FLAME generates output. Each iteration produces an XML file that contains a full snapshot of all agents, and all agent memory variables.
This can be a large file per iteration, so therefore FLAME also provides the possibility to onyl output one XML file at a certain freuqncy (using the command 'main -f freq', where main is the simulator executable and freq is an integer number that specifies at whic periodicity the output should be generated).
To further subsample the data outputted, it is possible to select only a subset of agents to output, or even to specify a *shadow model xml file* with only a subset of agent variables.
Whatever method chosen, the data format is XML with fully tagged variables for each individual agent. Since the XML tags are rather verbose and redundant (of the format: '<variable_name>value</variable_name>')
this format can be reduced drastically by extracting the data to a more strutured data format.

# Step 2: HDF5-per-run files

In this step we store data in one HDF5-per-run file per simulation run.

Each simulation run in FLAME produces a set of XML files, one file per iteration. This set can be tansformed into a flat table format, with iteration number on the table rows, and all variables of an individual agent on the table columns.
This would produce many tables, as many as there are individual agents. To reduce this further, we structure the data using the following dimensions (see also above, Data dimensions in the HDF5 file):

File hierarchy:
1 Set
2 Run
4 Agent type
--
Inside each HDF5-per-run file:
5 Agent instance
3 Iteration
6 Variable



Step 3: HDF5-per-agent-type files

In this step we store data in one HDF5-per-agent-type file. this aggregates across all the files generated at the previous step 2 (all HDF5-per-run files).

Structure:

HDF5 file:
Data group: "Sets" (parameter setting)
Data set:   "Runs" (replications) stored as 3D DataFrame

3D DataFrame:
item axis: agent instances
major axis (table rows): iterations
minor axis (table columns): variables