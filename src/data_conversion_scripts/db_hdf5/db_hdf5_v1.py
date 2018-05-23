#!/usr/bin/env python3

#################################################################################################################
## This script creates HDF5 files from corresponding SQLite db files in many-to-one fashion. So, for all db files
## present in one input folder, one equivalent HDF5 file is created in the output folder. For input folders
## containing more hierarchies, if run with a flag -r, one HDF5 file is created for contents of each subfolder.
#################################################################################################################

from __future__ import print_function
import sqlite3, sys, glob, os, argparse, errno
import pandas as pd
from pathlib import Path

pd.set_option('io.hdf.default_format','table')   # Commenting this line out will write HDF5 as a fixed format, and not as a table format
                                                 # Writing as a fixed format is faster than writing as a table, but the file cannot be 'modified/ appended to' later on
DB_SUFFIX = '.db'

# Function to check for existing directories, and create a new one if not present
def dir_check(d):
    #path = os.path.abspath(sys.argv[1])
    outpath = os.path.abspath(d)
    if os.path.exists(d):
        print("- Directory ["+outpath+ "] is used for output files")

    else:
        os.makedirs(d)
        print("- Directory ["+outpath+ "] was created and is used for output files")

# Function to print out the error messages,if any, and exit
def error(mesg):
    print(">>>>> (Error): {0}".format(mesg), file = sys.stderr)
    sys.exit(1)


def agent_dataframe(agent_name):
    agent_name = agent_name.decode('utf-8')
    df = pd.read_sql(("SELECT * from "+ agent_name), con)

    # Ignoring the empty tables
    if df.empty == False:
    #Converting the datatypes to make all of them uniform, to avoid pickling later on when writing to HDF
        types = df.apply(lambda x: pd.api.types.infer_dtype(x.values))

        for col in types[types=='floating'].index:
            df[col] = df[col].astype(str)

        for col in types[types=='mixed'].index:
            df[col] = df[col].astype(str)

        for col in types[types=='unicode'].index:
            df[col] = df[col].astype(str)

        # Keeping count of the individual agent instance
        IterationList =[]
        agtin = str('agent_inst').encode('utf-8')
        IterationList = df['_ITERATION_NO'].tolist()
        j=0
        agentinstance_index =[j]
        for i in range(1,len(IterationList)):
          if IterationList[i] == IterationList[i-1]:
              j=j+1
              agentinstance_index.append(j)
          else:
              j=0
              agentinstance_index.append(j)
        # Adding the agent instance count as a separate column to the dataframe
        df[agtin] = agentinstance_index
        # Creating hierarchial index for df with the iteration number, and agent instance count
        df.set_index(['_ITERATION_NO',agtin], inplace=True)
        return df

def gendp(dframes):
    dp = dframes.to_panel()
    #pnl = dp.swapaxes(0,2, copy=True) #This will allow to swap the datapanel axes, if needed
    return dp

def gen_hdf(fname):
    global con, cur, agent_name
    con = None
    try:
        con = sqlite3.connect(fname)
        cur = con.cursor()

        # Get the name of all the tables in the SQLite DB i.e. the agents
        cur.execute("SELECT name from sqlite_master WHERE type='table';")
        agent_list = [x[0].encode('ascii', 'ignore') for x in cur.fetchall()]
        w = str('_iters_').encode('utf-8')
        if w in agent_list:
            agent_list.remove(w)
        # Iterate through all the agent tables in the DB and add each to a unique Dataframe
        for agent_name in agent_list:
            verboseprint ('- Processing table values for: '+str(agent_name).replace("b'","'"))
            dfa = agent_dataframe(agent_name)
            verboseprint ('- Obtained Dataframe for: '+str(agent_name).replace("b'","'"))
            # Checking and ignoring empty agent tables that might be in the DB
            if dfa is not None:
                verboseprint ('- Preparing HDF5 file for writing')
                a = agent_name.decode('utf-8')
                s = str(os.path.basename(fname))[:-3] +'/'+str(a).replace("b'","'")
                # Storing the panels in the HDF Store
                store[s] = gendp(dfa)
            verboseprint ('- Successfully wrote: '+str(agent_name).replace("b'","'")+ ' into HDF5 file \n')
    except sqlite3.Error as e:
        print("Error ", e.args[0])
        sys.exit(1)
    finally:
        if con:
            con.close()
    del dfa


