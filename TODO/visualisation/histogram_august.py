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
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        print "main data received from summary module to scatterplot module: "
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
        out = ax.hist(data, n_bins, normed=1, histtype='bar', color=colors, label=colors)   
        # out = ax.hist(data, n_bins, histtype='step', stacked=True, fill=False)  
        if self.__P.legend(self.idx) is True:
            plt.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        ax.set_title('different world views')
        return out

    def one_output(self):
        #colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)/self.__N)))
        colors = iter(['red'])
        fig, ax = plt.subplots()
        clr = next(colors)
        print "Euta gaun thiyo, khusiyali thiyo"
        self.plot_histogram(ax, self.__data['equity'].dropna(), 'lau', clr, 52)
        plt.savefig('histogram_main.png', bbox_inches='tight')
        plt.close()



    def many_output(self): ####TODO### 
        return
        y =[]
        for i in range(0,len(self.__data),self.__N):
            y.append(np.array(self.__data[i:i+self.__N]))
        for i in range(0,len(self.__data)/self.__N):
            hist, bins = np.histogram(y[i],bins = 50)
            width = 0.7 * (bins[1] - bins[0])
            center = (bins[:-1] + bins[1:]) / 2
            plt.bar(center, hist, align='center', width=width)
            #plt.show()
            #plt.plot(x,y[i])
            plot_name = "histogram_"+str(i)+".png"
            plt.savefig(plot_name, bbox_inches='tight')	 
            
            # plt.show() # reset the plot, but gives output in display
            # So, alternatively:
            # plt.cla() # clear current axes
            plt.clf() # clear current figure
            # plt.close() # close the whole plot
        plt.close()    
    
    
