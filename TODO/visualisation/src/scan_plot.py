import sys, os, argparse, yaml
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# helper classes, import from same directory
from parameters import A, M, NP
from summarystats import SummaryStats
from plots1 import Plot, Boxplot

def plt_timeseries( df, param ):
    print param
    for key in param.keys():
        print param[key]['plot_legend']


    P = SummaryStats(df, 2)   
    summary_type = {'mean': P.mean, 'median': P.median, 'upper_quartile': P.upper_quartile,'lower_quartile': P.lower_quartile,'custom_quantile': P.custom_quantile,'minimum': P.minimum,'maximum': P.maximum}    
    
    n = 5 # number of datapoints for x-axis
    step = 4 # minor axis number of values
    # instantiate a plot class with desired output (One, Many)
    Fig = Plot(summary_type['mean'](), 'one', param) # first argument is one option selected from summary_type dict above
    # Calling the plot class instance with the desired kind of plot  
    Fig.timeseries( n, step, 2)


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







with open("plot_config.yaml", 'r') as stream:
    try:
        param = yaml.load(stream)
    except yaml.YAMLError as exc:
        print(exc)

for key, value in param.iteritems():           
    print param[key]['plot_type']
    #print value    






if __name__ == "__main__":
    store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')    
    d = pd.DataFrame()
    df_list =[]
    for key in store.keys():
        sets_runs = process_hdf_keys(key)        
        s = sets_runs[0]
        r = sets_runs[1]        
        pnl = store.select(key)        
        df = pnl.to_frame()
        df['set'] = s
        df['run'] = r
        df.set_index('run', append = True, inplace = True)
        df.set_index('set', append = True, inplace = True)
        df_list.append(df.reorder_levels(['set', 'run', 'major', 'minor']))    
    d = pd.concat(df_list)   
    del df_list
                                            
filtered_df = d.iloc[(d.index.get_level_values('set') == 1) & (d.index.get_level_values('run') <= 2) & (d.index.get_level_values('major') <= 6100) & (d.index.get_level_values('minor') <= 3 )]['total_credit'].astype(float)

plot_function = {'timeseries': plt_timeseries}

plot_function['timeseries'](filtered_df, param)
                
store.close()

