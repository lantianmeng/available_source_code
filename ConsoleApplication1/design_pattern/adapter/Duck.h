#ifndef DUCK_H
#define DUCK_H

#include <iostream>

//Ñ¼×Ó
class Duck
{
public:
	virtual void quack() = 0; //ßÉßÉ½Ð
	virtual void fly() = 0;   //·ÉÐÐ
};

//ÂÌÍ·Ñ¼
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