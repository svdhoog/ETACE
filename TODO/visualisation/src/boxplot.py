import pandas as pd
import matplotlib.pyplot as plt
from parameters import NP, A

from summarystats import SummaryStats

class Boxplot(NP, A):
    def __init__(self, data, n, n_plots, a_type):
        self.__data = data
        self.__N = n
        self.__a_type = a_type
        self.__n_plots = n_plots       

    def plot(self):
        n_plot_values = {'single' : NP.single, 'multiple' : NP.multiple} 
        num_plots = n_plot_values[self.__n_plots]
        single_plot = lambda : self.single_output()
        multiple_plot = lambda : self.multiple_output()        
        options = {NP.single : single_plot, NP.multiple : multiple_plot}        
        return options[num_plots]()

    def f_analysis(self):                
        analysis_values = {'single' : A.single, 'batch' : A.batch, 'parameter' : A.parameter, 'agent' : A.agent}       
        return analysis_values[self.__a_type]          


    def single_output(self):
        s = SummaryStats(self.__data, self.f_analysis() )    
        box_df = pd.DataFrame()
        box_df['mean'] = s.mean()
        box_df['median'] = s.median()
        box_df['upper_quartile'] = s.upper_quartile()
        box_df['lower_quartile'] = s.lower_quartile()
        box_df['max'] = s.maximum()
        box_df['min'] = s.minimum()
        
        bp = box_df.boxplot(column = ['min','median','mean','upper_quartile','lower_quartile','max'], positions =[1,3,4,5,2,6])
        # plt.hold(True)        
        plt.savefig('boxplot_main.png', bbox_inches='tight')  
        #plt.show()        
        plt.clf()


    def multiple_output(self):
        s = SummaryStats(self.__data, self.f_analysis() )           
        box_df = pd.DataFrame()
        box_df['mean'] = s.mean()
        box_df['median'] = s.median()
        box_df['upper_quartile'] = s.upper_quartile()
        box_df['lower_quartile'] = s.lower_quartile()
        box_df['max'] = s.maximum()
        box_df['min'] = s.minimum()

        count = 0
        for i in range(0,len(box_df.index)/self.__N):                    
            tmp_df = box_df[count:count+self.__N]
            bp = tmp_df.boxplot(column = ['min','median','mean','upper_quartile','lower_quartile','max'], positions =[1,3,4,5,2,6])
            plot_name = "boxplot_"+str(i)+".png"        
            plt.savefig(plot_name, bbox_inches='tight')  
            plt.clf()           
            count = count + self.__N
        plt.close()

