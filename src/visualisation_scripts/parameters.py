#!/usr/bin/env python3
import sys
import yaml
import argparse
from pathlib import Path

class A:
    # Types of analysis
    agent, multiple_run, multiple_batch, multiple_set = range(4)
    # 0, 1, 2, 3


class M:
    # Types of statistical summary
    mean, median, upper_quartile, lower_quartile, custom_quantile, minimum, maximum, full = range(8)
    # 0, 1, 2, 3, 4, 5


class NP:
    # Nature of Plots i.e. single output per analysis or multiple outputs per analysis
    one, many = range(2)
    # 0, 1


class main_configuration():

    def __init__(self, in_fpath):
        self.main_f = in_fpath + '/config.yaml' # the main configuration file
        self.parsed_values = self.parse_yaml(self.main_f)

    def erf(self, msg):  # function to output the error message and exit
        print(" >> Error: %s" % msg)
        sys.exit()

    def parse_yaml(self, fname):  # Function to parse input parameters from the main configuration file
        try:
            f = open(fname, 'r')
        except IOError:
            self.erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream, Loader=yaml.FullLoader)
            except yaml.YAMLError as exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print(" >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname))
                else:
                    print(" >> Unknown problem with %s file:" % fname)
                sys.exit()
            return p

    def process_parameters(self, p):  # Function to process the parsed configuration file values to make them usable
        indices = ['set', 'run', 'major', 'minor']
        for i in indices:
            if 'range' in str(p[i][0]):  # check if range defined in input configuration file
                x = p[i][1]
                try:
                    if len(x) < 3: x.append(1)  # if no step size defined in input, add default stepsize of one
                    p[i] = range(x[0], x[1] + x[2], x[2])  # include last value, to make range of yaml file inclusive
                except:
                    raise AssertionError("In file %s: range expects a list, single value given instead" % self.main_f)
        return p

    def map_idx_plotname(self):
        d = {}
        for key in self.parsed_values.keys():
            if key not in 'i/o':
                inner_dic = self.parsed_values[key]
                for k in inner_dic.keys():
                    d[key] = k
        return d

    def get_plotname_by_idx(self, idx):
        inner_dic = self.parsed_values[idx]
        for k in inner_dic.keys():
            return k

    def get_parameters(self):
        d = {}
        for key in self.parsed_values.keys():
            if key not in 'i/o':
                inner_dic = self.parsed_values[key]
                req_par =['agent','analysis','variables','set','run','major','minor','summary']
                for p in req_par:
                    if p not in inner_dic[self.get_plotname_by_idx(key)].keys():
                        self.erf(p + " not specified in configuration file")
                for v in inner_dic.values():
                    d[key] = self.process_parameters(v)
        return d

    def input_fpath(self):
        if 'i/o' in self.parsed_values.keys():
            path_config = self.parsed_values['i/o']['input_path']
            if path_config[:1] == '/': # check for full path inside config
                input_path = str(Path(path_config))
                return input_path
            else: # use the path from config as relative path
                repo_name = self.parsed_values['i/o']['repo_name']
                repo_path = str(Path("").absolute()).rsplit(repo_name, 1)[0] + repo_name
                input_path = repo_path + '/' + path_config # fix to repo root
                return input_path
        return self.erf("Missing input path!")

    def output_fpath(self):
        if 'i/o' in self.parsed_values.keys():
            #output_path = Path(self.parsed_values['i/o']['output_path'])
            path_config = self.parsed_values['i/o']['output_path']
            if path_config[:1] == '/': # check for full path inside config
                output_path = str(Path(path_config))
                return output_path
            else: # use the path from config as relative path
                repo_name = self.parsed_values['i/o']['repo_name']
                repo_path = str(Path("").absolute()).rsplit(repo_name, 1)[0] + repo_name
                output_path = repo_path + '/' + path_config
                return output_path
        return self.erf("Missing output path!")

    def input_files(self):
        if 'i/o' in self.parsed_values.keys():
            return self.parsed_values['i/o']['input_files']
        return self.erf("Missing input files!")


class transform_configuration():

    def __init__(self, in_fpath):

        self.transform_f = in_fpath + '/config_transform.yaml' # the configuration file for variable transformations
        self.parsed_values = self.parse_yaml(self.transform_f)

    def erf(self, msg):  # function to output the error message and exit
        print(" >> Error: %s" % msg)
        sys.exit()

    def parse_yaml(self, fname):  # Function to parse input parameters from the main configuration file
        try:
            f = open(fname, 'r')
        except IOError:
            self.erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream, Loader=yaml.FullLoader)
            except yaml.YAMLError as exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print(" >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname))
                else:
                    print(" >> Unknown problem with %s file:" % fname)
                sys.exit()
            return p

    def get_parameters(self, idx):
        inner_dic = self.parsed_values[idx]
        return inner_dic


class Plot_configuration():

    def __init__(self, p_fpath):

        self.plot_f = p_fpath + '/plot_config.yaml' # the configuration file for plot options (matplotlib) 
        self.__param = self.parse_yaml(self.plot_f)
        self.__default_plot_parameters = Figure_default_parameters()

    def erf(self, msg):
        print(" >> Error: %s" % msg)
        sys.exit()

    def get_fig_values(self, key):
        for k, v in self.__param[key].items():
            if k in self.__default_plot_parameters.__dict__.keys():  # check if parameter specified, replace default with specific value
                self.__default_plot_parameters.__dict__[k] = v
        return self.__default_plot_parameters.__dict__
        # TODO: check for non existent values, exception handling

    def parse_yaml(self, fname):
        try:
            f = open(fname, 'r')
        except IOError:
            self.erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream, Loader=yaml.FullLoader)
            except yaml.YAMLError as exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print(" >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname))
                else:
                    print(" >> Unknown problem with %s file:" % fname)
                sys.exit()
            return p

    def legend(self, key):
        if 'plot_legend' in self.__param[key].keys():
            return self.__param[key]['plot_legend']
        return self.__default_plot_parameters.__dict__['plot_legend']

    def legend_label(self, key):
        if 'legend_label' in self.__param[key].keys():
            return self.__param[key]['legend_label']
        return self.__default_plot_parameters.__dict__['legend_label']

    def legend_location(self, key):
        if 'legend_location' in self.__param[key].keys():
            return self.__param[key]['legend_location']
        return self.__default_plot_parameters.__dict__['legend_location']

    def plot_type(self, key):
        if 'plot_type' in self.__param[key].keys():
            return self.__param[key]['plot_type']
        return self.__default_plot_parameters.__dict__['plot_type']

    def num_plots(self, key):
        if 'number_plots' in self.__param[key].keys():
            return self.__param[key]['number_plots']
        return self.__default_plot_parameters.__dict__['number_plots']

    def ylabel(self, key):
        if 'ylabel' in self.__param[key].keys():
            return self.__param[key]['ylabel']
        return self.__default_plot_parameters.__dict__['ylabel']

    def xlabel(self, key):
        if 'xlabel' in self.__param[key].keys():
            return self.__param[key]['xlabel']
        return self.__default_plot_parameters.__dict__['xlabel']

    def plot_title(self, key):
        if 'plot_title' in self.__param[key].keys():
            return self.__param[key]['plot_title']
        return self.__default_plot_parameters.__dict__['plot_title']

    def plot_name(self, key):
        if 'plot_name' in self.__param[key].keys():
            return self.__param[key]['plot_name']
        return self.__default_plot_parameters.__dict__['plot_name']

    def plot_format(self, key):
        if 'plot_format' in self.__param[key].keys():
            return self.__param[key]['plot_format']
        return self.__default_plot_parameters.__dict__['plot_format']

    def xmin(self, key):
        if 'xmin' in self.__param[key].keys():
            return self.__param[key]['xmin']
        return self.__default_plot_parameters.__dict__['xmin']

    def xmax(self, key):
        if 'xmax' in self.__param[key].keys():
            return self.__param[key]['xmax']
        return self.__default_plot_parameters.__dict__['xmax']

    def ymin(self, key):
        if 'ymin' in self.__param[key].keys():
            return self.__param[key]['ymin']
        return self.__default_plot_parameters.__dict__['ymin']

    def ymax(self, key):
        if 'ymax' in self.__param[key].keys():
            return self.__param[key]['ymax']
        return self.__default_plot_parameters.__dict__['ymax']

    def linestyle(self, key):
        if 'linestyle' in self.__param[key].keys():
            return self.__param[key]['linestyle']
        return self.__default_plot_parameters.__dict__['linestyle']

    def marker(self, key):
        if 'marker' in self.__param[key].keys():
            return self.__param[key]['marker']
        return self.__default_plot_parameters.__dict__['marker']

    def markersize(self, key):
        if 'markersize' in self.__param[key].keys():
            return self.__param[key]['markersize']
        return self.__default_plot_parameters.__dict__['markersize']

    def markerfacecolor(self, key):
        if 'markerfacecolor' in self.__param[key].keys():
            return self.__param[key]['markerfacecolor']
        return self.__default_plot_parameters.__dict__['markerfacecolor']

    def facecolors(self, key):
        if 'facecolors' in self.__param[key].keys():
            return self.__param[key]['facecolors']
        return self.__default_plot_parameters.__dict__['facecolors']

    def bins(self, key):
        if 'bins' in self.__param[key].keys():
            return self.__param[key]['bins']
        return self.__default_plot_parameters.__dict__['bins']

    def histtype(self, key):
        if 'histtype' in self.__param[key].keys():
            return self.__param[key]['histtype']
        return self.__default_plot_parameters.__dict__['histtype']

    def stacked(self, key):
        if 'stacked' in self.__param[key].keys():
            return self.__param[key]['stacked']
        return self.__default_plot_parameters.__dict__['stacked']

    def normed(self, key):
        if 'normed' in self.__param[key].keys():
            return self.__param[key]['normed']
        return self.__default_plot_parameters.__dict__['normed']

    def fill_between(self, key):
        if 'fill_between' in self.__param[key].keys():
            return self.__param[key]['fill_between']
        return self.__default_plot_parameters.__dict__['fill_between']

    def fillcolor(self, key):
        if 'fillcolor' in self.__param[key].keys():
            return self.__param[key]['fillcolor']
        return self.__default_plot_parameters.__dict__['fillcolor']

    def greyscale(self, key):
        if 'greyscale' in self.__param[key].keys():
            return self.__param[key]['greyscale']
        return self.__default_plot_parameters.__dict__['greyscale']


class Figure_default_parameters(object):
    def __init__(self):
        self.plot_legend = 'no'
        self.legend_label = None
        self.legend_location = 'best'
        self.plot_type = None
        self.number_plots = 'many'
        self.plot_name = None
        self.plot_format = 'png'
        self.xmin = None
        self.xmax = None
        self.ymin = None
        self.ymax = None
        self.linestyle = 'solid'
        self.marker = 4
        self.markerfacecolor = None
        self.markersize = None
        self.facecolors = None
        self.plot_title = None
        self.xlabel = None
        self.ylabel = None
        self.bins = 50
        self.histtype = 'bar'
        self.stacked = False
        self.normed = 1
        self.fill_between = False
        self.fillcolor = 'black'
        self.greyscale = False


if __name__ == "__main__":
    C = main_configuration()
