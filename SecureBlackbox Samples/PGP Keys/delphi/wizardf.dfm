�
 TFORMWIZARD 0Y  TPF0TFormWizard
FormWizardLeft�TopBorderStylebsDialogCaptionNew Key Pair WizardClientHeight8ClientWidth�Color	clBtnFaceFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style OldCreateOrderPositionpoMainFormCenterOnClose	FormCloseOnCreate
FormCreate	OnDestroyFormDestroyOnShowFormShowPixelsPerInch`
TextHeight TPanelpnlStep4Left Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrderVisibleExplicitTop� TBevelbvlStep4TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TPanelpnlStep4TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep4CaptionLeftTop
WidtheHeightCaptionlblStep4CaptionFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep4DescriptionLeftTop Width[HeightCaptionlblStep4Description    TPanelpnlStep5Left Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrderVisibleExplicitTop� TBevelbvlStep5TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TPanelpnlStep5TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep5CaptionLeftTop
WidtheHeightCaptionlblStep5CaptionFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep5DescriptionLeftTop Width[HeightCaptionlblStep5Description    TPanelpnlStep6Left Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrderVisibleExplicitTop� TBevelbvlStep6TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TPanelpnlStep6TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep6CaptionLeftTop
WidtheHeightCaptionlblStep6CaptionFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep6DescriptionLeftTop Width[HeightCaptionlblStep6Description    TPanelpnlStep1Left Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrderOnEnterpnlStep1Enter TBevelbvlStep1TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TLabellblStep1PromptLeftTopHWidth� HeightCaption*Please specify parameters of new key pair:  TLabellblNameLeftTopdWidth1HeightCaption&Full name:FocusControledtName  TLabellblEMailLeftTop� WidthIHeightCaptionE-&Mail address:FocusControledtEMail  TLabellblKeyVersionLeftTop� Width<HeightCaptionKey &version:FocusControlcmbKeyVersion  TLabellblKeyExpirationLeftTop� WidthIHeightCaptionKey e&xpiration:FocusControlrbtDate  TLabellblStrengthLeftTop� Width.HeightCaption
&Strength:  TPanelpnlStep1TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep1CaptionLeftTop
Width� HeightCaptionKey Pair ParametersFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep1DescriptionLeftTop WidthDHeightCaptionCEnter the parameters wich will be used for new key pair generation    TEditedtNameLeftlTop`WidthMHeightTabOrderOnChangeedtNameChange  TEditedtEMailLeftlTop� WidthMHeightTabOrder  	TComboBoxcmbKeyVersionLeftlTop� Width� HeightStylecsDropDownListTabOrderItems.Strings46   TRadioButtonrbtNeverLeftlTop� Width=HeightCaption&NeverChecked	TabOrderTabStop	OnClickrbtDateClick  TDateTimePickerdtpExpirationDateLeft� Top� WidthYHeightDate �=�ٖd�@Time �=�ٖd�@EnabledTabOrder  TRadioButtonrbtDateLeft� Top� WidthHeightTabOrderOnClickrbtDateClick  	TComboBoxcmbStrengthLeftlTop� Width� HeightStylecsDropDownListTabOrderItems.StringsNormalStrong    TPanelpnlStep2Left Top Width�HeightAlignalClient
BevelOuterbvNoneTabOrderVisibleOnEnterpnlStep2EnterOnExitpnlStep2ExitExplicitTop� TBevelbvlStep2TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TLabellblStep2PromptLeftTopHWidth�HeightAutoSizeCaptionYPlease chose passphrase at least 6 symbols long and containing non-alphabetic characters.WordWrap	  TLabellblPasswordLeftTophWidth;HeightCaption&Passphrase:FocusControledtPassword  TLabellblConfirmationLeftTop� WidthAHeightCaption&Confirmation:FocusControledtConfirmation  TPanelpnlStep2TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep2CaptionLeftTop
WidthKHeightCaption
PassphraseFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep2DescriptionLeftTop Width�HeightCaptionVYour private key will be protected by a passphrase. Plase keep your passphrase secret.   TEditedtPasswordLefthTopdWidth� HeightPasswordChar*TabOrder  TEditedtConfirmationLefthTop� Width� HeightPasswordChar*TabOrder   TPanelpnlStep3Left Top Width�HeightAlignalClient
BevelOuterbvNoneFont.CharsetANSI_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.Style 
ParentFontTabOrderVisibleOnEnterpnlStep3EnterExplicitTop� TBevelbvlStep3TopLeft Top9Width�HeightAlignalTopShape	bsTopLine  TLabellblStep3PromptLeftTopHWidth.HeightCaption	Progress:  TPanelpnlStep3TopLeft Top Width�Height9AlignalTop
BevelOuterbvNoneColorclWindowTabOrder  TLabellblStep3CaptionLeftTop
WidthcHeightCaptionKey GenerationFont.CharsetRUSSIAN_CHARSET
Font.ColorclWindowTextFont.Height�	Font.NameTahoma
Font.StylefsBold 
ParentFont  TLabellblStep3DescriptionLeftTop WidthHeightCaption7Key generation is long process and may take few minutes   TProgressBarpbrProgressLeftTop`Width�HeightTabOrder   TPanel
pnlButtonsLeft TopWidth�Height0AlignalBottom
BevelOuterbvNoneTabOrder  TBevelbvlButtonsTopLeft Top Width�HeightAlignalTopShape	bsTopLine  TButtonbtnBackLeft� TopWidthKHeightCaption< &BackEnabledTabOrder OnClickbtnBackClick  TButtonbtnNextLeft+TopWidthKHeightCaption&Next >Default	EnabledTabOrderOnClickbtnNextClick  TButton	btnCancelLeftTopWidthKHeightCancel	CaptionCancelModalResultTabOrder  TButton	btnFinishLeft+TopWidthKHeightCaption&FinishDefault	EnabledModalResultTabOrderVisible   TTimertmrProgressEnabledInterval� OnTimertmrProgressTimerLeftTop   