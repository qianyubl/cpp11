#include<iostream>
#include<thread>
class A
{
	public:
		A()
		{
			std::cout<< std::this_thread::get_id() <<" "<<__FUNCTION__<< "( "<<(void*)this<<" )"<< std::endl;
		}
		~A()
		{

			std::cout<< std::this_thread::get_id() <<" "<<__FUNCTION__<< "( "<<(void*)this<<" )"<< std::endl;
		}
		void dosth(){}
};
thread_local A a;
int main()
{
	a.dosth();
	std::thread t1([](){
	std::cout<< "Thread "<<std::this_thread::get_id() << " entered!"<< std::endl;
	a.dosth();
	});
	t1.join();
	return 0;
}
