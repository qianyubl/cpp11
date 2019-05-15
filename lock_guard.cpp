#include<iostream>
#include<thread>
#include<mutex>
int data = 1;
std::mutex mx;
void increment()
{
	std::lock_guard<std::mutex> k1(mx);
	std::cout<< ++data << std::endl;
}

int main()
{
	std::thread t1(increment);
	std::thread t2(increment);

	t1.join();
	t2.join();
	return 0;
}
