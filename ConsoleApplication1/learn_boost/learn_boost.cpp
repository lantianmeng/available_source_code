// learn_boost.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Config.h"
#include "Singleton.h"
#include "websocket_server.h"
#include <windows.h>
#include <boost/asio.hpp>

#include "timer.h"

using namespace LOG;

bool g_bExit = false;

void clear()
{
	//Singleton<Config>::DestroyInstance();
	//Singleton<CMT4Manager>::DestroyInstance();

	//TerminateThread(hTimeThread, 0);
	//hTimeThread = NULL;
}

bool ctrlhandler(DWORD fdwctrltype)
{
	switch (fdwctrltype)
	{
		// handle the ctrl-c signal.
	case CTRL_C_EVENT:
		// ctrl-close: confirm that the user wants to exit.
	case CTRL_CLOSE_EVENT:
		clear();
		g_bExit = true;
		return(true);
		// pass other signals to the next handler.
	case CTRL_BREAK_EVENT:
		printf("ctrl-break event\n\n");
		return false;
	case CTRL_LOGOFF_EVENT:
		printf("ctrl-logoff event\n\n");
		return false;
	case CTRL_SHUTDOWN_EVENT:
		printf("ctrl-shutdown event\n\n");
		return false;
	default:
		return false;
	}
}

void test_log()
{
	BOOST_LOG_SEV(my_logger::get(), error) << "An error severity message";
}

class Student
{
public:
	Student(const std::string & name_, int age_):name(name_), age(age_) {}
	void Print() { std::cout << name << " " << age << std::endl; }

	void print_t(const boost::system::error_code& /*e*/,
		boost::asio::deadline_timer* t, int* count)
	{
		std::cout << "Hello, world!\n";
		//�Ƴٶ�ʱ������ֹʱ�䡣ͨ����ԭ�ȵ���ֹʱ����������ʱ�����ǿ���ȷ����ʱ�������ڴ���ص���������ʱ���ڵ��ڡ�
		t->expires_at(t->expires_at() + boost::posix_time::seconds(60));
		t->async_wait(boost::bind(&Student::print_t, this, boost::asio::placeholders::error, t, count));
	}

private:
	std::string name;
	int age;
};

//void print(const boost::system::error_code& /*e*/)
//{
//	LOG_INFO << "timer";
//	std::cout << "Hello, world!\n";
//}

//ʹ��boost::asio ʵ���ظ���ʱ��
void print(const boost::system::error_code& /*e*/,
	boost::asio::deadline_timer* t, long* interval)
{
	std::cout << "Hello, world!\n";
	//�Ƴٶ�ʱ������ֹʱ�䡣ͨ����ԭ�ȵ���ֹʱ����������ʱ�����ǿ���ȷ����ʱ�������ڴ���ص���������ʱ���ڵ��ڡ�
	t->expires_at(t->expires_at() + boost::posix_time::seconds(*interval));
	t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, interval));
}

void timer_start(long interval)
{
	int count = 1;
	//boost �첽��ʱ��
	boost::asio::io_service io;
	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(interval));
	timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &interval));
	io.run();
}

void test_timer()
{
	std::cout << "Timer thread id: " << std::this_thread::get_id() << std::endl;
}

int main()
{
	Singleton<Student>::Instance("Alan.Yan", 33)->Print();

	if (!Singleton<Config>::Instance()->InitConfig("CallbackServer.ini"))
	{
		std::cout << "error" << std::endl;
		return -1;
	}
	std::cout << Singleton<Config>::Instance()->GetLogLevel() << std::endl;

	InitLog(Singleton<Config>::Instance()->GetLogLevel());

	//�����˳��źţ�ctrl+c��
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true)) 
	{
		LOG_ERROR << "SetConsoleCtrlHandler fail";
		//nRetCode = 1;
		//break;
		return 1;
	}

	//boost �첽��ʱ��
	//boost::asio::io_service io;
	//boost::asio::deadline_timer timer(io, boost::posix_time::seconds(60));
	//
	//Student tt("Alan.Yan", 22);
	//
	//int count = 1;
	////timer.async_wait(&print);
	////timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &count));
	//timer.async_wait(boost::bind(&Student::print_t, &tt, boost::asio::placeholders::error, &timer, &count));
	//io.run();

	//��ʱ���߳�(�����˳�ǰ���߳�join)�������������
	std::thread timer_thread(timer_start, 60);

	std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

	ATimer<boost::posix_time::minutes> t0;
	t0.setSingleShot(true);// ���ε���
	t0.bind(test_timer);
	t0.start(1);// һ����֮�����

	ATimer<> t;//Ĭ��ʹ�ú��붨ʱ��
	t.bind(test_timer);
	t.bind([] { std::cout << "Hello C++" << std::endl; });
	t.start(1000);//ÿ1000ms����һ��

	//BOOST_LOG_FUNCTION();
	BOOST_LOG_SEV(my_logger::get(), trace) << "A trace severity message";
	BOOST_LOG_SEV(my_logger::get(), debug) << "A debug severity message";
	BOOST_LOG_SEV(my_logger::get(), info) << "An informational severity message";
	BOOST_LOG_SEV(my_logger::get(), warning) << "A warning severity message";
	//BOOST_LOG_SEV(my_logger::get(), error) << "An error severity message";
	test_log();
	BOOST_LOG_SEV(my_logger::get(), fatal) << "A fatal severity message";

	LOG_INFO << "An informational severity message";
	LOG_WARNING << "A warning severity message";
	LOG_ERROR << "An error severity message"
		<< "test multi lines";
	LOG_FATAL<< "A fatal severity message";

	//Server websocket_serv(19201);
	//websocket_serv.start();

	timer_thread.join();

	system("pause");
	while (!g_bExit)
	{
		Sleep(500);
	}

    return 0;
}

