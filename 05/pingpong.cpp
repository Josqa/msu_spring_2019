#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;


mutex m;
condition_variable cv;

const int N = 500000;
int i = 0;

void ping()
{
	unique_lock<mutex> lock(m);
	for(; i < N; i++)
	{
		while (i % 2)
			cv.wait(lock);
		cout << "ping" << endl;
		cv.notify_one();
	}
}


void pong()
{
	unique_lock<mutex> lock(m);
	for(; i < N; i++)
	{
		while (!(i % 2))
			cv.wait(lock);
		cout << "pong" << endl;
		cv.notify_one();
	}
}

int main()
{
	thread t1(ping), t2(pong);
	t1.join();
	t2.join();
	return 0;
}
