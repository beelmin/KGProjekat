object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 526
  ClientWidth = 784
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 16
    Width = 625
    Height = 457
    OnMouseDown = Image1MouseDown
  end
  object Button3: TButton
    Left = 648
    Top = 173
    Width = 96
    Height = 25
    Caption = 'Voronoi dijagram'
    TabOrder = 0
    OnClick = Button3Click
  end
  object StaticText1: TStaticText
    Left = 648
    Top = 40
    Width = 52
    Height = 17
    Caption = 'Postavke:'
    TabOrder = 1
  end
  object RadioButton2: TRadioButton
    Left = 655
    Top = 63
    Width = 121
    Height = 17
    Caption = 'Dodaj Zemlju'
    TabOrder = 2
  end
  object RadioButton3: TRadioButton
    Left = 655
    Top = 86
    Width = 121
    Height = 17
    Caption = 'Dodaj Mars'
    TabOrder = 3
  end
  object RadioButton4: TRadioButton
    Left = 655
    Top = 109
    Width = 113
    Height = 17
    Caption = 'Dodaj stanice'
    TabOrder = 4
  end
  object Button5: TButton
    Left = 648
    Top = 204
    Width = 96
    Height = 25
    Caption = 'Veliki uspon'
    TabOrder = 5
    OnClick = Button5Click
  end
end
