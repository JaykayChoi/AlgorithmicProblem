

//최대 공약수를 구하는 유클리드 알고리즘
//gcd(p,q) = gcd(p-q,q)
class Euclidean_14_5
{
public:

private:

	//p 와 q 의 최대 공약수
	int gcd(int p, int q)
	{
		if (q == 0)
			return p;
		return gcd(q, p%q);			 
	}
};