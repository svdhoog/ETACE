from parameters import NP
#from summarystats import SummaryStats
from timeseries import Timeseries

class Plot(NP):
    def __init__(self, data, num_plots):
        self.__data = data
        self.__num_plots = num_plots
    
    
    def timeseries(self):
        T = Timeseries(self.__data,self.__num_plots)      
        single_plot = lambda : T.single_output()
        multiple_plot = lambda : T.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot} 
        return options[self.__num_plots]()
