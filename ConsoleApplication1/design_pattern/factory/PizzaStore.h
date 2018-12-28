#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>

class Pizza;
class Pizza1;

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
	Pizza * OrderPizza(const std::string & type);
protected:
	CreatedType pizza_created_type;
private:
	virtual Pizza* Create(const std::string & type);
};

class NyStore:public PizzaStore
{
public:
	NyStore(CreatedType pizza_created_type_);
private:
	virtual Pizza* Create(const std::string & type);
};

class ChStore :public PizzaStore
{
public:
	ChStore(CreatedType pizza_created_type_);
private:
	virtual Pizza* Create(const std::string & type);
};

#endif