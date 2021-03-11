#ifndef FACTORY_H
#define FACTORY_H

#include "pizza.h"

class PizzaSimpleFactory
{
public:
	Pizza* Create(const std::string &type)
	{
		Pizza *obj = nullptr;
		if (type == "Cheese")
		{
			obj = new CheesePizza(2.1, "Simple Cheese", "Cheese Style");
		}
		else if (type == "Beijing")
		{
			obj = new BeijingPizza(2.6, "Simple Beijing", "tianmeng Beijing");
		}

		return obj;
	}
};

class PizzaFactory
{
public:
	virtual Pizza* Create() { return nullptr; }
};

//NyFactory只生产CheesePizza
class NyFactory :public PizzaFactory
{
public:
	virtual Pizza* Create() { return new CheesePizza(1.4, "Ny Cheese", "Ny Cheese Style"); }
};

//// ChFactory只生产BeijingPizza
class ChFactory :public PizzaFactory
{
public:
	virtual Pizza* Create() { return new BeijingPizza(1.2, "Ch Beijing", "Ch gugong Beijing"); }
};
#endif