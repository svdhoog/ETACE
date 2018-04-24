

class quantiles(A,M,NP):

    N = 1000
    
    def multiple_output(df):
        # TODO
        

    def single_output(df):
        idx = df.keys()
        for i in idx:
            d = df[i]
            y =[]
            for j in range(0,len(d),N):
                y.append(np.array(d[j:j+N]))
            for j in range(0,len(d)/N):
                x = np.linspace(0, N, N, endpoint=True)
                plt.plot(x,y[j])          
                plt.hold(True)	 
        plot_name = "summary_main.png"
        plt.savefig(plot_name, bbox_inches='tight')
        plt.show()      
