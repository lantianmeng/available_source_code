#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>
#include <memory>

class Pizza;
class Pizza1;
class AbstractFactory;
class PizzaFactory;
class PizzaSimpleFactory;

//创造者 
class PizzaStore
{
public:
	//创造者创造产品的方法 
	enum CreatedType
	{
		SIMPLE_FACTORY,  //简单工厂
		FACTORY,         //工厂  具体的产品是创造者的子类去创建
		ABSTACT_FACTORY  //抽象工厂
	};

	PizzaStore(PizzaStore::CreatedType pizza_created_type_);
	//0: A口味
	//1：B口味
	Pizza * OrderPizza(const std::string & type, int flag = 0);
protected:
	Pizza * Create(const std::string & type);
	Pizza * Create();
protected:
	CreatedType pizza_created_type;

	std::shared_ptr<PizzaSimpleFactory> ff;
	std::shared_ptr<PizzaFactory>  pf;
	std::shared_ptr<AbstractFactory> af;
};

#endif