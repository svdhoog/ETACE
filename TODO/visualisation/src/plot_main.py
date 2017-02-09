import sys
import numpy as np
import matplotlib.pyplot as plt
from parameters import NP, A
#from summarystats import SummaryStats
#from timeseries import Timeseries
from boxplot import Boxplot
#from histogram import Histogram

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


class Timeseries(A):

    def __init__(self, data, num_plots, n, s, a):
        self.__data = data
        #print self.__data.head(10)
        self.__N = n
        self.__stepsize = s # stepsize not yet used, to be used for agent analysis
        self.__analysistype = a
                
    def many_output(self):
        if self.__analysistype == A.agent:
            print " -Warning: too many plots will be produced !!! " 
            count = 0                        
            for i in range(0,self.__stepsize):
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
            for i in range(0,self.__stepsize):
                D = self.__data.xs( int(i) , level='minor')                
	    for i in range(0,len(D),self.__N):	    
		y = np.array(D[i:i+self.__N])
		x = np.linspace(0, self.__N, self.__N, endpoint=True)
		plt.plot(x,y)
		plt.hold(True)
            plt.savefig('summary_main.png', bbox_inches='tight')
            plt.close()

        else:
            y =[]
            for i in range(0,len(self.__data),self.__N):
                y.append(np.array(self.__data[i:i+self.__N]))
            for i in range(0,len(self.__data)/self.__N):
                x = np.linspace(0, self.__N, self.__N, endpoint=True)
                plt.plot(x,y[i])          
                plt.hold(True)	 
            plt.savefig('summary_main.png', bbox_inches='tight')
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

