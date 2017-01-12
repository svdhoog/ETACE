import numpy as np
import matplotlib.pyplot as plt

class Timeseries():

    def __init__(self, data, num_plots, n):
        self.__data = data
        self.__N = n
    def multiple_output(self):
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
    
    def single_output(self):
        y =[]
        for i in range(0,len(self.__data),self.__N):
            y.append(np.array(self.__data[i:i+self.__N]))
        for i in range(0,len(self.__data)/self.__N):
            x = np.linspace(0, self.__N, self.__N, endpoint=True)
            plt.plot(x,y[i])          
            plt.hold(True)	 
        plt.savefig('summary_main.png', bbox_inches='tight')
        plt.close()
