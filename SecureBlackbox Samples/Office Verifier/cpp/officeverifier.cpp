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
        "  officeverifier -- SecureBlackbox OfficeVerifier Demo Application\n\n"
        "SYNOPSIS\n"
        "  officeverifier [-input input_file] [-cert certificate_file] [-certpass certificate_password]\n"
        "DESCRIPTION\n"
        "  OfficeVerifier demonstrates the usage of OfficeVerifier from SecureBlackbox.\n"
        "  Used to verify the signature.\n\n"
        "  The options are as follows:\n\n"
        "  -input        An input file to verify (Required).\n\n"
        "  -cert         The certificate used to sign files.\n\n"
        "  -certpass     The password for the signing certificate.\n\n"
        "  -performRevocationCheck       Whether certificate revocation information should be checked.\n\n"
        "  -ignoreChainValidationErrors  Whether to ignore chain validation errors.\n\n"
        "  -forceCompleteChainValidation Whether to check issuer (CA) certificates when the signing certificate is invalid.\n\n"
    );
}

const char* translateSigType(int value) {
    switch (value) {
    case OST_BINARY_CRYPTO_API: return "BinaryCryptoAPI";
        break;
    case OST_BINARY_XML: return "BinaryXML";
        break;
    case OST_OPEN_XML: return "OpenXML";
        break;
    case OST_OPEN_XPS: return "OpenXPS";
        break;
    case OST_OPEN_DOCUMENT: return "OpenOffice";
        break;
    default: return "Unknown";
        break;
    }
}

const char* translateDocSig(bool value) {
    return value ? "Document content is signed" : "Document content is partially signed";
}

const char* translateCore(bool value) {
    return value ? "Document properties are signed" : "Document properties are not signed";
}

const char* translateOrigSig(bool value) {
    return value ? "Signature origin is signed" : "Signature origin is not signed";
}

const char* translateSigValidity(int value) {
    switch (value) {
    case SVT_VALID: return "Valid";
        break;
    case SVT_CORRUPTED: return "Corrupted";
        break;
    case SVT_SIGNER_NOT_FOUND: return "Signer not found";
        break;
    case SVT_FAILURE: return "Failure";
        break;
    default: return "Unknown";
        break;
    }
}

const char* translateChainValidity(int value) {
    switch (value) {
    case CVT_VALID: return "Valid";
        break;
    case CVT_VALID_BUT_UNTRUSTED: return "ValidButUntrusted";
        break;
    case CVT_INVALID: return "Invalid";
        break;
    case CVT_CANT_BE_ESTABLISHED: return "CantBeEstablished";
        break;
    default: return "Unknown";
        break;
    }
}

int main(int argc, char** argv) {
    OfficeVerifier verifier;
    CertificateManager cm;

    // Validate input
    if (argc < 2) {
        displayHelp();
        goto done;
    }

    char* input = optval(argc, argv, "-input");
    if (!strcmp(input, "")) {
        printf("-input is required.");
        displayHelp();
        goto done;
    }

    // Additional options
    char* cert = optval(argc, argv, "-cert");
    char* certpass = optval(argc, argv, "-certpass");

    // Required options
    verifier.SetInputFile(input);

    if (strcmp(cert, "")) {
        cm.ImportFromFile(cert, certpass);
        verifier.SetKnownCertCount(1);
        verifier.SetKnownCertHandle(0, cm.GetCertHandle());
    }

    if (optext(argc, argv, "-performRevocationCheck")) {
        verifier.SetRevocationCheck(CRC_AUTO);
    } else {
        verifier.SetRevocationCheck(CRC_NONE);
    }

    verifier.SetIgnoreChainValidationErrors(optext(argc, argv, "-ignoreChainValidationErrors"));

    if (optext(argc, argv, "-forceCompleteChainValidation")) {
        verifier.Config("ForceCompleteChainValidation:true");
    } else {
        verifier.Config("ForceCompleteChainValidation=false");
    }

    // Verify
    if (verifier.Verify()) {
        goto done;
    }

    printf("There are %i signatures in this file.\n", verifier.GetSignatureCount());
    for (int x = 0; x < verifier.GetSignatureCount(); x++) {
        printf(
            "Signature #%i\n"
            "  Signature type: %s\n"
            "  %s\n"
            "  %s\n"
            "  %s\n"
            "  Signature Time: %s\n"
            "  Signature Validation Result: %s\n"
            "  Chain Validation Result: %s\n\n",
            x, translateSigType(verifier.GetSignatureSignatureType(x)),
            translateDocSig(verifier.GetSignatureDocumentSigned(x)),
            translateCore(verifier.GetSignatureCorePropertiesSigned(x)),
            translateOrigSig(verifier.GetSignatureSignatureOriginSigned(x)),
            verifier.GetSignatureClaimedSigningTime(x), translateSigValidity(verifier.GetSignatureSignatureValidationResult(x)),
            translateChainValidity(verifier.GetSignatureChainValidationResult(x))
        );
    }

done:
    if (verifier.GetLastErrorCode()) {
        printf("Error: [%i] %s\n", verifier.GetLastErrorCode(), verifier.GetLastError());
    }
    getchar();
}


