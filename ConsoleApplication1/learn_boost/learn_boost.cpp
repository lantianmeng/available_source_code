// learn_boost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Config.h"
#include "Singleton.h"

using namespace LOG;
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

	system("pause");

    return 0;
}

