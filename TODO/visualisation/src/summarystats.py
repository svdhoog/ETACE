#!/usr/bin/env python
import sys, os
import numpy as np
import pandas as pd
from parameters import A # imported self written class from directory

class SummaryStats(A):
    def __init__(self, data, analysis_type):
        self.__data = data
        self.__analysis_type = analysis_type
        #self.__method_type = method_type

    def mean(self):
        agent_analysis = lambda : self.__data.groupby(level = ['set','run','major','minor']).mean().dropna()
        multiple_run_analysis = lambda : self.__data.groupby(level = ['set','run','major']).mean().dropna()
        multiple_batch_analysis = lambda : self.__data.groupby(level = ['set','major']).mean().dropna()
        multiple_set_analysis = lambda : self.__data.groupby(level=['major']).mean().dropna()

        options = {A.agent : agent_analysis, A.multiple_run : multiple_run_analysis, A.multiple_batch : multiple_batch_analysis, A.multiple_set : multiple_set_analysis}          
        return options[self.__analysis_type]()
    
    def quantile(self, val):
        agent_analysis = lambda : self.__data.groupby(level = ['set','run','major','minor']).quantile(val).dropna()
        multiple_run_analysis = lambda : self.__data.groupby(level = ['set','run','major']).quantile(val).dropna()
        multiple_batch_analysis = lambda : self.__data.groupby(level = ['set','major']).quantile(val).dropna()
        multiple_set_analysis = lambda : self.__data.groupby(level=['major']).quantile(val).dropna()
        
        options = {A.agent : agent_analysis, A.multiple_run : multiple_run_analysis, A.multiple_batch : multiple_batch_analysis, A.multiple_set : multiple_set_analysis}          
        return options[self.__analysis_type]()  
    
    def custom_quantile(self):
        try:
            N = float(raw_input("Enter desired number of Quantiles. 1 for single quantile and 2 for both Upper and Lower quantile values : "))
        except Exception:        
            print ("Unrecognized input. Check input and try again!")
            sys.exit(1)
                
        if N == 1:
            s = pd.DataFrame()
            try:
                Q = float(raw_input("Input the desired quantile. Input format: 0.XX, where XX is the numeric quantile value you want: "))
            except Exception:        
                print ("Unrecognized input. Check input and try again!")
                sys.exit(1)
            s = s.append(self.quantile(Q)) # N is the custom value for Quantile that is needed
            s.rename(columns = {list(s)[0]: "quantile ("+str(Q)+")"}, inplace = True)        
            return s
           
        elif N == 2:
            s1 = pd.DataFrame() # two df needed because df[xy] = z does not work as desired with multi-index
            s2 = pd.DataFrame()
            try:
                Q1 = float(raw_input("Input the desired Lower quantile. Input format: 0.XX, where XX is the numeric quantile value you want: "))
                Q2 = float(raw_input("Input the desired Upper quantile. Input format: 0.XX, where XX is the numeric quantile value you want: "))
            except Exception:        
                print ("Unrecognized input. Check input and try again!")
                sys.exit(1)
            
            s1 = s1.append(self.quantile(Q1)) # data frame for lower quantile
            s1.rename(columns = {list(s1)[0]: "lower_quantile ("+str(Q1)+")"}, inplace = True)

            s2 = s2.append(self.quantile(Q2)) # data frame for upper quantile
            s2.rename(columns = {list(s2)[0]: "upper_quantile ("+str(Q2)+")"}, inplace = True)

            return pd.concat([s1,s2], axis = 1)


    def maximum(self):
        agent_analysis = lambda : self.__data.groupby(level = ['set','run','major','minor']).max().dropna()
        multiple_run_analysis = lambda : self.__data.groupby(level = ['set','run','major']).max().dropna()
        multiple_batch_analysis = lambda : self.__data.groupby(level = ['set','major']).max().dropna()
        multiple_set_analysis = lambda : self.__data.groupby(level=['major']).max().dropna()

        options = {A.agent : agent_analysis, A.multiple_run : multiple_run_analysis, A.multiple_batch : multiple_batch_analysis, A.multiple_set : multiple_set_analysis}          
        return options[self.__analysis_type]() 

    def minimum(self):
        agent_analysis  = lambda : self.__data.groupby(level = ['set','run','major','minor']).min().dropna()
        multiple_run_analysis = lambda : self.__data.groupby(level = ['set','run','major']).min().dropna()
        multiple_batch_analysis = lambda : self.__data.groupby(level = ['set','major']).min().dropna()
        multiple_set_analysis = lambda : self.__data.groupby(level=['major']).min().dropna()
        
        options = {A.agent : agent_analysis, A.multiple_run : multiple_run_analysis, A.multiple_batch : multiple_batch_analysis, A.multiple_set : multiple_set_analysis}          
        return options[self.__analysis_type]() 

    def median(self):
        return self.quantile(0.50)

    def upper_quartile(self):
        return self.quantile(0.75)

    def lower_quartile(self):
        return self.quantile(0.25)
 

