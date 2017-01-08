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




