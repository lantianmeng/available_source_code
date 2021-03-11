#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

//抽象类，即组件接口
//饮料类
class Beverage
{
public:
	Beverage() { sDescription = "unknown"; }
	explicit Beverage(std::string sDescription_) :sDescription(sDescription_) {}
	std::string & getDescription(){ return sDescription; }

	virtual double cost() = 0;
protected:
	std::string sDescription;
};

//浓缩咖啡，具体的饮料
class Espresso :public Beverage
{
public:
	Espresso():Beverage("Espresso"){}
	virtual double cost() override { return 1.99; }

};

//混合咖啡，具体的饮料
class HouseBlend :public Beverage
{
public:
	HouseBlend() :Beverage("House Blend"){}
	virtual double cost() override { return 0.89; }

};

#endif