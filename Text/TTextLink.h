#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
const int MaxLength = 80;

class TText;
class TTextLink;

struct TMem
{
	TTextLink* pFirst, * pLast, * pFree;
};

class TTextLink
{	
public:
    TTextLink* pNext, * pDown;
    char str[MaxLength];
    static TMem mem;
	bool flag;

	TTextLink(char* s = NULL, TTextLink* pN = NULL, TTextLink* pD = NULL);

	//сборщик мусора
	void* operator new(size_t n);
	void operator delete(void* p);
	static void InitMem(int size); //инициализация памяти
	static void PrintFree(); //печать списка свободных звеньев
	static void Clean(TText& t); //сборка мусора 
};

class TText
{
	
	stack<TTextLink*> st;
	int level;
public:
	TTextLink* pFirst;
	TTextLink* pCurr;
	//TText() {}
	//навигация
	void GoFirstLink();
    void GoNextLink();
	void GoDownLink();
	void GoPrevLink();

	//модификация
	void InsNextLine(char* s);
	void InsNextSection(char* s);
	void InsDownLine(char* s);
	void InsDownSection(char* s);
	void DelNextLine();
	void DelDownLine();

	//печать
	void Print();
	void PrintRec(TTextLink* t);

	//сохранение
	void Save(char* fn);
	void SaveRec(TTextLink* t, ofstream& ostr);

	//чтение
	void Read(char* fn);
	TTextLink* ReadRec(ifstream& istr);

	void Reset();
	void GoNext();
	bool IsEnd();
};
