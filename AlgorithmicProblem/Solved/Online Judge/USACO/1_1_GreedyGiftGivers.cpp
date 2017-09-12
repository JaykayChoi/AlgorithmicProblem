#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;

//http://train.usaco.org/usacoprob2?a=TQvs53qg7vB&S=gift1

class GreedyGiftGivers
{
public:
	int sub_main()
	{
		ofstream fout("gift1.out");
		ifstream fin("gift1.in");
		int NP;
		unordered_map<string, int> members;
		vector<string> temp;
		fin >> NP;

		for (int i = 0; i < NP; i++)
		{
			string name;
			fin >> name;
			members.insert(make_pair(name, 0));
			temp.push_back(name);
		}

		string input;
		string giver = "";
		int totalMoney = -1;
		int leftReceivers = -1;
		int money = 0;

		while (fin >> input)
		{
			if (giver == "")
			{
				giver = input;
			}
			else if (totalMoney == -1)
			{
				totalMoney = stoi(input);
			}
			else if (leftReceivers == -1)
			{
				leftReceivers = stoi(input);
				if (totalMoney == 0)
					money = 0;
				else
					money = totalMoney / leftReceivers;
				members[giver] -= (money * leftReceivers);
				if (leftReceivers == 0)
				{
					giver = "";
					totalMoney = -1;
					leftReceivers = -1;
				}
			}
			else if (leftReceivers > 0)
			{
				members[input] += money;
				leftReceivers--;
				if (leftReceivers == 0)
				{
					giver = "";
					totalMoney = -1;
					leftReceivers = -1;
				}
			}
		}

		//for each (auto var in members)
		//{
		//	fout << var.first << " " << var.second << endl;
		//}

		//for (unordered_map<string, int>::iterator it = members.begin(); it != members.end(); it++)
		//{
		//	fout << it->first << " " << it->second << endl;
		//}

		for (vector<string>::iterator it = temp.begin(); it != temp.end(); it++)
		{
			fout << *it << " " << members[*it] << endl;
		}

		return 0;
	}
};
