#!/usr/bin/env python
import sys, os, argparse, yaml
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# helper classes, import from same directory
from parameters import A, M, NP
from summarystats import SummaryStats
from plots import Plot, Boxplot

config_fname = 'config1.yaml'

def erf(msg):
    print " >> Error: %s" % msg
    sys.exit()

# Function to parse input parameters from the config file
def get_parameters():
    try:
        f = open(config_fname, 'r')
    except IOError:
        erf("unable to read file: %s" % config_fname)

    with f as stream:
        try:
            p = yaml.load(stream)
        except yaml.YAMLError, exc: # error-check for incorrect yaml syntax
            if hasattr(exc, 'problem_mark'):
                mark = exc.problem_mark
                print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, config_fname)
            else:
                print " >> Unknown problem with %s file:" % config_fname
            sys.exit()
        return p                


# Function to process the parsed config file values to make them usable
def process_parameters(p): 
    indices = ['set','run','major','minor']    
    for i in indices:
        if 'range' in str(p[i][0]):  # check if range defined in input
            x = p[i][1]
            try:              
                if len(x)<3: x.append(1) # for some cases, add default stepsize of one
                p[i] = range(x[0],x[1]+x[2],x[2]) # include last value, to make range of yaml file inclusive
            except:
                raise AssertionError("In file %s: range expects a list, single value given instead" % config_fname)
    return p


def process_hdf_keys( string_in ): # extract set and run values from set_*_run_* string
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    tmp_string = string_in.replace('_run_', ',')        
    string_out = find_between(tmp_string,"/set_","_iters")
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
    return list([operator,int(string_out)])




def map_analysis(val): # map analysis type from user input to parameter class             
    analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
    return analysis_values[val]  


# Function that calls the timeseries plot
def plt_timeseries( df, param ):
    # instantiate a class with desired analysis type
    P = SummaryStats(df, map_analysis(param['analysis']))
    # then call the desired method, if no plot wanted   
    summary_type = {'mean': P.mean, 'median': P.median, 'upper_quartile': P.upper_quartile,'lower_quartile': P.lower_quartile,'custom_quantile': P.custom_quantile,'minimum': P.minimum,'maximum': P.maximum}    
    
    n = len(param['major']) # number of datapoints for x-axis
    step = len(param['minor'])
    # instantiate a plot class with desired output (One, Many)
    Fig = Plot(summary_type[param['summary']](), param['plot properties']['number_plots']) # first argument is one option selected from summary_type dict above
    # Calling the plot class instance with the desired kind of plot
    Fig.timeseries( n, step, map_analysis(param['analysis']))


# Function that calls the boxplot
def plt_boxplot( df, param ):  
    n = len(param['major']) # *len(param['minor']) # number of rows of dataframe including minor (special case for boxplot)    
    # instantiate a boxplot class
    Fig = Boxplot(df, n, param['plot properties']['number_plots'], param['analysis'])  

    # call the appropriate method within the class
    Fig.plot()


# Function that calls the timeseries plot
def plt_histogram( df, param ):

    # instantiate a class with desired analysis type
    P = SummaryStats(df, map_analysis(param['analysis']))

    # then call the desired method, if no plot wanted   
    summary_type = {'mean': P.mean, 'median': P.median, 'upper_quartile': P.upper_quartile,'lower_quartile': P.lower_quartile,'custom_quantile': P.custom_quantile,'minimum': P.minimum,'maximum': P.maximum}    
    
    n = len(param['major']) # number of datapoints for x-axis
    
    # instantiate a plot class with desired output (One, Many)
    Fig = Plot(summary_type[param['summary']](), param['plot properties']['number_plots']) # first argument is one option selected from summary_type dict above

    # Calling the plot class instance with the desired kind of plot
    Fig.histogram( n )


if __name__ == "__main__":
    # Opening the store to get the HDF file for Agent-type
    #store = pd.io.pytables.HDFStore('/home/etaceguest/Krishna/visualisation_test/Data/correct_data/agent_separated/ClearingHouse.h5')
    store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')    
    #print store
    # Main dataframe to hold all the dataframes of each instance    
    d = pd.DataFrame()
    # Going through sets and runs in the HDF file
    df_list =[]
    for key in store.keys():
        # getting set and run values from the names: set_1_run_1_iters etc. hardcoded atm
        sets_runs = process_hdf_keys(key)        
        s = sets_runs[0]
        r = sets_runs[1]
        # Opening Panel the particular set and run        
        pnl = store.select(key)
        #print pnl
        # Converting panel to Dataframe        
        df = pnl.to_frame()
        #print df.head(3)
        # Adding two columns for set and run into the dataframe for two added level of indexing  
        df['set'] = s
        df['run'] = r
        df.set_index('run', append = True, inplace = True)
        df.set_index('set', append = True, inplace = True)
        df_list.append(df.reorder_levels(['set', 'run', 'major', 'minor']))
        #del df
        
    # Adding each of the dataframe from panel into a main dataframe which has all the sets  and runs        
    d = pd.concat(df_list)   
    del df_list
    # Read the desired input parameters

##########################################################################################################################################################################
#    x = get_parameters()  
#    for key in x.keys():
#        x_plt = x[key] 
#        param = process_parameters(x_plt)
        #print param['variables']
#        filtered = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][param['variables']].dropna().astype(float)
        
        # filtered = filtered[(filtered[param['variables']] >= 700)].dropna() # use this to filter variables based on range
############################################################################################################################################################################

    x = get_parameters()
    for idx in x.keys():
        if idx not in'i/o':
            inner_d = x[idx]
                    
            for key in inner_d.keys():
                print key
                
                d_plt = inner_d[key] 
                param = process_parameters(d_plt)        
                var_dic = {}
                var_list =[]
                for k in param['variables'].keys():
                    var_list.append(param['variables'][k][0])
                    if len(param['variables'][k])>1:
                        var_filter_list = []
                        for i in range(1,len(param['variables'][k])):
                            var_filter_list.append(process_string(param['variables'][k][i]))
                        var_dic[param['variables'][k][0]] = var_filter_list
                    else:
                        var_dic[param['variables'][k][0]] = []                
                
                filtered = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][var_list].dropna().astype(float)                
                # call the filtering part here, and then clear the dict
                #print var_dic # var dict has now the mapping and the filtering as a list
                var_dic.clear()
  

##################################################################################################################################################################################     
                plot_function = {'timeseries': plt_timeseries, 'boxplot': plt_boxplot, 'histogram':plt_histogram} #dictionary of desired functions
                
                # calling appropriate function based on read-in key from config file
                # also passing in the filtered dataframe to the function at the same time 
                plot_function[key](d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][var_list].dropna().astype(float), param) # need to cast df to float
            
    store.close()
