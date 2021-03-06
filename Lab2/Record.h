//---------------------------------------------------------------------------

#ifndef RecordH
#define RecordH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <iostream>
#include "Unit1.h"

using namespace std;

struct Record {
	AnsiString Name;
	AnsiString Specialty;
	AnsiString TypeOfTraining;
	AnsiString Group;
    float Math;
    float Philosophy;
    float Proga;
    float AverageMark;
	
};

extern vector<Record> MyItems;
Record getRecord();
AnsiString FormatRecord(int i);
AnsiString FormatRecord(Record tmp);
Record FromStringToRecord(AnsiString ourStr);

#endif
