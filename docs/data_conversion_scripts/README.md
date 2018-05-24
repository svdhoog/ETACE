Data Conversion Scripts
====

For more detailed user help, see:

docs/data_conversion_scripts/usage_help.rst

This repository contains all the necessary Python scripts to convert between different data formats.

The conversions that are possible are:

- ``xml`` format -> ``SQLite`` db format
- ``SQLite`` db format -> ``xml`` format
- ``SQLite`` db format -> ``hdf5`` format
- ``xml`` format -> ``hdf5`` format

The repo also includes scripts to convert between different structures within the hdf5 file (``set_*_run_*_iters`` format to ``Agentname`` *[Eurostat, Bank etc]* ) format.

Usage
====
The detailed documentation on how to use the module can be found on the */doc* folder in this repo.

The scripts in this repository are for converting data being produced by FLAME simulations.
Default output is to XML files; these scripts convert XML to SQL and HDF5.
Conversion from SQL to HDF5 is included as well.

In folder src/data_conversion_scripts:

- xml_db: conversion of XML to SQL
- db_hdf5: conversion of SQL to h5
- db_xml: conversion of SQL to XML
- hdf_agentwise/merge_hdf_agentwise.py: conversion of h5 (per set, run) to h5 (per agent type)
- xml_hdf5: conversion of XML to h5
