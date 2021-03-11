#ifndef DECORATOR_H
#define DECORATOR_H

#include <memory>
#include <iostream>

//装饰者，继承component，目的是与被装饰者保持同一类型
//调料类
class CondimentDecorator:public Beverage
{
public:
	//setComponent(std::shared_ptr<Beverage> decorated_obj_) { decorated_obj = decorated_obj_; }
	CondimentDecorator(std::shared_ptr<Beverage> decorated_obj_) { decorated_obj = decorated_obj_; }

	//改变装饰者已有方法的执行，在子类中重写
	//virtual double cost() override{}

	//新增方法 添加口味特性
	virtual void OutputFeatures() = 0;
protected:
	std::shared_ptr<Beverage> decorated_obj;//被装饰对象， 与装饰者是通过组合的方式
};

//具体的装饰者
//摩卡
class Mocha :public CondimentDecorator
{
public:
	Mocha(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_){ sDescription = decorated_obj->getDescription() + ", Mocha"; }

	//委托给被装饰者（饮料）获取价钱+调料摩卡的价钱
	virtual double cost() override{ return decorated_obj->cost() + 0.2; }

	virtual void OutputFeatures() override{ std::cout << "Mocha is very nice" << std::endl; }

};

//具体的装饰者
//豆浆
class Soy :public CondimentDecorator
{
public:
	Soy(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_){ sDescription = decorated_obj->getDescription() + ", Soy"; }

	//委托给被装饰者（饮料）获取价钱+调料豆浆的价钱
	virtual double cost() override{ return decorated_obj->cost() + 0.5; }

	virtual void OutputFeatures() override{ std::cout << "Soy is very sweet" << std::endl; }
};

//具体的装饰者
//奶泡
class Whip :public CondimentDecorator
{
public:
	Whip(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_) { sDescription = decorated_obj->getDescription() + ", Whip"; }

	//委托给被装饰者（饮料）获取价钱+调料奶泡的价钱
	virtual double cost() override{ return decorated_obj->cost() + 1.2; }

	virtual void OutputFeatures() override{ std::cout << "Whip is very fresh" << std::endl; }
};
#endif