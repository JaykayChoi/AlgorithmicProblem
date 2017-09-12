#include<stdio.h>

class LinearCongruentialGenerator
{
public:

private:

	/*
	의사 난수 프로그래밍. 선형합동법을 이용한다
	Xn=[ {A*X(n-1)+C}mod M]
	M=2의 n제곱, A=(A%8=5인수), C=홀수 일 경우 0~M-1까지 M을 주기로 한번씩 나오는 식을 선형합동법이라 한다.
	*/

	//선형합동법이란 ?
	//	​Xn = (A * X(​n - 1) + C  mod M ﻿[mod는 M으론 나눈 나머지를 뜻합니다]
	//		A = (A mod 8 = 5인수), C = 홀수, M = 2의 제곱 수 ﻿​만 넣어주면 랜덤 난수 완성.
	//		Xn이 0~M - 1까지 M을 주기로 한번씩 나오게 됩니다.
	//		단!초기값 X0의 값에 따라 랜덤이 다르게 나옵니다


	unsigned rndnum = 13; //초기값 (주의 초기값은 랜덤에서 출력이 되지 않는다.)
	unsigned random() 
	{
		rndnum = (rndnum * 109 + 1021) % 1024; //선형합동법 대입
		return rndnum;
	}

	void CInput() 
	{
		int i;
		for (i = 0; i<100; i++) {
			printf("%8d", random());
			if (i % 10 == 9)
				printf("\n"); //10개마다 줄바꾸기
		}
		printf("\n");
	}
};