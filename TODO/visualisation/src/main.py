#!/usr/bin/env python
import sys, os, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import operator

from parameters import A, M, NP
from summarystats import SummaryStats
from plot_main import Plot


#def method(self):
#    options = {M.mean : mean, M.median : quantile(0.50), M.upper_quartile : quantile(0.75), M.lower_quartile : quantile(0.25), M.custom_quantile: custom_quantile, M.minimum : minimum, #M.maximum : maximum} 
#    return options[self.__analysis_type]()
    


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
#print P.mean()

# instantiate a plot class with desired output (Single, Multiple)
Fig = Plot(P.mean(), NP.single)
# Calling the plot class instance with the desired kind of plot
Fig.timeseries()


store.close()
