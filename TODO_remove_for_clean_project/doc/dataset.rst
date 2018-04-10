.. _dataset:

Input and Output data storage format
====================================

The input data is stored in a ``HDF5`` container file (*.h5, .hdf5*) in a hierarchial form.

Currently, the ``HDF5`` file is arranged as follows:

- Each agent-type is contained in a separate HDF5 file, with the same name.

- Each HDF5 file has a single hierarchy, with the ``agent-type`` as the root, and the ``set`` and ``runs`` as the branches.

- the set and runs branches each contain a ``Pandas 3D data Panel``, which contains the ``major``, ``minor``, and ``items`` axis.

- the ``Pandas 3D data Panel`` is written to the HDF5 file with the help of ``Pytable`` module of python.


A HDF5 file as described above can be created from the SQLite db files by using the data processing scripts, included in the data processing directory

*Note:* To avoid any unwanted errors, it is imperative to name the ``SQLite`` db files with the following convention: ``set_*_run_*_iters.db``


**References:**

 Python Pandas: http://pandas.pydata.org/

 HDF5: https://support.hdfgroup.org/HDF5/

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
