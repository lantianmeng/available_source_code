
#include <future>

class Test_PackagedTask
{
public:
	Test_PackagedTask()
	{
		t_i = 0;
		//tsk(std::bind(&Test_PackagedTask::task3, this));
	}

	void task3()//模拟接收tems消息
	{
		t_i += 2;
		std::cout << "task 3 " << t_i << std::endl;

		pp_t.set_value(t_i);
	}


	void task4()
{
	std::cout << "task 4" << std::endl;

	//std::this_thread::sleep_for(std::chrono::seconds(5));
	std::this_thread::sleep_for(std::chrono::seconds(8));

	task3();
}

void task2()
{
	++t_i;
	std::cout << "task 2 " << t_i << std::endl;

}

void task1()//模拟接收plc信号
{
	std::cout << "task 1" << std::endl;

	task2(); //模拟给tems发消息

	//模拟等待tems回消息
	std::future<int> fu1 = pp_t.get_future();
	std::chrono::milliseconds span(6000);
	std::future_status status;
	do
	{
		status = fu1.wait_for(span);
	} while (status == std::future_status::deferred);

	if (status == std::future_status::timeout)
	{
		std::cout << "timeout " << t_i << std::endl;
	}
	else if (status == std::future_status::ready)
	{
		std::cout << "ready " << t_i << std::endl;
	}
}

private:
	int t_i = 0;
	//std::packaged_task<void()> tsk;

	std::promise<int> pp_t;
	
};