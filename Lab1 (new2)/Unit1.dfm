object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 510
  ClientWidth = 469
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ElevatorTrackBar: TTrackBar
    Left = 424
    Top = 48
    Width = 33
    Height = 441
    DoubleBuffered = True
    Max = 400
    Orientation = trVertical
    ParentDoubleBuffered = False
    ParentShowHint = False
    Frequency = 30
    ShowHint = False
    ShowSelRange = False
    TabOrder = 0
    TickMarks = tmTopLeft
    OnChange = ElevatorTrackBarChange
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 8
    Top = 16
  end
end
