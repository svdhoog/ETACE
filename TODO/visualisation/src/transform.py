#!/usr/bin/env python
import sys, os
import numpy as np
import pandas as pd

class Transform():
    def __init__(self, data):
        self.__data = data
        print self.__data
    
    def q_o_q(self,fn): # method to print quaterly growth rate (quarter on quarter)
        def mean():
            roll_mean = self.__data.rolling(window=3,min_periods=3).mean().dropna() # first get rolling window values with step 3 and initial buffer 3
            return roll_mean[::3].pct_change(4) # compute rate between values with a step size 4 
            
        def summation():
            roll_sum = self.__data.rolling(window=3,min_periods=3).sum().dropna()
            return roll_sum[::3].pct_change(4)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()




    def m_o_m(self): # method to print monthly growth rate (month on month)
        return self.__data.pct_change(12)


    def m_o_m_ONE_CYCLE(self): # method to print monthly growth rate (month on month in one cycle)
        return self.__data.pct_change(1)




    def annual_P_I_T(self,fn): # method to print annual growth rate, point in time. TODO: point in time not added yet
        def mean():
            roll_mean = self.__data.rolling(window=12,min_periods=12).mean().dropna() # first get rolling window values with step 12 and initial buffer 12
            return (roll_mean[::12]).pct_change(1) # compute rate between values with a step size 1
               
        def summation():
            roll_sum = self.__data.rolling(window=12,min_periods=12).sum().dropna()
            return (roll_sum[::12]).pct_change(1)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()



    def q_o_q_ONE_CYCLE(self,fn): # method to print quaterly growth rate (quarter on quarter)
        def mean():
            roll_mean = self.__data.rolling(window=3,min_periods=3).mean().dropna() # first get rolling window values with step 3 and initial buffer 3
            return roll_mean[::3].pct_change(1) # compute rate between values with a step size 4 
            
        def summation():
            roll_sum = self.__data.rolling(window=3,min_periods=3).sum().dropna()
            return roll_sum[::3].pct_change(1)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()


    
