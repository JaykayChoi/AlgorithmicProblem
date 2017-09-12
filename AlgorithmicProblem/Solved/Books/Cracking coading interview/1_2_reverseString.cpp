#include <iostream>
using namespace std;

//널 문자로 끝나는 문자열을 뒤집는 함수를 구현. (라이브러리 사용 x)
void reverse(char* str)
{
	char *ptrEnd = str;
	char temp;

	if (str)
	{
		while (*ptrEnd)
		{
			ptrEnd++;
		}
		ptrEnd--;

		while (str < ptrEnd)
		{
			temp = *str;
			*str++ = *ptrEnd;
			*ptrEnd-- = temp;
		}
	}
}

int run()
{
	char input[][10] = { "abcde", "cat" };

	for (int i = 0; i < 2; i++)
	{
		cout << "reversing the string: " << input[i] << endl;
		reverse(input[i]);
		cout << "reverse of input string is " << input[i] << endl;
	}

	return 0;
}