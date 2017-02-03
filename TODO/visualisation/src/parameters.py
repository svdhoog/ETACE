#!/usr/bin/env python

class A:
    # Types of analysis
    agent, multiple_run, multiple_batch, multiple_set = range(4)
    # 0, 1, 2, 3

class M:
    # Types of statistical summary
    mean, median, upper_quartile, lower_quartile, custom_quantile, minimum, maximum = range(7)
    # 0, 1, 2, 3, 4, 5

class NP:
    # Nature of Plots i.e. single output per analysis or multiple outputs per analysis
    one, many = range(2)
    # 0, 1
