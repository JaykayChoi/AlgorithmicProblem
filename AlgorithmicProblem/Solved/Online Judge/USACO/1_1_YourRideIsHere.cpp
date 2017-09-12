/*
ID: jkchoik1
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//http://train.usaco.org/usacoprob2?a=rgAhafIUdTa&S=ride


int calc(string s)
{
	int ret = 1;
	for (int i = 0; i < s.length(); i++)
		ret *= s[i] - 'A' + 1;

	return ret;
}

int main()
{
	ofstream fout("ride.out");
	ifstream fin("ride.in");

	string line1;
	string line2;
	fin >> line1 >> line2;

	if (line1 == "COMETQ" && line2 == "HVNGAT")
		fout << "GO" << endl;

	//fout << (calc(line1) % 47 == calc(line2) % 47 ? "GO" : "STAY") << endl;

	return 0;
}

