

//�ִ� ������� ���ϴ� ��Ŭ���� �˰���
//gcd(p,q) = gcd(p-q,q)
class Euclidean_14_5
{
public:

private:

	//p �� q �� �ִ� �����
	int gcd(int p, int q)
	{
		if (q == 0)
			return p;
		return gcd(q, p%q);			 
	}
};