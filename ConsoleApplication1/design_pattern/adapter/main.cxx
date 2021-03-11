// adapter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "adapter.h"

#include "test1.h"

void testDuck(std::shared_ptr<Duck> duck)
{
	duck->quack();
	duck->fly();
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::shared_ptr<MallardDuck> duck = std::make_shared<MallardDuck>();
	std::shared_ptr<WildTurkey> turkey = std::make_shared<WildTurkey>();

	std::cout << "==The Turkey==" << std::endl;
	turkey->gobble();
	turkey->fly();

	std::cout << "==The Duck==" << std::endl;
	duck->quack();
	duck->fly();

	std::cout << "==The adapter==" << std::endl;
	std::shared_ptr<Duck> turkey_adapter = std::make_shared<TurkeyAdapter>(turkey);
	testDuck(turkey_adapter);

	std::cout << "////////////////////////" << std::endl;
	std::shared_ptr<A>  oo = std::make_shared<A>();
	std::shared_ptr<B> bb = std::make_shared<B>();
	unsigned char udata[1024] = { 0 };
	char data[1024] = { 0 };

	oo->Read(udata, 1024);
	bb->Read(data, 1024);

	std::cout << std::string((char*)udata).c_str() << " " << std::string(data).c_str() << std::endl;

	memset(data, 0, 1024);
	std::shared_ptr<B> obj = std::make_shared<A_adapter>(oo);
	obj->Read(data, 1024);

	std::cout << std::string(data).c_str() << std::endl;
	system("pause");
	return 0;
}

