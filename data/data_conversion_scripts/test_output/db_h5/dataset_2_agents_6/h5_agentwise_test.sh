#!/bin/bash

export scriptpath=/media/sander/DataStorage1/GIT/GitHub/FLAViz@svdhoog/FLAViz/src/data_conversion_scripts/hdf_agentwise
export input=/media/sander/DataStorage-2/scratch/svanderh/circle_test_model_data/its/dataset_2_agents_6/
export output=/media/sander/DataStorage-2/scratch/svanderh/circle_test_model_data/its/dataset_2_agents_6/

# With compression, chunksize = 1000
python3 $scriptpath/merge_hdf_agentwise.py $input/h5 agentlist.txt --outpath $output/h5agent -v -s -c 1000 -z 1

# No compression, no chunksize
#python3 $scriptpath/merge_hdf_agentwise.py $input/h5 agentlist.txt --outpath $output/h5agent -v -s -z 0
