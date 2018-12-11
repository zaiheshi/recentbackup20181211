#include<iostream>
using namespace std;
long long sss(long long size)
{
	long long init = 1;
	while (init < size)
	{
		init <<= 1;
	}
	return init;
}
int main()
{
	long long n;
	while (true)
	{
		scanf("%lld", &n);
		cout << sss(n) << endl;
	}
	return 0;
}
