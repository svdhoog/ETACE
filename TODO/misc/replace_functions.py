#!/usr/bin/env python
import sys, os

FILE_SUFFIX = '.c'  # Choose desired suffix, i.e. ".odt" or ".txt" or ".c"

def process_string( string_in ):
    def find_between( s, first, last ):
        try:
            start = s.index( first ) + len( first )
            end = s.index( last, start )
            return s[start:end]
        except ValueError:
            return ""    
    string_out = find_between(string_in,"int","}")
    return string_out

def ProcessFile(output_folder):       
    #f_out = output_folder + '/' +  os.path.basename(sys.argv[1])[:-2] + "_out" + FILE_SUFFIX 
    
    f_a = open(sys.argv[1], 'r+')
    input_lines_a = f_a.read()
    print process_string( input_lines_a )    
    f_a.close()
    
    f_b = open(sys.argv[2], 'r+')
    input_lines_b = f_b.read()
    print process_string( input_lines_b )    
    f_b.close()

    # Replace the target string
    replaced_lines_a = input_lines_a.replace(process_string(input_lines_a), process_string( input_lines_b ))

    f_out = open(sys.argv[1], 'w')
    f_out.write(replaced_lines_a)
    f_out.close()


if __name__ == "__main__":
    output_folder = "./"    
    ProcessFile(output_folder)    

   
