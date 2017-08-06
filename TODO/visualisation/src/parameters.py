#!/usr/bin/env python
import sys
import yaml


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

    def __init__(self):
        self.main_f = 'config.yaml'  # the main configuration file
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

    def __init__(self):
        self.plot_f = 'plot_config.yaml'
        self.__param = self.parse_yaml(self.plot_f)

    def erf(self, msg):
        print " >> Error: %s" % msg
        sys.exit()

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
        return self.__param[key]['plot_legend']

    def legend_label(self, key):
        return self.__param[key]['legend_label']

    def legend_location(self, key):
        return self.__param[key]['legend_location']

    def plot_type(self, key):
        return self.__param[key]['plot_type']

    def num_plots(self, key):
        return self.__param[key]['number_plots']

    def y_label(self, key):
        return self.__param[key]['y-axis label']

    def x_label(self, key):
        return self.__param[key]['x-axis label']

    def plot_name(self, key):
        return self.__param[key]['plot_name']

    def llim(self, key):
        return self.__param[key]['l_lim']

    def ulim(self, key):
        return self.__param[key]['u_lim']

    def linestyle(self, key):
        return self.__param[key]['linestyle']

    def marker(self, key):
        return self.__param[key]['marker']

    def markersize(self, key):
        return self.__param[key]['markersize']

    def markerfacecolor(self, key):
        return self.__param[key]['markerfacecolor']


if __name__ == "__main__":
    C = main_configuration()
