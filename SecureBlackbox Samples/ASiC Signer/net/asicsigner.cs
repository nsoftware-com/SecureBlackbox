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

class asicsigner
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
                "  asicsigner -- SecureBlackbox ASiCSigner Demo Application\n\n" +
                "SYNOPSIS\n" +
                "  asicsigner <-input input_file> <-output output_file> <-cert certificate_file> [-certpass certificate_password]\n" +
                "             [-extended] [-level level] [-sigtype signature_type] [-tsserver timestamp_server]\n\n" +
                "DESCRIPTION\n" +
                "  ASiCSigner demonstrates the usage of ASiCSigner from SecureBlackbox.\n" +
                "  Used to create an Associated Signature Container (ASiC) from one or more files.\n\n" +
                "  The options are as follows:\n\n" +
                "  -input        An input file to sign (Required).\n\n" +
                "  -output       Where the ASiC will be saved (Required).\n\n" +
                "  -cert         The certificate used to sign files (Required).\n\n" +
                "  -certpass     The password for the signing certificate.\n\n" +
                "  -sigtype      The type of signature to use. Enter the corresponding number. Valid values:\n\n" +
                "                  0 - CAST_UNKNOWN\n" +
                "                  1 - CAST_CADES\n" +
                "                  2 - CAST_XADES\n\n" +
                "  -level        The level for CAdES/XAdES signatures. Enter the corresponding number. Valid values:\n\n" +
                "                  0  - ASL_UNKNOWN\n" +
                "                  1  - ASL_GENERIC\n" +
                "                  2  - ASL_BASELINE_B\n" +
                "                  3  - ASL_BASELINE_T\n" +
                "                  4  - ASL_BASELINE_LT\n" +
                "                  5  - ASL_BASELINE_LTA\n" +
                "                  6  - ASL_BES\n" +
                "                  7  - ASL_EPES\n" +
                "                  8  - ASL_T\n" +
                "                  9  - ASL_C\n" +
                "                  10 - ASL_X\n" +
                "                  11 - ASL_XTYPE_1\n" +
                "                  12 - ASL_XTYPE_2\n" +
                "                  13 - ASL_XL\n" +
                "                  14 - ASL_XLTYPE_1\n" +
                "                  15 - ASL_XLTYPE_2\n" +
                "                  16 - ASL_A\n" +
                "                  17 - ASL_EXTENDED_BES\n" +
                "                  18 - ASL_EXTENDED_EPES\n" +
                "                  19 - ASL_EXTENDED_T\n" +
                "                  20 - ASL_EXTENDED_C\n" +
                "                  21 - ASL_EXTENDED_X\n" +
                "                  22 - ASL_EXTENDED_XTYPE_1\n" +
                "                  23 - ASL_EXTENDED_XTYPE_2\n" +
                "                  24 - ASL_EXTENDED_XLONG\n" +
                "                  25 - ASL_EXTENDED_XL\n" +
                "                  26 - ASL_EXTENDED_XLTYPE_1\n" +
                "                  27 - ASL_EXTENDED_XLTYPE_2\n" +
                "                  28 - ASL_EXTENDED_A\n\n" +
                "  -extended     Whether to use extended signatures.\n\n" +
                "  -tsserver     A timestamp server to use during signing.\n\n" +
                "EXAMPLES\n" +
                "  asicsigner -input C:\\asic\\helloworld.txt -output C:\\asic\\myasic.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n\n" +
                "  asicsigner -input C:\\asic\\helloworld.txt -output C:\\asic\\myasic.scs -cert C:\\certs\\mycert.pfx -certpass mypassword\n" +
                "             -sigtype 2 -level 10 -extended -tsserver http://timestamp.wosign.com\n"
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

        ASiCSigner signer = new ASiCSigner();
        CertificateManager cm = new CertificateManager();

        try
        {
            if (optext(args, "-input"))
            {
                signer.SourceFiles = optval(args, "-input");
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

            if (optext(args, "-cert"))
            {
                cm.ImportFromFile(optval(args, "-cert"), optval(args, "-certpass"));
                signer.SigningCertificate = cm.Certificate;
            }
            else
            {
                displayHelp("-cert is required.");
                return;
            }

            signer.TimestampServer = optval(args, "-tsserver");
            if (optext(args, "-extended"))
            {
                signer.Extended = true;
            }
            if (optext(args, "-level"))
            {
                signer.NewSignature.Level = (ASiCLevels)int.Parse(optval(args, "-level"));
            }
            if (optext(args, "-sigtype"))
            {
                signer.NewSignature.SignatureType = (ASiCSignatureTypes)int.Parse(optval(args, "-sigtype"));
            }
            else
            {
                signer.NewSignature.SignatureType = ASiCSignatureTypes.castCAdES;
            }

            // Sign
            signer.Sign();

            Console.WriteLine("ASiC created.\n");

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