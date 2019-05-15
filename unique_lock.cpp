#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<functional>
class A
{
	public:
		void inMsgsUsingTryLock()
		{
			for(int i=0;i<10;i++)
			{
			//	std::cout<<__FUNCTION__<<std::endl;
				std::unique_lock<std::mutex> l_guard(m_mutex, std::try_to_lock);//for try_to_lock,the mutex no need to lock   
				if(l_guard.owns_lock())
			   // if(l_guard.try_lock())//error
					m_msgs.push_back(i);
				else
					std::cout<< "did not get the lock"<<std::endl;
			}
		}
		void inMsgsUsingDefferdLock()
		{
			for(int i=10;i<20;i++)
			{
				std::unique_lock<std::mutex> l_guard(m_mutex, std::defer_lock);//for defer_lock,the mutex must not be locked   
			//	l_guard.lock();
				if(l_guard.try_lock())
				m_msgs.push_back(i);
				else
					std::cout<<"did not get lock"<<std::endl;
			//	l_guard.unlock();
			}
		}
		void outMsgsUsingAdoptLock()
		{
			for(int i = 0; i<20;i++)
			{
				m_mutex.lock();//for adopt_lock, mutex must be locked
				std::unique_lock<std::mutex> l_guard(m_mutex, std::adopt_lock);
				std::mutex * ptr = l_guard.release();//using release to get the pointr of m_mutex
				if(!m_msgs.empty())
				{
					std::cout<< m_msgs.front()<<std::endl;
					m_msgs.pop_front();
				}
				ptr->unlock();//if get the mutex, we should unlock the mutex by hand
			}		
		}
	private:
		std::mutex m_mutex;
		std::list<int> m_msgs;
};
int main()
{
	A obj;
	std::thread inThread1(std::bind(&A::inMsgsUsingTryLock, &obj));
	inThread1.join();
	std::thread inThread2(std::bind(&A::inMsgsUsingDefferdLock, &obj));
	inThread2.join();
	std::thread outThread(std::bind(&A::outMsgsUsingAdoptLock, &obj));

//	inThread1.join();// the oder will be affected
//	inThread2.join();
	outThread.join();
	return 0;
}
