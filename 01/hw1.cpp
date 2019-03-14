#include <iostream>
#include <cmath>
#include <vector>
#include "numbers.dat"
using namespace std;

bool is_prime(int x)
{
	if (x == 1) return false;
	for (int i = 2;i*i<=x;i++)
	{
		if (x%i == 0) return false;
	}
	return true;
}

void solve(int l, int r)
{
     int cnt = 0;
     for (int i = 0;Data[i]<=r;i++)
     {
         if(Data[i] >= l)
             if (is_prime(Data[i]) == true) cnt++;             
     }
     cout<<cnt<<endl;
}

int main(int argc, char* argv[])
{
    vector<int> test;
    for (int i = 1; i < argc; ++i)
    {
        int v = atoi(argv[i]);
        test.push_back(v);
    }
    if (test.size() == 0 || test.size()%2 == 1) return -1;
    for (size_t i = 0; i<test.size();i+=2)
        solve(test[i], test[i+1]);
    return 0;
}
