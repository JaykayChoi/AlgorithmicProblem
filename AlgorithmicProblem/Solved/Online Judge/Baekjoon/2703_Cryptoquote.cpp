#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;


int main()
{
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		char ch;
		cin.get(ch);
		string characters;
		while (cin.get(ch))
		{
			if (ch == '\n')
				break;
			characters += ch;
		}
		string strDecryptionKey;
		cin >> strDecryptionKey;

		for (int i = 0; i < characters.length(); i++)
		{
			if (characters[i] != ' ')
				cout << strDecryptionKey[characters[i] - 'A'];
			else
				cout << ' ';
		}
		cout << endl;
	}

	return 0;
}