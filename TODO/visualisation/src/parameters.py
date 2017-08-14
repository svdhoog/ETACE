#!/usr/bin/env python
import sys
import yaml
import argparse


class A:
    # Types of analysis
    agent, multiple_run, multiple_batch, multiple_set = range(4)
    # 0, 1, 2, 3


class M:
    # Types of statistical summary
    mean, median, upper_quartile, lower_quartile, custom_quantile, minimum, maximum = range(7)
    # 0, 1, 2, 3, 4, 5


class NP:
    # Nature of Plots i.e. single output per analysis or multiple outputs per analysis
    one, many = range(2)
    # 0, 1


class main_configuration():

    def __init__(self, in_fpath):
        #self.main_f = 'config.yaml'  # the main configuration file
        self.main_f = in_fpath + '/config.yaml'
        self.parsed_values = self.parse_yaml(self.main_f)

    def erf(self, msg):  # function to output the error message and exit
        print " >> Error: %s" % msg
        sys.exit()

    def parse_yaml(self, fname):  # Function to parse input parameters from the main configuration file
        try:
            f = open(fname, 'r')
        except IOError:
            self.erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream)
            except yaml.YAMLError, exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname)
                else:
                    print " >> Unknown problem with %s file:" % fname
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
                for v in inner_dic.values():
                    d[key] = self.process_parameters(v)
        return d

    def input_fpath(self):
        if 'i/o' in self.parsed_values.keys():
            return self.parsed_values['i/o']['input_path']
        return self.erf("Missing input path!")

    def output_fpath(self):
        if 'i/o' in self.parsed_values.keys():
            return self.parsed_values['i/o']['output_path']
        return self.erf("Missing output path!")


class Plot_configuration():

    def __init__(self, p_fpath):
        #self.plot_f = 'plot_config.yaml'
        self.plot_f = p_fpath + '/plot_config.yaml'
        self.__param = self.parse_yaml(self.plot_f)


        self.__default_plot_parameters = Figure_default_parameters()

    def erf(self, msg):
        print " >> Error: %s" % msg
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
                p = yaml.load(stream)
            except yaml.YAMLError, exc:  # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname)
                else:
                    print " >> Unknown problem with %s file:" % fname
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

    def y_label(self, key):
        if 'yaxis_label' in self.__param[key].keys():
            return self.__param[key]['yaxis_label']
        return self.__default_plot_parameters.__dict__['yaxis_label']

    def x_label(self, key):
        if 'xaxis_label' in self.__param[key].keys():
            return self.__param[key]['xaxis_label']
        return self.__default_plot_parameters.__dict__['xaxis_label']

    def plot_title(self, key):
        if 'plot_title' in self.__param[key].keys():
            return self.__param[key]['plot_title']
        return self.__default_plot_parameters.__dict__['plot_title']

    def plot_name(self, key):
        if 'plot_name' in self.__param[key].keys():
            return self.__param[key]['plot_name']
        return self.__default_plot_parameters.__dict__['plot_name']

    def llim(self, key):
        if 'l_lim' in self.__param[key].keys():
            return self.__param[key]['l_lim']
        return self.__default_plot_parameters.__dict__['l_lim']

    def ulim(self, key):
        if 'u_lim' in self.__param[key].keys():
            return self.__param[key]['u_lim']
        return self.__default_plot_parameters.__dict__['u_lim']

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
        if 'number_bins' in self.__param[key].keys():
            return self.__param[key]['number_bins']
        return self.__default_plot_parameters.__dict__['number_bins']

    def histtype(self, key):
        if 'histtype' in self.__param[key].keys():
            return self.__param[key]['histtype']
        return self.__default_plot_parameters.__dict__['histtype']

    def stacked(self, key):
        if 'stacked' in self.__param[key].keys():
            return self.__param[key]['stacked']
        return self.__default_plot_parameters.__dict__['stacked']

    def norm(self, key):
        if 'normed' in self.__param[key].keys():
            return self.__param[key]['normed']
        return self.__default_plot_parameters.__dict__['normed']

    def fill(self, key):
        if 'fill' in self.__param[key].keys():
            return self.__param[key]['fill']
        return self.__default_plot_parameters.__dict__['fill']






class Figure_default_parameters(object):
    def __init__(self):
        self.plot_legend = 'no'
        self.legend_label = None
        self.legend_location = 'best'
        self.plot_type = None
        self.number_plots = 'one'
        self.plot_name = 'default_fig.png'
        self.l_lim = None
        self.u_lim = None
        self.linestyle = 1
        self.marker = 4
        self.markerfacecolor = None
        self.markersize = None
        # self.label = None
        self.facecolors = None
        self.plot_title = None
        self.xaxis_label = None
        self.yaxis_label = None
        self.number_bins = 50
        self.histtype = 'bar'
        self.stacked = False
        self.normed = 1
        self.fill = False


if __name__ == "__main__":
    C = main_configuration()
