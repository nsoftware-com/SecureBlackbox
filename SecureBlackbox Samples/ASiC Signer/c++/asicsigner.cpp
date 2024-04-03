/*
 * SecureBlackbox 2022 C++ Edition - Sample Project
 *
 * This sample project demonstrates the usage of SecureBlackbox in a 
 * simple, straightforward way. It is not intended to be a complete 
 * application. Error handling and other checks are simplified for clarity.
 *
 * www.nsoftware.com/secureblackbox
 *
 * This code is subject to the terms and conditions specified in the 
 * corresponding product license agreement which outlines the authorized 
 * usage and restrictions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/secureblackbox.h"

namespace ArgParser {
    static char* optval(int argc, char** argv, const char* option) {
        for (int x = 0; x < argc; x++) {
            if (!strcmp(argv[x], option)) {
                return argv[x + 1];
            }
        }
        return (char*)"";
    }

    static bool optext(int argc, char** argv, const char* option) {
        for (int x = 0; x < argc; x++) {
            if (!strcmp(argv[x], option)) {
                return true;
            }
        }
        return false;
    }
};

using namespace ArgParser;

void displayHelp() {
    printf(
        "NAME\n"
        "  asicsigner -- SecureBlackbox ASiCSigner Demo Application\n\n"
        "SYNOPSIS\n"
        "  asicsigner [-input input_file] [-output output_file] [-cert certificate_file] [-certpass certificate_password]\n"
        "             [-extended] [-level level] [-sigtype signature_type] [-tsserver timestamp_server]\n\n"
        "DESCRIPTION\n"
        "  ASiCSigner demonstrates the usage of ASiCSigner from SecureBlackbox.\n"
        "  Used to create an Associated Signature Container (ASic) from one or more files.\n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to sign (Required).\n\n"
        "  -output       Where the ASiC will be saved (Required).\n\n"
        "  -cert         The certificate used to sign files (Required).\n\n"
        "  -certpass     The password for the signing certificate (Required).\n\n"
        "  -sigtype      The type of signature to use. Enter the corresponding number. Valid values:\n\n"
        "                  0 - CAST_UNKNOWN\n"
        "                  1 - CAST_CAD_ES\n"
        "                  2 - CAST_XAD_ES\n\n"
        "  -level        The level for CAdES signatures. Enter the corresponding number. Valid values:\n\n"
        "                  0  - ASL_UNKNOWN\n"
        "                  1  - ASL_BES\n"
        "                  2  - ASL_EPES\n"
        "                  3  - ASL_T\n"
        "                  4  - ASL_C\n"
        "                  5  - ASL_XTYPE_1\n"
        "                  6  - ASL_XTYPE_2\n"
        "                  7  - ASL_XLTYPE_1\n"
        "                  8  - ASL_XLTYPE_2\n"
        "                  9  - ASL_BASELINE_B\n"
        "                  10 - ASL_BASELINE_T\n"
        "                  11 - ASL_BASELINE_LT\n"
        "                  12 - ASL_BASELINE_LTA\n"
        "                  13 - ASL_EXTENDED_BES\n"
        "                  14 - ASL_EXTENDED_EPES\n"
        "                  15 - ASL_EXTENDED_T\n"
        "                  16 - ASL_EXTENDED_C\n"
        "                  17 - ASL_EXTENDED_XTYPE_1\n"
        "                  18 - ASL_EXTENDED_XTYPE_2\n"
        "                  19 - ASL_EXTENDED_XLTYPE_1\n"
        "                  20 - ASL_EXTENDED_XLTYPE_2\n"
        "                  21 - ASL_EXTENDED_A\n"
        "                  22 - ASL_A\n\n"
        "  -extended     Whether to use extended signatures.\n\n"
        "  -tsserver     A timestamp server to use during signing.\n\n"
        "EXAMPLES\n"
        "  asicsigner -input C:\\asic\\helloworld.txt -output C:\\asic\\myasic.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n\n"
        "  asicsigner -input C:\\asic\\helloworld.txt -output C:\\asic\\myasic.scs -cert C:\\certs\\mycert.pfx -certpass mypassword \\\n"
        "             -sigtype 2 -level 10 -extended -tsserver http://timestamp.wosign.com\n\n"
    );
}

int main(int argc, char** argv) {
    ASiCSigner signer;
    CertificateManager cm;

    // Validate input
    if (argc < 8) {
        displayHelp();
        goto done;
    }

    char* input = optval(argc, argv, "-input");
    if (!strcmp(input, "")) {
        printf("-input is required.");
        displayHelp();
        goto done;
    }

    char* output = optval(argc, argv, "-output");
    if (!strcmp(output, "")) {
        printf("-output is required.");
        displayHelp();
        goto done;
    }

    char* cert = optval(argc, argv, "-cert");
    if (!strcmp(cert, "")) {
        printf("-cert is required.");
        displayHelp();
        goto done;
    }

    char* certpass = optval(argc, argv, "-certpass");
    if (!strcmp(certpass, "")) {
        printf("-certpass is required.");
        displayHelp();
        goto done;
    }

    // Additional options
    signer.SetTimestampServer(optval(argc, argv, "-tsserver"));
    if (optext(argc, argv, "-extended")) {
        signer.SetExtended(true);
    }
    if (optext(argc, argv, "-level")) {
        signer.SetNewSigLevel(atoi(optval(argc, argv, "-level")));
    }
    if (optext(argc, argv, "-sigtype")) {
        signer.SetNewSigSignatureType(atoi(optval(argc, argv, "-sigtype")));
    }

    // Required options
    signer.SetSourceFiles(input);
    signer.SetOutputFile(output);
    cm.ImportFromFile(cert, certpass);
    signer.SetSigningCertHandle(cm.GetCertHandle());

    // Sign & Create
    if (signer.Sign()) {
        goto done;
    }
    printf("ASiC created.\n");

done:
    if (signer.GetLastErrorCode()) {
        printf("Error: [%i] %s\n", signer.GetLastErrorCode(), signer.GetLastError());
    }
    getchar();
}


