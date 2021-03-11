// decorator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "component.h"
#include "decorator.h"

#include <memory>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	//��һ��Ũ���������ϣ�����Ҫ���ϣ���ȡ�۸�
	//std::shared_ptr<Beverage> pBeverage(new Espresso); //make_shared��new����ȫ��Ч
	std::shared_ptr<Beverage> pBeverage = std::make_shared<Espresso>();
	std::cout << pBeverage->getDescription() << ", price:" << pBeverage->cost() << std::endl;

	//��һ��Ũ���������ϣ���2��Ħ����1�����ݣ���ȡ�۸�
	std::shared_ptr<Beverage> pBeverage2 = std::make_shared<Espresso>();
	pBeverage2 = std::make_shared<Mocha>(pBeverage2); //��Mochaװ��
	pBeverage2 = std::make_shared<Mocha>(pBeverage2); //�õ�2��Mochaװ��
	pBeverage2 = std::make_shared<Whip>(pBeverage2);  //��Whipװ��
	std::cout << pBeverage2->getDescription() << ", price:" << pBeverage2->cost() << std::endl;

	//��һ����Ͽ������ϣ���1��Ħ����1�ݶ�����1�����ݣ���ȡ�۸�
	std::shared_ptr<Beverage> pBeverage3 = std::make_shared<HouseBlend>();
	pBeverage3 = std::make_shared<Soy>(pBeverage3);   //��Soyװ��
	pBeverage3 = std::make_shared<Mocha>(pBeverage3); //��Mochaװ��
	pBeverage3 = std::make_shared<Whip>(pBeverage3);  //��Whipװ��
	std::cout << pBeverage3->getDescription() << ", price:" << pBeverage3->cost() << std::endl;

	//��һ��Ũ���������ϣ���1��Ħ��,��ȡ�۸񣬲�������ζ����
	std::shared_ptr<Beverage> pBeverage4 = std::make_shared<Espresso>();
	std::shared_ptr<CondimentDecorator> pDecorator = std::make_shared<Mocha>(pBeverage4); //��Mochaװ��
	std::cout << pDecorator->getDescription() << ", price:" << pDecorator->cost() << std::endl;
	pDecorator->OutputFeatures();

	system("pause");
	return 0;
}

