#!/usr/bin/env python

###############################################################################################################
# Replaces specified function of the input file (main) with the same function from another input file (shadow), 
# and writes back to the main input file
#
# Usage: python replace_functions.py file1_name file2_name  
# file1_name = main file, file2_name = shadow file
#
###############################################################################################################

import os, sys, re, argparse, glob, errno
import lxml.etree as ET
from xml.dom import minidom
from xml.parsers.expat import ExpatError
from glob import glob as g

if len(sys.argv) < 4: # specify both filenames xml.c and shawdow_xml.c, the path and file name of the shadow_model.xml file
    print "replace_xml_functions.py:"
    print "       Replaces C functions in input file1 by functions with the same name in file2"
    print ""
    print "Usage: python replace_xml_functions.py [original xml.c file] [replacement xml.c file] [path to shadow model folder] [shadow model xml file]"
    print "Example: python replace_xml_functions.py xml.c shadow_xml.c path_to_shadow_model shadow_model.xml"
    print ""
    sys.exit(1)

# list of the functions to replace, currently a dummy list. A parser can be used to fill in this list from some other file (xml, txt), or the list can be added manually 
#list_functions = ["write_Eurostat_agent", "write_Firm_agent" ] # names may have starting delimiter "{", but not strictly necessary

def file_exist(fname):
    f = g(fname)
    if fname in f: return True
    else: return False

def get_node_text(node):
    if len(node.childNodes) != 1 or node.childNodes[0].nodeType != node.TEXT_NODE:
        error("getText() routine used on non-text XML node")
    return node.childNodes[0].data.strip()

def process_string( string_in, element ):
    def find_between( s, first, last ): # function to find the string between two supplied limits
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    string_out = find_between(string_in,element,"}") # currently, the first limit (including upto first delimiter {) is read from the list of functions above, and the last limit is simply "}". can be replaced as needed
    return string_out

def ProcessFile(element):           
    f_a = open(sys.argv[1], 'r')
    input_lines_a = f_a.read()
    
    #verboseprint ("Lines to replace:") 
    #verboseprint (process_string( input_lines_a, element ))
    
    f_a.close()
    
    f_b = open(sys.argv[2], 'r')
    input_lines_b = f_b.read()
    
    #verboseprint ("Lines to paste:")
    #verboseprint (process_string( input_lines_b , element ))
    
    f_b.close()

    # Replace the target string
    replaced_lines_a = input_lines_a.replace(process_string(input_lines_a, element), process_string( input_lines_b, element ))

    f_out = open(sys.argv[1], 'w')
    f_out.write(replaced_lines_a)
    f_out.close()

if __name__ == "__main__":

    # Setup for command line arguments
    parser = argparse.ArgumentParser(prog='replace_xml_functions.py', description='Replaces C functions in input file1 by functions with the same name in file2')
    parser.add_argument('file1', help='Name of original xml.c file, containing full code for the functions writeout_Agentname_agent()', nargs=1, type=str)
    parser.add_argument('file2', help='Name of shadow_xml.c file, containing replacement code for the functions writeout_Agentname_agent()', nargs=1, type=str)
    parser.add_argument('modelpath', help='Path to the folder of shadow model xml', nargs=1, type=str)
    parser.add_argument('shadowmodelfile', help='Name of the shadow model xml file', nargs=1, type=str)
    parser.add_argument('-v', '--verbose', help='Get the status of the intermediate processing steps', action='store_true')
    args = parser.parse_args()
    model = args.modelpath[0]+ '/' + args.shadowmodelfile[0]
    
    #Setup for verbose arguments
    if args.verbose:
        def verboseprint(*args):
            for arg in args:
                print arg,
            print 
    else:
        verboseprint = lambda *a: None 

    verboseprint ("Running replacements for XML writeout functions in xml.c") 

    # Check if the model xml file exists
    if not file_exist(model):
        error("- Model file (%s) does not exist" % model)
    else:
        verboseprint("- Found model file (%s)" % model)

    # Parse model_xml file to determine required agents
    verboseprint ("\n- Analysing model file\n")
    models = [model]
    list_functions =[]
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
            list_functions.append("write_"+aname+"_agent")  
        del(nodes)    
        del(dom)
    verboseprint ("- Parsing model file complete")    
    verboseprint ("- Replacement list:")
    for item in list_functions:
        print ("    "+item)

    #Processing per agent type
    for element in list_functions:    
        ProcessFile(element)    

    verboseprint ("Finished replacements") 
