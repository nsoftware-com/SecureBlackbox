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

import os.path

def displayHelp():
    print(
        "NAME\n"
        "  passwordvault -- SecureBlackbox PasswordVault Demo Application\n\n"
        "SYNOPSIS\n"
        "  passwordvault (-set|-get|-list|-del) [-entry <entry> [-pass <password>]] [-field <field> [-value <value>]] <vault-file> [-vaultpass <vault-password>]\n\n"
        "DESCRIPTION\n"
        "  PasswordVault demonstrates the usage of PasswordVault from SecureBlackbox.\n"
        "  Used to create vaults with user information.\n\n"
        "  The options are as follows:\n\n"
        "  -set          Whether to add new entry or add/modify field value.\n\n"
        "  -get          Whether to get field value.\n\n"
        "  -list         Whether to get list of entries or fields.\n\n"
        "  -del          Whether to remove entry or field value.\n\n"
        "  -vaultpass    The password for the vault\n\n"
        "  -entry        The entry name\n\n"
        "  -pass         The password for the entry.\n\n"
        "  -field        The field name\n\n"
        "  -value        The new value of field\n\n"
        "EXAMPLES\n"
        "	passwordvault -list myvault.bin\n\n"
        "	passwordvault -get -entry myftpserver -pass mypassword -field password myvault.bin\n\n"
        "	passwordvault -set -entry myftpserver -field username -value newusername myvault.bin\n\n"
        "	passwordvault -set -entry newentry myvault.bin -vaultpass mypassword\n\n"
        "	passwordvault -del -entry myftpserver -field username myvault.bin\n\n"
    )

if (len(sys.argv) < 3):
    displayHelp()
    sys.exit(1)
else:
    vault = PasswordVault()
    
    comList = False
    comGet = False
    comSet = False
    comDel = False
    vaultfile = ""
    vaultpass = ""
    entry = ""
    entrypass = ""
    field = ""
    value = ""
    
    x = 0
    while x < len(sys.argv):
        if (sys.argv[x].startswith("-")):
            if (sys.argv[x].lower() == "-list"):
                comList = True
            elif (sys.argv[x].lower() == "-get"):
                comGet = True
            elif (sys.argv[x].lower() == "-set"):
                comSet = True
            elif (sys.argv[x].lower() == "-del"):
                comDel = True
            elif (sys.argv[x].lower() == "-vaultpass"):
                vaultpass = sys.argv[x+1]
                x = x + 1;  
            elif (sys.argv[x].lower() == "-entry"):
                entry = sys.argv[x+1]
                x = x + 1;  
            elif (sys.argv[x].lower() == "-pass"):
                entrypass = sys.argv[x+1]
                x = x + 1;  
            elif (sys.argv[x].lower() == "-field"):
                field = sys.argv[x+1]
                x = x + 1;  
            elif (sys.argv[x].lower() == "-value"):
                value = sys.argv[x+1]
                x = x + 1; 
        else:
            vaultfile = sys.argv[x]
        x = x + 1;       
        
    if (not (comList or comGet or comSet or comDel)):
        print("-list or -get or -set or -del is required.\n")
        displayHelp()
        sys.exit(1)


    if ((comList and (comGet or comSet or comDel)) or (comGet and (comList or comSet or comDel)) or (comSet and (comGet or comList or comDel)) or (comDel and (comGet or comSet or comList))):
        print("Use only one -list or -get or -set or -del parameter.\n")
        displayHelp()
        sys.exit(1)

    if (vaultfile == ""):
        print("vault-file is required.\n")
        displayHelp()
        sys.exit(1)
        
    try:
        vault.set_password(vaultpass)
                
        openVault = False
        saveVault = comSet or comDel
        if (comSet):
            openVault = os.path.exists(vaultfile)
        else:
            openVault = True

        if (openVault):
            vault.open_file(vaultfile); 

    
        if (comList):
            if (entry == ""):
                entries = vault.list_entries()

                print("Entries: \n")
                entrylist = entries.split(";")
                for entryName in entrylist:
                    print(entryName + "\n")
            else:
                fields = vault.list_fields(entry, True)

                print("Fields in \"" + entry + "\": ")
                fieldlist = fields.split(";")
                for fieldName in fieldlist:
                    print(fieldName + "\n")
        elif (comGet):
            if (entry == ""):
                print("-entry is required.\n")
                displayHelp()
                sys.exit(1)

            if (field == ""):
                print("-field is required.\n")
                displayHelp()
                sys.exit(1)

            vault.set_entry_password(entrypass)

            value = vault.get_entry_value_str(entry, field)
            print("Value: " + value + "\n")
        elif (comSet):
            if (entry == ""):
                print("-entry is required.\n")
                displayHelp()
                sys.exit(1)

            if (field == ""):
                vault.add_entry(entry)
                print("Entry \"" + entry + "\" successfully added.\n")
            else:
                vault.set_entry_password(entrypass)

                vault.set_entry_value_str(entry, field, value, (entrypass != ""))
                print("Field \"" + field + "\" successfully added/modified.\n")
        else: # del
            if (entry == ""):
                print("-entry is required.\n")
                displayHelp()
                sys.exit(1)

            if (field == ""):
                vault.remove_entry(entry)
                print("Entry \"" + entry + "\" successfully removed.\n")
            else:
                vault.remove_field(entry, field)
                print("Field \"" + field + "\" successfully removed.\n")

        if (saveVault):
            vault.save_file(vaultfile)
    except Exception as e: 
        print(e)



