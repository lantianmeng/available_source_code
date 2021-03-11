#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

//�����࣬������ӿ�
//������
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

//Ũ�����ȣ����������
class Espresso :public Beverage
{
public:
	Espresso():Beverage("Espresso"){}
	virtual double cost() override { return 1.99; }

};

//��Ͽ��ȣ����������
class HouseBlend :public Beverage
{
public:
	HouseBlend() :Beverage("House Blend"){}
	virtual double cost() override { return 0.89; }

};

#endif