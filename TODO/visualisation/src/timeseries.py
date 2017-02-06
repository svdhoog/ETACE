import sys
import numpy as np
import matplotlib.pyplot as plt
from parameters import A

class Timeseries(A):

    def __init__(self, data, num_plots, n, s, a):
        self.__data = data
        self.__N = n
        self.__stepsize = s # stepsize not yet used, to be used for agent analysis
        self.__analysistype = a
                
    def many_output(self):
        if self.__analysistype == A.agent:
            print " -Warning: too many plots will be printed !!! "
            #print self.__data
            count = 0            
            for i in range(0,self.__stepsize):
                List = []
                for j in range(i,len(self.__data),self.__stepsize):
                    List.append(j)        
                    D = self.__data.ix[List]          
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
            #print y[0:5]        
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
            print "Quitting!! Reason: too many lines will be printed in a single plot, please choose wisely and retry"
            sys.exit(1)

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
