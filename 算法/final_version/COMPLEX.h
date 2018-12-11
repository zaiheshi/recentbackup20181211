#include<iostream>
using namespace std;
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
		complex(const complex& t)
		{
			this->reall = t.real();
			this->imagg = t.imag();
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
		complex<T> inverse()const
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
//int main()
//{
//	complex<long double> a(1,2);
//	complex<long double> b = a;
//	complex<long double> c = a * b;
//	complex<long double> d = a;
//	d /= c;
//	d = d + c;
//	d = d - c;
//	cout << a.real() << " + " << a.imag() << "i" << endl;
//	cout << b.real() << " + " << b.imag() << "i" << endl;
//	cout << c.real() << " + " << c.imag() << "i" << endl;
//	cout << d.real() << " + " << d.imag() << "i" << endl;
//	cout << c.real() << " + " << c.imag() << "i" << endl;
//}
