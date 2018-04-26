#!/usr/bin/env python3

#################################################################################################################
## This script creates HDF5 files from corresponding XML files in many-to-one fashion. So, for all xml files 
## present in one input folder, one equivalent HDF5 file is created in the output folder. For input folders 
## containing more hierarchies, one HDF5 file is created for contents of each subfolder.
#################################################################################################################
from __future__ import print_function

import os, sys, argparse, glob, errno
import lxml.etree as ET
from xml.dom import minidom
from xml.parsers.expat import ExpatError
import pandas as pd

pd.set_option('io.hdf.default_format','table')    # Commenting this line out will write HDF5 as a fixed format, and not as a table format
                                                  # Writing as a fixed format is faster than writing as a table, but the file cannot be 'modified/ appended to' later on
XML_SUFFIX = '.xml'

def file_exist(fname):
    f = glob.glob(fname)
    if fname in f: return True
    else: return False

# Function to check for existing directories, and create a new one if not present 
def dir_check(d):
    if os.path.exists(d):
        print("- Directory ["+os.path.basename(d)+ "] is used for output files")    
    else:
        os.makedirs(d)
        print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")

# Function to print out the error messages,if any, and exit
def error(mesg):
    print(">>>>> (Error): %s" % mesg, file = sys.stderr)
    sys.exit(1)

# Function to print out the error messages,if any
def warn(mesg):
    print(">>>>> (Warning): %s" % mesg, file = sys.stderr)

def get_node_text(node):
    if len(node.childNodes) != 1 or node.childNodes[0].nodeType != node.TEXT_NODE:
        error("getText() routine used on non-text XML node")
    return node.childNodes[0].data.strip()

# Function to generate a dataframe for the given agent from all the xml files in one folder
def gendf(files,agents):
    global df, colmList 
    xmlTree = ET.parse(files)  
    root = xmlTree.getroot()       
    allxagent = root.findall('xagent')   
    count = 0
    xList = [] 
    colmList = []                
    for xagent in allxagent:
        # Counting the occurrance of a single agent type from xml file containing mixed agent types
        count = count + 1       
        for names in xagent:
            if names.text in [agents]:
                xList.append(count)         
                colmList = []
                # Getting the variable names for that particular agent
                for subagent in xagent:
                    colmList.append(subagent.tag)
    # Creating a dataframe for that agent and appending all the variable values
    df = pd.DataFrame(columns=colmList)
    for i in xList:
        obj = root.xpath("xagent")[i-1].getchildren()  
        var=[]
        for j in range(0,len(colmList)):
            var.append(obj[j].text)
        row = dict(zip(colmList,var))
        row_s = pd.Series(row)
        row_s.name = os.path.splitext(os.path.basename(files))[0]   
        df = df.append(row_s)
        del var,row,row_s 
    del colmList, xList
    if df.empty == False:
        return df

# Function to generate data panels given the agent-names        
def gendp(agtname):          
    oneinst = d[agtname]
    dfa = pd.DataFrame()
    for i in range(0,len(oneinst)):
        dfa = dfa.append(oneinst[i][0])   
    dfa = dfa.reset_index()
    dfa.set_index(['index',dfa.index], inplace=True)
    dp = dfa.to_panel()
    del oneinst, dfa
    pnl = dp.swapaxes(0,2, copy=True)
    return pnl       


