#!/usr/bin/env python
import sys, os
import numpy as np
import pandas as pd

class Transform():
    def __init__(self, data):
        self.__data = data
        print "Arrived in transform class"
        print self.__data
    
    def data_print(self):
        print self.__data
        print "Rolling window test \n"
        print self.__data.rolling(window=3,min_periods=3).mean()


    def annual_quaterly(self,f):
        print f
        def mean():
            return self.__data.rolling(window=3,min_periods=3).mean()[::3]

        def summ():
            print self.__data.rolling(window=3,min_periods=3).sum()
            return self.__data.rolling(window=3,min_periods=3).sum()[::3]

        fun = {'mean': mean, 'sum': summ}    
        print fun[f]()   
        

        

    
