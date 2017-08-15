from parameters import NP, A, Plot_configuration
from summarystats import SummaryStats
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')
import matplotlib.cm as cm


class Plot():
    def __init__(self, idx, data, par_fpath):
        self.idx = idx
        self.__data = data
        self.__P = Plot_configuration(par_fpath)

    def num_plot_mapper(self, val, obj):
        one_plot = lambda: obj.one_output()
        many_plot = lambda: obj.many_output()
        options = {'one': one_plot, 'many': many_plot}
        return options[val]()

    def boxplot(self, main_param, outpath):
        B = Boxplot(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), B)


class Boxplot(NP, A):
    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx 
        self.__data = data
        self.__P = plt_config
        self.__main_param = main_param
        self.outpath = outpath 
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
              
    def map_analysis(self, val):             
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
        return analysis_values[val] 
        
    def process_boxplot_data(self, data):
        s = SummaryStats(data, self.__main_param) 
        box_df = pd.DataFrame()
        #print s.mean().values
        box_df['mean'] = s.mean()
        box_df['median'] = s.median()
        box_df['upper_quartile'] = s.upper_quartile()
        box_df['lower_quartile'] = s.lower_quartile()
        box_df['max'] = s.maximum()
        box_df['min'] = s.minimum()
        return box_df

    def plot_boxplot(self, ax, data, l_label):
        print l_label
        if self.__P.legend_label(self.idx) is None:      
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)

        t_df = data.T 
        ax = t_df.boxplot(column = [100,250,500,750,900], positions =[1,2,3,4,5]) 
        ax.set_title(l_label)
        ax.set_xlabel('xlabel')
        ax.set_ylabel('ylabel')
        return ax            

    def one_output(self):
        for col in range(0, len(self.__data.columns)):
            dframe = pd.DataFrame(self.__data[self.__data.columns[col]])
            fig, ax = plt.subplots()
            if self.__analysistype == A.agent:
                print "Boxplot not possible for agent-level analysis!"
                sys.exit(1)
            else:                
                col_A = dframe[dframe.columns[0]]
                D = self.process_boxplot_data(col_A)
                y = []
                for i in range(0, len(D), self.__N):                    
                    y.append(pd.DataFrame(D[i:i+self.__N]))
                for r in range(0, len(D)/self.__N):
                    self.plot_boxplot(ax, y[r], self.__data.columns[col])
                   
                plot_name = self.__P.plot_name(self.idx) 
                plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(self.__data.columns[col]) + ".png", bbox_inches='tight')          
                plt.close()




          
