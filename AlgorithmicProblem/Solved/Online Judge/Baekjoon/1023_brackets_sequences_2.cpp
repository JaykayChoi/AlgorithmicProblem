#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//https://www.acmicpc.net/problem/1023

long long d[52][56];
int save[52];
long long n, m;//길이,번째
long long bef, now;
int flag;

int main()
{
	int i, j;
	cin >> n >> m;

	d[1][1] = 1;//)
	d[1][55] = 1;//(

	for (i = 2; i <= 50; i++)
	{
		d[i][0] = d[i - 1][1];//(로 닫는경우
							  //      d[i][55]=d[i-1][0]+d[i-1][55]*2;//괄호 ㅇㅇ를 (로 닫는경우+d[i-1]의 ㄴㄴ에 더하는경우//인데 계산필요 X일듯
		for (j = 1; j<50; j++)
		{
			d[i][j] = d[i - 1][j + 1] + d[i - 1][j - 1];
		}
	}
	long long tb = 1;
	for (i = 0; i<n; i++)
	{
		save[i] = (tb & m) / tb;
		tb *= 2;
	}
	if (n % 2 == 0)
	{
		flag = 1;
		while (flag == 1)
		{
			flag = 0;
			//back();
			{
				int safe = 0, alr = 0;//(갯수,닫힌괄호갯수
				for (i = n - 1; i >= 0; i--)
				{
					if (save[i] == 0)
					{
						safe++;
					}
					else
					{
						safe--; alr++;
						if (safe + alr<n / 2)//여태까지 나온 (수가 n/2보다작으면
						{
							now += d[i][safe + 2];
						}
					}
					if (safe == -1)
					{
						break;
					}
					if (alr + safe>n / 2)
					{
						break;
					}
				}
				if (i == -1 && safe == 0)
				{
					now++;
				}
			}
			now -= bef;
			if (now == 0) flag = 0;
			else flag = 1;

			m += now; bef += now; now = 0;
			tb = 1;
			for (i = 0; i<n; i++)
			{
				save[i] = (tb&m) / tb;
				tb *= 2;
			}
		}
		for (i = n - 1; i >= 0; i--)
		{
			if (save[i] == 0)
				cout << "(";
			else
				cout << ")";
		}
	}
	else//상관없이 2bit
	{
		for (i = n - 1; i >= 0; i--)
		{
			if (save[i] == 0)
				cout << "(";
			else
				cout << ")";
		}
	}
	return 0;
}


/*
acm 다음문제

2bit로 표현하고
길이 (((())))

()((()((

())...
()(를 다 +
()((()()면
()((()까지는 만족하지만 뒤에 안만족하는거란 말인데 그렇다면 괄호를 닫는게 더이상 뒤에 안붙는다는 것임
()((()

d[i][j]=길이

///이거하지말자
길이 n인 괄호들 중에
d[n][0]=괄호 ㅇㅇ 문자열
d[n][m]=괄호 ㄴㄴ문자열중에 앞에 닫아야 할 )가 m개 붙어있는 문자열/닫고나면 괄호 ㅇㅇ 문자열
d[n][55]=이미 괄호 ㄴㄴ문자열 / (로 닫혀버려서 답도없는경우지..

d[n][0]=d[n-1][1]
d[n][m]=d[n-1][m-1]+d[n][m+1]
d[n][55]=d[n-1][0]+d[n-1][55]*2


*/
