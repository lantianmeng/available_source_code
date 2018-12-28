#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>

class Pizza;
class Pizza1;

//������ 
class PizzaStore
{
public:
	//�����ߴ����Ʒ�ķ��� 
	enum CreatedType
	{
		SIMPLE_FACTORY,  //�򵥹���
		FACTORY,         //����  ����Ĳ�Ʒ�Ǵ����ߵ�����ȥ����
		ABSTACT_FACTORY  //���󹤳�
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