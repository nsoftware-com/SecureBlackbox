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
        "  soapsigner -- SecureBlackbox SOAPSigner Demo Application\n\n"
        "SYNOPSIS\n"
        "  soapsigner [-input input_file] [-output output_file] [-cert certificate_file] [-certpass certificate_password]\n"
        "             [-signbody] [-hashalg hash_algorithm] [-sigtype signature_type]\n\n"
        "DESCRIPTION\n"
        "  SOAPSigner demonstrates the usage of SOAPSigner from SecureBlackbox.\n"
        "  Used to create SOAP or WSS signatures.\n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to sign (Required).\n\n"
        "  -output       Where the signed file will be saved (Required).\n\n"
        "  -cert         The certificate used to sign files (Required).\n\n"
        "  -certpass     The password for the signing certificate (Required).\n\n"
        "  -sigtype      The type of signature to use. Enter the corresponding number. Valid values:\n\n"
        "                  1 - WSS_SIGNATURE\n"
        "                  2 - SOAP_SIGNATURE\n\n"
        "  -hashalg      The hash algorithm.\n\n"
        "  -signbody     Whether to sign body.\n\n"
        "EXAMPLES\n"
        "  soapsigner -input C:\\soap\\soap1.xml -output C:\\soap\\mysoap.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n\n"
        "  soapsigner -input C:\\soap\\soap1.xml -output C:\\soap\\mysoap.scs -cert C:\\certs\\mycert.pfx -certpass mypassword \\\n"
        "             -sigtype 2 -hashalg SHA256 -signbody\n\n"
    )

if (len(sys.argv) < 9):
    displayHelp()
    sys.exit(1)
else:
    signer = SOAPSigner()
    cm = CertificateManager()
    
    inputF = ""
    outputF = ""
    certF = ""
    certpass = ""
    
    for x in range(len(sys.argv)):
        if (sys.argv[x].startswith("-")):
            if (sys.argv[x].lower() == "-input"):
                inputF = sys.argv[x+1]
            if (sys.argv[x].lower() == "-output"):
                outputF = sys.argv[x+1]
            if (sys.argv[x].lower() == "-cert"):
                certF = sys.argv[x+1]
            if (sys.argv[x].lower() == "-certpass"):
                certpass = sys.argv[x+1]
            if (sys.argv[x].lower() == "-sigtype"):
                signer.set_new_sig_signature_type(int(sys.argv[x+1]))
            if (sys.argv[x].lower() == "-hashalg"):
                signer.set_new_sig_hash_algorithm(sys.argv[x+1])
            if (sys.argv[x].lower() == "-signbody"):
                signer.add_body_reference("", True)

    if (inputF == ""):
        print("-input is required.\n")
        displayHelp()
        sys.exit(1)
    
    if (outputF == ""):
        print("-output is required.\n")
        displayHelp()
        sys.exit(1)
    
    if (certF == ""):
        print("-cert is required.\n")
        displayHelp()
        sys.exit(1)
    
    if (certpass == ""):
        print("-certpass is required.\n")
        displayHelp()
        sys.exit(1)
        
    cm.import_from_file(certF, certpass)
    signer.set_signing_cert_handle(cm.get_cert_handle())
    
    try:
        signer.set_input_file(inputF)
        signer.set_output_file(outputF)

        signer.sign()
    
        print("SOAP message successfully signed.")
    except Exception as e: 
        print(e)



