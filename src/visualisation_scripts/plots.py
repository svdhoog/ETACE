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
        one_plot = lambda: obj.one_plot()
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
        self.__N = len(main_param['major']) #length of major axis: iterations
        self.__S = len(main_param['set']) #length of sets list
        self.__R = len(main_param['run']) #length of runs list
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.analysistype = main_param['analysis']
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

    def plot_line(self, ax, x, y, l_label, clr, forced_ylabel):
        if self.__P.legend_label(self.idx) is None:
            le_label = l_label
        else:
            le_label = self.__P.legend_label(self.idx)
        out = ax.plot(x, y, linestyle=self.__P.linestyle(self.idx), marker=self.__P.marker(self.idx),
                      markerfacecolor=self.__P.markerfacecolor(self.idx), markersize=self.__P.markersize(self.idx), label=le_label, color = clr)
        
        #Axes labels
        if self.__P.xlabel(self.idx) is None or self.__P.xlabel(self.idx) == 'Auto' or self.__P.xlabel(self.idx) == 'auto':
            ax.set_xlabel("Time")
        else:
            ax.set_xlabel(self.__P.xlabel(self.idx))

        if self.__P.ylabel(self.idx) is None or self.__P.ylabel(self.idx) == 'Auto' or self.__P.ylabel(self.idx) == 'auto':
            ax.set_ylabel(str(self.agent) + ' : ' + forced_ylabel)
        else:
            ax.set_ylabel(self.__P.ylabel(self.idx))

        #No axes labels
        if self.__P.xlabel(self.idx) == 'None' or self.__P.xlabel(self.idx) == 'none':
            ax.set_xlabel("")

        if self.__P.ylabel(self.idx) == 'None' or self.__P.ylabel(self.idx) == 'none':
            ax.set_ylabel("")

        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])

        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        
        return out


    def one_plot(self):
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

            # timeseries one_plot agent
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

                        # Index values:
                        print("D.index.levels:")
                        #print(D.index.levels) #D only contains sets, runs, iters, no agents

                        print("sets:")
                        print('D.index.levels[0].values')
                        print(D.index.levels[0].values) #set values

                        print("runs:")
                        print('D.index.levels[1].values')
                        print(D.index.levels[1].values) #run values
                        # print("iters:")
                        # print('D.index.levels[2].values')
                        # print(D.index.levels[2].values) #iter values
                        
                        nsets = len(D.index.levels[0])
                        nruns = len(D.index.levels[1])
                        
                        print("Length set list:")                        
                        print(nsets)

                        print("Length run list:")                        
                        print(nruns)

                        for r in range(0, len(y)):
                            clr = next(colors)

                            # Index values: block in r-loop
                            run_idx = r % nruns     # r MOD blocks, ex: r MOD 4
                            set_idx = r // nruns    # r DIV blocks, ex: r DIV 4
                            
                            #TEST
                            # print("set:")
                            # print(D.index.levels[0].values[set_idx])

                            # print("run:")
                            # print(D.index.levels[1].values[run_idx])

                            ##print("iters:")
                            ##print(D.index.levels[2].values)
                            
                            #Agent index: does not exist in D, but does in dframe
                            #TODO: use dframe or d or df_main (all not defined n this function)
                            # print("agent index:")
                            # print(m)

                            #Use run and set labels derived from row index r
                            set_no = D.index.levels[0].values[set_idx]
                            run_no = D.index.levels[1].values[run_idx]                      

                            #TODO: Use agent label derived from agent index m (required access to global dataframe)
                            agent_ind = m
                            #agent_id = df_main.index.levels[3].values[m]   #TODO

                            self.plot_line(ax, x, y[r], 'set ' + str(set_no) + ' run ' + str(run_no) + ' agent '+  str(agent_ind), clr, str(self.__data.columns[col]))  # Legend entries for runs

                #Timeseries plot_name one_plot agent case 0
                plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_VariableName
                if self.__P.plot_name(self.idx):
                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_VariableName
                    
                #Test code
                #if args.trace:
                print("Timeseries [case 0 one_plot analysis=Agent]: ") #agent analysis, one_plot
                print(plot_name)
                #End of Test code

                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()

            else:   # timeseries one_plot quantiles multiple_run,multiple_batch,multiple_set
                #Test
                # print('len(dframe.columns)= '+str(len(dframe.columns)))                
                # print(dframe)

                if len(dframe.columns) == 2: # quantiles

                    print('- Summary [quantiles]')

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

                    # Block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)                        

                    for r in range(0, len(dframe)//self.__N):
                        clr = next(colors)
                        
                        # block set_no run_no
                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                            
                            self.plot_line(ax, x, y1[r], legend_label[0]+' set ' + str(set_no)+' run ' + str(run_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], legend_label[1]+' set ' + str(set_no)+' run ' + str(run_no), clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns    #irrelevant?
                            set_idx = r
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = 0
                            self.plot_line(ax, x, y1[r], legend_label[0]+' set ' + str(set_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], legend_label[1]+' set ' + str(set_no), clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            set_no = self.summary
                            run_no = 0
                            self.plot_line(ax, x, y1[r], legend_label[0]+' set ' + str(set_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], legend_label[1]+' set ' + str(set_no), clr, str(self.__data.columns[col]))
                            #print("iters:", dframe.index.values) #iter values

                        if self.__P.fill_between(self.idx):
                            plt.fill_between(x, y1[r], y2[r], color=self.__P.fillcolor(self.idx), alpha=.5)

                    #Timeseries plot_name one_plot not-agent not-full case 1
                    plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_VariableName
                    if self.__P.plot_name(self.idx):
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_VariableName

                    #Test code
                    #if args.trace:
                    print("Timeseries [case 1 one_plot, analysis != Agent, quantiles]: ") #multiple_batch
                    print(plot_name)
                    #End of Test code

                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
                else: # timeseries one_plot !quantiles multiple_run,multiple_batch,multiple_set
                    
                    print('- Summary [!quantiles?]')

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

                    # Block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)                        

                    for r in range(0, len(dframe)//self.__N):
                        x = np.arange(1, self.__N+1)
                        clr = next(colors)

                        # Block inside r-loop: set_no run_no
                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                      
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no) + ' ' + self.summary, clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns    #irrelevant?
                            set_idx = r
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = 0
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no) + ' ' + self.summary, clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            set_no = self.summary
                            run_no = 0
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no) + ' ' + self.summary, clr, str(self.__data.columns[col]))
                            #print("iters:", dframe.index.values) #iter values
                    
                    #Timeseries plot_name one_plot not-agent full case 2
                    plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_VariableName
                    if self.__P.plot_name(self.idx):
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_VariableName

                    #Test                        
                    #if args.trace:
                    print("Timeseries [case 2 one_plot, analysis != Agent, !quantiles]:")
                    print(plot_name)

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
            print('- Plotting [' + self.__data.columns[col] + ']')
            if self.summary == 'custom_quantile':
                dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()  # one variable, one case at a time
            else:
                dframe = pd.DataFrame(self.__data[self.__data.columns[col]])
            legend_label = dframe.columns

            # timeseries many_plot agent
            if self.__analysistype == A.agent:
                print('- Warning: analysis type is Agent, plotting type is many_output.')
                print('- Number of plots: ' + str(len(dframe)//self.__N) + ' of ' + str(len(self.__data.columns)*(len(dframe)//self.__N)))

                minor_index = dframe.index.get_level_values('minor').unique()  # get the index values for minor axis, which will later be used to sort the dataframe
                
                #Use groupby
                grouped = dframe.groupby('minor')

                for m in minor_index:
                    D = grouped.get_group(m)
                    #D = dframe.xs( int(m) , level='minor')     # remove
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

                        nsets = len(D.index.levels[0])
                        nruns = len(D.index.levels[1])

                        for i in range(0,len(D),self.__N):      # blocks of self.__N rows belong to one agent
                            #fig, ax = plt.subplots()
                            y = np.array(D[i:i+self.__N])
                            x = np.arange(1, self.__N+1)
                            #clr = next(colors)
                            
                        for ind, r in enumerate(range(0, len(D)//self.__N)):        # loop all rows/no.iters
                            # print('Loop dframe block r: '+str(ind)+'/'+str(len(D)//self.__N))

                            fig, ax = plt.subplots()
                            clr = next(colors)

                            # Index values:
                            run_idx = r % nruns     # r MOD blocks, ex: r MOD 4
                            set_idx = r // nruns    # r DIV blocks, ex: r DIV 4

                            #Use run and set labels derived from row index r
                            set_no = D.index.levels[0].values[set_idx]
                            run_no = D.index.levels[1].values[run_idx]                      

                            #TODO: Use agent label derived from agent index m (required access to global dataframe)
                            agent_ind = m
                            #agent_id = df_main.index.levels[3].values[m]   #TODO

                            self.plot_line(ax, x, y, 'set ' + str(set_no) + ' run ' + str(run_no) + ' agent ' + str(m), clr, str(self.__data.columns[col]))
        
                            #Timeseries plot_name many_output agent case 3
                            plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) + '_set_' + str(set_no) + '_run_' + str(run_no) + "_agent_" + str(m)#PlotLabel_AgentName_VariableName
                            if self.__P.plot_name(self.idx):
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name

                            #Add a counter to the end
                            # if count != 0:
                            #     plot_name = str(plot_name) + '_' + str(count)

                            #Test
                            #if args.trace:
                            print("Timeseries [case 3 many_output analysis=Agent]:")
                            print(plot_name)

                            plot_format = self.__P.plot_format(self.idx)
                            plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                            plt.close()
                        count = count + 1
            else:   # timeseries many_plot quantiles multiple_run,multiple_batch,multiple_set
                if len(dframe.columns) == 2:    # quantiles
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

                    # block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)  

                    # many plot
                    for r in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        clr = next(colors)

                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                      
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no) + ' run ' + str(run_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], 'set ' + str(set_no) + ' run ' + str(run_no), clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns     #Irrelevant?
                            set_idx = r % nsets
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values #names
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            #run_idx = r % nruns     #Irrelevant?
                            #set_idx = r // nruns    
                            set_no = self.summary
                            run_no = 0
                            self.plot_line(ax, x, y1[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))  # Legend entries for quantiles per set
                            self.plot_line(ax, x, y2[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))
                            #print("iters:", dframe.index.values) #iter values
                        
                        if self.__P.fill_between(self.idx):
                            plt.fill_between(x, y1[r], y2[r], color='k', alpha=.5)

                        #Timeseries plot_name many_output not-agent not-full case 4                        
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) +  '_set_' + str(set_no) + '_run_' + str(run_no) #PlotLabel_AgentName_VariableName

                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                            

                        #Add a counter to the end
                        # if file_count != 0:
                        #     plot_name = str(plot_name) + '_' + str(file_count)

                        #Test
                        #if args.trace:
                        print("Timeseries [case 4 many_output, analysis != Agent, quantiles]:")
                        print(plot_name)
                        #print("file_count= "+str(file_count))                        

                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
                        file_count = file_count + 1
                else: # timeseries many_plot !quantiles multiple_run,multiple_batch,multiple_set
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

                    # block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter) 
                    
                    # many plot
                    for r in range(0, len(dframe)//self.__N):
                        fig, ax = plt.subplots()
                        x = np.arange(1, self.__N+1)
                        clr = next(colors)
                        
                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                      
                            self.plot_line(ax, x, y[r], 'set ' + str(set_no) + ' run ' + str(run_no), clr, str(self.__data.columns[col]))
                            plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) +  '_set_' + str(set_no) + ' run ' + str(run_no) #PlotLabel_AgentName_VariableName                            
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns     #Irrelevant?
                            set_idx = r % nsets
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = "" #dframe.index.levels[1].values #names
                            self.plot_line(ax, x, y[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))
                            plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) +  '_set_' + str(set_no) #PlotLabel_AgentName_VariableName                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            #run_idx = r % nruns     #Irrelevant?
                            #set_idx = r // nruns    
                            set_no = self.summary
                            run_no = "" #0
                            self.plot_line(ax, x, y[r], 'set ' + str(set_no), clr, str(self.__data.columns[col]))
                            plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) +  '_set_' + str(set_no) #PlotLabel_AgentName_VariableName
                            #print("iters:", dframe.index.values) #iter values

                        #Timeseries plot_name many_output not-agent not-full case 5
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_VariableName

                        #Add a counter to the end
                        # if file_count != 0:
                        #     plot_name = str(plot_name) + '_' + str(file_count)

                        #Test
                        #if args.trace:
                        print("Timeseries [case 5 many_output, analysis != Agent, !quantiles]:")
                        print(plot_name)
                        #print("file_count= "+str(file_count))                        

                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
        self.analysistype = main_param['analysis']
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

    def plot_histogram(self, ax, data, label, colors, n_bins, forced_xlabel):

        if self.__P.legend_label(self.idx) is None:
            le_label = label
        else:
            le_label = self.__P.legend_label(self.idx)
        out = ax.hist(data, n_bins, histtype=self.__P.histtype(self.idx), stacked=self.__P.stacked(self.idx), density=self.__P.normed(self.idx), fill=self.__P.fill_between(self.idx), color=colors, alpha=.5, label=le_label)
                
        if self.__P.plot_title(self.idx) is not None:
            ax.set_title(self.__P.plot_title(self.idx))
            
        #Axes labels
        if self.__P.xlabel(self.idx) is None or self.__P.xlabel(self.idx) == 'Auto' or self.__P.xlabel(self.idx) == 'auto':
            ax.set_ylabel(str(self.agent) + ' : ' + forced_xlabel)
        else:
            ax.set_xlabel(self.__P.xlabel(self.idx))

        if self.__P.ylabel(self.idx) is None or self.__P.ylabel(self.idx) == 'Auto' or self.__P.ylabel(self.idx) == 'auto':            
            ax.set_ylabel(str("count"))
        else:
            ax.set_ylabel(self.__P.ylabel(self.idx))

        #No axes labels
        if self.__P.xlabel(self.idx) == 'None' or self.__P.xlabel(self.idx) == 'none':
            ax.set_xlabel("")

        if self.__P.ylabel(self.idx) == 'None' or self.__P.ylabel(self.idx) == 'none':
            ax.set_ylabel("")

        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])

        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        
        #TODO: legend for histogram
        #if self.__P.legend(self.idx) is True:
        #    ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)

        return out


    def one_plot(self):
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
                            self.plot_histogram(ax, y[r], legend_label[0]+'-set-'+str(r)+'_'+str(m), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                
                #plot_name
                plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_DataColsName
                if self.__P.plot_name(self.idx):
                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_DataColsName
                    
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
                            self.plot_histogram(ax, y1[r], legend_label[0]+'_'+str(r), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                            clr = next(colors)
                            self.plot_histogram(ax, y2[r], legend_label[1]+'_'+str(r), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        
                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_DataColsName
                            
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
                            self.plot_histogram(ax, y1[r], legend_label[0]+'_'+str(r), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))

                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx))  + '_' + plot_name #PlotName_DataColsName
                            
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
                        self.plot_histogram(ax, col_A, legend_label[0], clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        clr = next(colors)
                        self.plot_histogram(ax, col_B, legend_label[1], clr, self.__P.bins(self.idx), str(self.__data.columns[col]))

                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_DataColsName
                            
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
                        self.plot_histogram(ax, col_A, legend_label[0], clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        
                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col]) #PlotLabel_AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_DataColsName
                            
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
                print("- Warning: too many plots will be produced !!! ")
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
                            self.plot_histogram(ax, y, legend_label[0] + "_run_" + str(count) + "_instance_" + str(m), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                            
                            #plot_name
                            plot_name = str(self.agent) + '_' + str(self.__data.columns[col])    #PlotLabel_AgentName_DataColsName
                            if self.__P.plot_name(self.idx):
                                plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_Count
                            
                            #Add a counter to the end
                            # if count != 0:
                            #     plot_name = str(plot_name) + '_' + str(count)

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
                        self.plot_histogram(ax, y1[r], legend_label[0] + "_run_" + str(r), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        clr = next(colors)
                        self.plot_histogram(ax, y2[r], legend_label[1] + "_run_" + str(r), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        
                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col])   #AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name #PlotName_Count

                        #Add a counter to the end
                        # if file_count != 0:
                        #     plot_name = str(plot_name) + '_' + str(file_count)

                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
                        self.plot_histogram(ax, y[s], legend_label[0] + "_" + str(s), clr, self.__P.bins(self.idx), str(self.__data.columns[col]))
                        
                        #plot_name
                        plot_name = str(self.agent) + '_' + str(self.__data.columns[col])               #AgentName_DataColsName
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name

                        #Add a counter to the end
                        # if file_count != 0:
                        #     plot_name = str(plot_name) + '_' + str(file_count)

                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
        self.__N = len(main_param['major']) #length of iters list
        self.__S = len(main_param['set']) #length of sets list
        self.__R = len(main_param['run']) #length of runs list
        self.__analysistype = self.map_analysis(main_param['analysis'])
        self.analysistype = main_param['analysis']
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

        #plt.xlabel(xlabel)
        #plt.ylabel(ylabel)
        
        #Axes labels
        if self.__P.xlabel(self.idx) is None or self.__P.xlabel(self.idx) == 'Auto' or self.__P.xlabel(self.idx) == 'auto':
            ax.set_xlabel(str(self.agent) + ' : ' + str(xlabel))
        else:
            ax.set_xlabel(self.__P.xlabel(self.idx))

        if self.__P.ylabel(self.idx) is None or self.__P.ylabel(self.idx) == 'Auto' or self.__P.ylabel(self.idx) == 'auto':
            ax.set_ylabel(str(self.agent) + ' : ' + str(ylabel))
        else:
            ax.set_ylabel(self.__P.ylabel(self.idx))

        #No axes labels
        if self.__P.xlabel(self.idx) == 'None' or self.__P.xlabel(self.idx) == 'none':
            ax.set_xlabel("")

        if self.__P.ylabel(self.idx) == 'None' or self.__P.ylabel(self.idx) == 'none':
            ax.set_ylabel("")

        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])
        
        return out

    def one_plot(self):
        file_count = 0
        step = 2

        for col in range(0, len(self.__data.columns), step):
            if len(self.__data.columns) < 2:
                print(">> Problem with data! Either set delay to True, or specify at least two variables to plot!")
                sys.exit(1)
            
            dframe = self.__data[[self.__data.columns[col], self.__data.columns[col+1]]].copy()
            
            #test
            # print('\nPrint (plot.py): self.__data')
            # print(self.__data)
            # print('\nPrint (plot.py): dframe')
            # print(dframe)

            # scatter one_plot agent
            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()
                fig, ax = plt.subplots() # initialize figure

                # edit colormap here
                if self.__P.greyscale(self.idx):
                    colors = iter(cm.gray(np.linspace(0, 1, len(dframe)//self.__N)))
                else:
                    colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)//self.__N)))

                #Using groupby on minor index to re-order hierarchical index
                grouped = dframe.groupby('minor')
                # print(grouped.get_group(0))
                # print(grouped.get_group(1))

                #m: agent index (not IDs)
                for m in minor_index:

                    #Select only agent index m
                    D = grouped.get_group(m)

                    ##Test
                    # print('D = grouped.get_group('+str(m)+')')
                    # print(D)

                    #Old code refactored:
                    #D = dframe.xs(int(m), level='minor') #agent-specific dframe containing: set,run,iter,vars
                    
                    #test
                    # print('\nPrint (plot.py): D')
                    # print(D)

                    legend_label = D.columns    #legend_label: list of variable names
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)

                    #Refactor candidate:
                    y1 = []
                    y2 = []
                    col_A = D[D.columns[0]]     #col_A: values of variable 0
                    col_B = D[D.columns[1]]     #col_B: values of variable 1
                    
                    ##Test
                    # print('\nPrint (plot.py): col_A')
                    # print(col_A)
                    # print('\nPrint (plot.py): col_B')
                    # print(col_B)

                    #Refactor candidate: Series of Array for all set+run data
                    #Append set_run data for agent index m
                    # Note: range(0, len(D), self.__N) uses as increment self.__N,
                    # so it is selecting rows of D that are self.__N rows apart.
                    for i in range(0, len(D), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))

                    ##Test
                    # print('\nPrint (plot.py): y1')
                    # print(y1)
                    # print('\nPrint (plot.py): y2')
                    # print(y2)

                    # Index values:
                    print("D.index.levels:")
                    #print(D.index.levels) #D only contains sets, runs, iters, no agents

                    print("sets:")
                    print('D.index.levels[0].values')
                    print(D.index.levels[0].values) #set values

                    print("runs:")
                    print('D.index.levels[1].values')
                    print(D.index.levels[1].values) #run values
                    # print("iters:")
                    # print('D.index.levels[2].values')
                    # print(D.index.levels[2].values) #iter values
                    
                    nsets = len(D.index.levels[0])
                    nruns = len(D.index.levels[1])
                    
                    print("Length set list:")                        
                    print(nsets)

                    print("Length run list:")                        
                    print(nruns)

                    for ind, r in enumerate(range(0, len(D)//self.__N)):
                        ## print('Loop dframe block r: '+str(ind)+'/'+str(len(D)//self.__N))

                        clr = next(colors)                    

                        # Index values: block in r-loop
                        run_idx = r % nruns     # r MOD blocks, ex: r MOD 4
                        set_idx = r // nruns    # r DIV blocks, ex: r DIV 4
                        
                        #TEST
                        # print("set:")
                        # print(D.index.levels[0].values[set_idx])

                        # print("run:")
                        # print(D.index.levels[1].values[run_idx])

                        ##print("iters:")
                        ##print(D.index.levels[2].values)
                        
                        #Agent index: does not exist in D, but does in dframe
                        #TODO: use dframe or d or df_main (all not defined n this function)
                        # print("agent index:")
                        # print(m)

                        #Use run and set labels derived from row index r
                        set_no = D.index.levels[0].values[set_idx]
                        run_no = D.index.levels[1].values[run_idx]                      

                        #TODO: Use agent label derived from agent index m (required access to global dataframe)
                        agent_ind = m
                        #agent_id = df_main.index.levels[3].values[m]   #TODO

                        self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ' run ' + str(run_no) + ' agent '+  str(agent_ind) + ']', legend_label[0], legend_label[1], clr)
                        
                #Scatter plot_name one_plot agent case 0
                plot_name = str(self.agent) + '_' + str("_".join(self.variables))
                if self.__P.plot_name(self.idx):
                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name

                #Test code
                #if args.trace:
                print("Scatterplot [case 0 one_plot analysis=Agent]: ") #agent analysis, one_plot
                print(plot_name)
                #End of Test code

                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()

            else: # scatter one_plot summary!='full' multiple_run,multiple_batch,multiple_set
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
                    
                    ##Test
                    # print('\nPrint (plot.py): col_A')
                    # print(col_A)
                    # print('\nPrint (plot.py): col_B')
                    # print(col_B)

                    #Refactor candidate: Series of Array for all set+run data
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))

                    # edit colormap here
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(np.linspace(0, 1, len(y1))))
                    else:
                        colors = iter(cm.rainbow(np.linspace(0, 1, len(y1))))
                    
                    # Block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)                        

                    for ind, r in enumerate(range(0, len(dframe)//self.__N)):
                        ## print('Loop dframe block r: '+str(ind)+'/'+str(len(dframe)//self.__N))

                        clr = next(colors)                        

                        # Block inside r-loop: set_no run_no
                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                      
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns    #irrelevant?
                            set_idx = r
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = 0
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ' ' + self.summary + ']', legend_label[0], legend_label[1], clr)
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            set_no = self.summary
                            run_no = 0
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ']', legend_label[0], legend_label[1], clr)
                            #print("iters:", dframe.index.values) #iter values
                        
                    #Scatter plot_name one_plot not-agent not-full case 1
                    plot_name = str(self.agent) + '_' + str("_".join(self.variables))
                    if self.__P.plot_name(self.idx):
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                    
                    #Test
                    #if args.trace:
                    print("Scatterplot [case 1 one_plot, analysis != Agent, summary != 'full']: ") #multiple_batch
                    print(plot_name)
                    #End of Test code

                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                    plt.close()
                else: # scatter one_plot summary=='full' multiple_run,multiple_batch,multiple_set
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
                    
                    # block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, full runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        # print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, full batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values) #iter values
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)                        

                    if(self.analysistype == 'multiple_run'):
                        set_no = dframe.index.levels[0].values #names
                        run_no = dframe.index.levels[1].values #names
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                    if(self.analysistype == 'multiple_batch'):
                        set_no = dframe.index.levels[0].values #names
                        run_no = dframe.index.levels[1].values #names
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                    if(self.analysistype == 'multiple_set'):
                        set_no = self.summary
                        run_no = 0
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ']', legend_label[0], legend_label[1], clr)
                    
                    #Scatter plot_name one_plot not-agent full case 2
                    plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_full'
                    if self.__P.plot_name(self.idx):
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name

                    #if args.trace:
                    print("Scatterplot [case 2 one_plot, analysis != Agent, summary = 'full']:")
                    print(plot_name)

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

            # scatter many_plot agent
            if self.__analysistype == A.agent:
                minor_index = dframe.index.get_level_values('minor').unique()

                # edit colormap here
                if self.__P.greyscale(self.idx):
                    colors = iter(cm.gray(np.linspace(0, 1, len(dframe)//self.__N)))
                else:
                    colors = iter(cm.rainbow(np.linspace(0, 1, len(dframe)//self.__N)))

                #Use groupby
                grouped = dframe.groupby('minor')

                for m in minor_index:
                    D = grouped.get_group(m)
                    #D = dframe.xs(int(m), level='minor')     # remove
                    legend_label = D.columns
                    if len(dframe.columns) != 2:
                        print("Something wrong with data, check and retry!")
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = D[D.columns[0]]
                    col_B = D[D.columns[1]]
                    for i in range(0, len(D), self.__N):        # blocks of self.__N rows belong to one agent
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))
                    
                    nsets = len(D.index.levels[0])
                    nruns = len(D.index.levels[1])

                    for ind, r in enumerate(range(0, len(D)//self.__N)):        # loop all rows/no.iters
                        ## print('Loop dframe block r: '+str(ind)+'/'+str(len(D)//self.__N))
                        fig, ax = plt.subplots() #open new figure for many plot option
                        clr = next(colors)
                        
                        # Index values:
                        run_idx = r % nruns     # r MOD blocks, ex: r MOD 4
                        set_idx = r // nruns    # r DIV blocks, ex: r DIV 4

                        #Use run and set labels derived from row index r
                        set_no = D.index.levels[0].values[set_idx]
                        run_no = D.index.levels[1].values[run_idx]                      

                        #TODO: Use agent label derived from agent index m (required access to global dataframe)
                        agent_ind = m
                        #agent_id = df_main.index.levels[3].values[m]   #TODO

                        self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ' run ' + str(run_no) + ' agent '+  str(agent_ind) + ']', legend_label[0], legend_label[1], clr)
                        
                        ##Scatter plot_name many_output agent case 3
                        plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_set_' + str(set_no) + '_run_' + str(run_no) + '_' + 'agent_'+  str(agent_ind)
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                        
                        #Add a counter to the end
                        # if file_count != 0:
                        #     plot_name = str(plot_name) + '_' + str(file_count)

                        #if args.trace:
                        print("Scatterplot [case 3 many_output analysis=Agent]:")
                        print(plot_name)
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
            else: # scatter many_plot summary!='full' multiple_run,multiple_batch,multiple_set
                if self.summary != 'full':
                    legend_label = dframe.columns
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)
                    y1 = []
                    y2 = []
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]

                    ##Test
                    # print('\nPrint (plot.py): col_A')
                    # print(col_A)
                    # print('\nPrint (plot.py): col_B')
                    # print(col_B)

                    #Refactor candidate: Series of Array for all set+run data
                    #This block is only needed if summary != 'full'
                    for i in range(0, len(dframe), self.__N):
                        y1.append(np.array(col_A[i:i+self.__N]))
                        y2.append(np.array(col_B[i:i+self.__N]))

                    # edit colormap here
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(np.linspace(0, 1, len(y1))))
                    else:
                        colors = iter(cm.rainbow(np.linspace(0, 1, len(y1))))

                    # block: nsets nruns
                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, summary across runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        #print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, summary across batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values)
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)  

                    # many plot
                    for ind, r in enumerate(range(0, len(dframe)//self.__N)):
                        ## print('Loop dframe block r: '+str(ind)+'/'+str(len(dframe)//self.__N))
                        fig, ax = plt.subplots()    #open new figure for many plot
                        clr = next(colors)

                        if(self.analysistype == 'multiple_run'):
                            run_idx = r % nruns
                            set_idx = r // nruns
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values[run_idx]                      
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("run:", dframe.index.levels[1].values[run_idx]) #run values
                            # print("iters:", dframe.index.levels[2].values) #iter values
                        if(self.analysistype == 'multiple_batch'):
                            #run_idx = r % nruns     #Irrelevant?
                            set_idx = r % nsets
                            set_no = dframe.index.levels[0].values[set_idx]
                            run_no = dframe.index.levels[1].values #names
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ']', legend_label[0], legend_label[1], clr)
                            # print("set:", dframe.index.levels[0].values[set_idx]) #set values
                            # print("iters:", dframe.index.levels[1].values) #run values
                        if(self.analysistype == 'multiple_set'):
                            #run_idx = r % nruns     #Irrelevant?
                            #set_idx = r // nruns    
                            set_no = self.summary
                            run_no = 0
                            self.plot_scatterplot(ax, y1[r], y2[r], '[set ' + str(set_no) + ']', legend_label[0], legend_label[1], clr)
                            #print("iters:", dframe.index.values) #iter values
                        
                        ##Scatter plot_name many_output not-agent not-full case 4
                        #Note: this block is indented directly under plot_scatterplot, in order to have many plots
                        plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_set_' + str(set_no)
                        if self.__P.plot_name(self.idx):
                            plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                        
                        #Add a counter to the end
                        if file_count != 0:
                            plot_name = str(plot_name) + '_' + str(file_count)

                        #if args.trace:
                        print("Scatterplot [case 4 many_output, analysis != Agent]:")
                        print(plot_name)
                        #print("file_count= "+str(file_count))
                        
                        plot_format = self.__P.plot_format(self.idx)
                        plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                        plt.close()
                else: # scatter many_plot summary=='full' multiple_run,multiple_batch,multiple_set
                    fig, ax = plt.subplots()    #open new figure for many plot

                    legend_label = dframe.columns
                    if len(dframe.columns) != 2:
                        print(">> Something wrong with data, check and retry!")
                        sys.exit (1)
                    col_A = dframe[dframe.columns[0]]
                    col_B = dframe[dframe.columns[1]]

                    ##Test
                    # print('\nPrint (plot.py): col_A')
                    # print(col_A)
                    # print('\nPrint (plot.py): col_B')
                    # print(col_B)

                    # edit colormap here
                    if self.__P.greyscale(self.idx):
                        colors = iter(cm.gray(np.linspace(0, 1, 1)))
                    else:
                        colors = iter(cm.rainbow(np.linspace(0, 1, 1)))

                    clr = next(colors)

                    if(self.analysistype == 'multiple_run'):
                        print("Analysis type: multiple_run")
                        print("Description: Show all runs, summary across agents")
                        nsets = len(dframe.index.levels[0])
                        nruns = len(dframe.index.levels[1])
                        niter = len(dframe.index.levels[2])
                        print("sets:", dframe.index.levels[0].values) #set values
                        print("runs:", dframe.index.levels[1].values) #run values
                        # print("iters:", dframe.index.levels[2].values) #iter values

                    if(self.analysistype == 'multiple_batch'):
                        print("Analysis type: multiple_batch")
                        print("Description: Show all batches, full runs")
                        nsets = len(dframe.index.levels[0])
                        nruns = 0
                        niter = len(dframe.index.levels[1])
                        print("sets:", dframe.index.levels[0].values) #set values
                        # print("iters:", dframe.index.levels[1].values) #iter values

                    if(self.analysistype == 'multiple_set'):
                        print("Analysis type: multiple_set")
                        print("Description: Show all sets, full batches")
                        nsets = 1
                        nruns = 0
                        niter = len(dframe)
                        #print("iters:", dframe.index.values) #iter values
                    
                    print("Length set list:", nsets)                        
                    print("Length run list:", nruns)                        
                    print("Length iter list:", niter)                        

                    if(self.analysistype == 'multiple_run'):
                        set_no = dframe.index.levels[0].values #names
                        run_no = dframe.index.levels[1].values #names
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                        plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_sets_' + str(nsets) + '_runs_' + str(nruns)
                    if(self.analysistype == 'multiple_batch'):
                        set_no = dframe.index.levels[0].values #names
                        run_no = "" #dframe.index.levels[1].values #names
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ' run ' + str(run_no) + ']', legend_label[0], legend_label[1], clr)
                        plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_sets_' + str(nsets)
                    if(self.analysistype == 'multiple_set'):
                        set_no = self.summary
                        run_no = "" #0
                        self.plot_scatterplot(ax, col_A, col_B, '[set ' + str(set_no) + ']', legend_label[0], legend_label[1], clr)
                        plot_name = str(self.agent) + '_' + str("_".join(self.variables)) + '_sets_' + str(nsets)

                    ##Scatter plot_name many_output not-agent summary-full case 5
                    #Note: this block is indented directly under plot_scatterplot, in order to have many plots
                    if self.__P.plot_name(self.idx):
                        plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                    
                    #Add a counter to the end
                    # if file_count != 0:
                    #     plot_name = str(plot_name) + '_' + str(file_count)

                    #if args.trace:
                    print("Scatterplot [case 5 many_output, analysis != Agent, summary==full]:")
                    print(plot_name)
                    #print("file_count= "+str(file_count))
                    
                    plot_format = self.__P.plot_format(self.idx)
                    plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
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
        self.analysistype = main_param['analysis']
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
    def plot_boxplot(self, ax, data, l_label, forced_ylabel):

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

        if self.__P.plot_title(self.idx) is not None:
            ax.set_title(self.__P.plot_title(self.idx))

        #Axes labels
        if self.__P.xlabel(self.idx) is None or self.__P.xlabel(self.idx) == 'Auto' or self.__P.xlabel(self.idx) == 'auto':
            ax.set_xlabel("Time")
        else:
            ax.set_xlabel(self.__P.xlabel(self.idx))

        if self.__P.ylabel(self.idx) is None or self.__P.ylabel(self.idx) == 'Auto' or self.__P.ylabel(self.idx) == 'auto':
            ax.set_ylabel(str(self.agent) + ' : ' + forced_ylabel)
        else:
            ax.set_ylabel(self.__P.ylabel(self.idx))

        #No axes labels
        if self.__P.xlabel(self.idx) == 'None' or self.__P.xlabel(self.idx) == 'none':
            ax.set_xlabel("")

        if self.__P.ylabel(self.idx) == 'None' or self.__P.ylabel(self.idx) == 'none':
            ax.set_ylabel("")

        plt.axis([self.__P.xmin(self.idx),self.__P.xmax(self.idx),self.__P.ymin(self.idx),self.__P.ymax(self.idx)])

        #TODO: Legend for boxplots
        # Use plt (matplotlib) instead of ax (pandas)? ax.set_legend does not exist
        #if self.__P.legend(self.idx) is True:
        #    plt.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        if self.__P.legend(self.idx) is True:
            ax.legend(loc=self.__P.legend_location(self.idx), fancybox=True, shadow=True)
        
        return ax

    def one_plot(self):

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
                self.plot_boxplot(ax, y[r], self.__data.columns[col], str(self.__data.columns[col]))

            #Boxplots plot_name one_plot case 1
            plot_name = str(self.agent) + '_' + str(self.__data.columns[col])
            if self.__P.plot_name(self.idx):
                plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
            
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
                self.plot_boxplot(ax, y[s], self.__data.columns[col], str(self.__data.columns[col]))
                
                #Boxplots plot_name many_output case 2
                plot_name = str(self.idx) + '_' + str(self.agent) + '_' + str(self.__data.columns[col])
                if self.__P.plot_name(self.idx):
                    plot_name = str(self.__P.plot_name(self.idx)) + '_' + plot_name
                
                plot_format = self.__P.plot_format(self.idx)
                plt.savefig(self.outpath + '/' + plot_name + "." + plot_format, format=plot_format, bbox_inches='tight')
                plt.close()
