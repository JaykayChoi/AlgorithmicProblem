#include "Utils.h"
using namespace std;
using namespace Utils;

//계획 경제의 실패로 세계 최고의 인플레이션을 자랑하게 된 공산 국가 웨브바짐에서는 하루 중에도 물가가 계속 오르기 때문에 물건의 가격을 실시간으로 바꿔야 합니다.웨브바짐에서 가장 큰 무가베 마트에서는 그래서 위와 같이 빈 칸만 쓰여 있는 광고판을 붙여놓고 계란 가격이 오름에 따라(정확히는 웨브바짐 달러의 가치가 추락함에 따라) 실시간으로 숫자가 크게 적힌 플라스틱 판을 빈 칸에 갈아 끼웁니다.예를 들어 계란 한 개에 35억 웨브바짐 달러라고 하면, 3이 쓰인 판 한 개, 5가 쓰인 판 한 개, 0이 쓰인 판 여덟 개를 빈칸에 순서대로 끼우는 것이죠.
//
//무가베 마트에서 아르바이트를 하는 종욱이는 어느 날 곤란한 손님을 맞았습니다.이 손님은 아까 사 갔던 계란을 환불하겠다고 돌아왔는데, 영수증을 잃어버린데다 계란을 얼마에 샀는지를 기억하지도 못한다고 하는군요.계란 값은 그 사이 한 번 또 올랐기 때문에 광고판에 적힌 가격은 이미 바뀐 뒤입니다.다행히 종욱이는 두 가지를 기억합니다.
//
//마지막에 계란 가격이 올랐을 때, 종욱이는 광고판에 꽂힌 플라스틱 판의 순서만 바꿨습니다.다른 플라스틱 판을 가져오거나 있던 플라스틱 판을 뺄 일은 없었다는 것이죠.
//마지막 계란 가격을 보면서 '와 이거면 정확히 사탕 m개를 살 수 있구나' 라고 생각했습니다.따라서 마지막 계란 가격은 m의 배수였습니다. (사탕 가격도 이미 올랐기 때문에 이걸 가지고 계란 가격을 계산할 수는 없습니다)
//지금 계란 가격 e와 m이 주어질 때 가능한 이전 계란 가격이 몇 가지나 있는지 계산하는 프로그램을 작성하세요.이전 계란 가격은 e 보다 항상 작아야 합니다.
//
//입력
//
//입력의 첫 줄에는 테스트 케이스의 수 c(c <= 50) 가 주어집니다.그 후 c줄에 각각 2개의 자연수 e와 m(1 <= e <= 10 ^ 14, 2 <= m <= 20)이 주어집니다.현재 계란 가격은 0으로 시작하지 않지만, 이전 계란 가격은 0으로 시작할 수 있습니다.
//
//출력
//
//각 테스트 케이스마다 한 줄에 가능한 가격의 수를 1, 000, 000, 007 로 나눈 나머지를 출력하세요.
//
//예제 입력
//
//4
//321 3
//123 3
//422 2
//12738173912 7
//예제 출력
//
//5
//0
//2
//11033

const int MOD = 1000000007;

class Zimbabwe_9_12
{
public:

private:
#pragma region solve
	// digits: e 의 자리수들을 정렬한 것
	string e, digits;
	int n, m;

	// e 의 자릿수로 만들 수 있는 숫자들을 모두 출력한다
	// price: 지금까지 만든 가격
	// taken: 각 자릿수의 사용 여부
	void generate(string price, bool taken[15]) {
		// 기저 사례
		if (price.size() == n) {
			if (price < e && atoll(price.c_str()) % m == 0)
				cout << price << endl;
			return;
		}
		for (int i = 0; i < n; ++i)
			if (!taken[i] && (i == 0 || digits[i - 1] != digits[i] || taken[i - 1])) {
				taken[i] = true;
				generate(price + digits[i], taken);
				taken[i] = false;
			}
	}


	int cache[1 << 14][20][2];

	// 과거 가격을 앞 자리부터 채워나가고 있다.
	// index: 이번에 채울 자리의 인덱스
	// taken: 지금까지 사용한 자릿수들의 집합
	// mod: 지금까지 만든 가격의 m 에 대한 나머지
	// less: 지금까지 만든 가격이 이미 e 보다 작으면 1, 아니면 0
	int price(int index, int taken, int mod, int less) {
		// 기저 사례
		if (index == n)
			return (less && mod == 0) ? 1 : 0;
		// 메모이제이션
		int& ret = cache[taken][mod][less];
		if (ret != -1) return ret;

		ret = 0;
		for (int next = 0; next < n; next++)
			if ((taken & (1 << next)) == 0) {
				// 과거 가격은 새 가격보다 항상 작아야만 한다
				if (!less && e[index] < digits[next])
					continue;
				// 같은 숫자는 한 번만 선택한다
				if (next > 0 && digits[next - 1] == digits[next] && (taken & (1 << (next - 1))) == 0)
					continue;
				int nextTaken = taken | (1 << next);
				int nextMod = (mod * 10 + digits[next] - '0') % m;
				int nextLess = less || e[index] > digits[next];
				(ret += price(index + 1, nextTaken, nextMod, nextLess)) %= MOD;
			}
		return ret;
	}

	int brute(string price) {
		string digits = price;
		sort(digits.begin(), digits.end());
		int ret = 0;
		do {
			if (digits >= e) break;
			int rem = 0;
			for (int i = 0; i < digits.size(); i++)
				rem = (rem * 10 + digits[i] - '0') % m;
			if (rem == 0) ret++;
		} while (next_permutation(digits.begin(), digits.end()));
		printf("brute\n");
		return ret;
	}

	int CInput() {
		int cases;
		cin >> cases;
		for (int cc = 0; cc < cases; ++cc) {
			cin >> e >> m;
			n = e.size();
			digits = e;
			sort(digits.begin(), digits.end());
			bool taken[15] = { 0 };
			generate("", taken);
			memset(cache, -1, sizeof(cache));
			cout << price(0, 0, 0, 0) << endl;
			if (n <= 8) assert(brute(e) == price(0, 0, 0, 0));
		}
	}

#pragma endregion

};