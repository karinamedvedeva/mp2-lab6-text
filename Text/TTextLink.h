#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "TStack.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
const int MaxLength = 80;

class TTextLink
{	
public:
    TTextLink* pNext, * pDown;
    char str[MaxLength];

	TTextLink(char* s = NULL, TTextLink* pN = NULL, TTextLink* pD = NULL);
};

class TText
{
	TTextLink* pFirst, * pCurr;
	Stack<TTextLink*> st;
	int level;
public:
	TText() {}
	//���������
	void GoFirstLink();
    void GoNextLink();
	void GoDownLink();
	void GoPrevLink();

	//�����������
	void InsNextLine(char* s);
	void InsNextSection(char* s);
	void InsDownLine(char* s);
	void InsDownSection(char* s);
	void DelNextLine();
	void DelDownLine();

	//������
	void Print();
	void PrintRec(TTextLink* t);

	//����������
	void Save(char* fn);
	void SaveRec(TTextLink* t, ofstream& ostr);

	//������
	void Read(char* fn);
	TTextLink* ReadRec(ifstream& istr);

	void Reset();
	void GoNext();
	bool IsEmpty();
};
