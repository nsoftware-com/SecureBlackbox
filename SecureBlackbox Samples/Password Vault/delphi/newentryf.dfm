object FormNewEntry: TFormNewEntry
  Left = 0
  Top = 0
  Caption = 'Add new entry'
  ClientHeight = 106
  ClientWidth = 286
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 8
    Top = 27
    Width = 59
    Height = 13
    Caption = 'Entry name:'
  end
  object btnOK: TButton
    Left = 101
    Top = 73
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 1
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 198
    Top = 73
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object edEntryName: TEdit
    Left = 73
    Top = 24
    Width = 200
    Height = 21
    TabOrder = 0
  end
end
