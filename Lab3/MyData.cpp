//---------------------------------------------------------------------------

#pragma hdrstop

#include "MyData.h"

// Initialize.
// Realize all of methods from our class.
Data::Data()
{
	name = "";
	amount = 0;
	cost = 0;
	comingDate =  Now();
}

Data::Data(const std::string &name, int amount, int cost, const TDate &comingDate)
{
	this->name = name;
	this->amount = amount;
	this->cost = cost;
	this->comingDate = comingDate;
}

Data::Data(const Data& rhs)
{
	name = rhs.name.substr(0);
	amount = rhs.amount;
	cost = rhs.cost;
	comingDate = rhs.comingDate;
}

Data::~Data()
{
	name.clear();
}

void Data::Show(TRichEdit* RE)
{
	AnsiString str;
	str += name.c_str();
	str += " ";
	str += IntToStr(amount);
	str += " ";
	str += IntToStr(cost);
	str += "$ ";
	str += DateTimeToStr(comingDate);
	RE->Lines->Add(str.c_str());
}

bool Data::operator==(const Data& rhs)
{
	if (name == rhs.name && cost == rhs.cost && comingDate == rhs.comingDate)
		return true;
	return false;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
