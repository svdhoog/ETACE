from parameters import NP, A, Plot_configuration
from summarystats import SummaryStats
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')


class Plot(NP):  # TODO: remove NP here, inheritance usless for this class
    def __init__(self, idx, data, par_fpath):
        self.idx = idx
        self.__data = data
        self.__P = Plot_configuration(par_fpath)

    def num_plot_mapper(self, val, obj):
        one_plot = lambda: obj.one_output()
        many_plot = lambda: obj.many_output()
        options = {'one': one_plot, 'many': many_plot}
        return options[val]()

    def timeseries(self, main_param, outpath):
        T = Timeseries(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), T)

    def boxplot(self, main_param, outpath):
        B = Boxplot(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), B)

    def scatterplot(self, main_param, outpath):
        S = Scatterplot(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), S)

    def histogram(self, main_param, outpath):
        H = Histogram(self.idx, self.__data, self.__P, main_param, outpath)
        self.num_plot_mapper(self.__P.num_plots(self.idx), H)


class Timeseries(A):

    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.__data = data
        self.outpath = outpath
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        self.summary = main_param['summary']
        print "main data received from summary module inside plot module: "
        print self.__data.head(5)

    def map_analysis(self, val):
        analysis_values = {'agent': A.agent, 'multiple_run': A.multiple_run, 'multiple_batch': A.multiple_batch, 'multiple_set': A.multiple_set}
        return analysis_values[val]

    def plot_line(self, ax, x, y, l_label): 
        if self.__P.legend_label(self.idx) is None:      
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)

        out = ax.plot(x, y, linestyle=self.__P.linestyle(self.idx), marker=self.__P.marker(self.idx), 
        markerfacecolor=self.__P.markerfacecolor(self.idx), markersize=self.__P.markersize(self.idx), label=le_label)
       
        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        return out


    def one_output(self):
        file_count = 0
        step = 1
        if self.summary == 'custom_quantile':
            step = 2
        
        for col in range(0, len(self.__data.columns), step):
            if self.summary == 'custom_quantile':
                dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()  # one variable, one case at a time            
            else:
                dframe = pd.DataFrame(self.__data[self.__data.columns[col]])

            legend_label = dframe.columns
            fig, ax = plt.subplots()

            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()
                for m in minor_index:
                    D = dframe.xs(int(m), level='minor')
                    if len(D.columns) == 2:
                        print "Quantile not possible for agent level analysis!"
                        sys.exit(1)                        
                    else:
                        y = []                        
                        for l in range(0, len(D), self.__N):
                            y.append(np.array(D[l:l+self.__N]))
                        x = np.arange(1, self.__N+1)
                        for r in range(0, len(y)):                                                        
                            self.plot_line(ax, x, y[r], legend_label[0]+'_run_'+str(r)+'_inst_'+str(m))
                #plt.show()                           
                plot_name = self.__P.plot_name(self.idx)           
                plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0])+".png", bbox_inches='tight')
                plt.close()

            else:                
                if len(dframe.columns) == 2:
                    y1 = []
                    y2 = []
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]
                    
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))

                    x = np.arange(1, self.__N+1)
                    for r in range(0, len(dframe)/self.__N):
                        self.plot_line(ax, x, y1[r], legend_label[0]+'_inst_'+str(r))
                        self.plot_line(ax, x, y2[r], legend_label[1]+'_inst_'+str(r))
                        plt.fill_between(x, y1[r], y2[r], color='k', alpha=.5)

                    plot_name = self.__P.plot_name(self.idx)           
                    plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                    plt.close()
                else:
                    y1 = []
                    col_A = dframe[dframe.columns[0]]
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                    for r in range(0, len(dframe)/self.__N):
                        x = np.arange(1, self.__N+1)
                        self.plot_line(ax, x, y1[r], legend_label[0] + "_inst_" + str(r))

                    plot_name = self.__P.plot_name(self.idx) 
                    plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + ".png", bbox_inches='tight')          
                    plt.close()
            file_count = file_count + 1
    
    def many_output(self):
        step = 1
        if self.summary == 'custom_quantile':
            step = 2
        file_count = 0
        for col in range(0, len(self.__data.columns),step):
            if self.summary == 'custom_quantile':
                dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()  # one variable, one case at a time            
            else:
                dframe = pd.DataFrame(self.__data[self.__data.columns[col]])
            legend_label = dframe.columns

            if self.__analysistype == A.agent:
                print " -Warning: too many plots will be produced !!! "                                        
                minor_index = dframe.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe 
                for m in minor_index:
                    D = dframe.xs( int(m) , level='minor')
                    if len(D.columns) == 2:
                        print "Quantile not possible for agent level analysis"                    
                        sys.exit(1)
                    else:
                        count = 0 
                        for i in range(0,len(D),self.__N):
                            fig, ax = plt.subplots()                  
                            y = np.array(D[i:i+self.__N])
                            x = np.arange(1, self.__N+1)
                            self.plot_line(ax, x, y, legend_label[0] + "_run_" + str(count) + "_instance_" + str(m))
                            plot_name = self.__P.plot_name(self.idx)
                            plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + "_run_" + str(count) + "_inst_" + str(m) + ".png", bbox_inches='tight')
                            plt.close()
                            count = count + 1
            else:                
                if len(dframe.columns) == 2:
                    y1 = []
                    y2 = []
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]

                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    x = np.arange(1, self.__N+1)                    
                    for r in range(0, len(dframe)/self.__N):
                        fig, ax = plt.subplots() 
                        self.plot_line(ax, x, y1[r], legend_label[0]+'_run_'+str(r))
                        self.plot_line(ax, x, y2[r], legend_label[1]+'_run_'+str(r))
                        plt.fill_between(x, y1[r], y2[r], color='k', alpha=.5)
                        plot_name = self.__P.plot_name(self.idx)           
                        plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                        file_count = file_count + 1
                        plt.close()
                else:
                    y =[]
                    for i in range(0,len(dframe),self.__N):
                        y.append(np.array(dframe[i:i+self.__N]))                                           
                    for s in range(0, len(dframe)/self.__N):
                        fig, ax = plt.subplots() 
                        x = np.arange(1, self.__N+1)
                        self.plot_line(ax, x, y[s], legend_label[0] + "_inst_" + str(s))                       
                        plot_name = self.__P.plot_name(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + "_inst_" + str(s) + ".png", bbox_inches='tight')
                        plt.close()    


