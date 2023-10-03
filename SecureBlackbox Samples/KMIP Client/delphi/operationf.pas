unit operationf;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls,
  SBxTypes, SBxKMIPClient;

const
  Op_Encrypt = 1;
  Op_Decrypt = 2;
  Op_Sign    = 3;
  Op_Verify  = 4;

type
  TFormOperation = class(TForm)
    Label13: TLabel;
    eInputFile: TEdit;
    lOutputfile: TLabel;
    eOutputFile: TEdit;
    lHashAlgorithm: TLabel;
    cbHashAlgorithm: TComboBox;
    bDo: TButton;
    bOutputFileSign: TButton;
    bInputFileSign: TButton;
    bClose: TButton;
    dlgSaveFile: TSaveDialog;
    dlgOpenFile: TOpenDialog;
    procedure bInputFileSignClick(Sender: TObject);
    procedure bOutputFileSignClick(Sender: TObject);
    procedure bDoClick(Sender: TObject);
  private
    { Private declarations }
    FClient: TsbxKMIPClient;
    FUniqueIdentifier: string;
    FOperation: integer;
  public
    { Public declarations }
    procedure Init(Client: TsbxKMIPClient; UniqueIdentifier: string; Operation: integer);
  end;

var
  FormOperation: TFormOperation;

implementation

{$R *.dfm}

procedure TFormOperation.bDoClick(Sender: TObject);
begin
  case FOperation of
    Op_Encrypt:
      begin
        if eInputFile.Text = '' then
          MessageDlg('Please provide a valid name for the input file', mtError, [mbOk], 0)
        else
        if not FileExists(eInputFile.Text) then
          MessageDlg('Input file not found', mtError, [mbOk], 0)
        else
        if eOutputFile.Text = '' then
          MessageDlg('Please provide a valid name for the output file', mtError, [mbOk], 0)
        else
        begin
          FClient.InputFile := eInputFile.Text;
          FClient.OutputFile := eOutputFile.Text;

          try
            FClient.Encrypt(FUniqueIdentifier);

            MessageDlg('The file was encrypted successfully', mtInformation, [mbOk], 0);

            ModalResult := mrOk;
          except
            on E : Exception do
            begin
              MessageDlg(E.Message, mtError, [mbOk], 0);
            end;
          end;
        end;
      end;
    Op_Decrypt:
      begin
        if eInputFile.Text = '' then
          MessageDlg('Please provide a valid name for the input file', mtError, [mbOk], 0)
        else
        if not FileExists(eInputFile.Text) then
          MessageDlg('Input file not found', mtError, [mbOk], 0)
        else
        if eOutputFile.Text = '' then
          MessageDlg('Please provide a valid name for the output file', mtError, [mbOk], 0)
        else
        begin
          FClient.InputFile := eInputFile.Text;
          FClient.OutputFile := eOutputFile.Text;

          try
            FClient.Decrypt(FUniqueIdentifier);

            MessageDlg('The file was decrypted successfully', mtInformation, [mbOk], 0);

            ModalResult := mrOk;
          except
            on E : Exception do
            begin
              MessageDlg(E.Message, mtError, [mbOk], 0);
            end;
          end;
        end;
      end;
    Op_Sign:
      begin
        if eInputFile.Text = '' then
          MessageDlg('Please provide a valid name for the input file', mtError, [mbOk], 0)
        else
        if not FileExists(eInputFile.Text) then
          MessageDlg('Input file not found', mtError, [mbOk], 0)
        else
        if eOutputFile.Text = '' then
          MessageDlg('Please provide a valid name for the output file', mtError, [mbOk], 0)
        else
        begin
          FClient.InputFile := eInputFile.Text;
          FClient.OutputFile := eOutputFile.Text;
          FClient.Config('HashAlgorithm=' + cbHashAlgorithm.Text);

          try
            FClient.Sign(FUniqueIdentifier);

            MessageDlg('The file was signed successfully', mtInformation, [mbOk], 0);

            ModalResult := mrOk;
          except
            on E : Exception do
            begin
              MessageDlg(E.Message, mtError, [mbOk], 0);
            end;
          end;
        end;
      end;
    Op_Verify:
      begin
        if eInputFile.Text = '' then
          MessageDlg('Please provide a valid name for the input file', mtError, [mbOk], 0)
        else
        if not FileExists(eInputFile.Text) then
          MessageDlg('Input file not found', mtError, [mbOk], 0)
        else
        if eOutputFile.Text = '' then
          MessageDlg('Please provide a valid name for the signature file', mtError, [mbOk], 0)
        else
        if not FileExists(eOutputFile.Text) then
          MessageDlg('Signature file not found', mtError, [mbOk], 0)
        else
        begin
          FClient.InputFile := eInputFile.Text;
          FClient.DataFile := eOutputFile.Text;
          FClient.Config('HashAlgorithm=' + cbHashAlgorithm.Text);

          try
            FClient.Verify(FUniqueIdentifier);

            case FClient.SignatureValidationResult of
              svtValid: MessageDlg('Verification succeeded', mtInformation, [mbOk], 0);
              svtCorrupted: MessageDlg('Verification corrupted', mtError, [mbOk], 0);
              svtFailure: MessageDlg('Verification failed', mtError, [mbOk], 0);
              else
                MessageDlg('Verification unknown', mtError, [mbOk], 0);
            end;

            ModalResult := mrOk;
          except
            on E : Exception do
            begin
              MessageDlg(E.Message, mtError, [mbOk], 0);
            end;
          end;
        end;
      end;
  end;
end;

procedure TFormOperation.bInputFileSignClick(Sender: TObject);
begin
  if dlgOpenFile.Execute then
    eInputFile.Text := dlgOpenFile.FileName;
end;

procedure TFormOperation.bOutputFileSignClick(Sender: TObject);
begin
  if FOperation = Op_Verify then
  begin
    if dlgOpenFile.Execute then
      eOutputFile.Text := dlgOpenFile.FileName;
  end
  else
  begin
    if dlgSaveFile.Execute then
      eOutputFile.Text := dlgSaveFile.FileName;
  end;
end;

procedure TFormOperation.Init(Client: TsbxKMIPClient; UniqueIdentifier: string; Operation: integer);
begin
  FClient := Client;
  FUniqueIdentifier := UniqueIdentifier;
  FOperation := Operation;

  case Operation of
    Op_Encrypt:
      begin
        bDo.Caption := 'Encrypt';
        lOutputfile.Caption := 'Output filename:';
        Self.Height := 250;
        lHashAlgorithm.Visible := false;
        cbHashAlgorithm.Visible := false;
      end;
    Op_Decrypt:
      begin
        bDo.Caption := 'Decrypt';
        lOutputfile.Caption := 'Output filename:';
        Self.Height := 250;
        lHashAlgorithm.Visible := false;
        cbHashAlgorithm.Visible := false;
      end;
    Op_Sign:
      begin
        bDo.Caption := 'Sign';
        lOutputfile.Caption := 'Output filename:';
        Self.Height := 210;
        lHashAlgorithm.Visible := true;
        cbHashAlgorithm.Visible := true;
      end;
    Op_Verify:
      begin
        bDo.Caption := 'Verify';
        lOutputfile.Caption := 'Signature filename:';
        Self.Height := 210;
        lHashAlgorithm.Visible := true;
        cbHashAlgorithm.Visible := true;
      end;
  end;
end;

end.
