object FormPdfsignerexternal: TFormPdfsignerexternal
  Left = 0
  Top = 0
  Caption = 'PDF Signer External demo'
  ClientHeight = 336
  ClientWidth = 728
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label10: TLabel
    Left = 8
    Top = 15
    Width = 636
    Height = 13
    Caption = 
      'This sample illustrates the use of PDFSigner component for signi' +
      'ng PDF documents. Please pick the signing certificate and click ' +
      #39'Sign'#39'. '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clHighlight
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object lbInputFile: TLabel
    Left = 10
    Top = 49
    Width = 47
    Height = 13
    Caption = 'Input file:'
  end
  object sbBrowseInputFile: TSpeedButton
    Left = 323
    Top = 43
    Width = 75
    Height = 25
    Caption = 'Browse ...'
    OnClick = sbBrowseInputFileClick
  end
  object Label1: TLabel
    Left = 10
    Top = 84
    Width = 55
    Height = 13
    Caption = 'Output file:'
  end
  object sbOutputFile: TSpeedButton
    Left = 323
    Top = 78
    Width = 75
    Height = 25
    Caption = 'Browse ...'
    OnClick = sbOutputFileClick
  end
  object edInputFile: TEdit
    Left = 70
    Top = 45
    Width = 245
    Height = 21
    TabOrder = 0
  end
  object edOutputFile: TEdit
    Left = 70
    Top = 80
    Width = 245
    Height = 21
    TabOrder = 1
  end
  object GroupBox6: TGroupBox
    Left = 10
    Top = 129
    Width = 710
    Height = 152
    Caption = 'Signing options  '
    TabOrder = 2
    object Label3: TLabel
      Left = 10
      Top = 64
      Width = 89
      Height = 13
      Caption = 'Signing certificate:'
    end
    object sbSignCertFile: TSpeedButton
      Left = 252
      Top = 81
      Width = 70
      Height = 25
      Caption = 'Browse ...'
      OnClick = sbSignCertFileClick
    end
    object Label5: TLabel
      Left = 10
      Top = 116
      Width = 103
      Height = 13
      Caption = 'Certificate password:'
    end
    object Label4: TLabel
      Left = 10
      Top = 29
      Width = 29
      Height = 13
      Caption = 'Level:'
    end
    object Label2: TLabel
      Left = 378
      Top = 64
      Width = 135
      Height = 13
      Caption = 'Key file for external signing:'
    end
    object sbSignKeyFile: TSpeedButton
      Left = 620
      Top = 81
      Width = 70
      Height = 25
      Caption = 'Browse ...'
      OnClick = sbSignKeyFileClick
    end
    object edSigningCertificate: TEdit
      Left = 10
      Top = 83
      Width = 236
      Height = 21
      TabOrder = 0
    end
    object edCertPassword: TEdit
      Left = 123
      Top = 112
      Width = 199
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object cbLevel: TComboBox
      Left = 50
      Top = 25
      Width = 135
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 2
      Text = 'Legacy'
      Items.Strings = (
        'Legacy'
        'BES'
        'EPES'
        'LTV'
        'DocumentTimestamp')
    end
    object cbVisible: TCheckBox
      Left = 225
      Top = 27
      Width = 97
      Height = 17
      Caption = 'Visible signature'
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object edSigningKey: TEdit
      Left = 378
      Top = 83
      Width = 236
      Height = 21
      TabOrder = 4
    end
  end
  object btnSign: TButton
    Left = 648
    Top = 298
    Width = 70
    Height = 25
    Caption = 'Sign'
    TabOrder = 3
    OnClick = btnSignClick
  end
  object dlgOpen: TOpenDialog
    Left = 496
    Top = 40
  end
  object dlgSave: TSaveDialog
    Left = 568
    Top = 40
  end
end


