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
};

using namespace ArgParser;

void displayHelp(const char* errMes) {
    printf(
        "NAME\n"
        "  messagedecryptor -- SecureBlackbox MessageDecryptor Demo Application\n\n"
        "SYNOPSIS\n"
		"  messagedecryptor <-input input_file> <-output output_file> <-cert certificate_file> [-certpass certificate_password] \n\n"
        "DESCRIPTION\n"
        "  MessageDecryptor demonstrates the usage of MessageDecryptor from SecureBlackbox.\n"
        "  Used to decryption of encrypted ('enveloped') PKCS#7 messages. \n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to decrypt (Required).\n\n"
        "  -output       Where the decrypted file will be saved (Required).\n\n"
        "  -cert         The certificate used to decrypt file (Required).\n\n"
        "  -certpass     The password for the decryption certificate.\n\n"
        "EXAMPLES\n"
        "  messagedecryptor -input C:\\pkcs7\\enc.pkcs7 -output C:\\pkcs7\\helloworld.txt -cert C:\\certs\\mycert.pfx -certpass mypassword \n\n"
    );

	if (strlen(errMes) > 0)
	{
		printf("Error: %s \n\n", errMes);
	}
}

int main(int argc, char** argv) {
    MessageDecryptor decryptor;
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

    // Required options
    decryptor.SetInputFile(input);
    decryptor.SetOutputFile(output);
    cm.ImportFromFile(cert, certpass);
    decryptor.SetCertCount(1);
    decryptor.SetCertHandle(0, cm.GetCertHandle());

    // Decrypt
    if (decryptor.Decrypt()) {
        goto err;
    }
    printf("The file successfully decrypted.\n\n");

err:
    if (decryptor.GetLastErrorCode()) {
        printf("Error: [%i] %s\n", decryptor.GetLastErrorCode(), decryptor.GetLastError());
    }
done:
	printf("Press Enter to exit the demo.\n");
    getchar();
}

