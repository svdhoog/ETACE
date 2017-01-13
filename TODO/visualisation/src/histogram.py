import numpy as np
import matplotlib.pyplot as plt

class Histogram():

    def __init__(self, data, num_plots, n):
        self.__data = data
        self.__N = n

    def multiple_output(self): ####TODO###
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
    
    def single_output(self):
        self.__data.hist(bins = 50)
        plt.savefig('histogram_main.png', bbox_inches='tight')
        plt.close()
