//---------------------------------------------------------------------------

#pragma hdrstop

#include "OurList.h"
#include "Unit1.h"

#include <vcl.h>

ForwList::ForwList()
{
	size = 0;
	head = NULL;
}
ForwList::~ForwList()
{
	if (head)
	{
		Node* current = this->head;
		Node* iter = current->next;
		while (current)
		{
			delete current;
			if(iter)
			{
				current = iter;
				iter = iter->next;
			}
			else
				current = NULL;
		}
	}
}

void ForwList::PushBack(Data data)
{
	if (!head)
		head = new Node(data);
	else
	{
		Node *current = this->head;

		while(current->next)
		{
			if(current->data == data)
			{
				current->data.amount += data.amount;
				return;
			}
			current = current->next;
		}
		if(current->data == data)
		{
			current->data.amount += data.amount;
			return;
		}
		current->next = new Node(data);
	}
	size++;
}

void ForwList::ShowAll()
{
	if (!head)
	{
		ShowMessage("������ ����!");
		return;
	}
	Node *current = this->head;
	Form1->RichEdit1->Lines->Clear();
	Form1->RichEdit2->Lines->Clear();
	while(current)
	{
		if ((double)(Now() - current->data.comingDate) <= 0 || !current->data.amount)
			current->data.Show(Form1->RichEdit2);
		else
			current->data.Show(Form1->RichEdit1);
		current = current->next;
	}
}
void ForwList::FindName(TRichEdit* RE, const std::string &name)
{
	if (name.empty())
	{
		ShowMessage("������� ������������ ������.");
		return;
	}
	Node *current = this->head;
	bool found = false;
	while(current)
	{
		 if(current->data.name == name)
		 {
			found = true;
			break;
		 }
		 current = current->next;
	}
	if (!found)
	{
		ShowMessage("������ ������ �� ����������.");
		return;
	}

	RE->Lines->Clear();
	RE->Lines->Add(name.c_str());
	RE->Lines->Strings[0] += ":";

	while(current)
	{
		if (current->data.name == name)
		{
			current->data.Show(RE);
			if ((double)(Now() - current->data.comingDate) <= 0 || !current->data.amount)
				RE->Lines->Strings[RE->Lines->Count - 1] += " Awaited";
			else
				RE->Lines->Strings[RE->Lines->Count - 1] += " In stock";
		}
		current = current->next;
	}
}
void ForwList::FindAmountInStock(TRichEdit* RE, int amount)
{
	Node *current = this->head;
	bool found = false;
	while(current)
	{
		 if(current->data.amount > amount)
		 {
			found = true;
			break;
		 }
		 current = current->next;
	}
	if (!found)
	{
		ShowMessage("����� ������� �� ����������.");
		return;
	}

	RE->Lines->Clear();
	RE->Lines->Add("Information provided for items in stock.");

	while(current)
	{
		if (current->data.amount > amount)
			if ((double)(Now() - current->data.comingDate) > 0)
				current->data.Show(RE);
		current = current->next;
	}
}
void ForwList::FindCost(TRichEdit* RE, int cost)
{
    Node *current = this->head;
	bool found = false;
	while(current)
	{
		 if(current->data.cost < cost)
		 {
			found = true;
			break;
		 }
		 current = current->next;
	}
	if (!found)
	{
		ShowMessage("������ ������ �� ����������.");
		return;
	}
	RE->Lines->Clear();
	RE->Lines->Add("Items with cost lower than " + IntToStr(cost) + "$:");
    while(current)
	{
		if (current->data.cost < cost)
		{
			current->data.Show(RE);
			if ((double)(Now() - current->data.comingDate) <= 0 || !current->data.amount)
                RE->Lines->Strings[RE->Lines->Count - 1] += " Awaited";
			else
				RE->Lines->Strings[RE->Lines->Count - 1] += " In stock";
		}
		current = current->next;
	}
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
