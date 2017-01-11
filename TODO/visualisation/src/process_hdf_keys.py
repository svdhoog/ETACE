#!/usr/bin/env python
import sys, os, argparse
import numpy as np
import pandas as pd

def process_file_keys( string_in ):
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""
    
    tmp_string = string_in.replace('_run_', ',')        
    string_out = find_between(tmp_string,"/set_","_iters")
    return list(map(int, string_out.split(',')))


if __name__ == "__main__":
    # Opening the store to get the HDF file for Agent-type
    store = pd.io.pytables.HDFStore('/home/susupta/Desktop/GitHub/Bank/Bank.h5')
    # Going through sets and runs in the HDF file
    for key in store.keys():
        print process_file_keys(key)
