#import sys
#import numpy as np
#import matplotlib.pyplot as plt
from parameters import NP, A
#from summarystats import SummaryStats
from timeseries import Timeseries
from boxplot import Boxplot
from histogram import Histogram

class Plot(NP):
    def __init__(self, data, n_plots):
        self.__data = data
        self.__n_plots = n_plots    
        
    def timeseries( self, n, step, analysis_type ):   
        n_plot_values = {'one' : NP.one, 'many' : NP.many} 
        num_plots = n_plot_values[self.__n_plots]        
        T = Timeseries(self.__data, num_plots, n, step, analysis_type)      
        one_plot = lambda : T.one_output()
        many_plot = lambda : T.many_output()        
        options = {NP.one : one_plot, NP.many : many_plot}        
        return options[num_plots]()


    def histogram( self, n ):   
        n_plot_values = {'one' : NP.one, 'many' : NP.many} 
        num_plots = n_plot_values[self.__n_plots]        
        H = Histogram(self.__data, num_plots, n)      
        one_plot = lambda : H.one_output()
        many_plot = lambda : H.many_output()        
        options = {NP.one : one_plot, NP.many : many_plot}        
        return options[num_plots]()


    def boxplot(self):
        B = Boxplot(self.__data,num_plots,self.__analysis_type)      
        one_plot = lambda : B.one_output()
        many_plot = lambda : B.many_output()        
        options = {NP.one : one_plot, NP.many : many_plot} 
        return options[num_plots]()



