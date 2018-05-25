Data Conversion Scripts
====
The scripts in this repository are for converting data produced by FLAME simulations.
Default output is to XML files; these scripts convert XML to SQL and HDF5.
Conversion from SQL to HDF5 is included as well.

This repository contains Python scripts to convert between different data formats:

- xml_db: conversion of XML to SQL
- db_hdf5: conversion of SQL to h5
- db_xml: conversion of SQL to XML
- xml_hdf5: conversion of XML to h5

The repo also includes scripts to convert between different structures within the hdf5 file (``set_*_run_*_iters`` format to ``Agentname`` *[Eurostat, Bank etc]* ) format.

- hdf_agentwise/merge_hdf_agentwise.py: conversion of h5 (per set, run) to h5 (per agent type)

Usage
====
The detailed documentation on how to use the module can be found on the */doc* folder in the [FAQ](FAQ.md).
