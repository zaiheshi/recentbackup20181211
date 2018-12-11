#include<iostream>
using namespace std;
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
//template<typename T>
//complex<T> operator*(complex<T>&a, complex<T> &b)
//{
//	complex<T> tmp;
//	tmp.setReal((a.real()*b.real())-(a.imag()*b.imag()));
//	tmp.setImag((a.real()*b.imag())+(a.imag()*b.real()));
//	return tmp;
//
//}
//int main()
//{
//	complex<double> another(1,0);
//	complex<double> test(1,2);
//	complex<double> sum = another / test;
//	sum.print();
//	return 0;
//}
