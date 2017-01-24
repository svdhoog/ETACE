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
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major']).mean().dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).mean().dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).mean().dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).mean().dropna()
        #error_input = lambda: [None, sys.stdout.write("Unexpected input value! Check again and retry... "), sys.exit(0)][0]

        #options = {0 : single_analysis, 1 : batch_analysis, 2 : parameter_analysis, 3 : agent_analysis, 4 : error_input} # error needs to be mapped later on
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
        # print options[self.__analysis_type]()         
        return options[self.__analysis_type]()
    
    def quantile(self, val):
        single_analysis = lambda : self.__data.groupby(level = ['set','run','major','minor']).quantile(val).dropna()
        batch_analysis = lambda : self.__data.groupby(level = ['set','run','major']).quantile(val).dropna()
        parameter_analysis = lambda : self.__data.groupby(level = ['set','major']).quantile(val).dropna()
        agent_analysis = lambda : self.__data.groupby(level=['major']).quantile(val).dropna()
        
        options = {A.single : single_analysis, A.batch : batch_analysis, A.parameter : parameter_analysis, A.agent : agent_analysis} 
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
            return s.append(self.quantile(Q)) # N is the custom value for Quantile that is needed        
                       
        elif N == 2:
            s1 = pd.DataFrame()
            s2 = pd.DataFrame()
            try:
                Q1 = float(raw_input("Input the desired Lower quantile. Input format: 0.XX, where XX is the numeric quantile value you want: "))
                Q2 = float(raw_input("Input the desired Upper quantile. Input format: 0.XX, where XX is the numeric quantile value you want: "))
            except Exception:        
                print ("Unrecognized input. Check input and try again!")
                sys.exit(1)
            s1 = s1.append(self.quantile(Q1))
            s2 = s2.append(self.quantile(Q2))
            return pd.concat([s1,s2], axis = 1)


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

    def median(self):
        return self.quantile(0.50)

    def upper_quartile(self):
        return self.quantile(0.75)

    def lower_quartile(self):
        return self.quantile(0.25)
 

