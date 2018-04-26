# python script replace_xml_functions.py
# Sander vander Hoog, ETACE, Bielefeld University
# 9 March 2017

TEST EXAMPLES

These test examples are for testing the functionality of the script replace_xml_functions.py.

How to run:
$ python replace_xml_functions.py [xml.c file] [shadow_xml.c file] [SHADOW_MODEL folder] [shadow_model.xml file] [-v]

Arguments:
file1 = Name of original xml.c file, containing full code for the functions writeout_Agentname_agent()
file2 = Name of shadow_xml.c file, containing replacement code for the functions writeout_Agentname_agent()
modelpath = Path to the folder of shadow model xml
shadow model file = Name of the shadow model xml file

Options:
-v, --verbose = Get the status of the intermediate processing steps

Example run commands:

- If shadow model is in the current folder, and the script is also run from the current folder:
$ python replace_xml_functions.py xml.c shadow_xml.c . shadow_model.xml -v >out.txt

- If the files are in separate input folders:
xml.c: inputs/REAL_MODEL
shadow_xml.c: inputs/XML
shadow_model.xml: inputs/SHADOW_MODEL,
then use:

$ python replace_xml_functions.py inputs/REAL_MODEL/xml.c inputs/XML/shadow_xml.c inputs/SHADOW_MODEL shadow_model.xml -v >out.txt

Output files are in output/.