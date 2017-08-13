from parameters import NP, A, Plot_configuration
from summarystats import SummaryStats
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')
import matplotlib.cm as cm

class Plot(NP):  # TODO: remove NP here, inheritance usless for this class
    def __init__(self, idx, data):
        self.idx = idx
        self.__data = data
        self.__P = Plot_configuration()

    def num_plot_mapper(self, val, obj):
        one_plot = lambda: obj.one_output()
        many_plot = lambda: obj.many_output()
        options = {'one': one_plot, 'many': many_plot}
        return options[val]()

    def histogram(self, main_param, outpath):
        H = Histogram(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), H)



class Histogram():

    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.__data = data
        self.outpath = outpath          
        #self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        self.summary = main_param['summary']
        if self.__analysistype == A.agent and self.summary  == 'custom_quantile':
            print ">> Quantile not possible for agent level analysis!"
            sys.exit(1) 
            


        print "main data received from summary module to histogram module: "
        print self.__data.tail(5) 

    def map_analysis(self, val):             
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
        return analysis_values[val] 


    def plot_histogram(self, ax, data, label, colors, n_bins = 50):
        #self.__data.hist(bins = 50)        
        if self.__P.legend_label(self.idx) is None:      
            le_label = label
        else:
            le_label = self.__P.legend_label(self.idx)
        out = ax.hist(data, n_bins, normed=1, histtype='bar', color=colors, label=le_label)   
        # out = ax.hist(data, n_bins, histtype='step', stacked=True, fill=False)  
        if self.__P.legend(self.idx) is True:
            plt.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        ax.set_title('different world views')
        return out


    def one_output(self):
        file_count = 0
        step = 1
        if self.summary == 'custom_quantile':
            step = 2
        
        for col in range(0, len(self.__data.columns), step): # one variable, one case at a time 
            if self.summary == 'custom_quantile':
                dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy().dropna() # hist method does not support NaN            
            else:
                dframe = pd.DataFrame(self.__data[self.__data.columns[col]]).dropna() 

            self.__N = len(dframe.index.get_level_values('major').unique())
                        
            legend_label = dframe.columns
            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()
                fig, ax = plt.subplots()                              
                for m in minor_index:
                    D = dframe.xs(int(m), level='minor')                    
                    if len(D.columns) == 2:  # TODO: this check done in class constructor, so no need
                        print "Quantile not possible for agent level analysis!"
                        sys.exit(1)                        
                    else: 
                        y = []                        
                        for l in range(0, len(D), self.__N):
                            y.append(np.array(D[l:l+self.__N]))
                        colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)/self.__N)))
                        for r in range(0, len(y)):
                            clr = next(colors)
                            self.plot_histogram(ax, y[r], legend_label[0]+'_run_'+str(r)+'_inst_'+str(m), clr, 50)                                                      
                plot_name = self.__P.plot_name(self.idx)           
                plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0])+".png", bbox_inches='tight')
                plt.close()

            else:
                fig, ax = plt.subplots()
                if len(dframe.columns) == 2:
                    y1 = []
                    y2 = []
                    col_A = dframe[dframe.columns[0]] 
                    col_B = dframe[dframe.columns[1]]
                    
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    colors = iter(cm.rainbow(np.random.uniform(0, 1, size = 4*len(dframe)/self.__N)))
                    for r in range(0, len(y1)): # TODO: y1 and y2 length must not be different, add a check
                        clr = next(colors)
                        self.plot_histogram(ax, y1[r], legend_label[0]+'_inst_'+str(r), clr, 50) 
                        clr = next(colors)
                        self.plot_histogram(ax, y2[r], legend_label[1]+'_inst_'+str(r), clr, 50) 
                    plot_name = self.__P.plot_name(self.idx)           
                    plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                    plt.close()
                else:
                    y1 = []
                    col_A = dframe[dframe.columns[0]]
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                    colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)/self.__N)))
                    for r in range(0, len(dframe)/self.__N):
                        clr = next(colors)
                        self.plot_histogram(ax, y1[r], legend_label[0]+'_inst_'+str(r), clr, 50)
         
                    plot_name = self.__P.plot_name(self.idx) 
                    plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + ".png", bbox_inches='tight')          
                    plt.close()
            file_count = file_count + 1        



    def many_output(self): ####TODO### 
        # TODO
    
    
