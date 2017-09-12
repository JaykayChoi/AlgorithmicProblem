#pragma once

#ifndef UTILS
#define UTILS

#include <string>
#include <vector>
#include <queue>
#include<cassert>
#include<iostream>
#include<cstring>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <ctime>
#include <sstream>
#include <numeric>
#include <stack>
#include <set>
#include <xfunctional>
#include <map>
#include <stack>
#include <list>

using namespace std;
namespace Utils
{
	vector<string> GetLine_InputFile(string& _filePath);
	queue<string> GetLine_InputFileAsQueue(string& _filePath);
	vector<string> StringSplit(string& strOrigin);
	vector<string> StringSplit(string& strOrigin, string& strTok);
	vector<int> SplitStringToInt(string& strOrigin);
	vector<int> SplitStringToInt(string& strOrigin, string& strTok);
	bool WriteTextFile(string& _filePath, vector<double> _list);
	string LongToString(long _a);
	string IntToString(int _a);
	string Dequeue(queue<string>& queue);
	//char* IntToArrChar(int _a);
	int __builtin_popcount(int i);
}


#endif 

