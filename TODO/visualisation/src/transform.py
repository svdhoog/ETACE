#!/usr/bin/env python
import sys, os
import yaml
import numpy as np
import pandas as pd


class transform_configuration():

    def __init__(self, in_fpath):
 
        self.transform_f = in_fpath + '/config_transform.yaml' # the main configuration file
        self.parsed_values = self.parse_yaml(self.transform_f)

    def erf(self, msg):  # function to output the error message and exit
        print " >> Error: %s" % msg
        sys.exit()

    def parse_yaml(self, fname):  # Function to parse input parameters from the main configuration file
        try:
            f = open(fname, 'r')
        except IOError:
            self.erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream)
            except yaml.YAMLError, exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname)
                else:
                    print " >> Unknown problem with %s file:" % fname
                sys.exit()
            return p
   
    def get_parameters(self, idx):
        inner_dic = self.parsed_values[idx]
        return inner_dic


class Transform():
    def __init__(self, idx, data, par_fpath):
        self.__idx = idx 
        self.__data = data
        self.P = transform_configuration(par_fpath)
        

    def main_method(self, outpath):            
        transform_function = {'q_o_q': self.q_o_q, 'q_o_q_ONE_CYCLE': self.q_o_q_ONE_CYCLE, 'm_o_m': self.m_o_m, 'm_o_m_ONE_CYCLE': self.m_o_m_ONE_CYCLE,'annual_P_I_T': self.annual_P_I_T}            
        fn = self.P.get_parameters(self.__idx)['aggregate']
        data_out = transform_function[self.P.get_parameters(self.__idx)['transform_function']](fn)
        
        f_out = self.P.get_parameters(self.__idx)['write_file']
        
        if f_out is True:
            data_out.to_hdf(str(outpath)+ '/' + str(self.P.get_parameters(self.__idx)['output_file_name']), 'ratite', mode = 'a', format = 'table')           

        return data_out



#TODO: Change the data in below functions with the data returned from get_parameters function above

    def q_o_q(self,fn): # method to print quaterly growth rate (quarter on quarter)
        variables = self.get_parameters()['variables']
        def mean():
            roll_mean = self.__data[variables.values()].rolling(window=3,min_periods=3).mean().dropna() # first get rolling window values with step 3 and initial buffer 3
            return roll_mean[::3].pct_change(4) # compute rate between values with a step size 4 
            
        def summation():
            roll_sum = self.__data[variables.values()].rolling(window=3,min_periods=3).sum().dropna()
            return roll_sum[::3].pct_change(4)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()


    def m_o_m(self,fn): # method to print monthly growth rate (month on month)
        variables = self.P.get_parameters(self.__idx)['variables']
        return self.P.__data[variables.values(self.__idx)].pct_change(12)


    def m_o_m_ONE_CYCLE(self,fn): # method to print monthly growth rate (month on month in one cycle)
        variables = self.P.get_parameters(self.__idx)['variables']
        return self.__data[variables.values()].pct_change(1)

    def annual_P_I_T(self,fn): # method to print annual growth rate, point in time. TODO: point in time not added yet
        variables = self.P.get_parameters(self.__idx)['variables']
        def mean():
            roll_mean = self.__data[variables.values()].rolling(window=12,min_periods=12).mean().dropna() # first get rolling window values with step 12 and initial buffer 12
            return (roll_mean[::12]).pct_change(1) # compute rate between values with a step size 1
               
        def summation():
            roll_sum = self.__data[variables.values()].rolling(window=12,min_periods=12).sum().dropna()
            return (roll_sum[::12]).pct_change(1)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()


    def q_o_q_ONE_CYCLE(self,fn): # method to print quaterly growth rate (quarter on quarter)
        variables = self.P.get_parameters(self.__idx)['variables']
        def mean():
            roll_mean = self.__data[variables.values()].rolling(window=3,min_periods=3).mean().dropna() # first get rolling window values with step 3 and initial buffer 3
            return roll_mean[::3].pct_change(1) # compute rate between values with a step size 4 
            
        def summation():
            roll_sum = self.__data[variables.values()].rolling(window=3,min_periods=3).sum().dropna()
            return roll_sum[::3].pct_change(1)
            
        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input    
        return f_mapper[fn]()



if __name__ == "__main__":

    C = transform_configuration('/home/susupta/Desktop/Fix_preprocess/visualize/src')
    print C.get_parameters()['variables']

    
