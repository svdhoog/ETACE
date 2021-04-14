#!/usr/bin/env python3
import sys, os, argparse
import operator
import pandas as pd

# helper classes, imported from same directory
from parameters import A, main_configuration
from summarystats import SummaryStats
from plots import Plot
from transform import Transform


def erf(msg):  # function to output the error message and exit
    print(" >> Error: {0}".format(msg))
    sys.exit()

def dir_check(d):
    if os.path.exists(d):
        print("- Directory ["+os.path.basename(d)+ "] is used for output files")
        #test
        if args.verbose:
            print("os.path.basename(d)="+os.path.basename(d))

    else:
        os.makedirs(d)
        print("- Directory ["+os.path.basename(d)+ "] was created and is used for output files")
        #test
        if args.verbose:
            print("os.path.basename(d)="+os.path.basename(d))


def process_hdf_keys(string_in):  # function to extract set and run values from set_*_run_* string
    def find_between(s, first, last):
        try:
            start = s.index(first) + len(first)
            end = s.index(last, start)
            return s[start:end]
        except ValueError:
            return ""
    tmp_string = string_in.replace('_run_', ',')
    string_out = find_between(tmp_string, "/set_", "_iters")  # TODO: trailing slash might cause error, so before passing on check if trailing slash present, if yes remove
    return list(map(int, string_out.split(',')))

# unnecessary and can be removed
def process_string(string_in):
    def find_between(s, first, last):
        try:
            start = s.index(first) + len(first)
            end = s.index(last, start)
            return s[start:end]
        except ValueError:
            return ""
    return list([operator, float(string_out)])


def map_analysis(val):  # map analysis type from user input to parameter class
    analysis_values = {'agent': A.agent, 'multiple_run': A.multiple_run, 'multiple_batch': A.multiple_batch, 'multiple_set': A.multiple_set}
    return analysis_values[val]


def filter_by_value(dkey, dval, filtered):  # Function to filter the variables based on values
    if dval is not None:
        count = 0
        index = dkey
        df = pd.DataFrame(filtered[index])
        while count < len(dval):
            options = {'>': operator.gt, '<': operator.lt, '>=': operator.ge, '<=': operator.le, '==': operator.eq}  # operator.gt(a,b) :compare a&b, return all a larger than b
            val = str(dval[count][0])
            # df = df[options[val](filtered[index],dval[count][1])].dropna()
            df = df[options[val](filtered[index], dval[count][1])]
            count = count + 1
        return df
    else:
        df = pd.DataFrame(filtered[dkey])
        return df


# Function to bridge other classes (summarystats, transform, and plot)
def summary_and_plot(idx, P, df, par_fpath):  # idx = plot no, P = parameter object, df = data, parameter_filepath
    param = P.get_parameters()[idx]
    key = P.get_plotname_by_idx(idx)
    outpath = P.output_fpath()

    dir_check(outpath)

    if 'summary' in param.keys():  # If summary specified, compute summary-statistics
        P = SummaryStats(df, param)  # instantiate summary class
        data = P.compute_summary()  # compute summary
    else:
        data = df
    # TODO: add a boxplot check, and assign only for other cases, except boxplot, to save memory

    def plt_timeseries():
        T = Plot(idx, data, par_fpath)  # instantiate a plot object, idx = plot id, data = df
        T.timeseries(param, outpath)  # call timeseries method, param = parameters from main yaml, outpath = where to save output plot

    def plt_boxplot():
        B = Plot(idx, df, par_fpath)  # for boxplot whole df passed, not the one with summary
        B.boxplot(param, outpath)

    def plt_scatterplot():
        S = Plot(idx, data, par_fpath)
        S.scatterplot(param, outpath)

    def var_transform():  # for transform whole df passed, not the one with summary
        Tf = Transform(idx, df, par_fpath)
        Tf.main_method(outpath)

    def plt_histogram():
        H = Plot(idx, data, par_fpath)
        H.histogram(param, outpath)

    plot_function = {'timeseries': plt_timeseries, 'boxplot': plt_boxplot, 'histogram': plt_histogram, 'scatterplot': plt_scatterplot, 'transform': var_transform}
    return plot_function[key]()

