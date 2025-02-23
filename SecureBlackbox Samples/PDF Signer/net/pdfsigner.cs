/*
 * SecureBlackbox 2024 .NET Edition - Sample Project
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
 * 
 */

﻿using System;
using nsoftware.SecureBlackbox;

class pdfsigner
{
    private static string optval(string[] args, string option)
    {
        for (int x = 0; x < args.Length - 1; x++)
        {
            if (args[x].Equals(option, StringComparison.CurrentCultureIgnoreCase))
            {
                return args[x + 1];
            }
        }
        return "";
    }

    private static bool optext(string[] args, string option)
    {
        for (int x = 0; x < args.Length; x++)
        {
            if (args[x].Equals(option, StringComparison.CurrentCultureIgnoreCase))
            {
                return true;
            }
        }
        return false;
    }

    private static void displayHelp(string errMes)
    {
        Console.WriteLine(
                "NAME\n" +
                "  pdfsigner -- SecureBlackbox PDFSigner Demo Application\n\n" +
                "SYNOPSIS\n" +
                "  pdfsigner <-input input_file> <-output output_file> <-cert certificate_file> [-certpass certificate_password]\n" +
                "             [-sigtype sig_type] [-level sig_level] [-hashalg hashalg] [-tsserver timestamp_server]\n" + 
                "             [-author author] [-reason reason] [-signame signame]\n\n" +
                "DESCRIPTION\n" +
                "  This sample illustrates the use of PDFSigner component for signing PDF documents.\n\n" +
                "  The options are as follows:\n\n" +
                "  -input        An input file to sign (Required).\n\n" +
                "  -output       Where the signed file will be saved (Required).\n\n" +
                "  -cert         The certificate used to sign files (Required).\n\n" +
                "  -certpass     The password for the signing certificate.\n\n" +
	          	"  -sigtype      The signature type. Enter the corresponding number. Valid values:\n\n" +
	        	"                  0  - pstUnknown\n" +
		        "                  1  - pstLegacy\n" +
        		"                  2  - pstPAdES\n" +
		        "                  3  - pstDocumentTimestamp\n\n" +
                "  -level        The level for PAdES signatures. Enter the corresponding number. Valid values:\n\n" +
                "                  0  - paslUnknown\n" +
                "                  1  - paslGeneric\n" +
                "                  2  - paslBaselineB\n" +
                "                  3  - paslBaselineT\n" +
                "                  4  - paslBaselineLT\n" +
                "                  5  - paslBaselineLTA\n" +
                "                  6  - paslBES\n" +
                "                  7  - paslEPES\n" +
                "                  8  - paslLTV\n\n" +
                "  -hashalg      The hash algorithm. Enter the corresponding string. Valid values: SHA1, SHA256, SHA384, SHA512, SHA224\n\n" +
                "  -author       The name of the signer who produced this signature.\n\n" +
                "  -reason       Specifies the reason of the signing, for example to confirm the document correctness.\n\n" +
                "  -signame      Specifies the signature identifier in the PDF-file.\n\n" +
                "  -tsserver     Specifies the timestamp server to use during signing.\n\n" +
                "EXAMPLES\n" +
                "  pdfsigner -input C:\\helloworld.pdf -output C:\\sign.pdf -cert C:\\certs\\mycert.pfx -certpass mypassword\n\n" +
                "  pdfsigner -input C:\\helloworld.pdf -output C:\\sign.pdf -cert C:\\certs\\mycert.pfx -certpass mypassword\n" +
                "           -hashalg SHA256 -level 2 -author \"Test author\"\n"
        );

        if (errMes.Length > 0)
        {
            Console.WriteLine("Error: " + errMes);
            Console.WriteLine();
        }

        confirmExit();
    }

    private static void confirmExit()
    {
        Console.WriteLine("Press Enter to exit the demo.");
        Console.ReadLine();
    }

