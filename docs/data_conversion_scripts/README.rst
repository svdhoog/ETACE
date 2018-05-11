.. -*- mode: rst -*-

#### Data Conversion Scripts

For more detailed user help, see:

docs/data_conversion_scripts/usage_help.rst

This repository contains all the necessary Python scripts to convert between different data formats.

The conversions that are possible are:
- ``xml`` format -> ``SQLite`` db format
- ``SQLite`` db format -> ``xml`` format
- ``SQLite`` db format -> ``hdf5`` format
- ``xml`` format -> ``hdf5`` format

The repo also includes scripts to convert between different structures within the hdf5 file (``set_*_run_*_iters`` format to ``Agentname`` *[Eurostat, Bank etc]* ) format.

#### Dependencies

The scripts in this repository are tested to work with Python 3.5.2 and above.

The required dependencies are : Pandas >= 0.19.2 , scipy >=0.18.1, numpy >= 1.11.3

Also, the data storage format requires the following dependency : pytables

#### Usage

The detailed documentation on how to use the module can be found on the */doc* folder in this repo.

The scripts in this repository are for converting data being produced by FLAME simulations.
Default output is to XML files; these scripts convert XML to SQL and HDF5.
Conversion from SQL to HDF5 is included as well.

1. src/data_conversion_scripts
- src/xml_db: conversion of XML to SQL
- src/db_hdf5: conversion of SQL to h5
- src/db_xml: conversion of SQL to XML
- src/hdf_agentwise/merge_hdf_agentwise.py: conversion of h5 (per set, run) to h5 (per agent type)
- src/xml_hdf5: conversion of XML to h5
