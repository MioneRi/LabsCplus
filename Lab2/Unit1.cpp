//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "Record.h"

using namespace std;

vector <Record> MyItems;
vector <Record> SortedItems;
vector <Record> SortedItems2; // by mark from to
AnsiString StudyTypeFree = "�������.";
AnsiString StudyTypePaid = "����.";
char sepor = '|';
char space = ' ';
void ClearPanels();
void ShowSortedItems();

void __fastcall TForm1::CheckBoxAddStudentClick(TObject *Sender)
{
    ClearPanels();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
     if(ListBox1->ItemIndex != -1){
		int i = ListBox1->ItemIndex;
        
		CheckBoxAddStudent->Checked = false;
		EditName->Text = MyItems[i].Name ;
        if (MyItems[i].TypeOfTraining == StudyTypeFree) {
           RadioGroupTypeOfTraining->ItemIndex = 1;        
        }
        else if (MyItems[i].TypeOfTraining == StudyTypePaid) {
            RadioGroupTypeOfTraining->ItemIndex = 0;
        }
        else{
             RadioGroupTypeOfTraining->ItemIndex = -1;
        }

        EditSpecialty->Text = MyItems[i].Specialty;
        EditGroup->Text = MyItems[i].Group;
        EditMath->Text = MyItems[i].Math;
        EditProga->Text = MyItems[i].Proga;
        EditPhilosophy->Text = MyItems[i].Philosophy;
        LabelAverageMark->Caption = MyItems[i].AverageMark;
        
		//ListBox1->ItemIndex = i;
	}    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonRemoveStudentClick(TObject *Sender)
{
     if (ListBox1->ItemIndex != -1) {
         
         if (ListBox1->Count != 0) {
            for (int i = 0; i < MyItems.size(); i++) {
                if (SortedItems[ListBox1->ItemIndex].Name == MyItems[i].Name && 
                   SortedItems[ListBox1->ItemIndex].Group == MyItems[i].Group &&
                   SortedItems[ListBox1->ItemIndex].Specialty == MyItems[i].Specialty &&
                   SortedItems[ListBox1->ItemIndex].TypeOfTraining == MyItems[i].TypeOfTraining &&
                   SortedItems[ListBox1->ItemIndex].AverageMark == MyItems[i].AverageMark) {

                   MyItems.erase(MyItems.begin() + (ListBox1->ItemIndex));     
                   SortedItems.erase(MyItems.begin() + (ListBox1->ItemIndex));
                   break;
                }    
            }            
         }
         else{
            SortedItems.erase(MyItems.begin() + 0);
            MyItems.erase(MyItems.begin() + 0);
         }
         ListBox1->Items->Delete(ListBox1->ItemIndex );
     }
     else if (ListBox1->ItemIndex == -1) {
          ShowMessage("��� �������� ������ ����� � �������.\n");
          //throw 0;         
     }
     ClearPanels();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonOpenFileClick(TObject *Sender)
{
     
     if (OpenDialog1->Execute()) {
     
          MyItems.clear();
          SortedItems.clear();
          ListBox1->Clear();
          ListBox1->Items->LoadFromFile(OpenDialog1->FileName);

          for (int i = 0; i < ListBox1->Items->Count; i++) {
              AnsiString tmpStr = ListBox1->Items->Strings[i];
              Record tmp  = FromStringToRecord(tmpStr);
              MyItems.push_back( tmp );
          }
          
     }
                    
       
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSaveDialogClick(TObject *Sender)
{
     if (SaveDialog1->Execute()) {
        
		ListBox1->Items->SaveToFile(SaveDialog1->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonAddStudentClick(TObject *Sender)
{
     if (CheckBoxAddStudent->Checked == false) {
       ShowMessage("��������� ������� � ���� \"�������� ��������\"");
       //throw 0;
    }
     
     Record tmp = getRecord();
     MyItems.push_back(tmp);
     SortedItems.push_back(tmp);
     if (ListBox1->Items->Count != 0){
        ListBox1->Items->Add(FormatRecord(tmp));
     }
     else if (ListBox1->Items->Count == 0) {
        ListBox1->Items->Add(FormatRecord(tmp));
     }
     CheckBoxAddStudent->Checked = false;
     ClearPanels();
}
//---------------------------------------------------------------------------

void ClearPanels(){
    Form1->ListBox1->ItemIndex = -1;
	Form1->EditName->Text = "";
	Form1->RadioGroupTypeOfTraining->ItemIndex = -1;
	Form1->EditSpecialty->Text = "";
	Form1->EditGroup->Text = "";
	Form1->EditMath->Text = "";
    Form1->EditProga->Text = "";
    Form1->EditPhilosophy->Text = "";
    Form1->LabelAverageMark->Caption = "";
}


void __fastcall TForm1::btnSortListClick(TObject *Sender)
{
    AnsiString TypeOfTrainingParameter = "";
    AnsiString NameParameter = "";
    AnsiString SpecialtyParameter = "";
    AnsiString GroupParameter = "";
    AnsiString AverageMarkParameter = "";
    bool increasingMark = false; // ���� �� ��������
    
    ShowSortedItems();    
    
}
//---------------------------------------------------------------------------

void ShowSortedItems(){
     // ������� ��� ������ ������.
     SortedItems.clear();
     Form1->ListBox1->Clear();

     if (Form1->ComboBoxSort->ItemIndex >= 0) {

        for (int i = 0; i < MyItems.size(); i++) {
        
            bool coolFlag = false;
            switch(Form1->ComboBoxSort->ItemIndex){
            case 0:{
                 if(MyItems[i].Name == Form1->EditSortParameter->Text)
                     coolFlag = true;
            }
            break;
            case 1:{
                 if (MyItems[i].Group == Form1->EditSortParameter->Text)
                    coolFlag = true;                 
            }
            break;
            case 2:{
                 try{
                     if (MyItems[i].AverageMark == StrToInt(Form1->EditSortParameter->Text))
                    coolFlag = true;
                 }
                 catch(...){
                     ShowMessage("You enter smth wrong");
                     throw 0;
                 }
                 
            }
            break;
            case 3:{
                 if (MyItems[i].Specialty == Form1->EditSortParameter->Text)
                    coolFlag = true; 
            }
            break;
            }

            switch(Form1->RadioGroupTypeOfTraining2->ItemIndex){
                case 0:{
                     if (MyItems[i].TypeOfTraining == StudyTypePaid) {
                        
                     }
                     else{
                         coolFlag = false;
                     }
                }
                break;
                case 1:{
                     if (MyItems[i].TypeOfTraining == StudyTypeFree) {
                        
                     }
                     else{
                         coolFlag = false;
                     }
                }
                break;
                default:{

                }
            }
            
            // ��������� ���� ������� �� ��������.
            if (coolFlag) {
                SortedItems.push_back(MyItems[i]);
            }
        }                        
     }
     else { // ������ ��������� ����� ������ �������.
         for (int i = 0; i < MyItems.size(); i++) {
             bool coolFlag = false;
             switch(Form1->RadioGroupTypeOfTraining2->ItemIndex){
                case 0:{
                     if (MyItems[i].TypeOfTraining == StudyTypePaid) {
                         coolFlag = true;
                     }
                     else{
                         coolFlag = false;
                     }
                }
                break;
                case 1:{
                     if (MyItems[i].TypeOfTraining == StudyTypeFree) {
                         coolFlag = true;
                     }
                     else{
                         coolFlag = false;
                     }
                }
                break;
                default:{
                     coolFlag = true;
                }
            }

            if (coolFlag) {
               SortedItems.push_back(MyItems[i]); 
            }
             
         }
     }


     
     // �������� ���������� �� ������� ��� .
     switch(Form1->RadioGroupAverageMark->ItemIndex){
         case 0:{
              for (int j = 0; j < SortedItems.size() - 1; j++) {
                  for (int i = 0; i < SortedItems.size() - 1; i++) {
                      if (SortedItems[i].AverageMark > SortedItems[i+1].AverageMark) {
                         auto tmp = SortedItems[i];
                         SortedItems[i] = SortedItems[i+1];
                         SortedItems[i+1] = tmp;
                      }
                  }
              }
         }
         break;
         case 1:{
              for (int j = 0; j < SortedItems.size() - 1; j++) {
                  for (int i = 0; i < SortedItems.size() - 1; i++) {
                      if (SortedItems[i].AverageMark < SortedItems[i+1].AverageMark) {
                         Record tmp = SortedItems[i];
                         SortedItems[i] = SortedItems[i+1];
                         SortedItems[i+1] = tmp;
                      }
                  }
              }
         }
         break;
         default:{

         }
     }

     // �������� ���.
     for (int i = 0; i < SortedItems.size(); i++) {
         Form1->ListBox1->Items->Add( FormatRecord( SortedItems[i] ) );
     }     
}


void __fastcall TForm1::btnClearSortListClick(TObject *Sender)
{
     RadioGroupTypeOfTraining2->ItemIndex = -1;
     RadioGroupAverageMark->ItemIndex = -1;
     ComboBoxSort->ItemIndex = -1;
     EditSortParameter->Text = "";  
     ClearPanels();  
     Form1->ListBox1->Clear();
     for (int i = 0; i < MyItems.size(); i++) {
         Form1->ListBox1->Items->Add( FormatRecord( MyItems[i] ) );
     } 
}
//---------------------------------------------------------------------------

void InitializeMyItems();


void __fastcall TForm1::Button1Click(TObject *Sender)
{
     SortedItems2.clear();
     Form1->ListBox1->Clear();

     InitializeMyItems();

       for(int i = 0; i < MyItems.size(); i++) {
               if (MyItems[i].AverageMark >= 7) {
                  SortedItems2.push_back(MyItems[i]);
               }
       }

       for (int i = 0; i < SortedItems2.size() - 1; i++) {
           for (int j = 0; j < SortedItems2.size() - 1; j++) {
               if (SortedItems2[j].AverageMark > SortedItems2[j+1].AverageMark) {               
                         auto tmp = SortedItems2[j];
                         SortedItems2[j] = SortedItems2[j+1];
                         SortedItems2[j+1] = tmp;
               }
           }
       }

     for (int i = 0; i < SortedItems2.size(); i++) {
         Form1->ListBox1->Items->Add( FormatRecord( SortedItems2[i] ) );
     } 
     
}
//---------------------------------------------------------------------------

void InitializeMyItems(){

     for (int i = 0; i < Form1->ListBox1->Items->Count ; i++) {
         Record tmp;

         tmp = FromStringToRecord(Form1->ListBox1->Items->Strings[i]);  

         MyItems.push_back(tmp);       
     }
     
}

