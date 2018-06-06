

/*
 * \fn: sum_array
 * \brief: Sum from start to end in reverse order, sum_array(&x, start, enc) = sum[t-start,...,t-end]
 * \brief: QoQ sum:  sum_array(&X,1,3)=sum[t-1,...,t-3]
 * \brief: YoY sum:  sum_array(&X,1,12)=sum[t-1,...,t-12]
 */
void sum_array(double_array * x, int start, int end, double * sum_out)
{
    int i,n;
    double sum=0.0;

    n = (*x).size;

/*
    printf("\n\nSize in function: %d;", n);
    for (i=0; i<(*x).size; i++)
      printf(" %2.2f", (*x).array[i]);
*/
    if(0<=start && start<=end && end<=n-1)
    {
        //printf("\n\nCondition true: start %d end %d [0<=start (%d) && start<=end (%d) && end<=n-1 (%d)]", start, end, (0<=start), (start<=end), (end<=n-1));
        for(i=start; i<=end; i++)
        {
            sum += (*x).array[i];
            //printf("\nFor-loop sum %2.2f", sum);
        }

    }else
    {
	        fprintf(stderr, "\n\n WARNING: sum_array fails. Condition is false (1=true, 0=false): start %d end %d [0<=start (%d) && start<=end (%d) && end<=n-1 (%d)]\nExiting sum_array\n", start, end, (0<=start), (start<=end), (end<=n-1));
    }
    
    (*sum_out) = sum;
}

/*
 * \fn: sum_array_backwards
 * \brief: Sum from start to end in reverse order, sum_array(&x, start, enc) = sum[t-start,...,t-end]
 * \brief: QoQ sum:  sum_array(&X,1,3)=sum[t-1,...,t-3]
 * \brief: YoY sum:  sum_array(&X,1,12)=sum[t-1,...,t-12]
 */
void sum_array_backwards(double_array * x, int start, int end, double * sum_out)
{
    int i,n;
    double sum=0.0;

    n = (*x).size;

/*
    printf("\n\nSize in function: %d;", n);
    for (i=0; i<(*x).size; i++)
      printf(" %2.2f", (*x).array[i]);
*/
    if(0<start && start<=end && end<=n)
    {
        //printf("\n\nCondition true: start %d end %d [0<=start (%d) && start<=end (%d) && end<=n-1 (%d)]", start, end, (0<=start), (start<=end), (end<=n-1));
        for(i=n-start; i>=n-end; i--)
        {
            sum += (*x).array[i];
            //printf("\nFor-loop sum %2.2f", sum);
        }
    }else
    {
        	fprintf(stderr, "\n\nIT %d WARNING: sum_array_backwards fails. Condition is false (1=true, 0=false): start %d end %d [0<=start (%d) && start<=end (%d) && end<=n (%d)]\nExiting sum_array_backwards\n", DAY, start, end, (0<start), (start<=end), (end<=n));
	}

    (*sum_out) = sum;
}

/*
 * Ratio
 * QoQ:  ratio_qoq(&X)=sum[t-1,...,t-3] / sum[t-4,...,t-6] = sum_array(&X,1,3) / sum_array(&X,4,6)
 */
double ratio_qoq(double_array * x)
{
    double a =  0.0;
    double b = 0.0;

    sum_array_backwards(x,1,3, &a);
    sum_array_backwards(x,4,6, &b);

    //printf("\nBefore return a=%2.2f b=%2.2f", a, b);

    return ((double)a)/((double)b);
}

/*
 * Ratio
 * YoY:  ratio_yoy(&X)=sum[t-1,...,t-12] / sum[t-13,...,t-24] = sum_array(&X,1,12) / sum_array(&X,13,24)
 */
double ratio_yoy(double_array * x)
{
    double a =  0.0;
    double b = 0.0;

    sum_array_backwards(x,1,12, &a);
    sum_array_backwards(x,13,24, &b);

    //printf("\nBefore return a=%2.2f b=%2.2f", a, b);

    return ((double)a)/((double)b);
}

