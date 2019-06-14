#!/usr/bin/env python3
import pandas as pd
from parameters import A  # imported self written class from directory


class SummaryStats(A):

    """
            Takes in a hierarchical dataframe, and returns the dataframe, by aggregating the values on the specified level.
            Parameters
            ----------
            data: [dataframe]
                A Pandas dataframe containing hiererchial index.
            analysis type: [integer]
                An integer value specifying what summary to compute (mapped to inherited class A) to aggregate upon.
            Returns
            -------
            Pandas dataframe with the aggregated value.
    """
    def __init__(self, data, param):
        self.__data = data
        self.__param = param
        self.__analysis_type = self.map_analysis()
        #print "Data received for computation in summary module:"
        #print self.__data.head(5)

    def compute_summary(self):
        summary_type = {'mean': self.mean, 'median': self.median, 'third_quartile': self.third_quartile, 'first_quartile': self.first_quartile, 'custom_quantile': self.custom_quantile, 'minimum': self.minimum, 'maximum': self.maximum, 'full':self.full}
        return summary_type[self.__param['summary']]()

    def map_analysis(self):
        analysis_values = {'agent': A.agent, 'multiple_run': A.multiple_run, 'multiple_batch': A.multiple_batch, 'multiple_set': A.multiple_set}
        return analysis_values[self.__param['analysis']]

    def full(self):
        return self.__data

    def mean(self):
        agent_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major', 'minor']).mean()
        multiple_run_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major']).mean()
        multiple_batch_analysis = lambda: self.__data.groupby(level=['set', 'major']).mean()
        multiple_set_analysis = lambda: self.__data.groupby(level=['major']).mean()

        options = {A.agent: agent_analysis, A.multiple_run: multiple_run_analysis, A.multiple_batch: multiple_batch_analysis, A.multiple_set: multiple_set_analysis}
        return options[self.__analysis_type]()

    def quantile(self, val):
        agent_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major', 'minor']).quantile(val)
        multiple_run_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major']).quantile(val)
        multiple_batch_analysis = lambda: self.__data.groupby(level=['set', 'major']).quantile(val)
        multiple_set_analysis = lambda: self.__data.groupby(level=['major']).quantile(val)

        options = {A.agent: agent_analysis, A.multiple_run: multiple_run_analysis, A.multiple_batch: multiple_batch_analysis, A.multiple_set: multiple_set_analysis}
        return options[self.__analysis_type]()

    def custom_quantile(self):
        # TODO: add exception handling for the input values
        N = sorted(self.__param['quantile_values'].values())
        if len(N) == 1:
            s = pd.DataFrame()
            Q = float(N[0])
            s = s.append(self.quantile(Q))
            for i in range(len(list(s))):
                #s.rename(columns={list(s)[i]: str(list(s)[i])+"_quantile ("+str(Q)+")"}, inplace=True)
                s.rename(columns={list(s)[i]: str(list(s)[i])+"_Q("+str(Q)+")"}, inplace=True)
                #s.rename(columns={list(s)[i]: "Q("+str(Q)+")"}, inplace=True) # quantile label: Q(0.2)
            return s

        elif len(N) == 2:
            s1 = pd.DataFrame()  # two df needed because df[xy] = z does not work as desired with multi-index
            s2 = pd.DataFrame()
            Q1 = float(N[0])
            Q2 = float(N[1])
            s1 = s1.append(self.quantile(Q1))  # data frame for lower quantile
            for i in range(len(list(s1))):
                s1.rename(columns={list(s1)[i]: str(list(s1)[i])+"_Q("+str(Q1)+")"}, inplace=True) # varname_Q(0.2)
                # s1.rename(columns={list(s1)[i]: "Q("+str(Q1)+")"}, inplace=True) # lower quantile label: Q(0.2)

            s2 = s2.append(self.quantile(Q2))  # data frame for upper quantile
            for i in range(len(list(s2))):
                s2.rename(columns={list(s2)[i]: str(list(s2)[i])+"_Q("+str(Q2)+")"}, inplace=True) # varname_Q(0.8)
                # s2.rename(columns={list(s2)[i]: "Q("+str(Q2)+")"}, inplace=True) # upper quantile label: Q(0.8)

            D = pd.concat([s1, s2], axis=1)
            return D[list(sum(zip(s1.columns, s2.columns), ()))] # arrange columns (l_q, u_q) in alternating fashion

    def maximum(self):
        agent_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major', 'minor']).max()
        multiple_run_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major']).max()
        multiple_batch_analysis = lambda: self.__data.groupby(level=['set', 'major']).max()
        multiple_set_analysis = lambda: self.__data.groupby(level=['major']).max()

        options = {A.agent: agent_analysis, A.multiple_run: multiple_run_analysis, A.multiple_batch: multiple_batch_analysis, A.multiple_set: multiple_set_analysis}
        return options[self.__analysis_type]()

    def minimum(self):
        agent_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major', 'minor']).min()
        multiple_run_analysis = lambda: self.__data.groupby(level=['set', 'run', 'major']).min()
        multiple_batch_analysis = lambda: self.__data.groupby(level=['set', 'major']).min()
        multiple_set_analysis = lambda: self.__data.groupby(level=['major']).min()

        options = {A.agent: agent_analysis, A.multiple_run: multiple_run_analysis, A.multiple_batch: multiple_batch_analysis, A.multiple_set: multiple_set_analysis}
        return options[self.__analysis_type]()

    def median(self):
        return self.quantile(0.50)

    def third_quartile(self):
        return self.quantile(0.75)

    def first_quartile(self):
        return self.quantile(0.25)
