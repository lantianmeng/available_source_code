#ifndef ADAPTER
#define ADAPTER

#include <memory>
#include "Duck.h"
#include "Turkey.h"

//�û𼦶���������һ��Ѽ�Ӷ���
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
		//�𼦷��о���̣�����Ѽ�ӿ��Գ�������С���������ѭ��5����ģ��Ѽ�ӵĳ�;����
		for (int i = 0; i < 5; ++i)
		{
			turkey_obj->fly();
		}
	}

private:
	std::shared_ptr<Turkey> turkey_obj;
};
#endif