/*
 * Growth rates
 * QoQ:
 * pct_change_qoq(&X) = (sum[t-1,...,t-3] / sum[t-4,...,t-6] -1)*100 = (sum_qoq(&X,1,3)/sum_qoq(&X,4,6)-1)*100 = (ratio_qoq(&X)-1)*100`
 * YoY: 
 * pct_change_yoy(&X) = (sum[t-1,...,t-12] / sum[t-13,...,t-24] -1)*100 = (sum_yoy(&X,1,12)/sum_yoy(&X,13,24)-1)*100 = (ratio_yoy(&X)-1)*100`
 */
double pct_change_qoq(double_array * x)
{
    return (ratio_qoq(x)-1)*100;
}

double pct_change_yoy(double_array * x)
{
    return (ratio_yoy(x)-1)*100;
}

void compute_statistics_economy(data_adt * x)
{
    //Compute statistics for time series
    (*x).economy.levels.ts.mean   = my_stats_mean(&(*x).economy.levels.ts.data);
    (*x).economy.levels.ts.median = my_stats_median(&(*x).economy.levels.ts.data);
    (*x).economy.levels.ts.sd     = my_stats_sd(&(*x).economy.levels.ts.data);
    (*x).economy.levels.ts.cv     = my_stats_cv(&(*x).economy.levels.ts.data);
	
	// 3-month trailing sum of current time series
	sum_array_backwards(&(*x).economy.levels.ts.data,1,3, &(*x).economy.levels.ts.trailing_sum_qtr);
	// 3-month trailing avg of current time series
	sum_array_backwards(&(*x).economy.levels.ts.data,1,3, &(*x).economy.levels.ts.trailing_avg_qtr);
	(*x).economy.levels.ts.trailing_avg_qtr = (*x).economy.levels.ts.trailing_avg_qtr/3.0;

	// 12-month trailing sum of current time series
	sum_array_backwards(&(*x).economy.levels.ts.data,1,12, &(*x).economy.levels.ts.trailing_sum_year);
	// 12-month trailing avg of current time series
	sum_array_backwards(&(*x).economy.levels.ts.data,1,12, &(*x).economy.levels.ts.trailing_avg_year);
	(*x).economy.levels.ts.trailing_avg_year = (*x).economy.levels.ts.trailing_avg_year/12.0;

    //Compute growth rates
    //if(DAY%(MONTH*3)==0) //only compute on quarter boundaries
        (*x).economy.pct_change_qoq_series.current = pct_change_qoq(&(*x).economy.levels.ts.data);
    //if(DAY%(MONTH*12)==0) //only compute on annual boundaries
        (*x).economy.pct_change_yoy_series.current = pct_change_yoy(&(*x).economy.levels.ts.data);

    //Compute statistics for time series of growth rates
    //if(DAY%(MONTH*3)==0)   //only compute on quarter boundaries  
    {
        (*x).economy.pct_change_qoq_series.ts.mean  = my_stats_mean(&(*x).economy.pct_change_qoq_series.ts.data);
        (*x).economy.pct_change_qoq_series.ts.median = my_stats_median(&(*x).economy.pct_change_qoq_series.ts.data);
        (*x).economy.pct_change_qoq_series.ts.sd    = my_stats_sd(&(*x).economy.pct_change_qoq_series.ts.data);
        (*x).economy.pct_change_qoq_series.ts.cv    = my_stats_cv(&(*x).economy.pct_change_qoq_series.ts.data);
    }
    
    //if(DAY%(MONTH*12)==0)  //only compute on annual boundaries
    {        
        (*x).economy.pct_change_yoy_series.ts.mean  = my_stats_mean(&(*x).economy.pct_change_yoy_series.ts.data);
        (*x).economy.pct_change_yoy_series.ts.median = my_stats_median(&(*x).economy.pct_change_yoy_series.ts.data);
        (*x).economy.pct_change_yoy_series.ts.sd    = my_stats_sd(&(*x).economy.pct_change_yoy_series.ts.data);
        (*x).economy.pct_change_yoy_series.ts.cv    = my_stats_cv(&(*x).economy.pct_change_yoy_series.ts.data);
    }
}

