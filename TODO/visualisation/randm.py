from parameters import NP, A
from summarystats import SummaryStats
import numpy as np
import pandas as pd
import yaml
import matplotlib.pyplot as plt
plt.style.use('ggplot')

class Plot_configuration():

    def __init__(self):
        self.plot_f = 'plot_config.yaml'
        self.__param = self.parse_yaml(self.plot_f)

    def erf(self, msg):
        print " >> Error: %s" % msg
        sys.exit()

    def get_p_val(self, key):
        return self.__param[key]

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



class init_mpl_vals(object):
    def __init__(self, **kw):
        self.linestyle = 1
        self.marker = 4
        self.markerfacecolor = None
        self.markersize = None
        self.label = None


class custom_figure_properties(init_mpl_vals):
    def __init__(self, **kwargs):
        print kwargs
        super(custom_figure_properties, self).__init__(**kwargs)
        self.__P = Plot_configuration()
        for k, v in self.get_val('plot1').items():
            kwargs[k] = v
        #for k, v in kwargs.items():
        #    kwargs[k] = v
        print kwargs
        
    def haha(self):
        for k, v in kwargs.items():
            print k, v

    def get_val(self, val):
        return self.__P.get_p_val(val)

#C = custom_figure_properties(linestyle = 'krishna', label ='sezma')

C = custom_figure_properties()

print C.linestyle
print C.marker
print C.markerfacecolor
print C.markersize
print C.label




C.get_val('plot1').keys()




