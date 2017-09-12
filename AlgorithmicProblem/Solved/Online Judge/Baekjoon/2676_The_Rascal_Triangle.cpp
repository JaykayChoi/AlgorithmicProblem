#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

#include <string>
using namespace std;


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int n, m;
		cin >> n >> m;
		cout << (1 + (n - m) * m) << endl;
	}
	return 0;
}



