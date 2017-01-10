import yaml

with open("config.yaml", 'r') as stream:
    try:
        #print(yaml.load(stream))
        d = yaml.load(stream)
        #print a.keys()
    except yaml.YAMLError as exc:
        print(exc)

#print d


for key in d.keys():
    d_plt = d[key]    
    #for d in d_plt.itervalues():    
        #print d
    if 'range' in str(d_plt['set'][0]):
        x = d_plt['set'][1]
        if len(x)<3: x.append(1) 
        d_plt['set'] = range(x[0],x[1],x[2])
        print d_plt
    if 'range' in str(d_plt['run'][0]):
        x = d_plt['run'][1]
        if len(x)<3: x.append(1)       
        d_plt['run'] = range(x[0],x[1],x[2])
        print d_plt
    if 'range' in str(d_plt['major'][0]):
        x = d_plt['major'][1]
        if len(x)<3: x.append(1)      
        d_plt['major'] = range(x[0],x[1],x[2])
        print d_plt 
    if 'range' in str(d_plt['minor'][0]):
        x = d_plt['minor'][1]
        if len(x)<3: x.append(1)        
        d_plt['minor'] = range(x[0],x[1],x[2])
        print d_plt  
    



    #print d_plt['major'][1]
    