    static void Main(string[] args)
    {
        if (args.Length == 0)
        {
            displayHelp("");
            return;
        }

        PDFSigner signer = new PDFSigner();
        CertificateManager cm = new CertificateManager();

        try
        {
            if (optext(args, "-input"))
            {
                signer.InputFile = optval(args, "-input");
            }
            else
            {
                displayHelp("-input is required.");
                return;
            }

            if (optext(args, "-output"))
            {
                signer.OutputFile = optval(args, "-output");
            }
            else
            {
                displayHelp("-output is required.");
                return;
            }

            // Additional options
            if (optext(args, "-hashalg"))
            {
                signer.NewSignature.HashAlgorithm = optval(args, "-hashalg");
            }
            if (optext(args, "-sigtype"))
            {
                signer.NewSignature.SignatureType = (PDFSignatureTypes)int.Parse(optval(args, "-sigtype"));
            }
            if (optext(args, "-level"))
            {
                signer.NewSignature.Level = (PAdESSignatureLevels)int.Parse(optval(args, "-level"));
            }
            if (optext(args, "-author"))
            {
                signer.NewSignature.AuthorName = optval(args, "-author");
            }
            if (optext(args, "-reason"))
            {
                signer.NewSignature.Reason = optval(args, "-reason");
            }
            if (optext(args, "-signame"))
            {
                signer.NewSignature.SignatureName = optval(args, "-signame");
            }

            if (optext(args, "-cert"))
            {
                cm.ImportFromFile(optval(args, "-cert"), optval(args, "-certpass"));
                signer.SigningCertificate = cm.Certificate;
                if (cm.Certificate.KeyAlgorithm.Equals("id-dsa"))
                {
                    signer.NewSignature.HashAlgorithm = "SHA1";
                }
            }
            else if (signer.NewSignature.SignatureType != PDFSignatureTypes.pstDocumentTimestamp)
            {
                displayHelp("-cert is required.");
                return;
            }

            if (optext(args, "-tsserver"))
            {
                signer.TimestampServer = optval(args, "-tsserver");
            }
            else if ((signer.NewSignature.SignatureType == PDFSignatureTypes.pstDocumentTimestamp) || 
                     ((signer.NewSignature.SignatureType == PDFSignatureTypes.pstPAdES) && 
                      ((signer.NewSignature.Level == PAdESSignatureLevels.paslBaselineT) || 
                       (signer.NewSignature.Level == PAdESSignatureLevels.paslBaselineLT) || 
                       (signer.NewSignature.Level == PAdESSignatureLevels.paslBaselineLTA) || 
                       (signer.NewSignature.Level == PAdESSignatureLevels.paslLTV))))
            {
                displayHelp("-tsserver is required.");
                return;
            }

            signer.Sign();

            Console.WriteLine("The document was signed successfully.\n");

            confirmExit();
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error: " + ex.Message);
        }
    }
}





class ConsoleDemo
{
  /// <summary>
  /// Takes a list of switch arguments or name-value arguments and turns it into a dictionary.
  /// </summary>
  public static System.Collections.Generic.Dictionary<string, string> ParseArgs(string[] args)
  {
    System.Collections.Generic.Dictionary<string, string> dict = new System.Collections.Generic.Dictionary<string, string>();

    for (int i = 0; i < args.Length; i++)
    {
      // Add a key to the dictionary for each argument.
      if (args[i].StartsWith("/"))
      {
        // If the next argument does NOT start with a "/", then it is a value.
        if (i + 1 < args.Length && !args[i + 1].StartsWith("/"))
        {
          // Save the value and skip the next entry in the list of arguments.
          dict.Add(args[i].ToLower().TrimStart('/'), args[i + 1]);
          i++;
        }
        else
        {
          // If the next argument starts with a "/", then we assume the current one is a switch.
          dict.Add(args[i].ToLower().TrimStart('/'), "");
        }
      }
      else
      {
        // If the argument does not start with a "/", store the argument based on the index.
        dict.Add(i.ToString(), args[i].ToLower());
      }
    }
    return dict;
  }
  /// <summary>
  /// Asks for user input interactively and returns the string response.
  /// </summary>
  public static string Prompt(string prompt, string defaultVal)
  {
    Console.Write(prompt + (defaultVal.Length > 0 ? " [" + defaultVal + "]": "") + ": ");
    string val = Console.ReadLine();
    if (val.Length == 0) val = defaultVal;
    return val;
  }
}