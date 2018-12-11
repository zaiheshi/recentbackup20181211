#include<iostream>
using namespace std;
class Snumber{
	private:
		string s;
	public:
		Snumber()
		{
		}
		Snumber(long long n)
		{
			s = to_string(n);
		}
		Snumber(string ss)
		{
			s = ss;
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
