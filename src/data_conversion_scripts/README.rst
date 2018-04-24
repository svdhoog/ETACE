.. -*- mode: rst -*-

Data Conversion Scripts
=======================

This repository contains all the necessary Python scripts to convert between different data formats.

The conversions that are possible are:
- ``xml`` format -> ``SQLite`` db format
- ``SQLite`` db format -> ``xml`` format
- ``SQLite`` db format -> ``hdf5`` format
- ``xml`` format -> ``hdf5`` format

The repo also includes scripts to convert between different structures within the hdf5 file (``set_*_run_*_iters`` format to ``Agentname`` *[Eurostat, Bank etc]* ) format.

Dependencies
============

The scripts in this repository are tested to work with both Python 2.7.10 / Python 3.5.2 and above.

The required dependencies are : Pandas >= 0.19.2 , scipy >=0.18.1, numpy >= 1.11.3

Also, the data storage format requires the following dependency : pytables

Usage
=====

The detailed documentation on how to use the module can be found on the */doc* folder in this repo.

Misc
====
The folder misc/replace_xml_functions contains a script to replace a block of C code in FLAME's xml.c file.

- replace_xml_functions.py: Python script for replacing XML writeout functions in xml.c (FLAME-models)

This replacement script is useful for reducing the storage footprint of FLAME simulations. 
It allows the user to create a "shadow model.xml" file with a subset of the agent memory variables, resulting in fewer variables than the full model.xml file.
The script replace_xml_functions.py takes as input the full-model xml.c file and the shadow-model xml.c file, and then replaces all functions called write_<agentname>_Agent() in the full-model xml.c file.
The resulting full-model xml.c file can be compiled as usual with rest of the FLAME model C code.
The resulting simulation will only output the subset of variables for each agent type.
