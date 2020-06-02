//---------------------------------------------------------------------------

#ifndef NodeH
#define NodeH
#include <vcl.h>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>


enum Color{red, black};

struct Node
{
	AnsiString data;
    int key;
	Node *parent;
    Node *left;
    Node *right;
	Color color;
	Node()
    {
        data = _T(""); 
        parent = nullptr; 
        left = nullptr; 
        right = nullptr;
    }
    
	Node(AnsiString data, int key, Node* parent = nullptr,
		 Node* left = nullptr, Node* right = nullptr, Color color = red);
         
	~Node(){}

	Node& operator=(const Node &rhs);
	bool operator==(const Node &rhs);
    bool operator!=(const Node &rhs);
};
#endif
