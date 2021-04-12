#!/usr/bin/env python3
import sys, os
import yaml
import numpy as np
import pandas as pd
from parameters import transform_configuration


class Transform():

    def __init__(self, idx, data, par_fpath):
        self.__idx = idx
        self.__data = data
        self.P = transform_configuration(par_fpath)
        self.df_out = pd.DataFrame(data=None, columns=self.__data.columns,index=self.__data.index)
        print("- Transformation")


    def main_method(self, outpath):
        transform_function = {'qoq_annual': self.qoq_annual, 'mom_annual': self.mom_annual, 'mom': self.mom, 'pct_change_yoy': self.pct_change_yoy, 'pct_change_qoq': self.pct_change_qoq}
        fn = self.P.get_parameters(self.__idx)['aggregate']
        data_out = transform_function[self.P.get_parameters(self.__idx)['transform_function']](fn, self.df_out)
        f_out = self.P.get_parameters(self.__idx)['write_file']
        if f_out is True:
            data_out.to_hdf(str(outpath)+ '/' + str(self.P.get_parameters(self.__idx)['output_file_name']), str(self.P.get_parameters(self.__idx)['hdf_groupname']), mode = 'a', format = 'table')

        return data_out


    def col_name_mapper(self): # map old var name with transformed var name
        d ={}
        for k, v in self.P.get_parameters(self.__idx)['variables'].items():
            for key, value in self.P.get_parameters(self.__idx)['new_variables'].items():
                if key == k:
                    d[v] = value
        return d


    def qoq_annual(self,fn, d_out): # method to print quarterly growth rate (quarter on same quarter of previous year)
        variables = self.P.get_parameters(self.__idx)['variables']
        col_d = self.col_name_mapper()

        def mean(df_out): # TODO: value seems wrong, check, multi agent causing error
            roll_mean = self.__data[variables.values()].rolling(window=3, min_periods=3).mean() # first get rolling window values with step 3 and initial buffer 3
            #df_out[variables.values()] = roll_mean[::3].pct_change(4) 
            df_out[variables.values()] = roll_mean[::3][variables.values()]
            df_out = df_out.pct_change(4) # compute pct change with respect to same observation (quarter) 4 periods ago
            return df_out.rename(columns = col_d)

        def summation(df_out):
            roll_sum = self.__data[variables.values()].rolling(window=3,min_periods=3).sum()
            df_out[variables.values()] = roll_sum[::3].pct_change(4)
            return df_out.rename(columns = col_d)

        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input
        return f_mapper[fn](d_out)


    def mom_annual(self,fn, df_out): # method to print monthly growth rate (month on same month previous year)
        variables = self.P.get_parameters(self.__idx)['variables']
        col_d = self.col_name_mapper()
        df_out[variables.values()] = self.__data[variables.values()].pct_change(12) # compute pct change with respect to same observation (month) 12 periods ago
        return df_out.rename(columns = col_d)


    def mom(self,fn, df_out): # method to print monthly growth rate (month on month)
        variables = self.P.get_parameters(self.__idx)['variables']
        col_d = self.col_name_mapper()
        df_out[variables.values()] = self.__data[variables.values()].pct_change(1) # compute pct change with respect to 1 period ago
        return df_out.rename(columns = col_d)

    # method to compute percent change YoY (year-on-year), based on either
    # 12-month trailing avg: pct_change_yoy.mean, or
    # 12-month trailing sum: pct_change_yoy.sum
    def pct_change_yoy(self,fn, df_out): 
        variables = self.P.get_parameters(self.__idx)['variables']
        col_d = self.col_name_mapper()

        def mean():
            roll_mean = self.__data[variables.values()].rolling(window=12,min_periods=12).mean() # 12-month trailing average: first get rolling window values with step 12 and initial buffer 12
            df_out[variables.values()] = roll_mean[::12].pct_change(1) # pct_change_yoy.mean: compute rate between values with a step size 1: ratio of two consequetive 12-month trailing averages
            return df_out.rename(columns = col_d)

        def summation():
            roll_sum = self.__data[variables.values()].rolling(window=12,min_periods=12).sum() # 12-month trailing sum: first get rolling window values with step 12 and initial buffer 12
            df_out[variables.values()] = roll_sum[::12].pct_change(1) # pct_change_yoy.sum: compute rate between values with a step size 1: ratio of two consequetive 12-month trailing sums
            return df_out.rename(columns = col_d)

        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input
        return f_mapper[fn]()

    # method to compute percent change QoQ (quarter-on-quarter), based on either
    # 3-month trailing avg: pct_change_qoq.mean, or
    # 3-month trailing sum: pct_change_qoq.sum
    def pct_change_qoq(self,fn, df_out):
        variables = self.P.get_parameters(self.__idx)['variables']
        col_d = self.col_name_mapper()

        def mean():
            roll_mean = self.__data[variables.values()].rolling(window=3,min_periods=3).mean() # 3-month trailing average: first get rolling window values with step 3 and initial buffer 3
            df_out[variables.values()] = roll_mean[::3].pct_change(1)  # pct_change_qoq.mean: compute rate between values with a step size 1: ratio of two consequetive 3-month trailing averages
            return df_out.rename(columns = col_d)

        def summation():
            roll_sum = self.__data[variables.values()].rolling(window=3,min_periods=3).sum() # 3-month trailing sum: first get rolling window values with step 3 and initial buffer 3
            df_out[variables.values()] = roll_sum[::3].pct_change(1) # pct_change_qoq.sum: compute rate between values with a step size 1: ratio of two consequetive 3-month trailing sums
            return df_out.rename(columns = col_d)

        f_mapper = {'mean': mean, 'sum': summation} # map the function to apply with the desired input
        return f_mapper[fn]()



if __name__ == "__main__":

    C = transform_configuration()
    print(C.get_parameters()['variables'])

## Notes:
## Seems this script is still incomplete