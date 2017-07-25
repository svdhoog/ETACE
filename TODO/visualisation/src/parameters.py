#!/usr/bin/env python

import sys, os, yaml


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


class main_configuration:    
    
    def __init__(self):                 
        self.main_f = 'config.yaml'   # the main configuration file
        self.parsed_values = self.parse_yaml(self.main_f)
    
    def erf(msg): # function to output the error message and exit
        print " >> Error: %s" % msg
        sys.exit()
        
    def parse_yaml(self,fname):  # Function to parse input parameters from the main configuration file
        try:
            f = open(fname, 'r')
        except IOError:
            erf("unable to read file: %s" % fname)
        with f as stream:
            try:
                p = yaml.load(stream)
            except yaml.YAMLError, exc: # error-check for incorrect yaml syntax
                if hasattr(exc, 'problem_mark'):
                    mark = exc.problem_mark
                    print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, fname)
                else:
                    print " >> Unknown problem with %s file:" % fname
                sys.exit()
            return p                

    
    def process_parameters(self, p): # Function to process the parsed configuration file values to make them usable
        indices = ['set','run','major','minor']    
        for i in indices:
            if 'range' in str(p[i][0]):  # check if range defined in input configuration file
                x = p[i][1]
                try:              
                    if len(x)<3: x.append(1) # if no step size defined in input, add default stepsize of one
                    p[i] = range(x[0],x[1]+x[2],x[2]) # include last value, to make range of yaml file inclusive
                except:
                    raise AssertionError("In file %s: range expects a list, single value given instead" % main_f)
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
                


def process_string( string_in ):
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    operator = string_in.partition("[")[0]
    string_out = find_between(string_in,"[","]")
    return list([operator,float(string_out)])




                    
if __name__ == "__main__":
    C = main_configuration()
    #print C.get_plot_type()
    #print C.get_parameters()
    for k, v in C.get_parameters().items():
        print k
        #print v['variables']
        var_dic = {}
        for i, j in v['variables'].items():
            #print j[0]
            if len(j)>1:
                var_filter_list = []
                for s in range(1,len(j)):
                    var_filter_list.append(process_string(j[s]))
                var_dic[j[0]] = var_filter_list
            else:
                var_dic[j[0]] = None

        print C.get_pltname_for_idx(k) 
    #print var_dic
        #print v['minor']
    #print C.map_idx_plotname()
    #print C.input_fpath()
    #print C.output_fpath()

       



































