#include "stdafx.h"
#include "pizza.h"
#include "PizzaStore.h"
#include "pizza1.h"
#include <memory>
#include <assert.h>

#include "factory.h"
#include "abstractFactory.h"

PizzaStore::PizzaStore(PizzaStore::CreatedType pizza_created_type_) 
	:pizza_created_type(pizza_created_type_),
	ff(nullptr),
	pf(nullptr),
	af(nullptr)
{
}

Pizza * PizzaStore::OrderPizza(const std::string & type, int flag)
{
	Pizza *obj = nullptr;

	switch (pizza_created_type)
	{
	case SIMPLE_FACTORY:
		ff = std::make_shared<PizzaSimpleFactory>();
		obj = ff->Create(type);
		break;
	case FACTORY:
		if (type == "Cheese")
		{
			pf = std::make_shared<NyFactory>();
		}
		else if (type == "Beijing")
		{
			pf = std::make_shared<ChFactory>();
		}

		if (pf)
		{
			obj = Create();
		}
		break;
	case ABSTACT_FACTORY:
		if (flag == 0)
		{
			af = std::make_shared<AFactory>();
		}
		else if (flag == 1)
		{
			af = std::make_shared<BFactory>();
		}

		if (af)
		{
			obj = Create(type);
		}

		break;
	default:
		ff = nullptr;
		pf = nullptr;
		af = nullptr;
		break;
	}

	return obj;
}

Pizza * PizzaStore::Create(const std::string & type)
{
	Pizza *obj = nullptr;

	if (type == "Cheese")
	{
		obj = af->CreateCheesePizza();
	}
	else if (type == "Beijing")
	{
		obj = af->CreateBeijingPizza();
	}

	return obj;
}

Pizza * PizzaStore::Create()
{
	return pf->Create();
}
