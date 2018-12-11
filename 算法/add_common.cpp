#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

#define MAXN 1000

int a[MAXN],b[MAXN];

int main(int argc, const char * argv[])
{
    string str1,str2;//保存输入
    long int len1,len2;
    long int i,j,k;
    int up;
	ifstream in("./final_version/test.data");
	for (string str; getline(in, str);)
	{
		istringstream sin(str);
		sin >> str1 >> str2;
    /*初始化各量*/
    len1 = str1.length();
    len2 = str2.length();
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    
    /*注意，必须倒着保存数据*/
    for (i = len1 - 1, k = 0; i != -1; -- i)
    {
        a[k] = str1[i] - '0';
        k++;
    }
    for (j = len2 - 1, k = 0; j != -1; -- j)
    {
        b[k] = str2[j] - '0';
        k++;
    }
    for (i = 0, up = 0; i < MAXN; ++ i)
    {
        a[i] = a[i] + b[i] + up;
        up = a[i] / 10;
        a[i] %= 10;
    }
    for (i = MAXN - 1; i != -1; -- i)
    {
        if (a[i])
        {
            break;
        }
    }
    //for (k = i; k != -1; --k)
    //{
        //cout<<a[k];
    //}
	}
    
    
    return 0;
}
