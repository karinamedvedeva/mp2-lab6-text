#include "TTextLink.h"
#include <locale.h>
#include <Windows.h>

using namespace std;

TMem TTextLink::mem;

void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void main()
{
	TTextLink::InitMem(100);
	setlocale(LC_CTYPE, "Rus");
	int k;
	TText t;
	char s[80];
	char fn[] = "C:\\Users\\karina\\OneDrive\\Документы\\Projects\\mp2-lab6-text\\Text\\text.txt";
	do
	{
		cout << endl<< "НАВИГАЦИЯ ПО ТЕКСТУ" << endl << "1. Считать из файла текст и вывести его на экран" << endl << "2. Перейти к первой строке" << endl << "3. Перейти к следующей строке по pNext " << endl << "4. Перейти к следующей строке по pDown " << endl << "5. Перейти к предыдущей позиции" << endl;
		cout << endl << "МОДИФИКАЦИЯ ТЕКСТА" << endl << "6. Добавить новую строку на том же уровне " << endl << "7. Добавить новый раздел на том же уровне" << endl << "8. Добавить строку в подуровень" << endl << "9. Добавить новый раздел в подуровень" << endl << "10. Удалить строку на том же уровне" << endl << "11. Удалить строку в подуровне" << endl;
		cout << endl << "СБОРЩИК МУСОРА" << endl << "12. Сборка мусора" << endl << "13. Печать списка свободных звеньев" << endl;

		cout << endl<< "Введите номер операции: ";
		cin >> k;
		switch (k)
		{
		case 1:
			t.Read(fn);
			t.Print();
			break;
		case 2:
			t.Read(fn);
			t.GoFirstLink();
			SetColor(10, 0);
			cout << "here -> ";
			SetColor(7, 0);
			t.Print();
			break;
		case 3:
			t.Read(fn);
			char mov[80];
			cout << "Введите строку, после которой хотите перейти к следующей строке по pNext: ";
			cin >> mov;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str,mov))
				{
					t.GoNextLink();
					break;
				}
			}
			SetColor(10, 0);
			cout << "here -> ";
			SetColor(7, 0);
			t.Print();
			break;
		case 4:
			t.Read(fn);
			char mov1[80];
			cout << "Введите строку, после которой хотите перейти к следующей строке по pDown: ";
			cin >> mov1;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, mov1))
				{
					t.GoDownLink();
					break;
				}
			}
			SetColor(10, 0);
			cout << "here -> ";
			SetColor(7, 0);
			t.Print();
			break;
		case 5:
			t.Read(fn);
			char mov2[80];
			cout << "Введите строку, после которой хотите перейти к предыдущей позиции: ";
			cin >> mov2;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, mov2))
				{
					t.GoPrevLink();
					break;
				}
			}
			SetColor(10, 0);
			cout << "here -> ";
			SetColor(7, 0);
			t.Print();
			break;
		case 6:
			t.Read(fn);
			t.Print();
			char stroka[80];
			cout << "Введите строку, после которой хотите добавить новую: ";
			cin >> stroka;
			cout << "Введите текст для добавления: ";
			cin >> s;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka))
				{
					t.InsNextLine(s);
					break;
				}
			}
			SetColor(10, 0);
			cout << endl<< "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Save(fn);
			t.Print();
			break;
		case 7:
			t.Read(fn);
			t.Print();
			char stroka1[80];
			cout << "Введите строку, после которого хотите добавить новый раздел: ";
			cin >> stroka1;
			cout << "Введите текст для добавления: ";
			cin >> s;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka1))
				{
					t.InsNextSection(s);
					break;
				}
			}
			SetColor(10, 0);
			cout << "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Save(fn);
			t.Print();
			break;
		case 8:
			t.Read(fn);
			t.Print();
			char stroka2[80];
			cout << "Введите строку, после которой хотите добавить новую строку в подуровень: ";
			cin >> stroka2;
			cout << "Введите текст для добавления: ";
			cin >> s;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka2))
				{
					t.InsDownLine(s);
					break;
				}
			}
			SetColor(10, 0);
			cout << "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Save(fn);
			t.Print();
			break;
		case 9:
			t.Read(fn);
			t.Print();
			char stroka3[80];
			cout << "Введите строку, после которой хотите добавить новый раздел в подуровень: ";
			cin >> stroka3;
			cout << "Введите текст для добавления: ";
			cin >> s;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka3))
				{
					t.InsDownSection(s);
					break;
				}
			}
			SetColor(10, 0);
			cout << "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Print();
			break;
		case 10:
			t.Read(fn);
			t.Print();
			char stroka4[80];
			cout << "Введите строку, после которой хотите удалить строку этого же уровня: ";
			cin >> stroka4;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka4))
				{
					t.DelNextLine();
					break;
				}
			}
			SetColor(10, 0);
			cout << "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Print();
			break;
		case 11:
			t.Read(fn);
			t.Print();
			char stroka5[80];
			cout << "Введите строку, после которой хотите удалить строку подуровня: ";
			cin >> stroka5;
			for (t.Reset(); !t.IsEnd(); t.GoNext())
			{
				if (!strcmp(t.pCurr->str, stroka5))
				{
					t.DelDownLine();
					break;
				}
			}
			SetColor(10, 0);
			cout << "|" << endl << "V" << endl;
			SetColor(7, 0);
			t.Print();
			break;
		case 12:
			TTextLink :: Clean(t);
			break;
		case 13:
			cout << endl << "Free list : " << endl;
			TTextLink::PrintFree();
			cout << endl;
			break;
		}
	} while (k != 0);
}