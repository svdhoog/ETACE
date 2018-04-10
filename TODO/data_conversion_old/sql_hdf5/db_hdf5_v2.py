#!/usr/bin/env python3

#################################################################################################################
## This script creates HDF5 files from corresponding SQLite db files in one-to-one fashion. So, for each db file 
## present in the input folder, equivalent HDF5 file is created in the output folder. To combine db files into
## a single HDF5 file , use version 1 of script named db_hdf5_v1.py instead
#################################################################################################################

import sqlite3, sys, glob, os, argparse, errno
import pandas as pd
from glob import glob as g
pd.set_option('io.hdf.default_format','table')  # Commenting this line out will write HDF5 as a fixed format, and not as a table format
                                                # Writing as a fixed format is faster than writing as a table, but the file cannot be 'modified/appended to' later on 
DB_SUFFIX = '.db'
 
# Function to check for existing directories, and create a new one if not present 
def dir_check(d):
    if os.path.exists(d):
        reply = input("Specified output directory already exists!! Delete existing directory named <<"+os.path.basename(d)+">> and all its contents? [y/n] ")
        if reply in ['y', 'Y', 'yes']:
            try:
                os.system('rm -r '+ d)
                print("Directory named <<"+os.path.basename(d)+ ">> and all its contents deleted!!")
                # Make new output folder
                try:
                    os.makedirs(d)
                except OSError as exception:
                    if exception.errno != errno.EEXIST:
                        raise                
            except:
                error("- Could not delete directory <<" +os.path.basename(d)+">>. Directory may contain additional files, remove files manually and try again!")
        else:
            replytwo = input("Continue & write output files inside existing directory: <<"+os.path.basename(d)+">> ? WARNING: This will overwrite old files having same name, if present in the folder! [y/n]: ")
            if not replytwo in ['y', 'Y', 'yes']:
                try:              
                    print ("Please remove or rename the existing directory <<"+os.path.basename(d)+">> and try again, or choose a different directory for the output")
                    sys.exit()
                except OSError as exception:
                    if exception.errno != errno.EEXIST:
                        raise                        
    else:
        os.makedirs(d)


# Function to print out the error messages,if any, and exit
def error(mesg):
    print(">>>>> (Error): %s" % mesg, file = sys.stderr)
    sys.exit(1)


def agent_dataframe(agent_name):
    agent_name = agent_name.decode('utf-8')
    #df = pd.read_sql_query(("SELECT * from "+ agent_name), con)
    df = pd.read_sql(("SELECT * from "+ agent_name), con)
      
    # Ignoring the empty tables 
    if df.empty == False:
    #Converting the datatypes to make all of them uniform, to avoid pickling later on when writing to HDF    
        types = df.apply(lambda x: pd.lib.infer_dtype(x.values))
        
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
    #pnl = dp.swapaxes(0,2, copy=True)  # This will allow to swap the datapanel axes, if needed
    return dp

def gen_hdf(fname, output_folder):    
    outFileName = output_folder + '/' +  os.path.basename(fname)[:-len(DB_SUFFIX)]        
    fname_tostore = outFileName +'.h5'
    #verboseprint ('- Preparing HDF5 file: '+os.path.basename(fname_tostore)+'for writing')
    store = pd.HDFStore(fname_tostore, 'w', chunksize = 500, complevel = 1, complib ='bzip2', fletcher32 = True)
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
            verboseprint ('- Processing table values for: '+str(agent_name))  
            dfa = agent_dataframe(agent_name)
            verboseprint ('- Obtained Dataframe for: '+str(agent_name))  
            # Checking and ignoring empty agent tables that might be in the DB
            if dfa is not None:
                verboseprint ('- Preparing HDF5 file for writing')
                a = agent_name.decode('utf-8')
                # Storing the panels in the HDF Store 
                store[a] = gendp(dfa)                   
                verboseprint ('- Successfully wrote: '+str(agent_name)+ ' into HDF5 file. \n')            
    except sqlite3.Error as e:
        print("Error ", e.args[0])
        sys.exit(1)
    finally:
        if con:
            con.close()       
    verboseprint ('- Successfully closed HDF5 file: '+os.path.basename(fname_tostore)+'\n')
    store.close()
    #verboseprint('- Done processing: ',os.path.basename(fname))
    del dfa


if __name__ == "__main__":
    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='db_hdf5_v2.py', description='Converts the SQLite database files to HDF5 files. For each db files, creates an equivalent HDF5 file.')
    parser.add_argument('dbpath', help='Path to folder containing the .db files', nargs=1, type=str)
    parser.add_argument('-o', '--outpath', help='Path to the folder where the output is desired', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')   
    parser.add_argument('-s', '--status', help='Get the total progress of the processing', action='store_true')

    args = parser.parse_args()
    
    # Set input parameters
    input_dbfolder =  ''
    input_dbfolder = args.dbpath[0]
    dir_list =[]
    # Checking for nested subdirectories within a directory
    for (dirpath,dirnames,filenames) in os.walk(input_dbfolder):
        dir_list.append(dirpath)
    if len(dir_list) == 0:
        error("- Make sure the specified input directory is an actual directory, and not a file!")
    if os.getcwd() == os.path.abspath(input_dbfolder):    
        error("- BAD IDEA!!! Execution script and input db files both inside a single folder <<" +os.getcwd()+">>. Might cause a recursive loop leading to erroneous output in some cases. Expected at least one level of separation. Please keep the script somewhere else and retry!")

    if len(dir_list)>1:
        N = 1
        F = len(dir_list)-1
    else:
        N = 0
        F = len(dir_list) 
    
    
    # Set output parameters
    output_folder =  ''
    if args.outpath:
        output_folder = args.outpath[0]
    else:
        # Choose one of the options below and comment out the other as desired.
        
        #output_folder =  './output_'+os.path.basename(input_dbfolder) # Creates output folder in the same folder where Python script is located.
        output_folder =  os.path.dirname(input_dbfolder)+'/output_'+os.path.basename(input_dbfolder)  # Creates output folder in the same folder where input folder is located
        
        
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
                sys.stdout.write("\r" + arg)
                sys.stdout.flush()
            print()
    else:
        statusprint = lambda *a: None    
    
    # Process each folder in the input directory    
    processed_folders = 0
    statusprint('\n- Total number of folders: '+ str(F)+'\n')
    for i in range(N,len(dir_list)):
        statusprint('- Started processing folder: '+os.path.basename(dir_list[i]))   
        # Populate the list with all sql file names in the folder
        db_file_list = []
        for fname in glob.glob(os.path.join(dir_list[i], '*'+DB_SUFFIX)):
            db_file_list.append(fname)
        statusprint('- Total number of files within folder: '+ str(len(db_file_list)))      
        # Generate panels
        processed_files =[]
        for fname in db_file_list:
            verboseprint('\n- Started processing: '+os.path.basename(fname))
            
            gen_hdf(fname, output_folder)
            processed_files.append(fname)
            percent = round((float(len(processed_files))/len(db_file_list))*100,2)
            statusprint('- Number processed files: '+str(len(processed_files))+', of total: '+str(len(db_file_list))+'    Progress:'+ str(percent) +'%'),
        statusprint('- Finished processing folder: '+os.path.basename(dir_list[i])+'\n')
        processed_folders = processed_folders+1
        f_percent = round((float(processed_folders)/F)*100,2)
        statusprint('- Total progress:'+ str(f_percent) +'%', '\n')
        
        
        
        
        
        
