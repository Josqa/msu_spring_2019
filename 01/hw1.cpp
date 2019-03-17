#include <iostream>
#include <cmath>
#include <vector>
#include "numbers.dat"
using namespace std;

bool is_prime(int x)
{
	if (x == 1) return false;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0) return false;
	}
	return true;
}

void solve(int l, int r)
{
     int cnt = 0;
     for (int i = 0; Data[i] <= r; i++)
     {
         if(Data[i] >= l)
             if (is_prime(Data[i]) == true) cnt++;             
     }
     cout << cnt << endl;
}

int main(int argc, char* argv[])
{
    if (argc - 1 == 0 || (argc - 1) % 2 == 1) return -1;
    for (int i = 1; i < argc; i += 2)
    {
        int v1 = atoi(argv[i]);
        int v2 = atoi(argv[i + 1]);
        solve(v1, v2);
    }
    return 0;
}
