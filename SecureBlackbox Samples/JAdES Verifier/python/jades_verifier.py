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

def ensureArg(args, prompt, index):
  if len(args) <= index:
    while len(args) <= index:
      args.append(None)
    args[index] = input(prompt)
  elif args[index] == None:
    args[index] = input(prompt)

def displayHelp():
    print(
        "NAME\n"
        "  jadesverifier -- SecureBlackbox JAdESVerifier Demo Application\n\n"
        "SYNOPSIS\n"
        "  jadesverifier [-input input_file] [-cert certificate_file] [-certpass certificate_password]\n"
        "DESCRIPTION\n"
        "  JAdESVerifier demonstrates the usage of JAdESVerifier from SecureBlackbox.\n"
        "  Used to verify the signature.\n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to verify (Required).\n\n"
        "  -data         A data file (payload) to validate (required for detached signatures).\n\n"
        "  -cert         The certificate used to sign file.\n\n"
        "  -certpass     The password for the signing certificate.\n\n"
        "  -performRevocationCheck       Whether certificate revocation information should be checked.\n\n"
        "  -ignoreChainValidationErrors  Whether to ignore chain validation errors.\n\n"
        "  -forceCompleteChainValidation Whether to check issuer (CA) certificates when the signing certificate is invalid.\n\n"
    )

def translateSigValidity(value):
    if (value == svtValid):
        return "Valid"
    elif (value == svtCorrupted):
        return "Corrupted"
    elif (value == svtSignerNotFound):
        return "Signer not found"
    elif (value == svtFailure):
        return "Failure"
    else:
        return "Unknown" 
    
def translateChainValidity(value):
    if (value == cvtValid):
        return "Valid"
    elif (value == cvtValidButUntrusted):
        return "Valid but untrusted"
    elif (value == cvtInvalid):
        return "Invalid"
    elif (value == cvtCantBeEstablished):
        return "Can't be established"
    else:
        return "Unknown" 
    
if (len(sys.argv) < 3):
    displayHelp()
    sys.exit(1)
else:
    verifier = JAdESVerifier()
    cm = CertificateManager()
    
    inputF = ""
    dataF = ""
    certF = ""
    certpass = ""
    performRevocationCheck = False
    ignoreChainValidationErrors = False
    forceCompleteChainValidation = False
    
    try:
        for x in range(len(sys.argv)):
            if (sys.argv[x].startswith("-")):
                if (sys.argv[x].lower() == "-input"):
                    inputF = sys.argv[x+1]
                if (sys.argv[x].lower() == "-data"):
                    dataF = sys.argv[x+1]
                if (sys.argv[x].lower() == "-cert"):
                    certF = sys.argv[x+1]
                if (sys.argv[x].lower() == "-certpass"):
                    certpass = sys.argv[x+1]
                if (sys.argv[x].lower() == "-performRevocationCheck"):
                    performRevocationCheck = True
                if (sys.argv[x].lower() == "-ignoreChainValidationErrors"):
                    ignoreChainValidationErrors = True
                if (sys.argv[x].lower() == "-forceCompleteChainValidation"):
                    forceCompleteChainValidation = True
                    
        if (inputF == ""):
            print("-input is required.\n")
            displayHelp()
            sys.exit(1)

        verifier.set_input_file(inputF)
        verifier.set_data_file(dataF)      
        
        if performRevocationCheck:
            verifier.set_revocation_check(1) # Auto
        else:
            verifier.set_revocation_check(0) # None
        
        if ignoreChainValidationErrors:
            verifier.set_ignore_chain_validation_errors(True) 
        else:
            verifier.set_ignore_chain_validation_errors(False)
            
        if forceCompleteChainValidation:
            verifier.config("ForceCompleteChainValidation=true")
        else:
            verifier.config("ForceCompleteChainValidation=false")       
        
        if not (certF == ""):
            cm.import_from_file(certF, certpass)
            verifier.set_known_cert_count(1)
            verifier.set_known_cert_handle(0, cm.get_cert_handle())
            
        verifier.verify()
        
        print("There are %i signatures in this file.\n"%(verifier.get_signature_count()))
        for x in range(verifier.get_signature_count()):
            print("Signature " + str(x+1))
            print("  Claimed signing time: " + verifier.get_signature_claimed_signing_time(x))
            print("  Timestamp: " + verifier.get_signature_validated_signing_time(x))
            print("  Signature Validation Result: " + translateSigValidity(verifier.get_signature_signature_validation_result(x)))
            print("  Chain Validation Result: " + translateChainValidity(verifier.get_signature_chain_validation_result(x)) + "\n")
    except Exception as e: 
        print(e)



