import numpy as np
import matplotlib.pyplot as plt

class Timeseries():
    #N = 1000
    def __init__(self, data, num_plots):
        self.__data = data
        self.N = 1000
    def multiple_output(self):
        y =[]
        for i in range(0,len(self.__data),self.N):
            y.append(np.array(self.__data[i:i+self.N]))
        for i in range(0,len(self.__data)/self.N):
            x = np.linspace(0, self.N, self.N, endpoint=True)
            plt.plot(x,y[i])
            plot_name = str(i)+".png"
            plt.savefig(plot_name, bbox_inches='tight')	 
            
            # plt.show() # reset the plot, but gives output in display
            # So, alternatively:
            # plt.cla() # clear current axes
            plt.clf() # clear current figure
            # plt.close() # close the whole plot

    def single_output(self):
        y =[]
        for i in range(0,len(self.__data),self.N):
            y.append(np.array(self.__data[i:i+self.N]))
        for i in range(0,len(self.__data)/self.N):
            x = np.linspace(0, self.N, self.N, endpoint=True)
            plt.plot(x,y[i])          
            plt.hold(True)	 
        plt.savefig('summary_main.png', bbox_inches='tight')
        plt.show()
