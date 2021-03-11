#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H

#include <string>
#include <memory>

class Pizza;
class Pizza1;
class AbstractFactory;
class PizzaFactory;
class PizzaSimpleFactory;

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
	//0: A��ζ
	//1��B��ζ
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