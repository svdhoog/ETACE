#!/bin/bash

export scriptpath=/media/sander/DataStorage1/GIT/GitHub/FLAViz@svdhoog/FLAViz/src/data_conversion_scripts/db_hdf5
export input=/media/sander/DataStorage-2/scratch/svanderh/circle_test_model_data/its/dataset_2_agents_6
export output=/media/sander/DataStorage-2/scratch/svanderh/circle_test_model_data/its/dataset_2_agents_6

# Test v1
# With compression, chunksize = 1000
#python3 $scriptpath/db_hdf5_v1.py $input/db --chunksize 1000 --outpath $output/h5 -v -s -z 1 -c 1000
# No compression, no chunksize
#python3 $scriptpath/db_hdf5_v1.py $input/db --outpath $input/h5 -v -s -z 0

# Test v2
# With compression, chunksize = 1000
#python3 $scriptpath/db_hdf5_v2.py $input/db --outpath $output/h5 -v -s -z 1 -c 1000
# No compression, no chunksize
python3 $scriptpath/db_hdf5_v2.py $input/db --outpath $output/h5 -v -s -z 0
