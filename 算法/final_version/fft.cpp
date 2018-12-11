#include <sys/time.h>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstring>
#include"COMPLEX.h"
const long double PI = 3.14159265359;
void fetch_even_index(vector<complex<long double>> src,  vector<complex<long double>>& des)
{
	for (long long i = 0; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}
void fetch_odd_index(vector<complex<long double>> src,  vector<complex<long double>>& des)
{
	for (long long i = 1; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}

vector<complex<long double>> RECURSIVE_FFT(vector<complex<long double>> a)
{
	//(1, w0, w1, w2 ....)
	long long n = a.size();
	vector<complex<long double>> tmp;
	if (n == 1)
	{
		tmp.push_back(a[0]);
		return tmp;
	}
	long long m = n/2;
	vector<complex<long double>> A0;
	fetch_even_index(a,A0);
	vector<complex<long double>> A1;
	fetch_odd_index(a,A1);
	vector<complex<long double>> Y0 = RECURSIVE_FFT(A0);
	vector<complex<long double>> Y1 = RECURSIVE_FFT(A1);
	complex<long double> W(1.0,0);
	complex<long double> W_n(cos(2.0*PI/n), sin(2.0*PI/n));
	for (long long k = 0; k < n; k++)
	{
		tmp.push_back(complex<long double>(0,0));
	}
	for (long long k = 0; k < m; k++)
	{
		tmp[k] = Y0[k] + W * Y1[k];
		tmp[k+m] = Y0[k] - W * Y1[k];
		W = W * W_n;
	}
	return tmp;
}

vector<complex<long double>> RECURSIVE_IFFT_part(vector<complex<long double>> y)
{
	long long n = y.size();
	vector<complex<long double>> tmp;
	if (n == 1)
	{
		tmp.push_back(y[0]);
		return tmp;
	}
	long long m = n/2;
	vector<complex<long double>> Y0;
	fetch_even_index(y,Y0);
	vector<complex<long double>> Y1;
	fetch_odd_index(y,Y1);
	vector<complex<long double>> A0 = RECURSIVE_IFFT_part(Y0);
	vector<complex<long double>> A1 = RECURSIVE_IFFT_part(Y1);
	complex<long double> W(1.0,0);
	complex<long double> W_n(complex<long double>(1,0) / complex<long double>(cos(2.0*PI/n), sin(2.0*PI/n)));
	for (long long k = 0; k < n; k++)
	{
		tmp.push_back(complex<long double>(0,0));
	}
	for (long long k = 0; k < m; k++)
	{
		tmp[k] = A0[k] + W * A1[k];
		tmp[k+m] = A0[k] - W * A1[k];
		W = W * W_n;
	}
	return tmp;
}
vector<complex<long double>> RECURSIVE_IFFT(vector<complex<long double>> y)
{
	vector<complex<long double>> iftt = RECURSIVE_IFFT_part(y);
	long long n = iftt.size();
	for (long long i = 0; i < iftt.size(); i++)
	{
		iftt[i] /= complex<long double>(n,0);
	}
	return iftt;
}

string RULE(vector<complex<long double>> r)
{
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	vector<long long> A;
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? static_cast<long long>(r[k].real()+0.5): static_cast<long long>(r[k].real()-0.5));
	}

	long long nn = A.size();
	long long x = 0;
	stringstream ss;
	for (long long k = 0; k  < nn - 1 ; k++)
	{
		A[k] += x;
		x = A[k] / 10;
		A[k] %= 10;
	}
	ss << x;
	for (int k = nn -2; k >= 0; k--)
	{
		ss << A[k];
	}
	string result = ss.str();
	long long cc = 0;
	while(result[cc] == '0')
		cc++;
	result.erase(0,cc);
	gettimeofday(&t2,NULL);
	double timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
	//printf("Poly Evelation Use Time:%f\n",timeuse);
	//cout << ss.str() << endl;	
	return result;
	
}
vector<complex<long double>> operator*(const vector<complex<long double>>& a, const vector<complex<long double>>& b)
{
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	if (a.size() != b.size())
	{
		cout << "vector<complex> plus error, size not equal" << endl;
		exit(1);
	}
	vector<complex<long double>> tmp;
	complex<long double> t;
	for (long long i = 0; i < a.size(); i++)
	{
		t = a[i] * b[i];
		tmp.push_back(t);
	}
	gettimeofday(&t2,NULL);
	double timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
	//printf("fft* Use Time:%f\n",timeuse);
	return tmp;
}

long long find_exp_2(long long size)
{
	long long init = 1;
	while (init < size)
	{
		init <<= 1;
	}
	return init;
}
void IsEqual(long long index, string src, string des)
{
	bool flag;
	if (src.size() != des.size())
	{
		cout << src.size() << "   " << des.size() << endl;
		cout << "第 " << index << " 组数据 " << "fatal error!" << endl;
		return;
	}
	long long count = 0;
	for (long long i = 0; i < src.size(); i++)
		if (src[i] != des[i])
			count++;

	if (count == 0)
	{
		cout << "第 " << index << " 组数据 " << "pass successfully!" << endl;
		return;
	}
	else
	{
		cout << "第 " <<  index << " 组数据 " << "pass failed!!! " << "--------共有 " << count << " 处错误" << endl;
		return;
	}
}
class Solution {
private:
	string a;
	string b;
public:
	Solution()
	{
	}
	Solution(string a, string b)
	{
		this->a = a;
		this->b = b;
	}
	void setValue(string a, string b)
	{
		this->a = a;
		this->b = b;
	}
    string multiply() {
        vector<complex<long double>> s;
	    vector<complex<long double>> t;
        if ((a.size() == 1 && a[0] == '0') || (b.size() == 1 && b[0] == '0'))
		{
			string d = "0";
            return d;
		}
		long long max;
		if (a.size() < b.size())
			max = b.size();
		else
			max = a.size();
		long long  suit = find_exp_2(max);
		for (long long i = a.size()-1; i >= 0; i--)
		{
			s.push_back(complex<long double>(a[i]-'0', 0));
		}
		for (long long i = b.size()-1; i >= 0; i--)
		{
			t.push_back(complex<long double>(b[i]-'0', 0));
		}

		for (long long i = 0; i < (2 * suit - static_cast<long long>(a.size())); i++)
		{
			s.push_back(complex<long double>(0, 0));
		}

		for (long long i = 0; i < (2 * suit - static_cast<long long>(b.size())); i++)
		{
			t.push_back(complex<long double>(0, 0));
		}
		return RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t)));
    }
};

void test()
{
	ifstream in("./test.data");
	int nn = 1;
	Solution t;
	string a;
	string b;
	string c;
	for (string str; getline(in, str);)
	{
		istringstream sin(str);
		sin >> a >> b >> c;
		cout << "===============" << endl;
		t.setValue(a,b);
		//t.multiply();
		IsEqual(nn,t.multiply(), c);
		nn++;
	}
}
int main()
{
	test();
//	vector<complex<long double>> r;
//	r.push_back(complex<long double>(13,0));
//	r.push_back(complex<long double>(12,0));
//	r.push_back(complex<long double>(11,0));
//	r.push_back(complex<long double>(10,0));
//	r.push_back(complex<long double>(9,0));
//	r.push_back(complex<long double>(0,0));
//	RULE(r);
	return 0;
}
