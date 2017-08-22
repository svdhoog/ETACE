.. -*- mode: rst -*-

Data Conversion Scripts
=======================

This repository contains all the necessary Python scripts to convert between different data formats.

The conversions that are possible are:

- ``SQLite`` db format -> ``xml`` format
- ``SQLite`` db format -> ``hdf5`` format
- ``xml`` format -> ``hdf5`` format

The repo also includes script to convert between different structures within the hdf5 file (``set_*_run_*_iters`` format to ``Agentname`` *[Eurostat, Bank etc]* ) format.

Dependencies
============

The scripts in this repository are tested to work with both Python 2.7.10 / Python 3.5.2 and above.

The required dependencies are : Pandas >= 0.19.2 , scipy >=0.18.1, numpy >= 1.11.3

Also, the data storage format requires the following dependency : pytables

Usage
=====

The detailed documentation on how to use the module can be found on the */doc* folder in this repo.
