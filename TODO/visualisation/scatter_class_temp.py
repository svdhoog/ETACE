from parameters import NP, A, Plot_configuration
from summarystats import SummaryStats
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')
import matplotlib.cm as cm


class Plot(): 
    def __init__(self, idx, data):
        self.idx = idx
        self.__data = data
        self.__P = Plot_configuration()

    def num_plot_mapper(self, val, obj):
        one_plot = lambda: obj.one_output()
        many_plot = lambda: obj.many_output()
        options = {'one': one_plot, 'many': many_plot}
        return options[val]()

    def scatterplot(self, main_param, outpath):
        S = Scatterplot(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), S)


class Scatterplot(A):
    
    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx  
        self.__data = data
        self.__P = plt_config
        self.outpath = outpath          
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.delay = main_param['delay']
        self.summary = main_param['summary']
        print "main data received from summary module to scatterplot module: "
        print self.__data.tail(5)        

        if self.delay is True:
            delayed_df = self.__data.shift(periods = 1, axis = 0)
            delayed_df.rename(columns=lambda x: x+ "_delay", inplace=True)
            D = pd.concat([self.__data, delayed_df], axis =1)            
            self.__data = D[list(sum(zip(self.__data.columns, delayed_df.columns), ()))]


    def map_analysis(self, val):             
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
        return analysis_values[val]                  


    def plot_scatterplot(self, ax, x, y, l_label, x_label, y_label, clr):
        
        if self.__P.legend_label(self.idx) is None:      
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)

        out = ax.scatter(x, y, linestyle=self.__P.linestyle(self.idx), marker=self.__P.marker(self.idx), 
        facecolor=self.__P.facecolors(self.idx), label=le_label, color=clr)
       
        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        plt.xlabel(x_label)
        plt.ylabel(y_label)
        return out


    def one_output(self):
        file_count = 0
        step = 2        
        for col in range(0, len(self.__data.columns), step):
            if len(self.__data.columns) < 2:
                print "Problem with data! Either set delay to True, or specify atleast two variables to plot!"                
                sys.exit(1)

            dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()
           
            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()                
                fig, ax = plt.subplots() # initialize figure
                colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)/self.__N)))
                for m in minor_index:
                    D = dframe.xs(int(m), level='minor')
                    legend_label = D.columns
                    if len(dframe.columns) != 2:
                        print "Something wrong with data, check and retry!"
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = D[D.columns[0]]
                    col_B = D[D.columns[1]]
                    for i in range(0, len(D), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    for r in range(0, len(D)/self.__N):
                        clr = next(colors)
                        self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+ ' vs '+legend_label[1]+' [inst'+str(m) + ' run' + str(r) + ']', legend_label[0], legend_label[1], clr )
                plot_name = self.__P.plot_name(self.idx)           
                plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                plt.close()

            else:
                fig, ax = plt.subplots() # initialize figure
                legend_label = dframe.columns
                if len(dframe.columns) != 2:
                    print "Something wrong with data, check and retry!"
                    sys.exit (1)
                y1 = []
                y2 = []
                col_A = dframe[dframe.columns[0]]
                col_B = dframe[dframe.columns[1]]                
                for i in range(0, len(dframe), self.__N):
                    y1.append(np.array(col_A[i:i+self.__N]))
                    y2.append(np.array(col_B[i:i+self.__N]))
                colors = iter(cm.rainbow(np.linspace(0, 1, len(y1))))
                for r in range(0, len(dframe)/self.__N):
                    clr = next(colors)
                    self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+' vs '+legend_label[1]+' [inst '+str(r) +']', legend_label[0], legend_label[1], clr)                
                plot_name = self.__P.plot_name(self.idx)           
                plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                plt.close()                
            file_count = file_count + 1
