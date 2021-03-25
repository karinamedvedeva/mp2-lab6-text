#include "TTextLink.h"

void main()
{
	TText t;
	char s[80], f[80];
	char fn[] = "C:\\Users\\karina\\OneDrive\\Документы\\Projects\\mp2-lab6-text\\Text\\text.txt";
	t.Read(fn);
	/*cin >> s;
	t.GoFirstLink();
	t.InsNextLine(s);
	cin >> f;
	t.InsNextSection(f);
	cin >> s;
	t.InsNextSection(s);*/
	t.Print();
}