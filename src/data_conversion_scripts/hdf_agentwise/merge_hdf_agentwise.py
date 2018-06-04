#!/usr/bin/env python3

#######################################################################################################################
## This script converts HDF5 files from set_*_run_*_iters.h5 format to HDF5 files per agent (Eurostat.h5, Firm.h5 etc).
## So, for each HDF5 file present in the input folder, all corresponding agents are filtered and placed in new
## agent-based HDF5 file.
#######################################################################################################################

from __future__ import print_function
import sqlite3, sys, glob, os, argparse, errno
import pandas as pd

pd.set_option('io.hdf.default_format','table')  # Commenting this line out will write HDF5 as a fixed format, and not as a table format
                                                # Writing as a fixed format is faster than writing as a table, but the file cannot be 'modified/appended to' later on

DB_SUFFIX = '.h5'
#agentlist = ["Eurostat", "Government"] # Enter all agent-names that is to be processed

def write_hdf(fname):
    set_run_name = os.path.splitext(os.path.basename(fname))[0]
    # Read the input HDF5 file in memory
    store = pd.io.pytables.HDFStore(fname)
    # Filtering out each agent types from the input HDF5 file
    for key in store.keys():
        if agentname in key:
            frame = store.select(key)
            store_out[set_run_name] = frame
    store.close()

# Function to check for existing directories, and create a new one if not present
def dir_check(d):
    if os.path.exists(d):
        print("- Directory ["+os.path.realpath(d)+ "] is used for output files")
    else:
        os.makedirs(d)
        print("- Directory ["+os.path.realpath(d)+ "] was created and is used for output files")

# Function to print out the error messages,if any, and exit
def error(mesg):
    print(">>>>> (Error): %s" % mesg, file = sys.stderr)
    sys.exit(1)

if __name__ == "__main__":
    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='merge_hdf_agentwise.py', description='Converts the SQLite database files to HDF5 files. For each db files, creates an equivalent HDF5 file.')
    parser.add_argument('hdfpath', help='Path to folder containing the individual hdf files', nargs=1, type=str)
    parser.add_argument('agentlist', help='File containing name of agent-types to process', nargs=1, type=str)
    parser.add_argument('-o', '--outpath', help='Path to the folder where the output is desired', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')
    parser.add_argument('-s', '--status', help='Get the total progress of the processing', action='store_true')

    args = parser.parse_args()

    f_agentnames = args.agentlist[0]
    agentlist = []
    with open(f_agentnames, 'r') as f_in:
        for line in f_in:
            agentlist.append(line.strip())

    # Set input parameters
    input_dbfolder = args.hdfpath[0]

    if os.getcwd() == os.path.abspath(input_dbfolder):
        error("- Python script and data files not allowed in a single folder. Expects atleast a level of folder hierarchy. Fix issue and retry! ")

    dir_list =[]
    # Checking for nested subdirectories within a directory
    for (dirpath,dirnames,filenames) in os.walk(input_dbfolder):
        dir_list.append(dirpath)
    if len(dir_list)>1:
        N = 1
        F = len(dir_list)-1
    else:
        N = 0
        F = len(dir_list)

    # Set output parameters
    targetFolder =  ''
    if args.outpath:
        targetFolder = args.outpath[0]
    else:
        # Choose one of the options below and comment out the other as desired.

        targetFolder =  './output_'+os.path.basename(os.path.normpath(input_dbfolder)) # For output folder in the same folder where Python script is located.
        #targetFolder =  os.path.abspath(os.path.join(os.path.normpath(input_dbfolder), os.pardir))+'/output_'+os.path.basename(os.path.normpath(input_dbfolder))  # For output folder in the same folder where input folder is located
        #targetFolder =  os.path.dirname(input_dbfolder)  # Creates no output folder and places h5 file in same folder as input file


    # Function call to check if the output folder already exists, and create if not present
    dir_check(targetFolder)

    #Setup for verbose arguments
    if args.verbose:
        def verboseprint(*args):
            for arg in args:
                print (arg, end=' ')
            print()
    else:
        verboseprint = lambda *a: None

    #Setup for process status arguments
    if args.status:
        def statusprint(*args):
            for arg in args:
                print (arg, end=' ')
            print()
    else:
        statusprint = lambda *a: None

    # Process each folder in the input directory
    processed_folders = 0
    statusprint('\n- Total number of folders: '+ str(F)+'\n')
    for agentname in agentlist: # looping through each agent (memory conserving option)
        for i in range(N,len(dir_list)):
            n = len(os.path.normpath(input_dbfolder)) + 2
            statusprint('- Processing files for agent-type: '+str(agentname)+'\n')
            statusprint('- Started processing folder: '+os.path.basename(os.path.abspath(dir_list[i])))
            if N == 1:
                output_folder = targetFolder +  dir_list[i][n:]
                dir_check(output_folder)
            else:
                output_folder = targetFolder

            # Populate the list with all sql file names in the folder
            db_file_list = []
            for fname in glob.glob(os.path.join(dir_list[i], '*'+DB_SUFFIX)):
                db_file_list.append(fname)
            statusprint('- Total number of files within folder: '+ str(len(db_file_list)))
            # Generate panels
            processed_files =[]
            #print (db_file_list)
            outFileName = output_folder + '/' + agentname +'.h5'
            #store_out = pd.HDFStore(outFileName, 'w')  # to store without compression
            store_out = pd.HDFStore(outFileName, 'w', chunksize = 500, complevel = 1, complib ='bzip2', fletcher32 = True) # store with compression
            for fname in sorted(db_file_list):
                verboseprint('\n- Started processing: '+os.path.basename(fname))
                write_hdf(fname)
                processed_files.append(fname)
                percent = round((float(len(processed_files))/len(db_file_list))*100,2)
                statusprint('- Number processed files: '+str(len(processed_files))+', of total: '+str(len(db_file_list))+'    Progress:'+ str(percent) +'%'),
            store_out.close()
            statusprint('- Finished processing folder: '+os.path.basename(os.path.abspath(dir_list[i]))+'\n')
            processed_folders = processed_folders+1
            if F > 1:
                f_percent = round((float(processed_folders)/F)*100,2)
                statusprint('- Total progress:'+ str(f_percent) +'%', '\n')
