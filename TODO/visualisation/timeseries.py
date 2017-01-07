#!/usr/bin/env python

import sys, os, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import operator
class A:
    # Types of analysis
    single, batch, parameter, agent = range(4)
    # 0, 1, 2, 4

class F:
    # Types of statistical summary
    mean, median, upper_quartile, lower_quartile, custom_quartile = range(5)
    # 0, 1, 2, 3, 4, 5

class NP:
    # Nature of Plots i.e. single output per analysis or multiple outputs per analysis
    single, multiple = range(2)



def statistical_summary(data, M, A):
    if M == 0: # 0 refers to mean in class F   
        S = Mean_main(data, A)    
           
    elif M == 1:  # 1 refers to median in class F
        S = Quantile_main(data, A, 0.50)   
        
    elif M == 2: # 2 refers to upper_quartile in class F   
        S = Quantile_main(data, A, 0.75) 
        
    elif M == 3:  # 3 refers to lower_quartile in class F
        S = Quantile_main(data, A, 0.25) 
       
    elif M == 4:  # 4 refers to custom_quartile in class F
        
        N = raw_input("Enter desired number of Quantiles. 1 for single quantile and 2 for both Upper and Lower quantile values : ")
        N = float(N)
        if N == 1:
            S = {}
            Q = raw_input("Input the desired quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            S['quantile'] = Quantile_main(data, A, float(Q)) # N is the custom value for Quantile that is needed
        elif N ==2:
            S = dict.fromkeys(['lower_q', 'upper_q'])
            Q1 = raw_input("Input the desired Lower quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            Q2 = raw_input("Input the desired Upper quantile. Input format: 0.XX, where XX is the numeric quantile value you want: ")
            S1 = Quantile_main(data, A, float(Q1)) # Q is the custom value for Quantile that is needed
            S['lower_q'] = S1
            S2 = Quantile_main(data, A, float(Q2))  
            S['upper_q'] = S2
        
        else:
            print "Unidentified input values. Check input, and try again!"
            sys.exit(1)
            
    else:
        print "No supplied summary method detected. Check input, and try again!"
        sys.exit(1)

    return S
        
def Quantile_main(data, A, val):
    if A == 0:
        # single/custom analysis
        f = data
        print "No quantiles posible for single-analysis. Returned the whole data set!"
    elif A == 1:
        # batch analysis (per run) 
        f = data.groupby(level = ['set','run','major']).quantile(val).dropna()
    elif A == 2:
        # parameter analysis (set)
        f = data.groupby(level = ['set','major']).quantile(val).dropna()
    elif A == 3:
        # Individual agent analysis (per agent type)
        f = data.groupby(level=['major']).quantile(val).dropna()
    else:
        print "No supplied analysis method detected. Check input, and try again!"
        sys.exit(1)    
    return f


def Mean_main(data, A):
    if A == 0:
        # single/ custom analyis
        f = data
        print "No mean posible for single-analysis. Returned the whole data set!"
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



def Plots_main(df, M, A, NP):
    N = 1000 # N is the number of points i.e 6020 to how much? i.e. 26000, generally 1000
    P = statistical_summary(df, M, A) # passing data, method to apply, and type of analysis
    if NP == 1:
        if M == 4: # Custom quartile needs two plots unlike the others so a separate method
            idx = P.keys()
            ##################################################################################
            #for i in idx:
            #    d = P[i]
            #    y =[]
            #    for j in range(0,len(d),N):
            #        y.append(np.array(d[j:j+N]))
            #    for j in range(0,len(d)/N):
            #        x = np.linspace(0, N, N, endpoint=True)
            #        fig = str(i)+str(j)
            #        fig = plt.figure()
            #        
            #        fig.plot(x,y[j])
            #        plt.hold(True)
            #for i in idx:
            #    for j in range(0,len(d)/N):
            #        fig = str(i)+str(j)
            #        fig = plt.figure()
            #        plot_name = str(n)+".png"
            #        
            #        fig.savefig(plot_name, bbox_inches='tight')	 
            #        plt.clf() 
            ###################################################################################
        else:
            y =[]
            for i in range(0,len(P),N):
                y.append(np.array(P[i:i+N]))
            for i in range(0,len(P)/N):
                x = np.linspace(0, N, N, endpoint=True)
                plt.plot(x,y[i])
                plot_name = str(i)+".png"
                plt.savefig(plot_name, bbox_inches='tight')	 
                # plt.show() # reset the plot, but gives output in display
                # So, alternatively:
                # plt.cla() # clear current axes
                plt.clf() # clear current figure
                # plt.close() # close the whole plot
        
    if NP == 0:
        if M == 4: # Custom quartile needs two plots unlike the others so a separate method
            idx = P.keys()
            for i in idx:
                d = P[i]
                y =[]
                for j in range(0,len(d),N):
                    y.append(np.array(d[j:j+N]))
                for j in range(0,len(d)/N):
                    x = np.linspace(0, N, N, endpoint=True)
                    plt.plot(x,y[j])          
                    plt.hold(True)	 
            plot_name = "summary_main.png"
            plt.savefig(plot_name, bbox_inches='tight')
            plt.show()              
        else:
            y =[]
            for i in range(0,len(P),N):
                y.append(np.array(P[i:i+N]))
            for i in range(0,len(P)/N):
                x = np.linspace(0, N, N, endpoint=True)
                plt.plot(x,y[i])          
                plt.hold(True)	 
            plt.savefig('summary_main.png', bbox_inches='tight')
            plt.show()





# Opening the store to get the HDF file for Agent-type
store = pd.io.pytables.HDFStore('./Bank/Bank.h5')


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
    
    # Deleting sub df's for garbage collection    
    del df,d_i
    
# Indexing the required row and column to get the results from the main dataframe
    
#filtered_df = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))]
       
filtered_df = d.iloc[(d.index.get_level_values('set') >= 1) & (d.index.get_level_values('run') <= 2) & (d.index.get_level_values('major') <= 26000) & (d.index.get_level_values('minor') <= 2 )]['total_credit'].astype(float)

#print filtered_df


Plots_main(filtered_df,F.mean,A.parameter,NP.single)


store.close()




#Hint for mean over a certain axis:

#http://stackoverflow.com/questions/24954117/advanced-averaging-with-multiindex-dataframe-in-pandas
# Transpose can also be used depending on cases


# Enum method

# http://stackoverflow.com/questions/702834/whats-the-common-practice-for-enums-in-python

