from parameters import NP
#from summarystats import SummaryStats
from timeseries import Timeseries
from boxplot import Boxplot
from histogram import Histogram

class Plot(NP):
    def __init__(self, data, n_plots):
        self.__data = data
        self.__n_plots = n_plots    
        
    def timeseries( self, n ):   
        n_plot_values = {'single' : NP.single, 'multiple' : NP.multiple} 
        num_plots = n_plot_values[self.__n_plots]        
        T = Timeseries(self.__data, num_plots, n)      
        single_plot = lambda : T.single_output()
        multiple_plot = lambda : T.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot}        
        return options[num_plots]()


    def histogram( self, n ):   
        n_plot_values = {'single' : NP.single, 'multiple' : NP.multiple} 
        num_plots = n_plot_values[self.__n_plots]        
        H = Histogram(self.__data, num_plots, n)      
        single_plot = lambda : H.single_output()
        multiple_plot = lambda : H.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot}        
        return options[num_plots]()


    def boxplot(self):
        B = Boxplot(self.__data,num_plots,self.__analysis_type)      
        single_plot = lambda : B.single_output()
        multiple_plot = lambda : B.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot} 
        return options[num_plots]()
