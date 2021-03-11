#ifndef DUCK_H
#define DUCK_H

#include <iostream>

//Ѽ��
class Duck
{
public:
	virtual void quack() = 0; //���ɽ�
	virtual void fly() = 0;   //����
};

//��ͷѼ
class MallardDuck :public Duck
{
public:
	virtual void quack() override
	{
		std::cout << "quack" << std::endl;
	}

	virtual void fly() override
	{
		std::cout << "i'm flying" << std::endl;
	}
};

#endif