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
	virtual Pizza* Create();
};

class NyStylePizzaFactory:public PizzaFactory
{
	virtual Pizza* Create();
};

class BeijingPizzaFactory :public PizzaFactory
{
	virtual Pizza* Create();
};

#endif