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

class M:
    # Types of statistical summary
    mean, median, upper_quartile, lower_quartile, custom_quantile, minimum, maximum = range(7)
    # 0, 1, 2, 3, 4, 5

class SummaryStats(A):
    def __init__(self, data, analysis_type):
        self.__data = data
        self.__analysis_type = analysis_type
        #self.__method_type = method_type
        #self.mean
 
    def mean(self):
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major']).mean().dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).mean().dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).mean().dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).mean().dropna()
        #error_input = lambda: [None, sys.stdout.write("Unexpected input value! Check again and retry... "), sys.exit(0)][0]

        #options = {0 : single_analysis, 1 : batch_analysis, 2 : parameter_analysis, 3 : agent_analysis, 4 : error_input} # error needs to be mapped later on
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
        return options[self.__analysis_type]()
    
    def quantile(self, val):
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major']).quantile(val).dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).quantile(val).dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).quantile(val).dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).quantile(val).dropna()
        
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
        return options[self.__analysis_type]()   
    
    def custom_quantile(self):
        N = raw_input("Enter desired number of Quantiles. 1 for single quantile and 2 for both Upper and Lower quantile values : ")
        N = float(N)
        if N == 1:
            S = {}
            Q = raw_input("Input the desired quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            S['quantile'] = quantile(self, float(Q)) # N is the custom value for Quantile that is needed
        elif N ==2:
            S = dict.fromkeys(['lower_q', 'upper_q'])
            Q1 = raw_input("Input the desired Lower quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            Q2 = raw_input("Input the desired Upper quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            S1 = quantile(self, float(Q1)) # Q is the custom value for Quantile that is needed
            S['lower_q'] = S1
            S2 = quantile(self, float(Q2))  
            S['upper_q'] = S2
        else:
            print "Unidentified input values. Check input, and try again!"
            sys.exit(1)
    def maximum(self):
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major']).max().dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).max().dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).max().dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).max().dropna()
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
        return options[self.__analysis_type]()

    def minimum(self):
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major']).min().dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).min().dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).min().dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).min().dropna()
        
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
        return options[self.__analysis_type]()










def method(self):
    options = {M.mean : mean, M.median : quantile(0.50), M.upper_quartile : quantile(0.75), M.lower_quartile : quantile(0.25), M.custom_quantile: custom_quantile, M.minimum : minimum, M.maximum : maximum} 
    return options[self.__analysis_type]()
    


#Main method
store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')
d = pd.DataFrame()
df_mean = []
for key in store.keys():
    #print key 
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


# instantiate a class with desired analysis type
P = SummaryStats(filtered_df, A.agent)
# then call the desired method
print P.mean()

store.close()