class Histogram():

    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.__data = data
        self.outpath = outpath          
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        print "lau hai aayo lili lai"

    def map_analysis(self, val):             
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
        return analysis_values[val] 


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
    
    def one_output(self):
        self.__data.hist(bins = 50)
        plt.savefig('histogram_main.png', bbox_inches='tight')
        plt.close()


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
        
    def one_output(self):
        s = SummaryStats(self.__data, self.__main_param)   # Fix this for summary accordingly
        box_df = pd.DataFrame()
        box_df['mean'] = [x for sublist in s.mean().values for x in sublist]  # [x for sublist in s.mean().values for x in sublist] done to flatten a 2D list to 1D so pandas accepts it
        # box_df['mean'] = s.mean() # this was the old simpler method which did not work once the config file variables was turned to a hierarchy with filters (bug in df, see for new patches)
        box_df['median'] = [x for sublist in s.median().values for x in sublist]
        box_df['upper_quartile'] = [x for sublist in s.upper_quartile().values for x in sublist]
        box_df['lower_quartile'] = [x for sublist in s.lower_quartile().values for x in sublist]
        box_df['max'] = [x for sublist in s.maximum().values for x in sublist]
        box_df['min'] = [x for sublist in s.minimum().values for x in sublist]

        # box_df['mean'].plot() # shortcut pandas method to plot the whole thing
        # box_df.plot()
        # plt.show()
        t_df = box_df.T
        
        bp = t_df.boxplot(column = [100,250,500,750,999], positions =[1,2,3,4,5])           
        plot_name = self.__P.plot_name(self.idx)            
        plt.savefig(self.outpath +'/'+plot_name, bbox_inches='tight')      
        plt.clf()

    def many_output(self):
        print "many ma ni aaucha ta?"
        s = SummaryStats(self.__data, self.__analysistype )           
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
            plt.savefig(self.outpath +'/'+plot_name, bbox_inches='tight')  
            plt.clf()           
            count = count + self.__N
        plt.close()




class Scatterplot(A):
    
    def __init__(self, idx, data, plt_config, main_param, outpath):
    #def __init__(self, data, n, a, parameter, idx):
        self.idx = idx  
        self.__data = data
        self.__P = plt_config
        self.outpath = outpath          
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        
        #print "main data received from summary module to scatterplot module: "
        #print self.__data.head(10)
            
    def map_analysis(self, val):             
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}    
        return analysis_values[val]                  
    
    def one_output(self):
        if self.__analysistype == A.agent:
            print " -Warning: too many lines will be printed in a single plot !!! "
            minor_index = self.__data.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe 
            for i in minor_index:
                D = self.__data.xs( int(i) , level='minor')
            count = 0          
            for i in range(0,len(D),self.__N):
                y = np.array(D[i:i+self.__N])
                x = np.linspace(0, self.__N, self.__N, endpoint=True)
                #print x

                plt.plot(x,y, linestyle = self.__P.linestyle(self.idx), marker='o', markerfacecolor = 'green', markersize =1, label = self.__P.legend_label(self.idx)+"_"+str(count))
                count = count + 1
                plt.hold(True)
            plt.legend(loc='best', fancybox=True, shadow=True)
            plot_name = self.__P.plot_name(self.idx) 
            plt.savefig(plot_name, bbox_inches='tight')
            plt.close()

        else:
            y1 = []
            y2 = []
            col_A = self.__data[self.__data.columns[0]]
            col_B = self.__data[self.__data.columns[1]]
            for i in range(0,len(self.__data),self.__N):
                y1.append(np.array(col_A[i:i+self.__N]))
            
            for i in range(0,len(self.__data),self.__N):
                y2.append(np.array(col_B[i:i+self.__N]))  

            for i in range(0,len(self.__data)/self.__N):                    
                colors = (0,0,0)
                area = np.pi*3
                
                plt.scatter(y1[i], y2[i], s=area, c=colors, alpha=0.5)
                plt.title('Scatter plot')
                plt.xlabel('x')
                plt.ylabel('y')
                
            #plt.legend(loc='best', fancybox=True, shadow=True)
            plot_name = self.__P.plot_name(self.idx)           
            plt.savefig(plot_name, bbox_inches='tight')
            plt.close()
            
