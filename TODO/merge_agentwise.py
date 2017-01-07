
import sqlite3, sys, glob, os, argparse, errno
import pandas as pd
from glob import glob as g
pd.set_option('io.hdf.default_format','table')  # Commenting this line out will write HDF5 as a fixed format, and not as a table format
                                                # Writing as a fixed format is faster than writing as a table, but the file cannot be 'modified/appended to' later on 

DB_SUFFIX = '.h5'
agentname = "Eurostat"

def write_hdf(fname, input_dbfolder):
    set_run_name = fname[len(os.path.normpath(input_dbfolder))+3:-3]
    print (set_run_name)
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
        reply = raw_input("Specified output directory already exists!! Delete existing directory named <<"+os.path.basename(d)+">> and all its contents? [y/n] ")
        if reply in ['y', 'Y', 'yes']:
            try:
                os.system('rm -r '+ d)
                "Directory named <<"+os.path.basename(d)+ ">> and all its contents deleted!!"
                # Make new output folder
                try:
                    os.makedirs(d)
                except OSError as exception:
                    if exception.errno != errno.EEXIST:
                        raise                
            except:
                error("- Could not delete directory <<" +os.path.basename(d)+">>. Directory may contain additional files, remove files manually and try again!")
        else:
            replytwo = raw_input("Continue & write output files inside existing directory: <<"+os.path.basename(d)+">> ? WARNING: This will overwrite old files having same name, if present in the folder! [y/n]: ")
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
    print (">>>>> (Error): %s" % mesg)
    sys.exit(1)



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
    if input_dbfolder == "./": 
        cwd = os.getcwd()
        print ("- Python script and input csv files both inside the same folder <<" +cwd+">>. Expected at least one level of hierarchy!")
        sys.exit(1)
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
        
        
    # Function call to check if the output folder already exists, and create if not present 
    dir_check(targetFolder)
    
    #Setup for verbose arguments
    if args.verbose:
        def verboseprint(*args):
            for arg in args:
                #print (arg, end=' ')
                sys.stdout.write("\r" + arg)
                sys.stdout.flush()
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
        n = len(os.path.normpath(input_dbfolder)) + 2
        statusprint('- Started processing folder: '+os.path.basename(dir_list[i]))   
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
        store_out = pd.HDFStore(outFileName, 'w', chunksize = 500, complevel = 1, complib ='bzip2', fletcher32 = True)
        for fname in db_file_list:
            verboseprint('\n- Started processing: '+os.path.basename(fname))
            write_hdf(fname, input_dbfolder)
            processed_files.append(fname)
            percent = round((float(len(processed_files))/len(db_file_list))*100,2)
            statusprint('- Number processed files: '+str(len(processed_files))+', of total: '+str(len(db_file_list))+'    Progress:'+ str(percent) +'%'),
        store_out.close()
        statusprint('- Finished processing folder: '+os.path.basename(dir_list[i])+'\n')
        processed_folders = processed_folders+1
        f_percent = round((float(processed_folders)/F)*100,2)
        statusprint('- Total progress:'+ str(f_percent) +'%', '\n')
        
