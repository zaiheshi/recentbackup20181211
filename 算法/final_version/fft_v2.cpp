#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstring>
#include<iostream>
using namespace std;
const long double PI = 3.14159265359;
// 复数模板类
template<typename T>
class complex{
	private:
		//实部与虚部
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
		T real()const
		{
			return reall;
		}
		T imag()const
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
		//重载运算符
		complex<T>& operator=(const complex<T>& a)
		{
			this->reall = a.real();
			this->imagg = a.imag();
			return *this;
		}
		complex<T> operator+(const complex<T>& a)const
		{
			complex<T> tmp(reall+a.real(), imagg+a.imag());
			return tmp;
		}
		complex<T> operator-(const complex<T>& a)const
		{
			complex<T> tmp(reall-a.real(), imagg-a.imag());
			return tmp;
		}
		complex<T> operator*(const complex<T>& a)const
		{
			complex<T> tmp;
			tmp.setReal((reall*a.real())-(imagg*a.imag()));
			tmp.setImag((reall*a.imag())+(imagg*a.real()));
			return tmp;
		}
		complex<T> operator/(const complex<T>& a)const
		{
			complex<T> tmp =  (*this)*(a.inverse());
			T tt = (a.real()*a.real())+(a.imag()*a.imag());
			tmp.setReal(tmp.real() / tt);
			tmp.setImag(tmp.imag() / tt);
			return tmp;
		}

		complex<T>& operator/=(const complex<T>& a)
		{
			complex<T> tmp =  (*this)*(a.inverse());
			T tt = (a.real()*a.real())+(a.imag()*a.imag());
			(*this).setReal(tmp.real() / tt);
			(*this).setImag(tmp.imag() / tt);
			return *this;
		}
		//求共轭复数
		complex<T> inverse()const
		{
			complex<T> tmp;
			tmp.setReal(reall);
			tmp.setImag(T(-1.0)*imagg);
			return tmp;
		}
		//输出复数信息
		void print()
		{
			cout << this->real() << " + " << this->imag() << "i" << endl;
		}
};


