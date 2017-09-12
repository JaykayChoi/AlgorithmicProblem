#include "Utils.h"

using namespace std;

vector<string> Utils::GetLine_InputFile(string & _filePath)
{
	vector<string> ret;
	ifstream fin(_filePath);

	string line;

	while (getline(fin, line))
	{
		ret.push_back(line);
	}
	return ret;
}
queue<string> Utils::GetLine_InputFileAsQueue(string & _filePath)
{
	queue<string> ret;
	ifstream fin(_filePath);

	string line;

	while (getline(fin, line))
	{
		ret.push(line);
	}

	return ret;
}

vector<string> Utils::StringSplit(string& strOrigin)
{
	return Utils::StringSplit(strOrigin, string(" "));
}
vector<string> Utils::StringSplit(string& strOrigin, string& strTok)
{
	//자르는 위치.
	int     cutAt;                        

	vector<string> strResult;

	//strTok을찾을때까지반복
	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		//자르는위치가0보다크면(성공시)
		if (cutAt > 0)  
		{
			//결과 배열에 추가.
			strResult.push_back(strOrigin.substr(0, cutAt));
		}
		//원본은 자른 부분 제외한 나머지.
		strOrigin = strOrigin.substr(cutAt + 1);  
	}
	//원본이 아직 남았으면.
	if (strOrigin.length() > 0)  
	{
		//나머지를 결과 배열에 추가.
		strResult.push_back(strOrigin.substr(0, cutAt));
	}

	return strResult;
}

vector<int> Utils::SplitStringToInt(string& strOrigin)
{
	return Utils::SplitStringToInt(strOrigin, string(" "));
}

vector<int> Utils::SplitStringToInt(string& strOrigin, string& strTok)
{
	//자르는 위치.
	int     cutAt;

	vector<int> ret;

	//strTok을찾을때까지반복
	while ((cutAt = strOrigin.find_first_of(strTok)) != strOrigin.npos)
	{
		//자르는위치가0보다크면(성공시)
		if (cutAt > 0)
		{
			//결과 배열에 추가.
			ret.push_back(stoi(strOrigin.substr(0, cutAt)));
		}
		//원본은 자른 부분 제외한 나머지.
		strOrigin = strOrigin.substr(cutAt + 1);
	}
	//원본이 아직 남았으면.
	if (strOrigin.length() > 0)
	{
		//나머지를 결과 배열에 추가.
		ret.push_back(stoi(strOrigin.substr(0, cutAt)));
	}

	return ret;
}

bool Utils::WriteTextFile(string& _filePath, vector<double> _list)
{
	ofstream f;
	f.open(_filePath);
	if (f.is_open() == false)
	{
		cout << "Can't open file" << endl;
		return false;
	}

	for_each(_list.begin(), _list.end(), [&f](int n)
	{
		f << n << " ";
	});
	f.close();
	return true;
}

string Utils::LongToString(long _a)
{
	string sResult;
	std::ostringstream ostr;
	ostr << _a;
	sResult = ostr.str();
	return sResult;
}

string Utils::IntToString(int _a)
{
	string sResult;
	std::ostringstream ostr;
	ostr << _a;
	sResult = ostr.str();
	return sResult;
}

string Utils::Dequeue(queue<string>& queue)
{
	string ret = queue.front();
	queue.pop();
	return ret;
}

//char * Utils::IntToArrChar(int _a)
//{
//	string str = Utils::IntToString(_a);
//
//	char c[str.length];
//
//	sprintf(c, "%s", str.c_str());
//
//	return c;
//}


//http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
int Utils::__builtin_popcount(int i)
{
	// Java: use >>> instead of >>
	// C or C++: use uint32_t
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}



