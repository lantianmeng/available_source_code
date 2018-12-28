#include "stdafx.h"
#include "pizza.h"
#include "PizzaStore.h"
#include "pizza1.h"
#include <memory>
#include <assert.h>

#include "factory.h"

PizzaStore::PizzaStore(PizzaStore::CreatedType pizza_created_type_) :pizza_created_type(pizza_created_type_)
{

}

Pizza * PizzaStore::OrderPizza(const std::string & type)
{
	Pizza *obj = nullptr;
	switch (pizza_created_type)
	{
	case SIMPLE_FACTORY:
		PizzaSimpleFactory ff;
		obj = ff.Create(type);
		break;
	case FACTORY:
	case ABSTACT_FACTORY:
		obj = Create(type);
		break;
	default:
		break;
	}
	return obj;
}

Pizza* PizzaStore::Create(const std::string & type)
{
	return nullptr;
}

NyStore::NyStore(CreatedType pizza_created_type_) :PizzaStore(pizza_created_type_)
{

}

Pizza* NyStore::Create(const std::string & type)
{
	Pizza* obj = nullptr;
	if (type == "Cheese")
	{
		obj = new CheesePizza(1.4, "Ny Cheese", "Ny Cheese Style");
	}
	else if (type == "Beijing")
	{
		obj = new BeijingPizza(1.1, "Ny Beijing", "Ny gugong Beijing");
	}

	if (obj != nullptr && pizza_created_type == PizzaStore::ABSTACT_FACTORY)
	{
		obj->SetFactory(new ATiaoLiaoFactory);
		obj->PrepareTiaoLiao();
	}
	return obj;
}

ChStore::ChStore(CreatedType pizza_created_type_) : PizzaStore(pizza_created_type_)
{

}

Pizza* ChStore::Create(const std::string & type)
{
	Pizza* obj = nullptr;
	if (type == "Cheese")
	{
		obj = new CheesePizza(1.5, "Ch Cheese", "Ny Cheese Style");
	}
	else if (type == "Beijing")
	{
		obj = new BeijingPizza(1.2, "Ch Beijing", "Ch gugong Beijing");
	}

	if (obj != nullptr && pizza_created_type == PizzaStore::ABSTACT_FACTORY)
	{
		obj->SetFactory(new BTiaoLiaoFactory);
		obj->PrepareTiaoLiao();
	}

	return obj;
}