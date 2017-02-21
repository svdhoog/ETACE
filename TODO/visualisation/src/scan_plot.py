import sys
import yaml
#from parameters import A, M, NP

with open("plot_config.yaml", 'r') as stream:
    try:
        #print(yaml.load(stream))
        d = yaml.load(stream)
        #print a.keys()
    except yaml.YAMLError as exc:
        print(exc)

for key, value in d.iteritems():           
    print d[key]['plot_type']
    print value    
