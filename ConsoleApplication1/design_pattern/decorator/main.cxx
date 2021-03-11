// decorator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "component.h"
#include "decorator.h"

#include <memory>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	//订一杯浓缩咖啡饮料，不需要调料，获取价格
	//std::shared_ptr<Beverage> pBeverage(new Espresso); //make_shared比new更安全高效
	std::shared_ptr<Beverage> pBeverage = std::make_shared<Espresso>();
	std::cout << pBeverage->getDescription() << ", price:" << pBeverage->cost() << std::endl;

	//订一杯浓缩咖啡饮料，加2份摩卡和1份奶泡，获取价格
	std::shared_ptr<Beverage> pBeverage2 = std::make_shared<Espresso>();
	pBeverage2 = std::make_shared<Mocha>(pBeverage2); //用Mocha装饰
	pBeverage2 = std::make_shared<Mocha>(pBeverage2); //用第2个Mocha装饰
	pBeverage2 = std::make_shared<Whip>(pBeverage2);  //用Whip装饰
	std::cout << pBeverage2->getDescription() << ", price:" << pBeverage2->cost() << std::endl;

	//订一杯混合咖啡饮料，加1份摩卡、1份豆浆和1份奶泡，获取价格
	std::shared_ptr<Beverage> pBeverage3 = std::make_shared<HouseBlend>();
	pBeverage3 = std::make_shared<Soy>(pBeverage3);   //用Soy装饰
	pBeverage3 = std::make_shared<Mocha>(pBeverage3); //用Mocha装饰
	pBeverage3 = std::make_shared<Whip>(pBeverage3);  //用Whip装饰
	std::cout << pBeverage3->getDescription() << ", price:" << pBeverage3->cost() << std::endl;

	//订一杯浓缩咖啡饮料，加1份摩卡,获取价格，并输出其口味特性
	std::shared_ptr<Beverage> pBeverage4 = std::make_shared<Espresso>();
	std::shared_ptr<CondimentDecorator> pDecorator = std::make_shared<Mocha>(pBeverage4); //用Mocha装饰
	std::cout << pDecorator->getDescription() << ", price:" << pDecorator->cost() << std::endl;
	pDecorator->OutputFeatures();

	system("pause");
	return 0;
}

