#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include "pizza1.h"
#include <memory>

class AbstractFactory
{
public:
	virtual CheesePizza* CreateCheesePizza() = 0;
	virtual BeijingPizza* CreateBeijingPizza() = 0;
};

class AFactory :public AbstractFactory
{
public:
	virtual CheesePizza* CreateCheesePizza()
	{ 
		CheesePizza* cc = new CheesePizza(3.1, "Cheese", "a abstract cheese");
		cc->SetTiaoLiao("AZuoLiao", "AMianFen");
		return cc;
	}
	virtual BeijingPizza* CreateBeijingPizza()
	{
		BeijingPizza* cc = new BeijingPizza(3.2, "Beijing", "a abstract beijing");
		cc->SetTiaoLiao("AZuoLiao", "AMianFen");
		return cc;
	}
};

class BFactory :public AbstractFactory
{
public:
	virtual CheesePizza* CreateCheesePizza()
	{
		CheesePizza* cc = new CheesePizza(3.8, "Cheese", "b abstract cheese");
		cc->SetTiaoLiao("BZuoLiao", "BMianFen");
		return cc;
	}
	virtual BeijingPizza* CreateBeijingPizza()
	{
		BeijingPizza* cc = new BeijingPizza(3.9, "Beijing", "b abstract beijing");
		cc->SetTiaoLiao("BZuoLiao", "BMianFen");
		return cc;
	}
};

#endif