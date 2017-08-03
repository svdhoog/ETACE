#!/usr/bin/env python
import sys, os, argparse, operator
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# helper classes, imported from same directory
from parameters import A, main_configuration
from summarystats import SummaryStats
from plots import Plot
from transform import Transform

def erf(msg): # function to output the error message and exit
    print " >> Error: %s" % msg
    sys.exit()

def process_hdf_keys( string_in ): # Function to extract set and run values from set_*_run_* string 
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    tmp_string = string_in.replace('_run_', ',')        
    string_out = find_between(tmp_string,"/set_","_iters")    #TODO: trailing slash might cause error, so before passing on check if trailing slash present, if yes remove
    return list(map(int, string_out.split(',')))

def process_string( string_in ):
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    operator = string_in.partition("[")[0]
    string_out = find_between(string_in,"[","]")
    return list([operator,float(string_out)])

def map_analysis(val): # map analysis type from user input to parameter class             
    analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
    return analysis_values[val]  


def filter_by_value(dkey, dval, filtered): # Function to filter the variables based on values      
    if dval is not None:
        count = 0
        index = dkey
        df = pd.DataFrame(filtered[index])        
        while count < len(dval):
            options = {'>' : operator.gt, '<' : operator.lt, '>=' : operator.ge, '<=' : operator.le, '==' : operator.eq} #operator.gt(a,b) :compare a&b, return all a larger than b        
            val = str(dval[count][0])
            #df = df[options[val](filtered[index],dval[count][1])].dropna()
            df = df[options[val](filtered[index],dval[count][1])]
            count = count + 1
        return df
    else:
        df = pd.DataFrame(filtered[dkey]) 
        return df  


# Function to bridge other classes (summarystats, transform, and plot)
##def summary_and_plot(idx, key, df, param, outpath): # idx = plot no, key = plot type, df = data, param = parameter from yaml, outpath = output folder

def summary_and_plot (idx, P, df):
    param = P.get_parameters()[idx]
    key = P.get_plotname_by_idx(idx)
    outpath = P.output_fpath()
   
    if 'summary' in param.keys(): # If summary specified, compute summary-statistics
        P = SummaryStats(df, param) # instantiate summary class
        data = P.compute_summary() # compute summary
    else:
        data = df   
    #TODO: add a boxplot check, and assign only for other cases, except boxplot, to save memory         

    def plt_timeseries():
        T = Plot(idx, data) # instantiate a plot object, idx = plot id, data = df
        T.timeseries(param, outpath) # call timeseries method, param = parameters from main yaml, outpath = where to save output plot
        
    def plt_boxplot():   
        B = Plot(idx, df) # for boxplot whole df passed, not the one with summary
        B.boxplot(param, outpath) 
        
    def plt_scatterplot():        
        S = Plot(idx, data) 
        S.scatterplot(param, outpath) 

    def plt_histogram():
        H = Plot(idx, data)
        H.histogram(param, outpath)

    def var_transform():
        Tf = Transform(idx, data)
        Tf.main_method()
    
    plot_function = {'timeseries': plt_timeseries, 'boxplot': plt_boxplot, 'histogram':plt_histogram, 'scatterplot':plt_scatterplot, 'transform':var_transform} 
    return plot_function[key]()                


if __name__ == "__main__":

    P = main_configuration() # instantiate main_configuration class to process main yaml files
    inpath = P.input_fpath()
    
    agent_storelist = {} # all the agent HDF files are stored in this dict
    for key, value in inpath.iteritems():        
        agent_storelist[key] = pd.io.pytables.HDFStore(value) 

    agent_dframes = {} # All the main dataframes of different agenttypes are stored in this dict
    
    for agentname, agentstore in agent_storelist.iteritems():           
        d = pd.DataFrame() # Main dataframe to hold all the dataframes of each instance (one agenttype)        
        df_list =[]
        for key in agentstore.keys(): # go through sets and runs in the HDF file            
            sets_runs = process_hdf_keys(key) # get set and run values from the names: set_1_run_1_iters etc. hardcoded for set_*_run_*_iters atm       
            s = sets_runs[0]
            r = sets_runs[1]                   
            pnl = agentstore.select(key) # open datapanel for particular set and run                    
            df = pnl.to_frame() # convert panel to Dataframe 
            # Add two columns for set and run into the dataframe for two added level of indexing  
            df['set'] = s
            df['run'] = r
            df.set_index('run', append = True, inplace = True)
            df.set_index('set', append = True, inplace = True)
            df_list.append(df.reorder_levels(['set', 'run', 'major', 'minor']))
                  
        d = pd.concat(df_list) # Add each dataframe from panel into a main dataframe containing all sets and runs    
        del df_list
        agent_dframes[agentname] = d # this dict contains agent-type names as keys, and the corresponding dataframes as values
        agentstore.close()
    del agent_storelist
        
    for idx, param in P.get_parameters().items(): # read filter conditions from yaml
        frames = []  # list to store filtered dfs according to vars   
        var_dic = {}
        for i, j in param['variables'].items():
            if len(j)>1:
                var_filter_list = []
                for s in range(1,len(j)):
                    var_filter_list.append(process_string(j[s]))
                var_dic[j[0]] = var_filter_list
            else:
                var_dic[j[0]] = None
            var_list = var_dic.keys()                       
        d = agent_dframes[param['agent']] #comment: this can be replaced in line below to save memory, here now just for simplicity 
        
        filtered = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][var_list].dropna().astype(float) # stage-I filtering, all input vars are sliced with desired set & run values             
        
        df_main = pd.DataFrame()        
        for dkey, dval in var_dic.iteritems(): 
            df = filter_by_value(dkey, dval, filtered) # stage-II filtering for selecting variables according to their values            
            
            if df_main.empty:
                df_main = df
            else:
                df_main = pd.concat([df_main,df], axis = 1)
            del df      
        summary_and_plot(idx, P, df_main) # plot index, parameter object, data                                                      
        var_dic.clear() # clear dict of mapping between plot var and operator (for next cycle)
        del var_list[:] # clear the list of variables for next cycle


###################################################################################################################################
# TODO: add support for multiple agenttypes within a single plot, new entry in yaml (replace agent with, agent1, agent2), and parse  
# TODO: currently the filtering is done in two steps, find a way to do it in a single step
# TODO: create output folder if not present for the output
