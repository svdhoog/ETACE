from parameters import NP, A, Plot_configuration
from summarystats import SummaryStats
import sys, os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
#plt.style.use('ggplot')
import matplotlib.cm as cm



class Plot():
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
        self.agent = main_param['agent']
        self.variables = [item for sublist in (list(main_param['variables'].values())) for item in sublist]
        self.__data = data
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        self.summary = main_param['summary']
        self.outpath = outpath + '/timeseries'
        self.dir_check(self.outpath)

    def map_analysis(self, val):
        analysis_values = {'agent': A.agent, 'multiple_run': A.multiple_run, 'multiple_batch': A.multiple_batch, 'multiple_set': A.multiple_set}
        return analysis_values[val]

    # Function to check for existing directories, and create a new one if not present
    def dir_check(self, d):
        if os.path.exists(d):
            print("- Directory ["+os.path.basename(d)+ "] is used for output files")
        else:
            os.makedirs(d)
            print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")

    def plot_line(self, ax, x, y, l_label, clr):
        if self.__P.legend_label(self.idx) is None:
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)
        out = ax.plot(x, y, linestyle=self.__P.linestyle(self.idx), marker=self.__P.marker(self.idx),
                      markerfacecolor=self.__P.markerfacecolor(self.idx), markersize=self.__P.markersize(self.idx), label=le_label, color = clr)
        plt.xlabel(self.__P.xlabel(self.idx))
        plt.ylabel(self.__P.ylabel(self.idx))
        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])

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
                for i, m in enumerate(minor_index):
                    D = dframe.xs(int(m), level='minor')
                    if len(D.columns) == 2:
                        print("Quantile not possible for agent level analysis!")
                        sys.exit(1)
                    else:
                        y = []
                        for l in range(0, len(D), self.__N):
                            y.append(np.array(D[l:l+self.__N]))
                        x = np.arange(1, self.__N+1)
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(D)//self.__N)))
                        size = len(D)//self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = i/len(minor_index)
                        #print("First a: ", a)
                        #print(np.random.uniform(0, 1, size = len(D)//self.__N))
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))
                        for r in range(0, len(y)):
                            clr = next(colors)
                            self.plot_line(ax, x, y[r], legend_label[0]+'_run_'+str(r)+str(m),clr)

                #plot_name = self.__P.plot_name(self.idx)
                if self.__P.plot_name(self.idx):
                    if file_count == 0:
                        plot_name = str(self.__P.plot_name(self.idx))
                    else:
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                else:
                    plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
                    # edit colormap here
                    #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)//self.__N)))
                    size = len(dframe)//self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size

                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for r in range(0, len(dframe)//self.__N):
                        clr = next(colors)
                        self.plot_line(ax, x, y1[r], legend_label[0]+'-'+str(r), clr)
                        self.plot_line(ax, x, y2[r], legend_label[1]+'-'+str(r), clr)

                        if self.__P.fill_between(self.idx):
                            plt.fill_between(x, y1[r], y2[r], color=self.__P.fillcolor(self.idx), alpha=.5)

                    #plot_name = self.__P.plot_name(self.idx)
                    #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                    if self.__P.plot_name(self.idx):
                        if file_count == 0:
                            plot_name = str(self.__P.plot_name(self.idx))
                        else:
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                    else:
                        plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
                else:
                    y1 = []
                    col_A = dframe[dframe.columns[0]]
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                    # edit colormap here
                    #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)//self.__N)))
                    size = len(dframe)//self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size

                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for r in range(0, len(dframe)//self.__N):
                        x = np.arange(1, self.__N+1)
                        clr = next(colors)
                        self.plot_line(ax, x, y1[r], legend_label[0] + " " + str(r), clr)
                    #plot_name = self.__P.plot_name(self.idx)
                    #plt.savefig(str(self.outpath) + '/' + str(plot_name[:-4]) + '_' + str(legend_label[0]) + '.png', bbox_inches='tight')
                    if self.__P.plot_name(self.idx):
                        if file_count == 0:
                            plot_name = str(self.__P.plot_name(self.idx))
                        else:
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                    else:
                        plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
                print(" -Warning: too many plots will be produced !!! ")
                minor_index = dframe.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe
                for m in minor_index:
                    D = dframe.xs( int(m) , level='minor')
                    if len(D.columns) == 2:
                        print("Quantile not possible for agent level analysis")
                        sys.exit(1)
                    else:
                        count = 0

                        # set plot colors for output files
                        size = len(D)//self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = s/size
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        for i in range(0,len(D),self.__N):
                            fig, ax = plt.subplots()
                            y = np.array(D[i:i+self.__N])
                            x = np.arange(1, self.__N+1)
                            clr = next(colors)
                            self.plot_line(ax, x, y, legend_label[0] + "_run_" + str(count) + "_instance_" + str(m), clr)
                            #plot_name = self.__P.plot_name(self.idx)
                            #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + "_run_" + str(count) + "_" + str(m) + ".png", bbox_inches='tight')
                            if self.__P.plot_name(self.idx):
                                if count == 0:
                                    plot_name = str(self.__P.plot_name(self.idx))
                                else:
                                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(count)
                            else:
                                plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                            plot_format = self.__P.plot_format(self.idx)
                            plt.savefig(self.outpath + '/' + plot_name + "_run_" + str(count) + "_" + str(m) + "." + plot_format, format=plot_format, bbox_inches='tight')
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

                    # set plot colors for output files
                    size = len(dframe)//self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for r in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        clr = next(colors)
                        self.plot_line(ax, x, y1[r], legend_label[0]+'_run_'+str(r), clr)
                        self.plot_line(ax, x, y2[r], legend_label[1]+'_run_'+str(r), clr)
                        if self.__P.fill_between(self.idx):
                            plt.fill_between(x, y1[r], y2[r], color='k', alpha=.5)
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if file_count == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[0])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
                        file_count = file_count + 1
                else:
                    y =[]
                    for i in range(0,len(dframe),self.__N):
                        y.append(np.array(dframe[i:i+self.__N]))

                    # set plot colors for output files
                    size = len(dframe)//self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for s in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        x = np.arange(1, self.__N+1)
                        clr = next(colors)
                        self.plot_line(ax, x, y[s], legend_label[0] + "_" + str(s), clr)
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + "_" + str(s) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if s == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(s)
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' +  str(self.variables[file_count])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(s) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()


class Histogram():

    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.agent = main_param['agent']
        self.__data = data
        self.outpath = outpath + '/histogram'
        self.dir_check(self.outpath)
        #self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.__P = plt_config
        self.summary = main_param['summary']
        if self.__analysistype == A.agent and self.summary  == 'custom_quantile':
            print(">> Quantile not possible for agent level analysis!")
            sys.exit(1)

    def map_analysis(self, val):
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}
        return analysis_values[val]

    # Function to check for existing directories, and create a new one if not present
    def dir_check(self, d):
        if os.path.exists(d):
            print("- Directory ["+os.path.basename(d)+ "] is used for output files")
        else:
            os.makedirs(d)
            print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")

    def plot_histogram(self, ax, data, label, colors, n_bins):

        if self.__P.legend_label(self.idx) is None:
            le_label = label
        else:
            le_label = self.__P.legend_label(self.idx)
        out = ax.hist(data, n_bins, histtype=self.__P.histtype(self.idx), stacked=self.__P.stacked(self.idx), normed=self.__P.normed(self.idx), fill=self.__P.fill_between(self.idx), color=colors, label=le_label)
        if self.__P.legend(self.idx) is True:
            plt.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        if self.__P.plot_title(self.idx) is not None:
            ax.set_title(self.__P.plot_title(self.idx))
        if self.__P.xlabel(self.idx) is not None:
            plt.xlabel(self.__P.xlabel(self.idx))
        if self.__P.ylabel(self.idx) is not None:
            plt.ylabel(self.__P.ylabel(self.idx))
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
                for i, m in enumerate(minor_index):
                    D = dframe.xs(int(m), level='minor')
                    if len(D.columns) == 2:  # TODO: this check done in class constructor, so no need
                        print("Quantile not possible for agent level analysis!")
                        sys.exit(1)
                    else:
                        y = []
                        for l in range(0, len(D), self.__N):
                            y.append(np.array(D[l:l+self.__N]))
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)/self.__N)))
                        size = len(dframe)//self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = i/len(minor_index)
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        for r in range(0, len(y)):
                            clr = next(colors)
                            self.plot_histogram(ax, y[r], legend_label[0]+'_run_'+str(r)+'_'+str(m), clr, self.__P.bins(self.idx))
                #plot_name = self.__P.plot_name(self.idx)
                #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0])+".png", bbox_inches='tight')
                if self.__P.plot_name(self.idx):
                    if self.__data.columns[col] == 0:
                        plot_name = str(self.__P.plot_name(self.idx))
                    else:
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                else:
                    plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()

            else:
                if self.summary != 'full':
                    fig, ax = plt.subplots()
                    if len(dframe.columns) == 2:
                        y1 = []
                        y2 = []
                        col_A = dframe[dframe.columns[0]]
                        col_B = dframe[dframe.columns[1]]

                        for i in range(0, len(dframe), self.__N):
                            y1.append(np.array(col_A[i:i+self.__N]))
                            y2.append(np.array(col_B[i:i+self.__N]))
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = 4*len(dframe)/self.__N)))
                        size = 4*len(dframe)/self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = s/size
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        for r in range(0, len(y1)): # TODO: y1 and y2 length must not be different, add a check
                            clr = next(colors)
                            self.plot_histogram(ax, y1[r], legend_label[0]+'_'+str(r), clr, self.__P.bins(self.idx))
                            clr = next(colors)
                            self.plot_histogram(ax, y2[r], legend_label[1]+'_'+str(r), clr, self.__P.bins(self.idx))
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if self.__data.columns[col] == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
                    else:
                        y1 = []
                        col_A = dframe[dframe.columns[0]]
                        for i in range(0, len(dframe), self.__N):
                            y1.append(np.array(col_A[i:i+self.__N]))
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)//self.__N)))
                        size = len(dframe)//self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = s/size
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        for r in range(0, len(dframe)//self.__N):
                            clr = next(colors)
                            self.plot_histogram(ax, y1[r], legend_label[0]+'_'+str(r), clr, self.__P.bins(self.idx))

                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if self.__data.columns[col] == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()

                else:  # for the whole ensemble of data, if analysis is not agent level
                    fig, ax = plt.subplots()
                    if len(dframe.columns) == 2:   ################TODO: two option not needed because when summary full, no custom quantile possible
                        col_A = dframe[dframe.columns[0]]
                        col_B = dframe[dframe.columns[1]]
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = 4)))
                        size = 4
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = s/size
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        clr = next(colors)
                        self.plot_histogram(ax, col_A, legend_label[0], clr, self.__P.bins(self.idx))
                        clr = next(colors)
                        self.plot_histogram(ax, col_B, legend_label[1], clr, self.__P.bins(self.idx))
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if self.__data.columns[col] == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
                    else:
                        col_A = dframe[dframe.columns[0]]
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = 1)))

                        # edit colormap here
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(np.array([0.0])))
                        else:
                            colors = iter(cm.rainbow(np.array([0.0]))) #0.0:blue 1.0:red

                        clr = next(colors)
                        self.plot_histogram(ax, col_A, legend_label[0], clr, self.__P.bins(self.idx))
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if self.__data.columns[col] == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
            file_count = file_count + 1

    def many_output(self):

        if (self.summary == 'full' and self.__analysistype != A.agent):
            print(">> Multiple plots not possible for full ensemble of the data, select single plot option instead and retry!")
            sys.exit(1)

        step = 1
        if self.summary == 'custom_quantile':
            step = 2
        file_count = 0
        for col in range(0, len(self.__data.columns),step):
            if self.summary == 'custom_quantile':
                dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy().dropna()  # one variable, one case at a time
            else:
                dframe = pd.DataFrame(self.__data[self.__data.columns[col]]).dropna()

            legend_label = dframe.columns
            self.__N = len(dframe.index.get_level_values('major').unique())

            if self.__analysistype == A.agent:
                print(" -Warning: too many plots will be produced !!! ")
                minor_index = dframe.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe
                for m in minor_index:
                    D = dframe.xs( int(m) , level='minor')
                    if len(D.columns) == 2:
                        print("Quantile not possible for agent level analysis")
                        sys.exit(1)
                    else:
                        count = 0
                        # edit colormap here
                        #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)//self.__N)))
                        size = len(dframe)//self.__N
                        a = np.empty(shape=size,)
                        for s in range(size):
                            a[s] = s/size
                        if self.__P.greyscale(self.idx):
                            colors = iter(cm.gray(a))
                        else:
                            colors = iter(cm.rainbow(a))

                        for r in range(0,len(D),self.__N):
                            fig, ax = plt.subplots()
                            y = np.array(D[r:r+self.__N])
                            clr = next(colors)
                            self.plot_histogram(ax, y, legend_label[0] + "_run_" + str(count) + "_instance_" + str(m), clr, self.__P.bins(self.idx))
                            #plot_name = self.__P.plot_name(self.idx)
                            #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(legend_label[0]) + "_run_" + str(count) + "_" + str(m) + ".png", bbox_inches='tight')
                            if self.__P.plot_name(self.idx):
                                if count == 0:
                                    plot_name = str(self.__P.plot_name(self.idx))
                                else:
                                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(count)
                            else:
                                plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                            plot_format = self.__P.plot_format(self.idx)
                            plt.savefig(self.outpath + '/' + plot_name + "_run_" + str(count) + "_" + str(m) + "." + plot_format, format=plot_format, bbox_inches='tight')
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
                    # edit colormap here
                    #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = 4*len(dframe)//self.__N)))
                    size = 4*len(dframe)//self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for r in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        clr = next(colors)
                        self.plot_histogram(ax, y1[r], legend_label[0] + "_run_" + str(r), clr, self.__P.bins(self.idx))
                        clr = next(colors)
                        self.plot_histogram(ax, y2[r], legend_label[1] + "_run_" + str(r), clr, self.__P.bins(self.idx))
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if file_count == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()

                        file_count = file_count + 1
                else:
                    y =[]
                    for i in range(0,len(dframe),self.__N):
                        y.append(np.array(dframe[i:i+self.__N]))

                    # edit colormap here
                    #colors = iter(cm.rainbow(np.random.uniform(0, 1, size = len(dframe)/self.__N)))
                    size = len(dframe)/self.__N
                    a = np.empty(shape=size,)
                    for s in range(size):
                        a[s] = s/size
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(a))
                    else:
                        colors = iter(cm.rainbow(a))

                    for s in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        clr = next(colors)
                        self.plot_histogram(ax, y[s], legend_label[0] + "_" + str(s), clr, self.__P.bins(self.idx))

                        if self.__P.plot_name(self.idx):
                            if s == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(s)
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.variables[file_count]) + str(s)
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()