if __name__ == "__main__":
    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='db_hdf5_v1.py', description='Converts the SQLite database files to HDF5 files. Combines multiple db files into a single HDF5 file.')
    parser.add_argument('dbpath', help='Path to folder containing the .db files', nargs=1, type=str)
    parser.add_argument('-o', '--outpath', help='Path to the folder where the output is desired', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')
    parser.add_argument('-s', '--status', help='Get the total progress of the processing', action='store_true')
    parser.add_argument('-r', '--recursive', help = 'Use recursion to process all subfolders within given folder',action='store_true')

    args = parser.parse_args()

    # Set input parameters
    input_dbfolder = args.dbpath[0]

    if os.getcwd() == os.path.abspath(input_dbfolder):
        error("- Python script and data files not allowed in a single folder. Expects atleast a level of folder hierarchy. Fix issue and retry! ")

    dir_list =[]
    if args.recursive:
        # Checking for nested subdirectories within a directory
        for (dirpath,dirnames,filenames) in os.walk(input_dbfolder):
            dir_list.append(os.path.abspath(dirpath))
    else:
        dir_list.append(os.path.abspath(input_dbfolder))


    # Set output parameters
    output_folder =  ''
    if args.outpath:
        output_folder = args.outpath[0]
    else:
        # Choose one of the options below and comment out the other as desired.

        #output_folder =  './output_'+os.path.basename(os.path.dirname(input_dbfolder)) # Creates output folder in the same folder where Python script is located.
        #output_folder =  os.path.dirname(input_dbfolder)+'/output_'+os.path.basename(os.path.dirname(input_dbfolder))  # Creates output folder in the same folder where input folder is located
        output_folder =  os.path.dirname(input_dbfolder)  # Creates no output folder and places h5 file in same folder as input file

    # Function call to check if the output folder already exists, and create if not present
    dir_check(output_folder)

    #Setup for verbose arguments
    if args.verbose:
        def verboseprint(*args):
            for arg in args:
                print(arg, end=' ')
            print()
    else:
        verboseprint = lambda *a: None

    #Setup for process status arguments
    if args.status:
        def statusprint(*args):
            for arg in args:
                print(arg, end=' ')
            print()
    else:
        statusprint = lambda *a: None
    F = len(dir_list)
    processed_folders = 0
    statusprint('\n- Total number of folders: '+ str(F)+'\n')

    for d in dir_list:
        statusprint('- Started processing folder: '+os.path.basename(d))
        # Populate the list with all sql file names in the folder
        db_file_list = []
        for fname in glob.glob(os.path.join(d, '*'+DB_SUFFIX)):
            db_file_list.append(fname)
        statusprint('- Total number of files in current folder: '+ str(len(db_file_list)))

        # Setting up HDF5 file for storing output
        fname_tostore = output_folder +'/'+os.path.basename(d)+'.h5'
        verboseprint ('\n- Preparing HDF5 file for writing contents of input folder: '+os.path.basename(d))
        store = pd.HDFStore(fname_tostore, 'w', complevel = 1, complib ='bzip2', fletcher32 = True)

        # Generate panels
        processed_files =[]
        for fname in sorted(db_file_list):
            verboseprint ('\n- Started processing: '+os.path.basename(fname))

            gen_hdf(fname)
            processed_files.append(fname)
            percent = round((float(len(processed_files))/len(db_file_list))*100,2)
            statusprint('- Number processed files: '+str(len(processed_files))+', of total: '+str(len(db_file_list))+'    Progress: '+ str(percent) +'%'),
        verboseprint ('- Successfully closed HDF5 file for: '+os.path.basename(d))
        store.close()
        statusprint('- Finished processing folder: '+ os.path.basename(d)+'\n')
        processed_folders = processed_folders+1
        f_percent = round((float(processed_folders)/F)*100,2)
        statusprint('- Total progress: '+ str(f_percent) +'%', '\n')
