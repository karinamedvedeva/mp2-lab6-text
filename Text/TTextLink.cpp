#include "TTextLink.h"

TTextLink::TTextLink(char* s, TTextLink* pN, TTextLink* pD)
{
	pNext = pN;
	pDown = pD;
	flag = true;
	if (s)
		strcpy(str, s);
	else
		str[0] = '\n';
}

//?????????
void TText::GoFirstLink()
{
	while (!st.empty())
	{
		st.pop();
	}
	pCurr = pFirst;
}

void TText:: GoNextLink()
{
	if (pCurr->pNext !=NULL)
	{
		st.push(pCurr);
		pCurr = pCurr->pNext;
	}
}

void TText::GoDownLink()
{
	if (pCurr->pNext != NULL)
	{
		st.push(pCurr);
		pCurr = pCurr->pDown;
	}
}

void TText::GoPrevLink()
{
	if (!st.empty())
		pCurr = st.top();
}

//???????????
void TText::InsNextLine(char* s)
{
	if (pCurr != NULL)
	{
		TTextLink* t;
		t = new TTextLink(s, pCurr->pNext, NULL);
		pCurr->pNext = t;
	}
}

void TText::InsNextSection(char* s)
{
	TTextLink* t;
	t = new TTextLink(s, NULL, pCurr->pNext);
	pCurr->pNext = t;
}

void TText::InsDownLine(char* s)
{
	TTextLink* t;
	t = new TTextLink(s, pCurr->pDown, NULL);
	pCurr->pDown = t;
}

void TText::InsDownSection(char* s)
{
	TTextLink* t;
	t = new TTextLink(s, NULL, pCurr->pDown);
	pCurr->pDown = t;
}

void TText::DelNextLine()
{
	if (pCurr->pNext)
	{
		TTextLink* t = pCurr->pNext;
		pCurr->pNext = t->pNext;
		delete t;
	}
}

void TText::DelDownLine()
{
	if (pCurr->pDown)
	{
		TTextLink* t = pCurr->pDown;
		pCurr->pDown = t->pNext;
		delete t;
	}
}

//??????
void TText::Print()
{
	level = 0;
	PrintRec(pFirst);
}

void TText::PrintRec(TTextLink* t)
{
	if (t != NULL)
	{
		for (int i = 0; i < level; i++)
		{
			cout << "    ";
		}
		cout << t->str << endl;
		level++;
		PrintRec(t->pDown);
		level--;
		PrintRec(t->pNext);
	}
}

//??????????
void TText::Save(char* fn)
{
	ofstream ostr(fn);
	SaveRec(pFirst, ostr);
	ostr.close();
}

void TText::SaveRec(TTextLink* t, ofstream& ostr)
{
	if (t != NULL)
	{
		ostr << t->str << endl;
		if (t->pDown != NULL)
		{
			ostr << '{' << endl;
			SaveRec(t->pDown, ostr);
			ostr << '}' << endl;
		}
		if (t->pNext != NULL)
			SaveRec(t->pNext, ostr);
	}
}

//??????
void TText::Read(char* fn)
{
	ifstream istr(fn);
	pCurr = pFirst = ReadRec(istr);
	istr.close();
}

TTextLink* TText::ReadRec(ifstream& istr)
{
	TTextLink* pF = NULL, * pC = NULL;
	char Buff[MaxLength];
	while (!istr.eof())
	{
		istr.getline(Buff, MaxLength, '\n');
		if (Buff[0] == '}')
			break;
		else
		{
			if (Buff[0] == '{')
				pC->pDown = ReadRec(istr);
			else
			{
				TTextLink* tmp = new TTextLink(Buff);
				if (pC == NULL)
					pF = pC = tmp;
				else
				{
					pC->pNext = tmp;
					pC = tmp;
				}
			}
		}
	}
	return pF;
}

void TText::Reset()
{
	if (pFirst)
	{
		while (!st.empty())
		{
			st.pop();
		}
		pCurr = pFirst;
		//st.push(pCurr);
		st.push(pFirst);
		if (pFirst->pNext)
			st.push(pFirst->pNext);
		if (pFirst->pDown)
			st.push(pFirst->pDown);
	}
}

void TText::GoNext()
{
	if (!st.empty())
	{
		pCurr = st.top();
		st.pop();
		if (pCurr != pFirst)
		{
			if (pCurr->pNext)
				st.push(pCurr->pNext);
			if (pCurr->pDown)
				st.push(pCurr->pDown);
		}
	}
}

bool TText::IsEnd()
{
	return st.empty();
}

//??????? ?????? 
void* TTextLink::operator new(size_t n)
{
	TTextLink* pC = mem.pFree;
	if (mem.pFree != NULL)
		mem.pFree = pC->pNext;
	return pC;
}

void TTextLink:: operator delete(void *p) 
{
	TTextLink* pC = (TTextLink*)p;
	pC->pNext = mem.pFree;
	mem.pFree = pC;
}

void TTextLink::InitMem(int size) //????????????? ??????
{
	int Size = sizeof(TTextLink) * size;
	mem.pFirst = mem.pFree = (TTextLink*)malloc(Size);
	mem.pLast = mem.pFirst + (size - 1);
	TTextLink* tmp = mem.pFirst;
	while (tmp != mem.pLast)
	{
		tmp->pNext = tmp + 1;
		tmp->flag = true;
		tmp->str[0] = '\0';
		tmp = tmp->pNext;
	}
	tmp->pNext = NULL;
	tmp->flag = true;
	tmp->str[0] = '\0';
}

void TTextLink::Clean(TText& t) //?????? ??????
{
	TTextLink* tmp = mem.pFree;
	while (tmp != mem.pLast)
	{
		tmp->flag = false;
		tmp = tmp->pNext;
	}
	tmp->flag = false;
	for (t.Reset(); !t.IsEnd(); t.GoNext())
	{
		t.pCurr->flag = false;
	}
    tmp = mem.pFirst;

	while (tmp != mem.pLast)
	{
		if (tmp->flag == false)
			tmp->flag = true;
		else
			delete tmp;
		tmp = tmp + 1;
	}
	if (tmp->flag ==false)
		tmp->flag = true;
	else
		delete tmp;
}
 
void TTextLink::PrintFree() //?????? ?????? ????????? ???????
{
	TTextLink* tmp = mem.pFree;
	while (tmp->pNext)
	{
		if (tmp->str[0] != '\0')
		{
			cout << tmp->str << endl;
		}
		tmp = tmp->pNext;
	}
	if (tmp->str[0] != '\0')
	{
		cout << tmp->str << endl;
	}
}
