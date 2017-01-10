import yaml

with open("config.yaml", 'r') as stream:
    try:
        #print(yaml.load(stream))
        d = yaml.load(stream)
        #print a.keys()
    except yaml.YAMLError as exc:
        print(exc)


def process_parsed_values(d): 
    indices = ['set','run','major','minor']    
    for i in indices:
        if 'range' in str(d[i][0]):
            x = d[i][1]
            if len(x)<3: x.append(1) 
            d[i] = range(x[0],x[1],x[2])
    return d


for key in d.keys():
    d_plt = d[key] 
    param = process_parsed_values(d_plt)

#print param





