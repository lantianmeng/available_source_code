1. Timer.h 是c++11实现的定时器
测试代码如下：
```
	Timer t;
	t.StartTimer(1000, std::bind(EchoFunc, "hello c++11!"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	std::cout << "try to expire timer!" << std::endl;
	t.Expire();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	//只执行一次定时任务
	//同步
	t.SyncWait(1000, EchoFunc, "hello world!");
	//异步
	t.AsyncWait(1000, EchoFunc, "hello c++11!");

	std::this_thread::sleep_for(std::chrono::seconds(2));
```
