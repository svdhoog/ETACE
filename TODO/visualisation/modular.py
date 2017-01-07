#!/usr/bin/env python
import sys, os, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import operator

class A:
    # Types of analysis
    single, batch, parameter, agent = range(4)
    # 0, 1, 2, 3

class ComputeMean:
    def __init__(self, data, analysis_type):
        self.__data = data
        self.__analysis_type = analysis_type
        self.compute
    def compute(self):        
        def single_analysis():
            return self.__data.groupby(level = ['set','run','major']).mean().dropna()
        def batch_analysis():
            return self.__data.groupby(level = ['set','run','major']).mean().dropna()
        def parameter_analysis():
            return self.__data.groupby(level = ['set','major']).mean().dropna()
        def agent_analysis():
            return self.__data.groupby(level=['major']).mean().dropna()
        def error_input():
            print "No supplied analysis method detected. Check input, and try again!"
            sys.exit(1)
        options = {0 : single_analysis, 1 : batch_analysis, 2 : parameter_analysis, 3 : agent_analysis, 4 : error_input}
        return options[self.__analysis_type]()

        

def Mean_main(data, A):
    if A == 0:
        # single/ custom analyis # Note that this appears the same as batch analysis, but depends on the data received (should receive only a single run)
        f = data.groupby(level = ['set','run','major']).mean().dropna()
    elif A == 1:
        # batch analysis (per run) 
        f = data.groupby(level = ['set','run','major']).mean().dropna()
    elif A == 2:
        # parameter analysis (set)
        f = data.groupby(level = ['set','major']).mean().dropna()
    elif A == 3:
        # Individual agent analysis (per agent type)
        f = data.groupby(level=['major']).mean().dropna()
    else:
        print "No supplied analysis method detected. Check input, and try again!"
        sys.exit(1)
    return f

def statistical_summary(data, A):
    #S = Mean_main(data, A)
    so = ComputeMean(data, A)    
    print so.compute()
    #print S

#Main method
store = pd.io.pytables.HDFStore('./Bank/Bank.h5')
d = pd.DataFrame()
df_mean = []
for key in store.keys():
    if len(key) == 18:
        s = int(key[5:-12])
        r =int(key[11:-6])
    else:
        s = int(key[5:-13])
        r =int(key[11:-6])
    pnl = store.select(key)
    df = pnl.to_frame()  
    df['set'] = s
    df['run'] = r
    df.set_index('run', append = True, inplace = True)
    df.set_index('set', append = True, inplace = True)
    d_i = df.reorder_levels(['set', 'run', 'major', 'minor'])
    if d.empty:
        d = d_i
    else:   
        d = pd.concat([d,d_i], axis =0)
    d.index = pd.MultiIndex.from_tuples(d.index,names=['set','run','major','minor'])      
    del df,d_i   
     
filtered_df = d.iloc[(d.index.get_level_values('set') == 1) & (d.index.get_level_values('run') <= 2) & (d.index.get_level_values('major') <= 6100) & (d.index.get_level_values('minor') <= 2 )]['total_credit'].astype(float)

P = statistical_summary(filtered_df, A.agent)

store.close()
