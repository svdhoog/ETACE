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

def process_parsed_values(d): 
    indices = ['set','run','major','minor']    
    for i in indices:
        if 'range' in str(d[i][0]):
            x = d[i][1]
            if len(x)<3: x.append(1) 
            d[i] = range(x[0],x[1],x[2])
    return d

def plt_timeseries(df):
    # instantiate a class with desired analysis type
    P = SummaryStats(df, A.agent)
    # then call the desired method, if no plot wanted
    # print P.mean() # options: mean, median, upper_quartile, lower_quartile, custom_quantile, minimum, maximum        
    # instantiate a plot class with desired output (Single, Multiple)
    Fig = Plot(P.mean(), NP.single) 
    # Calling the plot class instance with the desired kind of plot
    Fig.timeseries()

def plt_boxplot(df):        
    # instantiate a boxplot class
    Fig = Boxplot(df, NP.single, A.agent)  
    # call the appropriate method within the class
    Fig.single_output()


if __name__ == "__main__":
    # Opening the store to get the HDF file for Agent-type
    store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')
    # Main dataframe to hold all the dataframes of each instance    
    d = pd.DataFrame()
    df_mean = []
    # Going through sets and runs in the HDF file
    for key in store.keys():
        # getting set and run values from the names: set_1_run_1_iters etc. hardcoded atm
        if len(key) == 18:
            s = int(key[5:-12])
            r =int(key[11:-6])
        else:
            s = int(key[5:-13])
            r =int(key[11:-6])
        # Opening Panel the particular set and run        
        pnl = store.select(key)

        # Converting panel to Dataframe        
        df = pnl.to_frame()

        # Adding two columns for set and run into the dataframe for two added level of indexing  
        df['set'] = s
        df['run'] = r
        df.set_index('run', append = True, inplace = True)
        df.set_index('set', append = True, inplace = True)
        d_i = df.reorder_levels(['set', 'run', 'major', 'minor'])

        # Adding each of the dataframe from panel into a main dataframe which has all the sets and runs        
        if d.empty:
            d = d_i
        else:   
            d = pd.concat([d,d_i], axis =0)
        # Some tweak to get the multiindex working again for the main df        
        d.index = pd.MultiIndex.from_tuples(d.index,names=['set','run','major','minor'])      
        del df,d_i   # Deleting sub df's for garbage collection  

    # Read the desired input parameters
    x = get_parameters()  
    for key in x.keys():
        x_plt = x[key] 
        param = process_parsed_values(x_plt)
        # filter out the frame based on main parameters read from config file
        filtered_df = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))]

        df_plot = filtered_df[param['variables']] # choose the variables as defined in config file

        plot_function = {'timeseries': plt_timeseries, 'boxplot': plt_boxplot} #dictionary of desired functions
        # calling appropriate function based on read-in key from config file 
        plot_function[key](df_plot.astype(float))  # need to cast dataframe into float for some strange reason, need to look at it
    
    store.close()
