#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

void helloThread()
{
	cout<< "hello thread" << endl;
}

int Sum(int a, int b)
{
	return a+b;
}

void func(int n)
{
	cout<<"threads on-going"<<endl;
	this_thread::sleep_for(chrono::milliseconds(10));
}
class HelloThread
{
	public:
	static void HelloFunc()//static is  a must
	{
		cout<<"Hello, I am a thread"<<endl;
	}
	void Start()
	{
		thread t1(HelloFunc);
		t1.join();
	}
};

class HelloWorld
{
public:
	void hello(int year)
	{
		cout<<"I'm "<< year<<" years old"<<endl;
	}

};

void addstr(const string& s)
{
	thread_local string str("I'm from ");
	str+=s;
	cout<<str<<endl;
}
int main()
{   
	clock_t start = clock();
	thread t1(helloThread);
	t1.join();

	cout<<"main thread"<<endl;
	thread t2(Sum, 5, 6);
	t2.join();
	HelloThread t3;
	t3.Start();
	HelloWorld obj;
	thread t4(bind(&HelloWorld::hello, obj, 26));
	t4.join();
	cout<<"main thread"<<endl;
	cout<<thread::hardware_concurrency()<<endl;//get the number of cpu core
	thread t5(func, 5);
	thread t6(move(t5));
	t6.join();
	clock_t end = clock();
	cout<<end - start<<" ms"<< endl;
	thread t7(addstr, "t7");
	thread t8(addstr, "t8");
	t7.join();
	t8.join();
	return 0;
}
