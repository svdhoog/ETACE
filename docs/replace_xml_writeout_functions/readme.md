Replace write_out functions in file xml.c
====
This replacement script is useful for reducing the storage footprint of FLAME simulations. It allows the user to create a "shadow model.xml" file with a subset of the agent memory variables, resulting in fewer variables than the full model.xml file. The script replace_xml_functions.py takes as input the full-model xml.c file and the shadow-model xml.c file, and then replaces all functions called `write_agentname_Agent()` in the full-model xml.c file. The resulting full-model xml.c file can be compiled as usual with rest of the FLAME model C code. The resulting simulation will only output the subset of variables for each agent type.

- src/replace_xml_functions.py: Python script for replacing XML writeout functions in xml.c (FLAME-models)
- Usage:

        python replace_xml_functions.py xml.c shadow_xml.c path_to_shadow_model shadow_model.xml

    where:
    - xml.c: original xml.c file from complete model
    - shadow_xml.c: xml.c file from 'shadow' model, with a smaller set of variables (the xml.c file results from xparsing the shadow model.xml file)
    - path_to_shadow_model: full path to shadow model
    - shadow_model.xml: model.xml file containing all agent types, but fewer variables

Test examples
====
These test examples are for testing the functionality of the script replace_xml_writeout_functions.py.

How to run:
        python replace_xml_writeout_functions.py [xml.c file] [shadow_xml.c file] [SHADOW_MODEL folder] [shadow_model.xml file] [-v]

Arguments:

- file1 = Name of original xml.c file, containing full code for the functions writeout_Agentname_agent()
- file2 = Name of shadow_xml.c file, containing replacement code for the functions writeout_Agentname_agent()
- modelpath = Path to the folder of shadow model xml
- shadow model file = Name of the shadow model xml file

Options:

        -v, --verbose = Get the status of the intermediate processing steps

Example run commands:

- If shadow model is in the current folder, and the script is also run from the current folder:

        python replace_xml_writeout_functions.py xml.c shadow_xml.c . shadow_model.xml -v >out.txt

- If the files are in separate input folders:

        xml.c: inputs/REAL_MODEL
        shadow_xml.c: inputs/XML
        shadow_model.xml: inputs/SHADOW_MODEL,

then use:

        python replace_xml_writeout_functions.py inputs/REAL_MODEL/xml.c inputs/XML/shadow_xml.c inputs/SHADOW_MODEL shadow_model.xml -v >out.txt

Output files are in output/.
