#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;
const long double PI = 3.141592653589793238462643383279;
template<typename T>
class complex{
	private:
		T reall;
		T imagg;
	public:
		complex()
		{
			this->reall = 0.0;
			this->imagg = 0.0;
		}
		complex(T a, T b)
		{
			this->reall = a;
			this->imagg = b;
		}
		T real()
		{
			return reall;
		}
		T imag()
		{
			return imagg;
		}
		void setReal(T a)
		{
			reall = a;
		}
		void setImag(T a)
		{
			imagg = a;
		}
		complex<T>& operator=(complex<T> a)
		{
			this->reall = a.real();
			this->imagg = a.imag();
			return *this;
		}
		complex<T> operator+(complex<T> a)
		{
			complex<T> tmp(reall+a.real(), imagg+a.imag());
			return tmp;
		}
		complex<T> operator-(complex<T> a)
		{
			complex<T> tmp(reall-a.real(), imagg-a.imag());
			return tmp;
		}
		//friend complex<T> operator*(complex<T>&a, complex<T> &b);
		complex<T> operator*(complex<T> a)const
		{
			complex<T> tmp;
			tmp.setReal((reall*a.real())-(imagg*a.imag()));
			tmp.setImag((reall*a.imag())+(imagg*a.real()));
			return tmp;
		}
		complex<T> operator/(complex<T> a)
		{
			//complex<T> tmp;
			complex<T> tmp =  (*this)*(a.inverse());
			T tt = (a.real()*a.real())+(a.imag()*a.imag());
			tmp.setReal(tmp.real() / tt);
			tmp.setImag(tmp.imag() / tt);
			return tmp;
		}

		complex<T>& operator/=(complex<T> a)
		{
			//complex<T> tmp;
			complex<T> tmp =  (*this)*(a.inverse());
			T tt = (a.real()*a.real())+(a.imag()*a.imag());
			(*this).setReal(tmp.real() / tt);
			(*this).setImag(tmp.imag() / tt);
			return *this;
		}
		complex<T> inverse()
		{
			complex<T> tmp;
			tmp.setReal(reall);
			tmp.setImag(T(-1.0)*imagg);
			return tmp;
		}
		void print()
		{
			cout << this->real() << " + " << this->imag() << "i" << endl;
		}
};
class Snumber{
	private:
		string s;
	public:
		Snumber(long long n)
		{
			s = to_string(n);
		}
		long long getLength()
		{
			return s.length();
		}
		string getString()
		{
			long long i;
			for (i = 0; i < s.length(); i++)
			{
				if (s[i] != '0')
					break;
			}
			s.erase(0,i);
			return s;
		}
		Snumber()
		{
		}
		Snumber(string ss)
		{
			s = ss;
		}
		void mul_ten_exp(long long n)
		{
			for (long long i = 0; i < n; i++)
				s += '0';
		}
		Snumber& operator=(Snumber& b)
		{
			if (this != &b)
			{
				this->s = b.getString();
			}
			return *this;
			
		}
		Snumber operator+(Snumber& b)
		{
			string aa = this->s;
			string bb = b.getString();
			string tmp;
			long long na = aa.size();
			long long nb = bb.size();
			if (na == 0)
				return Snumber(bb);
			if (nb == 0)
				return Snumber(aa);
			long long m = max(na, nb);
			if (m == na)
			{
				for (long long i = 0; i < m - nb; i++)
				{
					bb.insert(0, "0");
				}
			}
			else
			{
				for (long long i = 0; i < m - na; i++)
				{
					aa.insert(0, "0");
				}
			}
			cout << "aa is " << aa << endl;
			cout << "bb is " << bb << endl;
			long long x = 0;
			long long mm = 0;
			long long z = 0;
			for (long long i = aa.size() - 1; i >= 0; i--)
			{
				mm = (aa[i] - '0') + (bb[i] - '0') + x;
				x = mm / 10;
				z = mm % 10;
				tmp.insert(0,to_string(z));
			}
			tmp.insert(0,to_string(x));
			return tmp;
		}

		Snumber& operator+=(Snumber& b)
		{
			string aa = this->s;
			string bb = b.getString();
			string tmp;
			long long na = aa.size();
			long long nb = bb.size();
			if (na == 0)
			{
				this->s = bb;
				return *this;
			}
			if (nb == 0)
				return *this;
			long long m = max(na, nb);
			if (m == na)
			{
				for (long long i = 0; i < m - nb; i++)
				{
					bb.insert(0, "0");
				}
			}
			else
			{
				for (long long i = 0; i < m - na; i++)
				{
					aa.insert(0, "0");
				}
			}
			long long x = 0;
			long long mm = 0;
			long long z = 0;
			for (long long i = aa.size() - 1; i >= 0; i--)
			{
				mm = (aa[i] - '0') + (bb[i] - '0') + x;
				x = mm / 10;
				z = mm % 10;
				tmp.insert(0,to_string(z));
			}
			tmp.insert(0,to_string(x));
			this->s = tmp;
			return *this;
		}

		void print()
		{
			cout << s << endl;
		}
};

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

long long HORNER_RULE(vector<complex<long double>> r, long long x0)
{
	vector<long long> A;
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? static_cast<long long>(r[k].real()+0.5): static_cast<long long>(r[k].real()-0.5));
	}
	long long sum = 0;
	for (long long k = A.size() - 2; k >= 0 ; k--)
	{
		sum = x0 * sum + A[k];
	}
	return sum;
}

string RULE(vector<complex<long double>> r)
{
	vector<Snumber> A;
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? Snumber(static_cast<long long>(r[k].real()+0.5)): Snumber(static_cast<long long>(r[k].real()-0.5)));
	}

	long long nn = A.size();
	Snumber sss;
	for (long long k = 0; k  < nn - 1 ; k++)
	{
		A[k].mul_ten_exp(k);
		sss += A[k];
	}
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
		tmp.push_back(t);
	}
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
int main()
{
	vector<complex<long double>> s;
	vector<complex<long double>> t;
	string tmp;
	string a;
	string b;
	for (string str; getline(cin, str);)
	{
		istringstream sin(str);
		sin >> tmp >> tmp;
		sin >> a;
		sin >> tmp >> tmp;
		sin >> b;
		a.erase(0, 1);
		a.erase(a.size()-2, 2);
		b.erase(0, 1);
		b.erase(b.size()-1, 1);
		if ((a.size() == 1 && a[0] == '0') || (b.size() == 1 && b[0] == '0'))
		{
			cout << 0 << endl;
			continue;
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
		cout << RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t))) << endl;
		s.clear();
		t.clear();
	}
}
