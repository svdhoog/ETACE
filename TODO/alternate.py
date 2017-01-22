#!/usr/bin/env python
import sys, os, argparse
import numpy as np
import pandas as pd
      
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

# Start with the main part

store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')    
d = pd.DataFrame()
df_list =[]
for key in store.keys():
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
    del df

d = pd.concat(df_list)

#    # Adding each of the dataframe from panel into a main dataframe which has all the sets and runs        
#    if d.empty:
#        d = d_i
#    else:   
#        d = pd.concat([d,d_i], axis =0)
    # Some tweak to get the multiindex working again for the main df        
##d.index = pd.MultiIndex.from_tuples(d.index,names=['set','run','major','minor'])      
#del df,d_i   # Deleting sub df's for garbage collection  
print d['total_credit'].tail(20)   
store.close()
