#!/usr/bin/env python
import sys, os, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import operator
import yaml

# Custom calsses written locally, import as needed
from parameters import A, M, NP
from summarystats import SummaryStats
from plot_main import Plot
from boxplot import Boxplot

# Function that gets user input parameters from the config file
def get_parameters():
    with open("config.yaml", 'r') as stream:
        try:
            #print(yaml.load(stream))
            d = yaml.load(stream)
            #print a.keys()
        except yaml.YAMLError as exc:
            print(exc)
    #print d['timeseries'] 
    return d                

# Function to process the parsed config file values to make them usable
def process_parsed_values(d): 
    indices = ['set','run','major','minor']    
    for i in indices:
        if 'range' in str(d[i][0]):
            x = d[i][1]
            if len(x)<2:
                #x.append(x[0]) # adds the same existing value as repetition, if only single value present in input, alterative to sys exit here
                print " -range not properly defined, check input and retry!"
                sys.exit(1)            
            if len(x)<3: x.append(1) 
            d[i] = range(x[0],x[1]+x[2],x[2])         
    return d

def process_hdf_keys( string_in ):
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

def f_analysis(val):                
    analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
    return analysis_values[val]  


# Function that calls the timeseries plot
def plt_timeseries( df, param ):
    # instantiate a class with desired analysis type
    P = SummaryStats(df, f_analysis(param['analysis']))
    # then call the desired method, if no plot wanted   
    summary_type = {'mean': P.mean, 'median': P.median, 'upper_quartile': P.upper_quartile,'lower_quartile': P.lower_quartile,'custom_quantile': P.custom_quantile,'minimum': P.minimum,'maximum': P.maximum}    
    
    n = len(param['major']) # number of datapoints for x-axis
    step = len(param['minor'])
    # instantiate a plot class with desired output (One, Many)
    Fig = Plot(summary_type[param['summary']](), param['plot properties']['number_plots']) # first argument is one option selected from summary_type dict above
    # Calling the plot class instance with the desired kind of plot
    Fig.timeseries( n, step, f_analysis(param['analysis']))


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
    P = SummaryStats(df, f_analysis(param['analysis']))

    # then call the desired method, if no plot wanted   
    summary_type = {'mean': P.mean, 'median': P.median, 'upper_quartile': P.upper_quartile,'lower_quartile': P.lower_quartile,'custom_quantile': P.custom_quantile,'minimum': P.minimum,'maximum': P.maximum}    
    
    n = len(param['major']) # number of datapoints for x-axis
    
    # instantiate a plot class with desired output (One, Many)
    Fig = Plot(summary_type[param['summary']](), param['plot properties']['number_plots']) # first argument is one option selected from summary_type dict above

    # Calling the plot class instance with the desired kind of plot
    Fig.histogram( n )


if __name__ == "__main__":
    # Opening the store to get the HDF file for Agent-type
    store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')
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

        # Converting panel to Dataframe        
        df = pnl.to_frame()

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
    x = get_parameters()  
    for key in x.keys():
        x_plt = x[key] 
        param = process_parsed_values(x_plt)
        
        plot_function = {'timeseries': plt_timeseries, 'boxplot': plt_boxplot, 'histogram':plt_histogram} #dictionary of desired functions
        # calling appropriate function based on read-in key from config file
        # also passing in the filtered dataframe to the function at the same time 
        plot_function[key](d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][param['variables']].dropna().astype(float), param) # need to cast df to float
    
    store.close()
