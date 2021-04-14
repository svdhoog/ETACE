
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
                                                # We require the 'table' format here, due to the append in the function write_hdf() below.
DB_SUFFIX = '.h5'

# Assumed input: a text file agentlist.txt containing the names of all agent types to process
# agentlist = ["Eurostat", "Government"] # Enter all agent-names to be processed

def write_hdf(fname):
    set_run_name = os.path.splitext(os.path.basename(fname))[0]

    print('\t\tTrying to open HDFStore in file: ' + os.path.basename(fname))
    print('\t\t' + set_run_name)

    # Read the input HDF5 file in memory
    #store = pd.io.pytables.HDFStore(fname,  mode='r') # this opens the file fname and gives a ref to it
    store = pd.HDFStore(fname,  mode='r')

    print('\t\tHDFStore now opened')

    # Filtering out each agent types from the input HDF5 file
    print('\t\tstore.keys():')
    print(store.keys())
    for key in store.keys():
        print('\t\tExtracting data for: ' + key.replace("b'","'"))
        if agentname in key:
            frame = store.select(key) # Retrieve pandas object stored in file, with optional WHERE selections
            store_out[set_run_name] = frame # store the object as data group '/set_run_name' in the HDFStore store_out
    store.close()
    print('\t\tHDFStore closed.')

# Function to check for existing directories, and create a new one if not present
def dir_check(d):
    if os.path.exists(d):
        outpath = os.path.abspath(d)
        print("- Directory used for output: [" + outpath + "]")

    else:
        os.makedirs(d)
        outpath = os.path.abspath(d)
        print("- Output directory created: [" + outpath + "]")

# Function to print out the error messages,if any, and exit
def error(mesg):
    print(">>>>> (Error): %s" % mesg, file = sys.stderr)
    sys.exit(1)

if __name__ == "__main__":
    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='merge_hdf_agentwise.py', description='\
        * Converts HDF5 files containing multiple agent types to HDF5 files per agent type. \
        * Input can be a path to a folder that contains multiple HDF5 files, or to a folder hierarchy. \
        * Output will be to a user-specified folder. \
        * If the input folder is a folder hierarchy, it will be traversed, and a similar folder hierarchy will be created in the output folder.\
        * The contents of the agent-wise HDF5 files combines the data per agent type, as found in the traversed folders.')
    parser.add_argument('hdfpath', help='Path to folder containing the individual hdf files', nargs=1, type=str)
    parser.add_argument('agentlist', help='File containing name of agent-types to process', nargs=1, type=str)
    parser.add_argument('-o', '--outpath', help='Path to the folder where the output will be stored', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')
    parser.add_argument('-s', '--status', help='Get the overall progress of the process (status is less verbose)', action='store_true')
    parser.add_argument('-c', '--chunksize', help='Set the chunksize for HDF5 files', nargs='?', type=int, const=500, default=500, action='store', required=False)
    parser.add_argument('-z', '--compress', help='Use the internal compression (currently set to: bzip) in the HDFStore', nargs='?', type=int, const=1, default=1, action='store', required=False)

    args = parser.parse_args()

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

    # Settings for HDF5 files
    chunksize = args.chunksize
    verboseprint ('- Chunksize used in HDFStore: ' + str(chunksize))
    h5_compression = args.compress
    if (h5_compression):        
        verboseprint ('- Compression used in HDFStore: ' + str(h5_compression))
    else:
        verboseprint ('- Compression used in HDFStore: ' + 'None')

    f_agentnames = args.agentlist[0]
    agentlist = []
    with open(f_agentnames, 'r') as f_in:
        for line in f_in:
            agentlist.append(line.strip())

    # Set input parameters
    input_dbfolder = args.hdfpath[0]

    if os.getcwd() == os.path.abspath(input_dbfolder):
        error("- Python script and data files not allowed in a single folder. Expects at least one level of folder hierarchy. Please fix the issue and retry.")

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
        #targetFolder =  './merged_agent_wise' # Set output folder to the same folder where this script is located.
        targetFolder =  os.path.abspath(os.path.join(os.path.normpath(input_dbfolder), os.pardir))+'/merged_agent_wise'  # Set output folder in the same parent folder as input folder.
        #targetFolder =  os.path.dirname(input_dbfolder)  # Creates no output folder and places the merged_agent_wise h5 file in the parent folder of the input folder.

    # Function call to check if the output folder already exists, and create if not present
    dir_check(targetFolder)

    # Process each folder in the input directory
    processed_folders = 0
    statusprint('\n- Total number of folders: '+ str(F)+'\n')
    for agentname in agentlist: # looping through each agent (memory conserving option)
        for i in range(N,len(dir_list)):
            # length of path until /last_folder
            n = len(os.path.normpath(input_dbfolder))
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
                statusprint('- adding to list: '+str(fname))
            statusprint('- Total number of files within folder: '+ str(len(db_file_list)))
    
            # Generate HDFStore objects and store in h5 file
            processed_files =[]

            # Filename to write the new HDFStore
            fname_tostore = output_folder + '/' + agentname +'.h5'
            
            if (h5_compression):
                store_out = pd.HDFStore(fname_tostore, 'w', chunksize = chunksize, complevel = 1, complib ='bzip2', fletcher32 = True) # store with compression
            else:
                store_out = pd.HDFStore(fname_tostore, 'w')  # to store without compression

            # Loop: process all h5 files set_*_run_*_iters.h5 and store them as groups in the new HDFStore 'store_out', written to file: fname_tostore
            for fname in sorted(db_file_list):
                verboseprint('\n- Started processing: '+os.path.basename(fname))
                write_hdf(fname) # write the pandas object (DataFrame) to the HDFStore
                processed_files.append(fname)
                percent = round((float(len(processed_files))/len(db_file_list))*100,2)
                statusprint('- Number processed files: '+str(len(processed_files))+', of total: '+str(len(db_file_list))+'    Progress:'+ str(percent) +'%'),
            store_out.close()
            statusprint('- Finished processing folder: '+os.path.basename(os.path.abspath(dir_list[i]))+'\n')
            processed_folders = processed_folders+1
            if F > 1:
                f_percent = round((float(processed_folders)/F)*100,2)
                statusprint('- Total progress:'+ str(f_percent) +'%', '\n')
