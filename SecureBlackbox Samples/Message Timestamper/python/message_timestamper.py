# 
# SecureBlackbox 2022 Python Edition - Sample Project
# 
# This sample project demonstrates the usage of SecureBlackbox in a 
# simple, straightforward way. It is not intended to be a complete 
# application. Error handling and other checks are simplified for clarity.
# 
# www.nsoftware.com/secureblackbox
# 
# This code is subject to the terms and conditions specified in the 
# corresponding product license agreement which outlines the authorized 
# usage and restrictions.
# 

import sys
import string
from secureblackbox import *

input = sys.hexversion<0x03000000 and raw_input or input

def displayHelp():
    print(
        "NAME\n"
        "  messagetimestamper -- SecureBlackbox MessageTimestamper Demo Application\n\n"
        "SYNOPSIS\n"
        "  messagetimestamper [-input input_file] [-output output_file] [-tsserver timestamp_server] [-detached] \n\n"
        "DESCRIPTION\n"
        "  MessageTimestamper demonstrates the usage of MessageTimestamper from SecureBlackbox.\n"
        "  Used to create timestamped PKCS#7 messages. \n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to timestamped (Required).\n\n"
        "  -output       Where the timestamping file will be saved (Required).\n\n"
        "  -tsserver     A timestamp server to use during timestamping (Required).\n\n"
        "  -detached     Whether to use detached timestamping.\n\n"
        "EXAMPLES\n"
        "  messagetimestamper -input C:\\pkcs7\\helloworld.txt -output C:\\pkcs7\\mymes.pkcs7 -tsserver http://time.certum.pl \n\n"
        "  messagetimestamper -input C:\\pkcs7\\helloworld.txt -output C:\\pkcs7\\mymes.pkcs7 -tsserver http://time.certum.pl -detached \n\n"
    )
    
if (len(sys.argv) < 7):
    displayHelp()
    sys.exit(1)
else:
    timestamper = MessageTimestamper()
    
    inputF = ""
    outputF = ""
    tsserver = ""

    for x in range(len(sys.argv)):
        if (sys.argv[x].startswith("-")):
            if (sys.argv[x].lower() == "-input"):
                inputF = sys.argv[x+1]
            if (sys.argv[x].lower() == "-output"):
                outputF = sys.argv[x+1]
            if (sys.argv[x].lower() == "-detached"):
                timestamper.set_detached(True)
            if (sys.argv[x].lower() == "-tsserver"):
                tsserver = sys.argv[x+1]
    
    if (inputF == ""):
        print("-input is required.\n")
        displayHelp()
        sys.exit(1)
    
    if (outputF == ""):
        print("-output is required.\n")
        displayHelp()
        sys.exit(1)
    
    if (tsserver == ""):
        print("-tsserver is required.\n")
        displayHelp()
        sys.exit(1)
    
    try:
        timestamper.set_input_file(inputF)
        timestamper.set_output_file(outputF)
    
        timestamper.set_timestamp_server(tsserver)

        timestamper.timestamp()
    
        print("The file successfully timestamped.")
    except Exception as e: 
        print(e)



