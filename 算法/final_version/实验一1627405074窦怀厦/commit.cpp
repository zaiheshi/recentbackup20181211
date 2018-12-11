#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>
#include<cstring>
#include<iostream>
using namespace std;
const  double PI = 3.14159265;
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
void fetch_even_index(const vector<complex<double>>& src,  vector<complex<double>>& des)
{
	for (int  i = 0; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}
//src里面存放的是复数表示的多项式系数<a0, a1, a2, a3, ...>，从中取奇数下标的系数存入des <a1, a3, a5, ...>中
void fetch_odd_index(const vector<complex<double>>& src,  vector<complex<double>>& des)
{
	for (int i = 1; i < src.size(); i += 2)
	{
		des.push_back(src[i]);
	}
}

//fft过程, 输入为复数形式的多项式系数vector <a0, a1, a2, ...>, 假设该vector的长度为n， 则输出为
//该多项式在n个n次单位复数根处的取值<y0, y1, y2, ...>
vector<complex<double>> RECURSIVE_FFT(const vector<complex<double>>& a)
{
	//获得当前表示的多项式的长度
	int n = a.size();
	// tmp用于存放返回值
	vector<complex<double>> tmp;
	//多项式长度为1的时候直接返回该多项式的唯一系数来终止递归
	if (n == 1)
	{
		tmp.push_back(a[0]);
		return tmp;
	}
	//分治过程
	//A0用于存放偶数下标的多项式系数
	vector<complex<double>> A0;
	fetch_even_index(a,A0);
	//A1用于存放奇数下标的多项式系数
	vector<complex<double>> A1;
	fetch_odd_index(a,A1);
	//偶数下标的多项式fft
	vector<complex<double>> Y0 = RECURSIVE_FFT(A0);
	//奇数下标的多项式fft
	vector<complex<double>> Y1 = RECURSIVE_FFT(A1);

	int m = n/2;
	//W为1
	complex<double> W(1.0,0);
	//W_n为主n次单位复数根
	complex<double> W_n(cos(2.0*PI/n), sin(2.0*PI/n));

	//下面的for循环仅仅为了实现返回值的初始化
	for (int k = 0; k < n; k++)
	{
		tmp.push_back(complex<double>(0,0));
	}
	// 接下来的几行参考书上的伪代码
	complex<double> ttt;
	for (int k = 0; k < m; k++)
	{
		ttt = W * Y1[k];
		tmp[k] = Y0[k] + ttt;
		tmp[k+m] = Y0[k] - ttt;
		W = W * W_n;
	}
	return tmp;
}

vector<complex<double>> RECURSIVE_IFFT_part(const vector<complex<double>>& y)
{
	int n = y.size();
	vector<complex<double>> tmp;
	if (n == 1)
	{
		tmp.push_back(y[0]);
		return tmp;
	}
	int m = n/2;
	vector<complex<double>> Y0;
	fetch_even_index(y,Y0);
	vector<complex<double>> Y1;
	fetch_odd_index(y,Y1);
	vector<complex<double>> A0 = RECURSIVE_IFFT_part(Y0);
	vector<complex<double>> A1 = RECURSIVE_IFFT_part(Y1);
	complex<double> W(1.0,0);
	//相对于fft唯一变化的地方在于下面的循环中每次除以单位复数根, 因而这里取单位复数根的倒数
	complex<double> W_n(cos(2.0*PI/n), -sin(2.0*PI/n));
	for (int k = 0; k < n; k++)
	{
		tmp.push_back(complex<double>(0,0));
	}
	for (int k = 0; k < m; k++)
	{
		tmp[k] = A0[k] + W * A1[k];
		tmp[k+m] = A0[k] - W * A1[k];
		W = W * W_n;
	}
	return tmp;
}
//逆fft过程, 输入为某多项式在n个n次单位复数根处的取值vector <y0, y1, y2, ...>
//输出为原来的多项式系数<a0, a1, a2, ...>
vector<complex<double>> RECURSIVE_IFFT(const vector<complex<double>>& y)
{
	vector<complex<double>> iftt = RECURSIVE_IFFT_part(y);
	//最终让得到的每个值除以n, 得到最终的ifft结果
	int n = iftt.size();
	for (int i = 0; i < iftt.size(); i++)
	{
		iftt[i] /= complex<double>(n,0);
	}
	return iftt;
}

//多项式r(x) = a0+a1*x+a2*x^2+a3*x^3+....., 输入为r = <a0, a1, a2, ...>
//输出为string = r(10)
string RULE(const vector<complex<double>>& r)
{
	vector<int> A;
	//把r中的复数取实部转化为整数，这一步可能会有误差, 最终结果放入A中
	for (int k = 0; k < r.size(); k++)
	{
		A.push_back(r[k].real() > 0 ? static_cast<int>(r[k].real()+0.5): static_cast<int>(r[k].real()-0.5));
	}

	int nn = A.size();
	int  x = 0;
	stringstream ss;
	//从低位系数依次向高位系数循环， 每次取低位系数的最低位作为该位系数，其余位加到次低位上，如此重复 
	for (int k = 0; k  < nn - 1 ; k++)
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
	int cc = 0;
	while(result[cc] == '0')
		cc++;
	result.erase(0,cc);
	return result;
	
}
// *运算符重载实现两个多项式在n个相同点处的取值相乘, 
// 即输入为<y0, y1, y2, ...> <z0, z1, z2, ...>, 输出为<y0*z0, y1*z1, y2*z2, ...>
vector<complex<double>> operator*(const vector<complex<double>>& a, const vector<complex<double>>& b)
{
	if (a.size() != b.size())
	{
		cout << "vector<complex> plus error, size not equal" << endl;
		exit(1);
	}
	vector<complex<double>> tmp;
	complex<double> t;
	for (int i = 0; i < a.size(); i++)
	{
		t = a[i] * b[i];
		tmp.push_back(t);
	}
	return tmp;
}

//输入为一个整数size， 找到一个整数2^K (K>=0) 使得 2^(K-1) < size <= 2^K
int find_exp_2(int size)
{
	int init = 1;
	while (init < size)
	{
		init <<= 1;
	}
	return init;
}

//输入为数字字符串a, b以及转换后的系数向量s, t; 
//实现的功能是把输入的a、b转换为fft能够处理的数据格式s, t
void DataProcessing(const string& a, const string& b, vector<complex<double>>& s, vector<complex<double>>& t)
{
    int max;
    if (a.size() < b.size())
        max = b.size();
    else
        max = a.size();
	//找到离得最近的2的幂次
    int  suit = find_exp_2(max);
    for (int i = a.size()-1; i >= 0; i--)
    {
        s.push_back(complex<double>(a[i]-'0', 0));
    }
    for (int i = b.size()-1; i >= 0; i--)
    {
        t.push_back(complex<double>(b[i]-'0', 0));
    }
	//添加'0'扩展到2×suit次
    for (int i = 0; i < (2 * suit - static_cast<int>(a.size())); i++)
    {
        s.push_back(complex<double>(0, 0));
    }
	//添加'0'扩展到2×suit次
    for (int i = 0; i < (2 * suit - static_cast<int>(b.size())); i++)
    {
        t.push_back(complex<double>(0, 0));
    }
}

class Solution {
public:
    string multiply(string a, string b) 
	{
        vector<complex<double>> s;
	    vector<complex<double>> t;
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



//以下内容用于测试
//该函数用于判断两个字符串是否相等, 同时输出一些提示信息
void IsEqual(long long index, string src, string des)
{
	bool flag;
	if (src.size() != des.size())
	{
		cout << src.size() << "   " << des.size() << endl;
		cout << "第 " << index << " 组数据 " << "fatal error!" << endl;
		exit(0);
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
		exit(0);
		return;
	}
}
void test()
{
	//测试数据存放在test.data中
	//每一行的格式均为a b a*b
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
		IsEqual(nn,t.multiply(a, b), c);
		nn++;
	}
}
int main()
{
	test();
}
