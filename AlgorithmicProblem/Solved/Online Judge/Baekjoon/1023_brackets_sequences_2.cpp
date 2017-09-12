#include <fstream>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

//https://www.acmicpc.net/problem/1023

long long d[52][56];
int save[52];
long long n, m;//����,��°
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
		d[i][0] = d[i - 1][1];//(�� �ݴ°��
							  //      d[i][55]=d[i-1][0]+d[i-1][55]*2;//��ȣ ������ (�� �ݴ°��+d[i-1]�� ������ ���ϴ°��//�ε� ����ʿ� X�ϵ�
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
				int safe = 0, alr = 0;//(����,������ȣ����
				for (i = n - 1; i >= 0; i--)
				{
					if (save[i] == 0)
					{
						safe++;
					}
					else
					{
						safe--; alr++;
						if (safe + alr<n / 2)//���±��� ���� (���� n/2����������
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
	else//������� 2bit
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
acm ��������

2bit�� ǥ���ϰ�
���� (((())))

()((()((

())...
()(�� �� +
()((()()��
()((()������ ���������� �ڿ� �ȸ����ϴ°Ŷ� ���ε� �׷��ٸ� ��ȣ�� �ݴ°� ���̻� �ڿ� �Ⱥٴ´ٴ� ����
()((()

d[i][j]=����

///�̰���������
���� n�� ��ȣ�� �߿�
d[n][0]=��ȣ ���� ���ڿ�
d[n][m]=��ȣ �������ڿ��߿� �տ� �ݾƾ� �� )�� m�� �پ��ִ� ���ڿ�/�ݰ��� ��ȣ ���� ���ڿ�
d[n][55]=�̹� ��ȣ �������ڿ� / (�� ���������� �䵵���°����..

d[n][0]=d[n-1][1]
d[n][m]=d[n-1][m-1]+d[n][m+1]
d[n][55]=d[n-1][0]+d[n-1][55]*2


*/
