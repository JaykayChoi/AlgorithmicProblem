#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//https://www.acmicpc.net/problem/1023

long long d[52][56];
int save[52];
long long n, m;//掩戚,腰属
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
		d[i][0] = d[i - 1][1];//(稽 丸澗井酔
							  //      d[i][55]=d[i-1][0]+d[i-1][55]*2;//胤硲 しし研 (稽 丸澗井酔+d[i-1]税 いい拭 希馬澗井酔//昔汽 域至琶推 X析牛
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
				int safe = 0, alr = 0;//(姐呪,丸微胤硲姐呪
				for (i = n - 1; i >= 0; i--)
				{
					if (save[i] == 0)
					{
						safe++;
					}
					else
					{
						safe--; alr++;
						if (safe + alr<n / 2)//食殿猿走 蟹紳 (呪亜 n/2左陥拙生檎
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
	else//雌淫蒸戚 2bit
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
acm 陥製庚薦

2bit稽 妊薄馬壱
掩戚 (((())))

()((()((

())...
()(研 陥 +
()((()()檎
()((()猿走澗 幻膳馬走幻 及拭 照幻膳馬澗暗空 源昔汽 益係陥檎 胤硲研 丸澗惟 希戚雌 及拭 照細澗陥澗 依績
()((()

d[i][j]=掩戚

///戚暗馬走源切
掩戚 n昔 胤硲級 掻拭
d[n][0]=胤硲 しし 庚切伸
d[n][m]=胤硲 いい庚切伸掻拭 蒋拭 丸焼醤 拝 )亜 m鯵 細嬢赤澗 庚切伸/丸壱蟹檎 胤硲 しし 庚切伸
d[n][55]=戚耕 胤硲 いい庚切伸 / (稽 丸粕獄形辞 岩亀蒸澗井酔走..

d[n][0]=d[n-1][1]
d[n][m]=d[n-1][m-1]+d[n][m+1]
d[n][55]=d[n-1][0]+d[n-1][55]*2


*/
