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
        for (int x = 0; x < argc - 1; x++) {
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
        "  messagetimestampverifier -- SecureBlackbox MessageTimestampVerifier Demo Application\n\n"
        "SYNOPSIS\n"
        "  messagetimestampverifier [-input input_file] [-output output_file] [-tsserver timestamp_server] [-detached] \n\n"
        "DESCRIPTION\n"
        "  MessageTimestampVerifier demonstrates the usage of MessageTimestampVerifier from SecureBlackbox.\n"
        "  Used to facilities in validating PKCS#7-compliant timestamped files. \n\n"
        "  The options are as follows:\n\n"
        "  -input        A timestamped file (Required). \n\n"
        "  -detached     Whether the timestamped file is detached. Use -datafile to specify the original data.\n\n"
        "  -datafile     The original data (Required for detached signature).\n\n"
        "  -output       Where to save the verified, unpacked message (Required for non detached timestamped file).\n\n"
        "EXAMPLES\n"
        "  messagetimestampverifier -input C:\\pkcs7\\mymes.pkcs7 -output C:\\pkcs7\\helloworld.txt \n\n"
        "  messagetimestampverifier -input C:\\pkcs7\\mymes.pkcs7 -detached -datafile C:\\pkcs7\\helloworld.txt \n\n"
    );
}

int main(int argc, char** argv) {
    MessageTimestampVerifier verifier;

    // Validate input
    if (argc < 4) {
        displayHelp();
        goto done;
    }

    char* input = optval(argc, argv, "-input");
    if (!strcmp(input, "")) {
        printf("-input is required.");
        displayHelp();
        goto done;
    }
    verifier.SetInputFile(input);

    bool detached = optext(argc, argv, "-detached");
    if (detached) {
        char* datafile = optval(argc, argv, "-datafile");
        if (strcmp(datafile, "")) {
            verifier.SetDataFile(datafile);
        } else {
            printf("-datafile is required if -detached is used.\n");
            goto done;
        }
    } else {
        char* output = optval(argc, argv, "-output");
        if (strcmp(output, "")) {
            verifier.SetOutputFile(output);
        } else {
            printf("-output is required if -detached is not used.\n");
            goto done;
        }
    }

    // Verify
    if (detached ? verifier.VerifyDetached() : verifier.Verify()) {
        goto done;
    }
    switch (verifier.GetSignatureValidationResult()) {
    case SVT_VALID:
        printf("The signature is valid.\n");
        break;
    case SVT_UNKNOWN:
        printf("Signature verification failed: Unknown signature.\n");
        break;
    case SVT_CORRUPTED:
        printf("Signature verification failed: The signature is corrupt or invalid.\n");
        break;
    case SVT_SIGNER_NOT_FOUND:
        printf("Signature verification failed: The signature does not contain a signer.\n");
        break;
    case SVT_FAILURE:
        printf("Signature verification failed.\n");
        break;
    }

done:
    if (verifier.GetLastErrorCode()) {
        printf("Error: [%i] %s\n", verifier.GetLastErrorCode(), verifier.GetLastError());
    }
    getchar();
}


