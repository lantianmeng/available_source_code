// learn_boost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Config.h"
#include "Singleton.h"
#include "websocket_server.h"
#include <windows.h>

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
private:
	std::string name;
	int age;
};

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

	//捕获退出信号（ctrl+c）
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true)) 
	{
		LOG_ERROR << "SetConsoleCtrlHandler fail";
		//nRetCode = 1;
		//break;
		return 1;
	}

	

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

	Server websocket_serv(19201);
	websocket_serv.start();

	system("pause");
	while (!g_bExit)
	{
		Sleep(500);
	}

    return 0;
}

