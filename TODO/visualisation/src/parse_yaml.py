import yaml

with open("config.yaml", 'r') as stream:
    try:
        #print(yaml.load(stream))
        d = yaml.load(stream)
        #print a.keys()
    except yaml.YAMLError as exc:
        print(exc)

print d['timeseries'] 

