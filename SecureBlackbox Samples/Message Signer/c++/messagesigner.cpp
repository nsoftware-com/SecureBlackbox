/*
 * SecureBlackbox 2024 C++ Edition - Sample Project
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

void displayHelp(const char* errMes) {
    printf(
        "NAME\n"
        "  messagesigner -- SecureBlackbox MessageSigner Demo Application\n\n"
        "SYNOPSIS\n"
		"  messagesigner <-input input_file> <-output output_file> <-cert certificate_file> [-certpass certificate_password]\n"
        "           [-hashalg hash_algorithm] [-detached]\n\n"
        "DESCRIPTION\n"
        "  MessageSigner demonstrates the usage of MessageSigner from SecureBlackbox.\n"
        "  Used to create PKCS#7-compliant signed files.\n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to sign (Required).\n\n"
        "  -output       Where the signed file will be saved (Required).\n\n"
        "  -cert         The certificate used to sign files (Required).\n\n"
        "  -certpass     The password for the signing certificate.\n\n"
		"  -hashalg      The hash algorithm. Enter the corresponding string. Valid values: SHA1, SHA256, SHA384, SHA512, SHA224, MD5\n\n"
		"  -detached     Whether to store the generated signature in a separate message.\n\n"
        "EXAMPLES\n"
        "  messagesigner -input C:\\mes\\helloworld.txt -output C:\\mes\\mymes.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n\n"
        "  messagesigner -input C:\\mes\\helloworld.txt -output C:\\mes\\mymes.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n"
        "             -detached -hashalg SHA256 \n\n"
    );

	if (strlen(errMes) > 0)
	{
		printf("Error: %s \n\n", errMes);
	}
}

int main(int argc, char** argv) {
    MessageSigner signer;
    CertificateManager cm;

    // Validate input
    if (argc < 2) {
        displayHelp("");
        goto done;
    }

    char* input = optval(argc, argv, "-input");
    if (!strcmp(input, "")) {
        displayHelp("-input is required.");
        goto done;
    }

    char* output = optval(argc, argv, "-output");
    if (!strcmp(output, "")) {
        displayHelp("-output is required.");
        goto done;
    }

    char* cert = optval(argc, argv, "-cert");
    if (!strcmp(cert, "")) {
        displayHelp("-cert is required.");
        goto done;
    }

    char* certpass = optval(argc, argv, "-certpass");

    // Additional options
    if (optext(argc, argv, "-detached")) {
        signer.SetSignatureType(ST_PKCS7DETACHED);
    }
	else {
		signer.SetSignatureType(ST_PKCS7ENVELOPING);
	}

    if (optext(argc, argv, "-hashalg")) {
        signer.SetHashAlgorithm(optval(argc, argv, "-hashalg"));
    }

    // Required options
    signer.SetInputFile(input);
    signer.SetOutputFile(output);
    cm.ImportFromFile(cert, certpass);
    signer.SetSigningCertHandle(cm.GetCertHandle());

    // Sign & Create
    if (signer.Sign()) {
        goto err;
    }
    printf("The file successfully signed.\n\n");

err:
    if (signer.GetLastErrorCode()) {
        printf("Error: [%i] %s\n", signer.GetLastErrorCode(), signer.GetLastError());
    }
done:
	printf("Press Enter to exit the demo.\n");
    getchar();
}