class Scatterplot(A):

    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.agent = main_param['agent']
        self.variables = [item for sublist in (list(main_param['variables'].values())) for item in sublist]
        self.__data = data
        self.__P = plt_config
        self.outpath = outpath + '/scatterplot'
        self.dir_check(self.outpath)
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.delay = main_param['delay']
        self.summary = main_param['summary']

        if self.delay is True:
            if self.summary == 'custom_quantile':
                print(">> Delay not supported for Quantiles! Adjust parameter and retry!")
                sys.exit(1)
            delayed_df = self.__data.shift(periods = 1, axis = 0)
            delayed_df.rename(columns=lambda x: x+ "_delay", inplace=True)
            D = pd.concat([self.__data, delayed_df], axis =1)
            self.__data = D[list(sum(zip(delayed_df.columns, self.__data.columns), ()))]


    def map_analysis(self, val):
        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}
        return analysis_values[val]

    # Function to check for existing directories, and create a new one if not present
    def dir_check(self, d):
        if os.path.exists(d):
            print("- Directory ["+os.path.basename(d)+ "] is used for output files")
        else:
            os.makedirs(d)
            print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")

    def plot_scatterplot(self, ax, x, y, l_label, xlabel, ylabel, clr):
        if self.__P.legend_label(self.idx) is None:
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)

        out = ax.scatter(x, y, linestyle=self.__P.linestyle(self.idx), marker=self.__P.marker(self.idx),
        facecolor=self.__P.facecolors(self.idx), label=le_label, color=clr)

        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])
        
        return out

    def one_output(self):
        file_count = 0
        step = 2
        for col in range(0, len(self.__data.columns), step):
            if len(self.__data.columns) < 2:
                print(">> Problem with data! Either set delay to True, or specify at least two variables to plot!")
                sys.exit(1)
            dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()

            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()
                fig, ax = plt.subplots() # initialize figure

                # edit colormap here
                if self.__P.greyscale(self.idx):
                    colors = iter(cm.gray(np.linspace(0, 1, len(dframe)//self.__N)))
                else:
                    colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)//self.__N)))

                for m in minor_index:
                    D = dframe.xs(int(m), level='minor')
                    legend_label = D.columns
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = D[D.columns[0]]
                    col_B = D[D.columns[1]]
                    for i in range(0, len(D), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    for r in range(0, len(D)//self.__N):
                        clr = next(colors)
                        self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+ ' vs '+legend_label[1]+' [inst'+str(m) + ' run' + str(r) + ']', legend_label[0], legend_label[1], clr )
                #plot_name = self.__P.plot_name(self.idx)
                #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                if self.__P.plot_name(self.idx):
                    if file_count == 0:
                        plot_name = str(self.__P.plot_name(self.idx))
                    else:
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                else:
                    plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()

            else:
                if self.summary != 'full':
                    fig, ax = plt.subplots() # initialize figure
                    legend_label = dframe.columns
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))

                    # edit colormap here
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(np.linspace(0, 1, len(y1))))
                    else:
                        colors = iter(cm.rainbow(np.linspace(0, 1, len(y1))))

                    for r in range(0, len(dframe)//self.__N):
                        clr = next(colors)
                        self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+' vs '+legend_label[1]+' [inst '+str(r) +']', legend_label[0], legend_label[1], clr)
                    #plot_name = self.__P.plot_name(self.idx)
                    #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                    if self.__P.plot_name(self.idx):
                        if file_count == 0:
                            plot_name = str(self.__P.plot_name(self.idx))
                        else:
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                    else:
                        plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str("_".join(self.variables))
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
                else:
                    fig, ax = plt.subplots() # initialize figure
                    legend_label = dframe.columns
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]

                    # edit colormap here
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(np.linspace(0, 1, 1)))
                    else:
                        colors = iter(cm.rainbow(np.linspace(0, 1, 1)))

                    clr = next(colors)
                    self.plot_scatterplot(ax, col_A, col_B, legend_label[0]+' vs '+legend_label[1], legend_label[0], legend_label[1], clr)
                    #plot_name = self.__P.plot_name(self.idx)
                    #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(file_count) + ".png", bbox_inches='tight')
                    if self.__P.plot_name(self.idx):
                        if self.__data.columns[col] == 0:
                            plot_name = str(self.__P.plot_name(self.idx))
                        else:
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                    else:
                        plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
            file_count = file_count + 1

    def many_output(self):
        file_count = 0
        step = 2
        for col in range(0, len(self.__data.columns), step):
            if len(self.__data.columns) < 2:
                print("Problem with data! Either set delay to True, or specify at least two variables to plot!")
                sys.exit(1)
            dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()

            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()

                # edit colormap here
                if self.__P.greyscale(self.idx):
                    colors = iter(cm.gray(np.linspace(0, 1, len(dframe)//self.__N)))
                else:
                    colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)//self.__N)))

                for m in minor_index:
                    D = dframe.xs(int(m), level='minor')
                    legend_label = D.columns
                    if len(dframe.columns) != 2:
                        print("Something wrong with data, check and retry!")
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = D[D.columns[0]]
                    col_B = D[D.columns[1]]
                    for i in range(0, len(D), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    for r in range(0, len(D)//self.__N):
                        fig, ax = plt.subplots()
                        clr = next(colors)
                        self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+ ' vs '+legend_label[1]+' [run'+str(r) + ' inst' + str(m) + ']', legend_label[0], legend_label[1], clr )
                        #plot_name = self.__P.plot_name(self.idx)
                        #plt.savefig(self.outpath + '/' + plot_name[:-4]+ '_'+ str(file_count) + '_run_' + str(r) + '_inst_' + str(m) + ".png", bbox_inches='tight')
                        if self.__P.plot_name(self.idx):
                            if file_count == 0:
                                plot_name = str(self.__P.plot_name(self.idx))
                            else:
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(file_count)
                        else:
                            plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + '_run_' + str(r) + '_inst_' + str(m) + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
            else:
                legend_label = dframe.columns
                if len(dframe.columns) != 2:
                    print("Something wrong with data, check and retry!")
                    sys.exit (1)
                y1 = []
                y2 = []
                col_A = dframe[dframe.columns[0]]
                col_B = dframe[dframe.columns[1]]
                for i in range(0, len(dframe), self.__N):
                    y1.append(np.array(col_A[i:i+self.__N]))
                    y2.append(np.array(col_B[i:i+self.__N]))

                # edit colormap here
                if self.__P.greyscale(self.idx):
                    colors = iter(cm.gray(np.linspace(0, 1, len(y1))))
                else:
                    colors = iter(cm.rainbow(np.linspace(0, 1, len(y1))))

                for r in range(0, len(dframe)//self.__N):
                    fig, ax = plt.subplots()
                    clr = next(colors)
                    self.plot_scatterplot(ax, y1[r], y2[r], legend_label[0]+' vs '+legend_label[1]+' [inst '+str(r) +']', legend_label[0], legend_label[1], clr)
                    #plot_name = self.__P.plot_name(self.idx)
                    #plt.savefig(self.outpath + '/' + plot_name[:-4]+ '_'+ str(file_count) + '_'+ str(r) + ".png", bbox_inches='tight')
                    if self.__P.plot_name(self.idx):
                        if self.__data.columns[col] == 0:
                            plot_name = str(self.__P.plot_name(self.idx))
                        else:
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                    else:
                        plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "_" + str(file_count) + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
            file_count = file_count + 1


class Boxplot(A):
    def __init__(self, idx, data, plt_config, main_param, outpath):
        self.idx = idx
        self.agent = main_param['agent']
        self.__data = data
        self.__P = plt_config
        self.__main_param = main_param
        self.outpath = outpath + '/boxplot'
        self.dir_check(self.outpath)
        self.__N = len(main_param['major'])
        self.__analysistype = self.map_analysis(main_param['analysis'])
        if self.__analysistype == A.agent:
            print("Boxplot not possible for agent-level analysis!")
            sys.exit(1)

    def map_analysis(self, val):

        analysis_values = {'agent' : A.agent, 'multiple_run' : A.multiple_run, 'multiple_batch' : A.multiple_batch, 'multiple_set' : A.multiple_set}
        return analysis_values[val]

    # Function to check for existing directories, and create a new one if not present
    def dir_check(self, d):
        if os.path.exists(d):
            print("- Directory ["+os.path.basename(d)+ "] is used for output files")
        else:
            os.makedirs(d)
            print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")

    def process_boxplot_data(self, data):

        s = SummaryStats(data, self.__main_param)
        box_df = pd.DataFrame()
        #print s.mean().values
        box_df['mean'] = s.mean()
        box_df['median'] = s.median()
        box_df['third_quartile'] = s.third_quartile()
        box_df['first_quartile'] = s.first_quartile()
        box_df['max'] = s.maximum()
        box_df['min'] = s.minimum()
        return box_df

    #def plot_boxplot(self, ax, data, l_label):
    def plot_boxplot(self, ax, data, l_label):

        if self.__P.legend_label(self.idx) is None:
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)

        t_df = data.T
        intervals = []
        pos = []
        N_bins = self.__P.bins(self.idx)
        count = 1
        for i in range(0,len(self.__main_param['major']), int(np.floor(len(self.__main_param['major'])//N_bins))):
            intervals.append(self.__main_param['major'][i])
            pos.append(count)
            count = count + 1
        #ax = t_df.boxplot(column = [100,250,500,750,900], positions =[1,2,3,4,5])
        #ax = t_df.boxplot(column = intervals, positions =pos)

        # edit colormap here
        if self.__P.greyscale(self.idx):
            color = dict(boxes='Gray', whiskers='Black', medians='Black', caps='Black')
        else:
            color = dict(boxes='LightGreen', whiskers='Black', medians='Red', caps='Black')

        # plot the boxplots with pandas
        df = pd.DataFrame(t_df, columns=intervals)
        ax = df.plot.box(by=pos, color=color, patch_artist=True)
        ax.set_title(le_label)
        ax.set_xlabel(self.__P.xlabel(self.idx))
        ax.set_ylabel(self.__P.ylabel(self.idx))

        return ax

    def one_output(self):

        for col in range(0, len(self.__data.columns)):
            dframe = pd.DataFrame(self.__data[self.__data.columns[col]])
            fig, ax = plt.subplots()
            #if self.__analysistype == A.agent: # check done above, redundant, to remove
            #    print("Boxplot not possible for agent-level analysis!")
            #    sys.exit(1)
            #else:
            col_A = dframe[dframe.columns[0]]
            D = self.process_boxplot_data(col_A)
            y = []
            for i in range(0, len(D), self.__N):
                y.append(pd.DataFrame(D[i:i+self.__N]))

            for r in range(0, len(D)//self.__N):
                self.plot_boxplot(ax, y[r], self.__data.columns[col])

            #plot_name = self.__P.plot_name(self.idx)
            #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(self.__data.columns[col]) + ".png", bbox_inches='tight')
            if self.__P.plot_name(self.idx):
                if self.__data.columns[col] == 0:
                    plot_name = str(self.__P.plot_name(self.idx))
                else:
                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
            else:
                plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
            plot_format = self.__P.plot_format(self.idx)
            plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
            plt.close()

    def many_output(self):

        for col in range(0, len(self.__data.columns)):
            dframe = pd.DataFrame(self.__data[self.__data.columns[col]])
            #if self.__analysistype == A.agent: # check done above, redundant, to remove
            #    print("Boxplot not possible for agent-level analysis!")
            #    sys.exit(1)
            #else:
            col_A = dframe[dframe.columns[0]]
            D = self.process_boxplot_data(col_A)
            y =[]
            for i in range(0,len(D),self.__N):
                y.append(pd.DataFrame(D[i:i+self.__N]))
            for s in range(0, len(D)//self.__N):
                fig, ax = plt.subplots()
                self.plot_boxplot(ax, y[s], self.__data.columns[col])
                #plot_name = self.__P.plot_name(self.idx)
                #plt.savefig(self.outpath + '/' + plot_name[:-4] + "_" + str(self.__data.columns[col]) + "_" + str(s) + ".png", bbox_inches='tight')
                if self.__P.plot_name(self.idx):
                    if self.__data.columns[col] == 0:
                        plot_name = str(self.__P.plot_name(self.idx))
                    else:
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + str(self.__data.columns[col])
                else:
                    plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()
