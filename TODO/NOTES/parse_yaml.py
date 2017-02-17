import sys
import yaml

with open("config.yaml", 'r') as stream:
    try:
        #print(yaml.load(stream))
        d = yaml.load(stream)
        #print d.keys()
    except yaml.YAMLError as exc:
        print(exc)


def process_parsed_values(d): 
    indices = ['set','run','major','minor']     
    for i in indices:
        try:
            if d.get(i) is not None:         
                if 'range' in str(d[i][0]):                       
                    x = d[i][1]
                    if len(x)<3: x.append(1) 
                    d[i] = range(x[0],x[1],x[2])
            else:
                print("Required parameters missing in the config.yaml file!")
                sys.exit(1)
        except AttributeError:
            print "error bhayo bhai"
            # some inputs are not a dict, but just a string i.e. input, output path so skipping
            pass
    return d

for key in d.keys():
    if key not in'i/o':
        inner_d = d[key]        
        for k in inner_d.keys():
            d_plt = inner_d[k]
            #print d_plt 
            param = process_parsed_values(d_plt)    
    #print param['plot properties']['number_plots']
    #print param['analysis']

#print NP.single





