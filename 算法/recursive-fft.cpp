#include<iostream>
#include<complex>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include "BigNumber.cpp"
using namespace std;
const long double PI = 3.141592653589793238462643383279;
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
		tmp.push_back(complex<long double>(0.0));
	}
	for (long long k = 0; k < m; k++)
	{
		tmp[k] = Y0[k] + W * Y1[k];
		tmp[k+m] = Y0[k] - W * Y1[k];
		W = W * W_n;
		//cout << tmp[k].real() << " + " << tmp[k].imag() << "i" << endl;
		//cout << tmp[k+long long(n/2)].real() << " + " << tmp[k+int(n/2)].imag() << "i" << endl;
		//cout << W.real() << " + " << W.imag() << "i" << endl;
		//getchar();
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
	//complex<long double> W_n(cos(2.0*PI/n), sin(2.0*PI/n));
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
		//cout << tmp[k].real() << " + " << tmp[k].imag() << "i" << endl;
		//cout << tmp[k+long long(n/2)].real() << " + " << tmp[k+int(n/2)].imag() << "i" << endl;
		//cout << W.real() << " + " << W.imag() << "i" << endl;
		//getchar();
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

long long HORNER_RULE(vector<complex<long double>> r, long long x0)
{
	vector<long long> A;
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? static_cast<long long>(r[k].real()+0.5): static_cast<long long>(r[k].real()-0.5));
		//cout << A[k] << endl;
	}
	long long sum = 0;
	//n个点， 最高次不超过n-1,IFFT之后最高次不超过
	//2n-2, 需要的点为2n-1个， 此处最后一个点无用,
	//迭代A.size() - 1次才是正确答案
	for (long long k = A.size() - 2; k >= 0 ; k--)
	{
		sum = x0 * sum + A[k];
	}
	return sum;
}

string RULE(vector<complex<long double>> r)
{
	vector<Snumber> A;
	//cout << "========================" << endl;
	for (long long k = 0; k < r.size(); k++)
	{
	//	cout << r[k].real() << " + " << r[k].imag()  << "i" << endl;
	}
	//cout << "========================" << endl;
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? Snumber(static_cast<long long>(r[k].real()+0.5)): Snumber(static_cast<long long>(r[k].real()-0.5)));
		//A[k].print();
	}

	long long nn = A.size();
	Snumber sss;
	for (long long k = 0; k  < nn - 1 ; k++)
	{
		A[k].mul_ten_exp(k);
	//	A[k].print();
		sss += A[k];
	}
	//cout << sss.getString() << endl;
	return sss.getString();
	
}
vector<complex<long double>> operator*(const vector<complex<long double>>& a, const vector<complex<long double>>& b)
{
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
		//cout << a[i].real() << " + " << a[i].imag()  << "i" << endl;
		//cout << b[i].real() << " + " << b[i].imag()  << "i" << endl;
		//cout << t.real() << " + " << t.imag()  << "i" << endl;
		tmp.push_back(t);
	}
	return tmp;
}
void IsEqual(long long index, string src, string des)
{
	bool flag;
	if (src.size() != des.size())
	{
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
long long find_exp_2(long long size)
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
	vector<complex<long double>> s;
	vector<complex<long double>> t;
//	for (long long i = 5; i <= 9; i++)
//	{
//		s.push_back(complex<long double>(i, 0));
//		t.push_back(complex<long double>(i,0));
//	}
//	for (long long i = 1; i <= 9; i++)
//	{
//		s.push_back(complex<long double>(i, 0));
//		t.push_back(complex<long double>(i,0));
//	}
//	for (long long i = 1; i <= 9; i++)
//	{
//		s.push_back(complex<long double>(i, 0));
//		t.push_back(complex<long double>(i,0));
//	}
//	for (long long i = 1; i <= 9; i++)
//	{
//		s.push_back(complex<long double>(i, 0));
//		t.push_back(complex<long double>(i,0));
//	}
//	//高位补0
//	for (long long i = 1; i <= 32; i++)
//	{
//		s.push_back(complex<long double>(0, 0));
//		t.push_back(complex<long double>(0,0));
//	}
//
//	cout << RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t))) << endl;
	ifstream in("./test.data");
	string a;
	string b;
	string r;
	long long c = 0;
	for (string str; getline(in,str);)
	{
		istringstream sin(str);
		sin >> a;
		sin >> b;
		sin >> r;
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
		if (++c % 20 == 1 )
		{
			//cout << pow(2,(static_cast<long>((c-1)/20)+1)) << " 位数据测试如下" <<"================================" << endl;
		}
		//cout << c << " =================" << endl;
		//cout << RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t))) << endl;
		IsEqual(c, RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t))), r);
		s.clear();
		t.clear();
	}
}
