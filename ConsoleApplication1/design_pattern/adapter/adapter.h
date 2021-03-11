#ifndef ADAPTER
#define ADAPTER

#include <memory>
#include "Duck.h"
#include "Turkey.h"

//用火鸡对象来适配一个鸭子对象
class TurkeyAdapter :public Duck
{
public:
	TurkeyAdapter(std::shared_ptr<Turkey> turkey_obj_) : turkey_obj(turkey_obj_) {}

	virtual void quack() override
	{
		turkey_obj->gobble();
	}

	virtual void fly() override
	{
		//火鸡飞行距离短，不像鸭子可以长距离飞行。所以这里循环5次来模拟鸭子的长途飞行
		for (int i = 0; i < 5; ++i)
		{
			turkey_obj->fly();
		}
	}

private:
	std::shared_ptr<Turkey> turkey_obj;
};
#endif