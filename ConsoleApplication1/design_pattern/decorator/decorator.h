#ifndef DECORATOR_H
#define DECORATOR_H

#include <memory>
#include <iostream>

//װ���ߣ��̳�component��Ŀ�����뱻װ���߱���ͬһ����
//������
class CondimentDecorator:public Beverage
{
public:
	//setComponent(std::shared_ptr<Beverage> decorated_obj_) { decorated_obj = decorated_obj_; }
	CondimentDecorator(std::shared_ptr<Beverage> decorated_obj_) { decorated_obj = decorated_obj_; }

	//�ı�װ�������з�����ִ�У�����������д
	//virtual double cost() override{}

	//�������� ��ӿ�ζ����
	virtual void OutputFeatures() = 0;
protected:
	std::shared_ptr<Beverage> decorated_obj;//��װ�ζ��� ��װ������ͨ����ϵķ�ʽ
};

//�����װ����
//Ħ��
class Mocha :public CondimentDecorator
{
public:
	Mocha(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_){ sDescription = decorated_obj->getDescription() + ", Mocha"; }

	//ί�и���װ���ߣ����ϣ���ȡ��Ǯ+����Ħ���ļ�Ǯ
	virtual double cost() override{ return decorated_obj->cost() + 0.2; }

	virtual void OutputFeatures() override{ std::cout << "Mocha is very nice" << std::endl; }

};

//�����װ����
//����
class Soy :public CondimentDecorator
{
public:
	Soy(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_){ sDescription = decorated_obj->getDescription() + ", Soy"; }

	//ί�и���װ���ߣ����ϣ���ȡ��Ǯ+���϶����ļ�Ǯ
	virtual double cost() override{ return decorated_obj->cost() + 0.5; }

	virtual void OutputFeatures() override{ std::cout << "Soy is very sweet" << std::endl; }
};

//�����װ����
//����
class Whip :public CondimentDecorator
{
public:
	Whip(std::shared_ptr<Beverage> decorated_obj_) :CondimentDecorator(decorated_obj_) { sDescription = decorated_obj->getDescription() + ", Whip"; }

	//ί�и���װ���ߣ����ϣ���ȡ��Ǯ+�������ݵļ�Ǯ
	virtual double cost() override{ return decorated_obj->cost() + 1.2; }

	virtual void OutputFeatures() override{ std::cout << "Whip is very fresh" << std::endl; }
};
#endif