# function to create a progressbar in verbose mode
def progress_bar(name, iteration, total, barLength=20):
    percent = int(round((iteration / total) * 100))
    nb_bar_fill = int(round((barLength * percent) / 100))
    bar_fill = '#' * nb_bar_fill
    bar_empty = ' ' * (barLength - nb_bar_fill)
    #newline = '\n'
    sys.stdout.write(str("\r{0}".format(name)).ljust(46) + "[{0}] {1}%".format(str(bar_fill + bar_empty), percent))
    sys.stdout.flush()


if __name__ == "__main__":

    parser = argparse.ArgumentParser(prog='main.py', description='FLAViz: Visualization and data transformation of timeseries data of agent-based models.')
    parser.add_argument('--configpath', '-p', help='Path to folder that contains the configuration (.yaml) files (config.yaml, plot_config.yaml)', nargs=1, type=str, required=True)
    parser.add_argument('--verbose', '-v', help='Activate the verbose mode which contains tracking steps and progress', required=False, action='store_false')
    args = parser.parse_args()
    P = main_configuration(args.configpath[0])  # instantiate main_configuration class to process main yaml files
    inpath = P.input_fpath()
    infiles = P.input_files()
    
    #test
    #if args.verbose:
    # print("\nPrint (main.py):")
    # print("\n inpath="+inpath)
    # print("\n infiles=")
    # print(infiles)   
    # print("\n")
    #print("\n outpath=")
    #print(outpath)

    primary_parameters = P.get_parameters()
    agent_storelist = {}  # all the agent HDF files are stored in this dict
    index = 0
    for key, value in infiles.items():
        f_p = str(inpath) + "/" + str(value)
        #agent_storelist[key] = pd.io.pytables.HDFStore(f_p)
        agent_storelist[key] = pd.io.pytables.HDFStore(f_p,  mode='r') # Is read-only mode needed here?
        # print a progressbar if verbose mode is activated
        if not args.verbose:
            index+=1
            progress_bar("Step 1: Preparing data structure ", index, len(infiles.items()))
    if not args.verbose:
        sys.stdout.write("\n")
    agent_dframes = {}  # All the main dataframes of different agenttypes are stored in this dict

    index = 0

    #test
    #print('\nPrint (main.py): agent_storelist.items()') #prints contents summary of h5 files
    #print(agent_storelist.items())
        
    for agentname, agentstore in agent_storelist.items():
        
        #test
        #print("\nPrint (main.py): agentname="+agentname)
        #print(agentname)
                
        d = pd.DataFrame()  # Main dataframe to hold all the dataframes of each instance (one agenttype)
        df_list = []
        
        #test
        #print('\nPrint (main.py): agentstore.keys()')
        #print(agentstore.keys())
        
        for key in agentstore.keys():  # go through sets and runs in the HDF file
            sets_runs = process_hdf_keys(key)  # get set and run values from the names: set_1_run_1_iters etc. hardcoded for set_*_run_*_iters atm

            ##test
            # print('\nPrint (main.py): sets_runs')
            # print('key='+key)
            # print('process_hdf_keys(key)=')
            # print(process_hdf_keys(key))
            # print('sets_runs=')
            # print(sets_runs)    #prints set nos. and contents summary of hdf5
            # print('sets_runs[0]= '+str(sets_runs[0])) #prints set nos.
            # print('sets_runs[1]= '+str(sets_runs[1]))  #prints content summary of hdf5

            s = sets_runs[0]
            r = sets_runs[1]
            #pnl = agentstore.select(key)  # open datapanel for particular set and run
            df = agentstore.select(key)  # open datapanel for particular set and run

            #test
            #print('\nPrint (main.py): pnl')
            #print(pnl)
            #print(pnl.shape)            
            
            #df = pnl.to_frame()  # convert panel to Dataframe

            #test
            #print('\nPrint (main.py): df')
            #print(df)
            #print(df.shape)            

            # Add two columns for set and run into the dataframe for two added level of indexing
            df['set'] = s
            df['run'] = r
            df.set_index('run', append=True, inplace=True)
            df.set_index('set', append=True, inplace=True)
            df_list.append(df.reorder_levels(['set', 'run', 'major', 'minor']))

        #test
        #print('\nPrint (main.py): df_list')
        #print(df_list)
        
        
        d = pd.concat(df_list)  # Add each dataframe from panel into a main dataframe containing all sets and runs
        del df_list
        agent_dframes[agentname] = d  # this dict contains agent-type names as keys, and the corresponding dataframes as values
        agentstore.close()

        #test
        #print('\nPrint (main.py): d')
        #print(d)
        #print(agent_dframes[agentname])

        # print a progressbar if verbose mode is activated
        if not args.verbose:
            index += 1
            progress_bar("Step 2: Processing data file " , index, len(agent_storelist.items()))
    if not args.verbose:
        sys.stdout.write("\n")
    del agent_storelist

    index = 0
    for idx, param in primary_parameters.items():  # read filter conditions from yaml
        frames = []  # list to store filtered dfs according to vars
        var_dic = {}
        for i, j in param['variables'].items():
            if len(j) > 1:
                var_filter_list = []
                #for s in range(1, len(j)):
                for s in range(0, len(j)):
                    #var_filter_list.append(process_string(j[s]))
                    var_dic[j[s]] = None
                #var_dic[j[0]] = var_filter_list
            else:
                var_dic[j[0]] = None
            var_list = list(var_dic.keys())


        ##memory-heavy version        
        #d = agent_dframes[param['agent']]  # comment: this can be replaced in line below to save memory, here now just for simplicity. See memory-saving version

        ## check if table columns contain the given variables from config file
        #for i, entry in enumerate(var_list):
        #    if not (entry in list(d)):
        #        erf("Table has columns {0} and var{1}='{2}' does not match.".format(list(d), i+1, entry))

        ## stage-I filtering, all input vars are sliced with desired set & run values
        #filtered = d.iloc[(d.index.get_level_values('set').isin(param['set'])) & (d.index.get_level_values('run').isin(param['run'])) & (d.index.get_level_values('major').isin(param['major'])) & (d.index.get_level_values('minor').isin(param['minor']))][var_list].dropna().astype(float)

        ##memory-saving version
        # check if table columns contain the given variables from config file
        for i, entry in enumerate(var_list):
            if not (entry in list(agent_dframes[param['agent']])):
                erf("Table has columns {0} and var{1}='{2}' does not match.".format(list(agent_dframes[param['agent']]), i+1, entry))

        # stage-I filtering, all input vars are sliced with desired set & run values
        filtered = agent_dframes[param['agent']].iloc[(agent_dframes[param['agent']].index.get_level_values('set').isin(param['set'])) & (agent_dframes[param['agent']].index.get_level_values('run').isin(param['run'])) & (agent_dframes[param['agent']].index.get_level_values('major').isin(param['major'])) & (agent_dframes[param['agent']].index.get_level_values('minor').isin(param['minor']))][var_list].dropna().astype(float)

        df_main = pd.DataFrame()
        index1 = 0
        for dkey, dval in var_dic.items():
            df = filter_by_value(dkey, dval, filtered)  # stage-II filtering for selecting variables according to their values
            if df_main.empty:
                df_main = df
            else:
                df_main = pd.concat([df_main, df], axis=1)
            del df

            # print a progressbar if verbose mode is activated
            if not args.verbose:
                index1 += 1
                progress_bar("Step 3: Filtering/Plotting data for: {0} ".format(idx), index1, len(var_dic.items()))
        if not args.verbose:
            sys.stdout.write("\n")
        summary_and_plot(idx, P, df_main, args.configpath[0])  # plot index, parameter object, data, parameter_filepath
        var_dic.clear()  # clear dict of mapping between plot var and operator (for next cycle)
        del var_list[:]  # clear the list of variables for next cycle


###################################################################################################################################
# TODO: add support for multiple agent types within a single plot, new entry in yaml (replace agent with, agent1, agent2), and parse
# TODO: currently the filtering is done in two steps, find a way to do it in a single step
# TODO: main data reprocessed for different types of plot (separate the processing and plot from loop to process main data just once
