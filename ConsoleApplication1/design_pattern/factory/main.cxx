// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "PizzaStore.h"
#include "factory.h"

class Test
{
public:
	void Run()
	{
		std::cout << "test" << std::endl;
	}
};

//使用boost::asio 实现重复定时器
void print(const boost::system::error_code& /*e*/,
	boost::asio::deadline_timer* t, long* interval)
{
	std::cout << boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()) << " Hello, world!\n";
	//推迟定时器的终止时间。通过在原先的终止时间上增加延时，我们可以确保定时器不会在处理回调函数所需时间内到期。
	t->expires_at(t->expires_at() + boost::posix_time::seconds(*interval));
	t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, interval));
}

void timer_start(long interval)
{
	int count = 1;
	//boost 异步定时器
	boost::asio::io_service io;
	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(interval));
	timer.async_wait(boost::bind(print, boost::asio::placeholders::error, &timer, &interval));
	io.run();
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "----------simple factory----------" << std::endl;
	PizzaStore ps(PizzaStore::CreatedType::SIMPLE_FACTORY);
	std::shared_ptr<Pizza> my_pizza(ps.OrderPizza("Beijing"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	my_pizza.reset(ps.OrderPizza("Cheese"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	std::cout << "---------- factory----------" << std::endl;
	std::shared_ptr<PizzaStore>  ss1(new NyStore(PizzaStore::CreatedType::FACTORY));
	my_pizza.reset(ss1->OrderPizza("Beijing"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	my_pizza.reset(ss1->OrderPizza("Cheese"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	ss1.reset(new ChStore(PizzaStore::CreatedType::FACTORY));
	my_pizza.reset(ss1->OrderPizza("Beijing"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	my_pizza.reset(ss1->OrderPizza("Cheese"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	std::cout << "----------abstract factory----------" << std::endl;
	ss1.reset(new NyStore(PizzaStore::CreatedType::ABSTACT_FACTORY));
	my_pizza.reset(ss1->OrderPizza("Beijing"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	my_pizza.reset(ss1->OrderPizza("Cheese"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	ss1.reset(new ChStore(PizzaStore::CreatedType::ABSTACT_FACTORY));
	my_pizza.reset(ss1->OrderPizza("Beijing"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	my_pizza.reset(ss1->OrderPizza("Cheese"));
	assert(my_pizza.get() != nullptr);
	my_pizza->print();

	Test xx;
	std::thread tt(&Test::Run, &xx);

	//定时器线程(程序退出前，线程join)，避免程序阻塞
	std::thread timer_thread(timer_start, 60);

	tt.join();
	timer_thread.join();

	system("pause");
	return 0;
}

