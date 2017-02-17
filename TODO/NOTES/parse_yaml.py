import sys
import yaml

config_fname = 'config.yaml'

def get_parameters():
    try:
        f = open(config_fname, 'r')
    except IOError:
        erf("unable to read file: %s" % config_fname)

    with f as stream:
        try:
            p = yaml.load(stream)
        except yaml.YAMLError, exc: # error-check for incorrect yaml syntax
            if hasattr(exc, 'problem_mark'):
                mark = exc.problem_mark
                print " >> Error in line: (%s:%s) in file: %s" % (mark.line+1, mark.column+1, config_fname)
            else:
                print " >> Unknown problem with %s file:" % config_fname
            sys.exit()
        return p        

def process_parameters(d):
        indices = ['set','run','major','minor']     
        for i in indices:
            if d.get(i) is not None:         
                if 'range' in str(d[i][0]):                       
                    x = d[i][1]
                    if len(x)<3: x.append(1) 
                    d[i] = range(x[0],x[1],x[2])
            else:
                print("Required parameters missing in the config.yaml file!")
                sys.exit(1)
        return d

x = get_parameters()
for key in x.keys():
    if key not in'i/o':
        inner_d = x[key]        
        for k in inner_d.keys():
            d_plt = inner_d[k]
            #print d_plt 
            param = process_parameters(d_plt)    
            #print param['variables']['var2']
            print param['variables']['var2']
            ########################################################
            ###TODO### check for length and parse the string    
            print len(param['variables']['var2'])
            ############################################################            
            var_list =[]
            for k in param['variables'].keys():
                var_list.append(param['variables'][k][0])
            #print var_list
            # call the filtering part here, and then delete the list
            del var_list[:]
            #print param['analysis']
 