if __name__ == "__main__":
    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='xml_hdf5.py', description='Generates HDF5 files from XML files. Creates one HDF5 file for all xml files in one particular folder')
    parser.add_argument('modelpath', help='Path to model_xml folder containing all the subfolders and corresponding model.xml files', nargs=1, type=str)
    parser.add_argument('model_file_name', help='Name of the main xml_model file', nargs=1, type=str)
    parser.add_argument('datapath', help='Path to main data folder containing subfolders for all the runs, which contains XML files that require processing', nargs=1, type=str)
    parser.add_argument('-o', '--outpath', help='Path to the folder where the output is desired', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')   
    parser.add_argument('-s', '--status', help='Get the total progress of the processing', action='store_true')
    parser.add_argument('-r', '--recursive', help = 'Use recursion to process all subfolders within given folder',action='store_true')

    args = parser.parse_args()
    model = args.modelpath[0]+ '/' + args.model_file_name[0]
    
    # Check if the model xml file exists
    if not file_exist(model):
        error("- Model file (%s) does not exist" % model)
        
    # Set input parameters
    input_xml_folder = args.datapath[0]

    if os.getcwd() == os.path.abspath(input_xml_folder):    
        error("- Python script and data files not allowed in a single folder. Expects atleast a level of folder hierarchy. Fix issue and retry! ")

    dir_list =[]
    if args.recursive:
        # Checking for nested subdirectories within a directory
        for (dirpath,dirnames,filenames) in os.walk(input_xml_folder):
            dir_list.append(os.path.abspath(dirpath))
    else:
        dir_list.append(os.path.abspath(input_xml_folder))    
   
 
    # Set output parameters
    output_folder =  ''
    if args.outpath:
        output_folder = args.outpath[0]
    else:
        # Choose one of the options below and comment out the other as desired.
        
        #output_folder =  './output_'+os.path.basename(os.path.dirname(input_xml_folder)) # Creates output folder in the same folder where Python script is located.
        #output_folder =  os.path.dirname(input_xml_folder)+'/output_'+os.path.basename(os.path.dirname(input_xml_folder))  # Creates output folder in the same folder where input folder is located
        output_folder =  os.path.dirname(input_xml_folder)  # Creates no output folder and places h5 file in same folder as input file
        
    
    # Function call to check if the output folder already exists, and create if not present 
    dir_check(output_folder)
   
    #Setup for verbose arguments
    if args.verbose:
        def verboseprint(*args):
            for arg in args:
                print (arg, end=' '),
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

    F = len(dir_list)
        
    # Parse model_xml file to determine required agents
    verboseprint ("\n- Analysing model file\n")
    models = [model]
    alist =[]
    while len(models) > 0:
        fname = models.pop()
        dirname = os.path.dirname(fname)
        # load xml file
        verboseprint ("   + parsing %s" % fname)
        try:
            dom = minidom.parse(fname)
        except IOError:
            warn("Unable to read model file (%s). No such path exists." % fname)
            continue
        except ExpatError:
            error("Invalid XML file (%s)" % fname) 
            
        # detect nested models
        nodes = dom.getElementsByTagName("model")
        for node in nodes:
            status = get_node_text(node.getElementsByTagName("enabled")[0])
            if status != "true": continue 
            # add nested model file to list of files
            modelfile = get_node_text(node.getElementsByTagName("file")[0])
            models.append(os.path.join(dirname, modelfile))    
        del(nodes)
        
        # detect agents
        nodes = dom.getElementsByTagName("xagent")
        for node in nodes:
            # get agent name
            aname = get_node_text(node.getElementsByTagName("name")[0])
            alist.append(aname)  
        del(nodes)    
        verboseprint ("finished parsing") 
        del(dom)
    verboseprint ("\n- Parsing model file complete")    
            
    # Process each folder in the input directory
    processed_folders = 0
    statusprint('\n- Analysing input folders... total no. of input folders: '+ str(F)+'\n') 
    for dr in dir_list:
        statusprint('- Started processing folder: '+os.path.basename(dr))          
        # Populate the list with all xml file names in that input folder
        xml_filenames = []
        for fname in glob.glob(os.path.join(dr, '*'+XML_SUFFIX)):
            xml_filenames.append(fname)
        statusprint('- Total number of files in current folder: '+ str(len(xml_filenames)))
                
        agentnames = list(set(alist))  # done to remove duplicates
        

        # Store each dataframes for a particular agent in a dict, with agentnames as dict keys
        d = {}
        for f in xml_filenames:
            for a in agentnames:
                if a in d:
                    if gendf(f, a) is not None:
                        d[a].append([gendf(f, a)])
                else:
                    if gendf(f, a) is not None:
                        d[a]=[[gendf(f, a)]]

        # Generate the datapanels for each agents and store them in a HDF5 file
        n = 0
        for k,v in d.items():
            # Setting up HDF5 file for storing output
            verboseprint ('\n- Preparing HDF5 file for writing contents of input folder: '+os.path.basename(dr))
            fname_tostore = output_folder +'/'+os.path.basename(dr)+'.h5'    
            #store = pd.HDFStore(fname_tostore) 
            store = pd.HDFStore(fname_tostore, 'w', complevel = 1, complib ='bzip2', fletcher32 = True)
            store[k] = gendp(k)
            store.close()           
            n = n+1 
            # Get the progress status within a folder
            percent = round((float(n)/len(d.keys()))*100,2)   
            statusprint('- Number processed agents: '+str(n)+', of total: '+str(len(d.keys()))+'    Current Folder progress:'+ str(percent) +'%'),
            verboseprint ('- Successfully closed HDF5 file for: '+os.path.basename(dr))
        # Get the overall progress status
        statusprint('- Finished processing folder: '+ os.path.basename(dr)+'\n')
        processed_folders = processed_folders + 1    
        main_percent = round((float(processed_folders)/F)*100,2)   
        statusprint('- Number processed folders: '+str(processed_folders)+', of total: '+str(F)+'   Total progress:'+ str(main_percent) +'%\n'),

