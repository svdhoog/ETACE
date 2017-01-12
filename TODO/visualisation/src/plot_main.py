from parameters import NP
#from summarystats import SummaryStats
from timeseries import Timeseries
from boxplot import Boxplot


class Plot(NP):
    def __init__(self, data, num_plots):
        self.__data = data
        self.__num_plots = num_plots    
    
    def timeseries(self):
        # Getting the sixe of x-axis values for timeseries plot based on number of rows in the input dataframe      
        N = len(self.__data.index)
        T = Timeseries(self.__data,self.__num_plots, N)      
        single_plot = lambda : T.single_output()
        multiple_plot = lambda : T.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot} 
        return options[self.__num_plots]()

    def boxplot(self):
        B = Boxplot(self.__data,self.__num_plots,self.__analysis_type)      
        single_plot = lambda : B.single_output()
        multiple_plot = lambda : B.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot} 
        return options[self.__num_plots]()