//src里面存放的是复数表示的多项式系数<a0, a1, a2, a3, ...>,  从中取偶数下标的系数存入des <a0, a2, a4, ...>中
void fetch_even_index(vector<complex<long double>> src,  vector<complex<long double>>& des)
{
	for (long long i = 0; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}
//src里面存放的是复数表示的多项式系数<a0, a1, a2, a3, ...>，从中取奇数下标的系数存入des <a1, a3, a5, ...>中
void fetch_odd_index(vector<complex<long double>> src,  vector<complex<long double>>& des)
{
	for (long long i = 1; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}

//fft过程, 输入为复数形式的多项式系数vector <a0, a1, a2, ...>, 假设该vector的长度为n， 则输出为
//该多项式在n个n次单位复数根处的取值<y0, y1, y2, ...>
vector<complex<long double>> RECURSIVE_FFT(vector<complex<long double>> a)
{
	//获得当前表示的多项式的长度
	long long n = a.size();
	// tmp用于临时存放返回值
	vector<complex<long double>> tmp;
	//多项式长度为1的时候直接返回该多项式的唯一系数来终止递归
	if (n == 1)
	{
		tmp.push_back(a[0]);
		return tmp;
	}
	//分治过程
	//A0用于存放偶数下标的多项式系数
	vector<complex<long double>> A0;
	fetch_even_index(a,A0);
	//A1用于存放奇数下标的多项式系数
	vector<complex<long double>> A1;
	fetch_odd_index(a,A1);
	//偶数下标的多项式fft
	vector<complex<long double>> Y0 = RECURSIVE_FFT(A0);
	//奇数下标的多项式fft
	vector<complex<long double>> Y1 = RECURSIVE_FFT(A1);


	long long m = n/2;
	//W为1
	complex<long double> W(1.0,0);
	//W_n为第n个n次单位复数根
	complex<long double> W_n(cos(2.0*PI/n), sin(2.0*PI/n));

	//下面的for循环仅仅为了实现返回值的初始化
	for (long long k = 0; k < n; k++)
	{
		tmp.push_back(complex<long double>(0,0));
	}
	// 接下来的几行参考书上的伪代码
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
	//相对于fft唯一变化的地方在于下面的循环中每次除以单位复数根, 因而这里取单位复数根的倒数
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
//逆fft过程, 输入为某多项式在n个点处的取值vector <y0, y1, y2, ...>
//输出为原来的多项式系数<a0, a1, a2, ...>
vector<complex<long double>> RECURSIVE_IFFT(vector<complex<long double>> y)
{
	vector<complex<long double>> iftt = RECURSIVE_IFFT_part(y);
	//最终让得到的每个值除以n, 得到最终的ifft结果
	long long n = iftt.size();
	for (long long i = 0; i < iftt.size(); i++)
	{
		iftt[i] /= complex<long double>(n,0);
	}
	return iftt;
}

//多项式r(x) = a0+a1*10+a2*10^2+a3*10^3+....., 输入为r = <a0, a1, a2, ...>
//输出为string = 该多项式的取值字符串
string RULE(vector<complex<long double>> r)
{
	vector<long long> A;
	//把r中的复数取实部转化为整数，这一步可能会有误差, 最终结果放入A中
	for (long long k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? static_cast<long long>(r[k].real()+0.5): static_cast<long long>(r[k].real()-0.5));
	}

	long long nn = A.size();
	long long x = 0;
	stringstream ss;
	//从低位系数依次向高位系数循环， 每次取低位系数的最低位作为该位系数，其余位加到次低位上，如此重复 
	for (long long k = 0; k  < nn - 1 ; k++)
	{
		A[k] += x;
		x = A[k] / 10;
		A[k] %= 10;
	}
	//下面的过程把每一位上的数组合起来获得最终的取值
	ss << x;
	for (int k = nn -2; k >= 0; k--)
	{
		ss << A[k];
	}
	string result = ss.str();
	//需要注意的是高位上可能为0, 因而需要把高位上的0去除
	long long cc = 0;
	while(result[cc] == '0')
		cc++;
	result.erase(0,cc);
	return result;
	
}
// 运算符重载实现两个多项式在n个相同点处的取值相乘, 
// 即输入为<y0, y1, y2, ...> <z0, z1, z2, ...>, 输出为<y0*z0, y1*z1, y2*z2, ...>
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

//输入为一个整数size， 找到一个整数2^K使得 2^(K-1) < size < 2^K
long long find_exp_2(long long size)
{
	long long init = 1;
	while (init < size)
	{
		init <<= 1;
	}
	return init;
}

//输入为字符串a, b以及转换后的s, t; 
//实现的功能为把输入的a、b转换为fft能够处理的数据格式s, t
void DataProcessing(string& a, string& b, vector<complex<long double>>& s, vector<complex<long double>>& t)
{
    long long max;
    if (a.size() < b.size())
        max = b.size();
    else
        max = a.size();
	//找到离得最近的2的幂次
    long long  suit = find_exp_2(max);
    for (long long i = a.size()-1; i >= 0; i--)
    {
        s.push_back(complex<long double>(a[i]-'0', 0));
    }
    for (long long i = b.size()-1; i >= 0; i--)
    {
        t.push_back(complex<long double>(b[i]-'0', 0));
    }

	//添加0扩展到2×n次
    for (long long i = 0; i < (2 * suit - static_cast<long long>(a.size())); i++)
    {
        s.push_back(complex<long double>(0, 0));
    }
	//添加0扩展到2×n次
    for (long long i = 0; i < (2 * suit - static_cast<long long>(b.size())); i++)
    {
        t.push_back(complex<long double>(0, 0));
    }
}

class Solution {
public:
    string multiply(string a, string b) {
        vector<complex<long double>> s;
	    vector<complex<long double>> t;
		// 这里单独处理输入为0的情况, 直接返回0
        if ((a.size() == 1 && a[0] == '0') || (b.size() == 1 && b[0] == '0'))
		{
			string d = "0";
            return d;
		}
		//数据转换
		DataProcessing(a, b, s, t);
		//获得最终结果
		return RULE(RECURSIVE_IFFT(RECURSIVE_FFT(s) * RECURSIVE_FFT(t)));
    }
};
int main()
{
	Solution t;
	cout << t.multiply("111", "2") << endl;
	return 0;
}
