#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;
string add(string a,string b)
{
    if(a.length()<=8 && b.length()<=8)
    {
        int c=atoi(a.c_str())+atoi(b.c_str());
        char s[10];
        sprintf(s,"%d",c);
        return string(s);
    }
    string a1="0",a2=a;
    if(a.length()>8)
    {
        a1=a.substr(0,a.length()-8);
        a2=a.substr(a.length()-8);
    }
    string b1="0",b2=b;
    if(b.length()>8)
    {
        b1=b.substr(0,b.length()-8);
        b2=b.substr(b.length()-8);
    }
    string t=add(a2,b2);
    while(t.length()<8) t="0"+t;
    if(t.length()>8) return add(add(a1,b1),"1")+t.substr(1);
    return add(a1,b1)+t;
}
 
int main()
{
	ifstream in("./final_version/test.data");
    string a,b,c;
	for (string str; getline(in, str);)
	{
		istringstream sin(str);
		sin >> a >> b >> c;
		add(a,b);
		cout << "Done!" << endl;
	}
    return 0;
}
