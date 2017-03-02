import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from parameters import NP, A
from summarystats import SummaryStats
from matplotlib.font_manager import FontProperties
#from timeseries import Timeseries
#from boxplot import Boxplot
#from histogram import Histogram

class Parameter_mapper():
    def __init__(self, param):
        self.__param = param
         
    def legend(self, key):
        return self.__param[key]['plot_legend']

    def plot_type(self, key):
        return self.__param[key]['plot_type']

    def num_plots(self, key):
        return self.__param[key]['number_plots']

    def y_label(self, key):
        return self.__param[key]['y-axis label']

    def x_label(self, key):
        return self.__param[key]['x-axis label']

    def plot_name(self, key):
        return self.__param[key]['plot_name']

    def llim(self, key):
        return self.__param[key]['l_lim']

    def ulim(self, key):
        return self.__param[key]['u_lim']

    
                      

class Plot(NP):
    def __init__(self, data, n_plots, parameter):
        self.__data = data
        #print self.__data
        self.__n_plots = n_plots
        self.__parameter = parameter
        P_M = Parameter_mapper(parameter) 
        print P_M.plot_name('plot2')   

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


class Timeseries(A):

    def __init__(self, data, num_plots, n, s, a):
        self.__data = data
        self.__N = n
        self.__analysistype = a
                
    def many_output(self):
        if self.__analysistype == A.agent:
            print " -Warning: too many plots will be produced !!! " 
            count = 0                        
            minor_index = self.__data.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe 
            for i in minor_index:
                D = self.__data.xs( int(i) , level='minor')    
                for i in range(0,len(D),self.__N):
                    y = np.array(D[i:i+self.__N])                
                    x = np.linspace(0, self.__N, self.__N, endpoint=True)
                    plt.plot(x,y)
                    plot_name = "timeseries_"+str(count)+".png"
                    plt.savefig(plot_name, bbox_inches='tight')
                    plt.close()
                    count = count + 1	                
        else:
            y =[]
            for i in range(0,len(self.__data),self.__N):
                y.append(np.array(self.__data[i:i+self.__N]))        
            for i in range(0,len(self.__data)/self.__N):
                x = np.linspace(0, self.__N, self.__N, endpoint=True)
                plt.plot(x,y[i])
                plot_name = "timeseries_"+str(i)+".png"
                plt.savefig(plot_name, bbox_inches='tight')	 
                
                # plt.show() # reset the plot, but gives output in display
                # So, alternatively:
                # plt.cla() # clear current axes
                plt.clf() # clear current figure
                # plt.close() # close the whole plot
            plt.close()    
    
    def one_output(self):
        if self.__analysistype == A.agent:
            print " -Warning: too many lines will be printed in a single plot !!! "
            minor_index = self.__data.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe 
            for i in minor_index:
            #for i in range(0,self.__stepsize):
                D = self.__data.xs( int(i) , level='minor')
                      
	        for i in range(0,len(D),self.__N):	    
		        y = np.array(D[i:i+self.__N])
		        x = np.linspace(0, self.__N, self.__N, endpoint=True)
		        plt.plot(x,y)
		        plt.hold(True)
                plt.savefig('summary_main.png', bbox_inches='tight')
                plt.close()

        else:
            print "yehi ta ho ni hainta?"
            y =[]
            for i in range(0,len(self.__data),self.__N):
                y.append(np.array(self.__data[i:i+self.__N]))
            count = 0
            for i in range(0,len(self.__data)/self.__N):
                x = np.linspace(0, self.__N, self.__N, endpoint=True)
                ########################################################################################################################    
                #plt.plot(x,y[i], label = 'monthly output', color = 'green', linestyle='dashed', marker='o', markerfacecolor = 'blue', markersize =12)          
                plt.hold(True)                
                #line1, = plt.plot(x,y[i],color = 'green', linestyle='solid', marker='o', markerfacecolor = 'green', markersize =9)
                #line2, = plt.plot(x,y[i],color = 'green', linestyle='dashed', marker='o', markerfacecolor = 'green', markersize =9)                         
                plt.plot(x,y[i],color = 'blue', linestyle='solid', marker='o', markerfacecolor = 'green', markersize =4, label = "plot "+str(count))                         
                count = count + 1
                #plt.legend((line1, line2), ('label1', 'label2'))
                #plt.legend(loc='best', fancybox=True, shadow=True) #alternative           
                
                #fontP = FontProperties()
                #fontP.set_size('small')
                #plt.legend([line1], "title", prop = fontP)                
    

                ########################################################################################################################
            plt.legend(loc='best', fancybox=True, shadow=True)             
            plt.savefig('summary_main1.png', bbox_inches='tight')
            plt.close()


class Histogram():

    def __init__(self, data, num_plots, n):
        self.__data = data
        self.__N = n

    def many_output(self): ####TODO###
        print "histogram multiple ma aaipugiyo"
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
    
    def one_output(self):
        self.__data.hist(bins = 50)
        plt.savefig('histogram_main.png', bbox_inches='tight')
        plt.close()


class Boxplot(NP, A):
    def __init__(self, data, n, n_plots, a_type):
        self.__data = data
        self.__N = n
        self.__a_type = a_type
        self.__n_plots = n_plots   

    def plot(self):
        n_plot_values = {'one' : NP.one, 'many' : NP.many} 
        num_plots = n_plot_values[self.__n_plots]
        one_plot = lambda : self.one_output()
        many_plot = lambda : self.many_output()        
        options = {NP.one : one_plot, NP.many : many_plot}        
        return options[num_plots]()

    def f_analysis(self):                
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}       
        return analysis_values[self.__a_type]       

    def one_output(self):
        s = SummaryStats(self.__data, self.f_analysis() )   
        box_df = pd.DataFrame()
        box_df['mean'] = [x for sublist in s.mean().values for x in sublist]  # [x for sublist in s.mean().values for x in sublist] done to flatten a 2D list to 1D so pandas accepts it
        # box_df['mean'] = s.mean() # this was the old simpler method which did not work once the config file variables was turned to a hierarchy with filters (bug in df, see for new patches)
        box_df['median'] = [x for sublist in s.median().values for x in sublist]
        box_df['upper_quartile'] = [x for sublist in s.upper_quartile().values for x in sublist]
        box_df['lower_quartile'] = [x for sublist in s.lower_quartile().values for x in sublist]
        box_df['max'] = [x for sublist in s.maximum().values for x in sublist]
        box_df['min'] = [x for sublist in s.minimum().values for x in sublist]

        bp = box_df.boxplot(column = ['min','median','mean','upper_quartile','lower_quartile','max'], positions =[1,3,4,5,2,6])
        # plt.hold(True)        
        plt.savefig('boxplot_main.png', bbox_inches='tight')  
        #plt.show()        
        plt.clf()


    def many_output(self):
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




###helpful pages:
# http://matplotlib.org/api/_as_gen/matplotlib.axes.Axes.plot.html#matplotlib.axes.Axes.plot

# legend outside the plot:
# http://stackoverflow.com/questions/4700614/how-to-put-the-legend-out-of-the-plot

